// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

#ifndef INCLUDED_protocols_mpi_refinement_utils_hh
#define INCLUDED_protocols_mpi_refinement_utils_hh

#include <core/types.hh>
#include <core/pose/Pose.fwd.hh>
#include <core/scoring/ScoreFunction.fwd.hh>

#include <core/io/silent/SilentStruct.fwd.hh>
#include <protocols/wum/SilentStructStore.fwd.hh>
#include <core/kinematics/MoveMap.fwd.hh>

#include <protocols/minimization_packing/PackRotamersMover.fwd.hh>




#include <ObjexxFCL/FArray2D.fwd.hh>


#include <utility/vector1.hh>

#include <map> // AUTO IWYU For map

namespace protocols {
namespace mpi_refinement {

utility::vector1< std::pair< core::Size, core::Size > >
get_loop_info_full( core::io::silent::SilentStructOP ss,
	utility::vector1< bool > &is_terminus,
	std::string const & mode = "loop"
);
void
get_loop_info( core::io::silent::SilentStructOP ss,
	core::Size &res1,
	core::Size &res2,
	bool &is_terminus );

void
constrain_residue( core::pose::Pose &pose,
	core::Size const resno,
	utility::vector1< core::Size > const exclres,
	std::string const & cst_type = "atompair",
	core::Real const stdev = 0.5
);

//void
//setup_cutpoints( core::pose::Pose &pose,
//   utility::vector1< core::Size > cutpoints );

utility::vector1< core::Size >
get_touched_res( core::pose::Pose const pose,
	utility::vector1< core::Size > const loopres,
	core::Real dist_cut = 6.0
);

protocols::minimization_packing::PackRotamersMoverOP
setup_packer( core::pose::Pose const &pose,
	core::kinematics::MoveMap const mm,
	core::scoring::ScoreFunctionCOP sfxn );

void
add_movemap_from_loopres( core::kinematics::MoveMap &mm,
	core::pose::Pose const &pose,
	utility::vector1< core::Size > const loopres,
	bool const nonideal );

// This will only work in Cartesian space because
// local loophash doesn't care about ideal geometry
void ramp_minpack_loop( core::pose::Pose &pose,
	utility::vector1< core::Size > const loopres,
	core::scoring::ScoreFunctionCOP sfxn,
	bool const nonideal = true,
	bool const ramp = true,
	bool const efficient = false,
	bool const envmin = false
);

void ramp_minpack_pose( core::pose::Pose &pose,
	core::scoring::ScoreFunctionCOP sfxn,
	bool const nonideal = true,
	bool const ramp = true
);

void add_poseinfo_to_ss( core::io::silent::SilentStruct &ss,
	core::pose::Pose const &ref_pose,
	std::string const & suffix );

core::Real Zscore_to_library( core::Real const score,
	core::Real const mean,
	core::Real const stdev,
	core::Real const maxval = 0.0,
	core::Real const minval = -3.0
);

utility::vector1< core::Size >
loopstring_to_loopvector( std::string const & loopstr,
	core::Size const ext = 0);

utility::vector1< utility::vector1< core::Size > >
loopstring_to_loopregions( std::string const & loopstr );

void
copy_pose_crd( core::pose::Pose const pose_frame,
	core::pose::Pose &pose_work,
	utility::vector1< utility::vector1< core::Size > > const loopregions );

void mean_and_stdev( utility::vector1< core::Real > values,
	core::Real const frac,
	core::Real &shave_cut,
	core::Real &mean,
	core::Real &stdev );

void
superimpose_all( core::io::silent::SilentStructCOP ss_ref,
	protocols::wum::SilentStructStore &structs,
	utility::vector1< std::string > const columns_copy = utility::vector1< std::string >( 0 )
);

core::Real
distance( core::io::silent::SilentStructOP ss1,
	core::io::silent::SilentStructOP ss2,
	std::string const & similarity_measure,
	bool const superimpose );

core::Real CA_Sscore( core::io::silent::SilentStructOP ss1,
	core::io::silent::SilentStructOP ss2,
	core::Real &rmsd,
	utility::vector1< core::Size > const & loopres,
	bool const superimpose = true,
	core::Real const dbase = 1.0
);

core::Real CA_Sscore( core::io::silent::SilentStructOP ss1,
	core::io::silent::SilentStructOP ss2,
	core::Real &rmsd,
	bool const superimpose = true,
	core::Real const dbase = 1.0
);

core::Real
distance( core::io::silent::SilentStructOP ss1,
	core::io::silent::SilentStructOP ss2,
	std::string const & similarity_measure,
	bool const superimpose );

void
add_init_dev_penalty( core::io::silent::SilentStructOP ss,
	ObjexxFCL::FArray2D< core::Real > const init_xyz,
	std::string const & mode = "absolute",
	core::Real const iha_cut = -1.0,
	core::Real const iha_penalty_slope = 0.004
);

void
add_init_dev_penalty( core::io::silent::SilentStructOP ss,
	core::pose::Pose const pose0,
	std::string const & mode = "absolute",
	core::Real const iha_cut = -1.0,
	core::Real const iha_penalty_slope = 0.004
);

void
add_init_dev_penalty( protocols::wum::SilentStructStore &structs,
	core::pose::Pose const pose0,
	std::string const & mode = "absolute",
	core::Real const iha_cut = -1.0,
	core::Real const iha_penalty_slope = 0.004
);

// ss2 format parser
std::map< core::Size, utility::vector1< core::Real > >
read_ss2( std::string ssfile );

} // namespace mpi_refinement
} // namespace

#endif
