// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file   core/scoring/methods/RNA_FA_ElecEnergy.hh
/// @brief  Electrostatics for RNA
/// @author Joseph Yesselman


#ifndef INCLUDED_core_scoring_elec_RNA_FA_ElecEnergy_hh
#define INCLUDED_core_scoring_elec_RNA_FA_ElecEnergy_hh

/// Unit Headers
#include <core/energy_methods/RNA_FA_ElecEnergy.fwd.hh>

/// Package Headers
#include <core/scoring/elec/FA_ElecEnergy.hh>

#include <core/scoring/ScoreFunction.fwd.hh>

#include <core/scoring/methods/EnergyMethod.fwd.hh>
#include <core/scoring/methods/EnergyMethodOptions.fwd.hh>

#include <core/scoring/MinimizationData.fwd.hh>

#include <ObjexxFCL/FArray2D.fwd.hh>

#include <utility/vector1.hh>


enum RNAAtomType { PHOSPHATE=1, SUGAR=2, BASE=3 };


namespace core {
namespace energy_methods {


///
class RNA_FA_ElecEnergy : public core::scoring::elec::FA_ElecEnergy  {
public:
	typedef FA_ElecEnergy parent;
	typedef core::scoring::methods::ContextIndependentTwoBodyEnergy grandparent;

public:


	RNA_FA_ElecEnergy( core::scoring::methods::EnergyMethodOptions const & options );


	RNA_FA_ElecEnergy( RNA_FA_ElecEnergy const & src );


	/// clone
	core::scoring::methods::EnergyMethodOP
	clone() const override;

	void
	setup_for_minimizing(
		pose::Pose & pose,
		core::scoring::ScoreFunction const & sfxn,
		kinematics::MinimizerMapBase const & min_map
	) const override;

	void
	setup_for_derivatives( pose::Pose & pose, core::scoring::ScoreFunction const & ) const override;

	void
	setup_for_scoring( pose::Pose & pose, core::scoring::ScoreFunction const & ) const override;

	void
	finalize_total_energy(
		pose::Pose & pose,
		core::scoring::ScoreFunction const &,
		core::scoring::EnergyMap & totals
	) const override;

	void
	setup_for_packing( pose::Pose & pose, utility::vector1< bool > const &, utility::vector1< bool > const & ) const override;

	/// @brief overrides parent class implementation which would have
	/// created several tries
	void
	prepare_rotamers_for_packing(
		pose::Pose const & pose,
		conformation::RotamerSetBase & set ) const override;

	/// @brief overrides parent class implementation which would have
	/// updated a trie
	void
	update_residue_for_packing( pose::Pose & pose, Size resid ) const override;

	/////////////////////////////////////////////////////////////////////////////
	// scoring
	/////////////////////////////////////////////////////////////////////////////

	void
	residue_pair_energy(
		conformation::Residue const & rsd1,
		conformation::Residue const & rsd2,
		pose::Pose const & pose,
		core::scoring::ScoreFunction const &,
		core::scoring::EnergyMap & emap
	) const override;

	void
	setup_for_minimizing_for_residue_pair(
		conformation::Residue const & rsd1,
		conformation::Residue const & rsd2,
		pose::Pose const & pose,
		core::scoring::ScoreFunction const &,
		kinematics::MinimizerMapBase const &,
		core::scoring::ResSingleMinimizationData const &,
		core::scoring::ResSingleMinimizationData const &,
		core::scoring::ResPairMinimizationData & pair_data
	) const override;

	void
	residue_pair_energy_ext(
		conformation::Residue const & rsd1,
		conformation::Residue const & rsd2,
		core::scoring::ResPairMinimizationData const & min_data,
		pose::Pose const & pose,
		core::scoring::ScoreFunction const &,
		core::scoring::EnergyMap & emap
	) const override;

	/// @brief Returns "true" because this energy method has not been updated to
	/// use the new derivative evaluation machinery.  Note that this class requires
	/// the definition of this method because it's parent class, FA_ElecEnergy,
	/// HAS been updated to use the new derivative evaluation machinery, and,
	/// if this class did not return "true", it would be asked to evaluate derivatives
	/// in ways it cannot yet evaluate them in.
	bool
	minimize_in_whole_structure_context( pose::Pose const & pose ) const override;

