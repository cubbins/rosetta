// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file   core/scoring/methods/RG_Energy_RNA.hh
/// @brief  Radius of gyration score for RNA, to match Rosetta++
/// @author Rhiju Das


#ifndef INCLUDED_core_scoring_rna_RG_Energy_RNA_hh
#define INCLUDED_core_scoring_rna_RG_Energy_RNA_hh


// Package headers
#include <core/scoring/methods/WholeStructureEnergy.hh>

#include <core/scoring/ScoreFunction.fwd.hh>


// Project headers
#include <core/pose/Pose.fwd.hh>
#include <core/types.hh>
#include <numeric/xyzVector.hh>

#include <utility/vector1.hh>


// Utility headers


namespace core {
namespace energy_methods {


class RG_Energy_RNA : public core::scoring::methods::WholeStructureEnergy  {
public:
	typedef core::scoring::methods::WholeStructureEnergy  parent;

public:

	/// @brief Defines a center of mass based RG calculation that is O(n) rather
	/// than O(n^2). Not tested yet.
	RG_Energy_RNA();

	/// clone
	core::scoring::methods::EnergyMethodOP
	clone() const override;

	/////////////////////////////////////////////////////////////////////////////
	// scoring
	/////////////////////////////////////////////////////////////////////////////

	void
	setup_for_scoring( pose::Pose & pose, core::scoring::ScoreFunction const & ) const override;

	void
	setup_for_derivatives( pose::Pose & pose, core::scoring::ScoreFunction const & ) const override;

	void
	finalize_total_energy(
		pose::Pose & pose,
		core::scoring::ScoreFunction const &,
		core::scoring::EnergyMap & totals
	) const override;

	/////////////////////////////////
	void
	eval_atom_derivative(
		id::AtomID const & atom_id,
		pose::Pose const & pose,
		kinematics::DomainMap const & domain_map,
		core::scoring::ScoreFunction const &,
		core::scoring::EnergyMap const & weights,
		Vector & F1,
		Vector & F2 ) const override;

	void
	indicate_required_context_graphs(
		utility::vector1< bool > & /*context_graphs_required*/
	) const override {}

private:

	mutable core::Vector center_of_mass_;
	mutable core::Real rg_;
	core::Size version() const override;

};


} //scoring
} //core

#endif // INCLUDED_core_energy_methods_RG_Energy_RNA_HH