	/// @brief Jan 10, 2012. Parin Sripakdeevon (sripakpa@stanford.edu)
	/// Returns "false" to overwrite the behavior in the parent class (FA_ElecEnergy)!
	/// AMW: changed this so that we do use the extended interface
	bool
	use_extended_residue_pair_energy_interface() const override { return true; }

	void
	eval_intrares_energy(
		conformation::Residue const &,
		pose::Pose const &,
		core::scoring::ScoreFunction const &,
		core::scoring::EnergyMap &
	) const override {}

	//@brief overrides default rotamer/rotamer energy calculation
	// and overrides the parent class trie implementatoin
	void
	evaluate_rotamer_pair_energies(
		conformation::RotamerSetBase const & set1,
		conformation::RotamerSetBase const & set2,
		pose::Pose const & pose,
		core::scoring::ScoreFunction const & sfxn,
		core::scoring::EnergyMap const & weights,
		ObjexxFCL::FArray2D< core::PackerEnergy > & energy_table
	) const override;

	Real
	score_atom_pair(
		conformation::Residue const & rsd1,
		conformation::Residue const & rsd2,
		Size const at1,
		Size const at2,
		core::scoring::EnergyMap & emap,
		core::scoring::ScoreFunction const & sfxn,
		Real const cpweight,
		Real & d2
	) const;

	void
	backbone_backbone_energy(
		conformation::Residue const & rsd1,
		conformation::Residue const & rsd2,
		pose::Pose const & pose,
		core::scoring::ScoreFunction const & sfxn,
		core::scoring::EnergyMap & emap
	) const override;


	//@brief overrides default rotamer/background energy calculation
	// and overrides the parent class trie implementatoin
	void
	evaluate_rotamer_background_energies(
		conformation::RotamerSetBase const & set,
		conformation::Residue const & residue,
		pose::Pose const & pose,
		core::scoring::ScoreFunction const & sfxn,
		core::scoring::EnergyMap const & weights,
		utility::vector1< core::PackerEnergy > & energy_vector
	) const override;


	void
	eval_atom_derivative(
		id::AtomID const & atom_id,
		pose::Pose const & pose,
		kinematics::DomainMap const & domain_map,
		core::scoring::ScoreFunction const &,
		core::scoring::EnergyMap const & weights,
		Vector & F1,
		Vector & F2
	) const override;

	void
	eval_residue_pair_derivatives(
		conformation::Residue const & rsd1,
		conformation::Residue const & rsd2,
		core::scoring::ResSingleMinimizationData const &,
		core::scoring::ResSingleMinimizationData const &,
		core::scoring::ResPairMinimizationData const & min_data,
		pose::Pose const & pose, // provides context
		core::scoring::EnergyMap const & weights,
		utility::vector1< core::scoring::DerivVectorPair > & r1_atom_derivs,
		utility::vector1< core::scoring::DerivVectorPair > & r2_atom_derivs
	) const override;

	bool
	defines_intrares_energy( core::scoring::EnergyMap const & /*weights*/ ) const override { return false; }

	void indicate_required_context_graphs( utility::vector1< bool > & context_graphs_required ) const override;

	bool
	requires_a_setup_for_minimizing_for_residue_pair_opportunity( pose::Pose const & ) const { return true; }

	//bool
	//requires_a_setup_for_derivatives_for_residue_pair_opportunity( pose::Pose const & ) const { return true; }

	//bool
	//requires_a_setup_for_scoring_for_residue_pair_opportunity( pose::Pose const & ) const { return true; }

public:

	Real
	rna_fa_elec_one_way(
		conformation::Residue const &,
		conformation::Residue const &,
		RNAAtomType const &,
		RNAAtomType const &

	) const;


	void
	eval_atom_derivative_RNA(
		conformation::Residue const & rsd1,
		Size const i,
		conformation::Residue const & rsd2,
		Size const j,
		core::scoring::EnergyMap const & weights,
		Vector & F1,
		Vector & F2
	) const;
	core::Size version() const override;


};


}
}

#endif
