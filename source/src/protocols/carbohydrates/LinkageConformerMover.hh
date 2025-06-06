// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file protocols/carbohydrates/LinkageConformerMover.hh
/// @brief This code changes all of the dihedrals of a particular glycosidic linkage based on database info,
///   esentially sampling carbohydrate dihedral conformers of two residues.
/// @author Jared Adolf-Bryfogle (jadolfbr@gmail.com)
/// @author Labonte <JWLabonte@jhu.edu>


#ifndef INCLUDED_protocols_carbohydrates_LinkageConformerMover_hh
#define INCLUDED_protocols_carbohydrates_LinkageConformerMover_hh

// Unit headers
#include <protocols/carbohydrates/LinkageConformerMover.fwd.hh>
#include <protocols/simple_moves/BBDihedralSamplerMover.fwd.hh>
#include <protocols/moves/Mover.hh>


#include <core/select/residue_selector/ResidueSelector.fwd.hh>
#include <core/pose/Pose.fwd.hh>


#include <basic/datacache/DataMap.fwd.hh>


namespace protocols {
namespace carbohydrates {

///@brief This code changes all of the dihedrals of a particular glycosidic linkage based on database info,
///  esentially sampling carbohydrate dihedral conformers of two residues.  Randomly samples on any set selector at each apply or (default) samples a linkage conformer for each residue set.
///
///@details The linkage conformers are carbohydrate residue type and (and linkage oxygen) dependant ie MAN-MAN
/// If data is not known here, by default we sample from restype-independant data.
/// If there are multiple conformers for a given linkage, will randomly select from them.
///
/// 3 Main Conformer Sampling Strategies:
////  1) Mean + uniform in X standard deviations (Default)
////     ->Build conformers using the means of dihedrals + or - some amount within X standard deviations of the mean.
////
////     See Also:
////      LinkageConformerMover.set_x_standard_deviations
////
////  2) Mean + probability in X standard deviations
////
////  3) Idealize
////     -> Use only means when building linkage conformers.
////
////     See:
////      LinkageConformerMover.set_idealize_torsions
/////
class LinkageConformerMover : public protocols::moves::Mover {

public:

	///@brief Default constructor
	LinkageConformerMover();

	///@brief Constructor with pair of residues in linkage we will build the conformer for.
	LinkageConformerMover(core::select::residue_selector::ResidueSelectorCOP selector);

	// copy constructor
	LinkageConformerMover( LinkageConformerMover const & src );

	~LinkageConformerMover() override;

	///@brief Set the Selector.  Each apply will randomly sample Selector.
	/// If the conformer is not found, will set move status to false.
	/// Will optimize the linkage between the residue and the parent residue.
	void
	set_residue_selector( core::select::residue_selector::ResidueSelectorCOP selector );

	///@brief Set a single resnum to sample on instead of a movemap.
	void
	set_single_resnum( core::pose::Pose const & pose, core::Size resnum );

	void
	apply( core::pose::Pose & pose ) override;


public:

	///@brief Use phi/psi data if restype-dependant conformer data unavailable.
	/// Will set phi/psi to lowest energy values if idealize is true.
	/// Default FALSE
	void
	set_use_sugar_bb_data_if_needed( bool use_sugar_bb);

	///@brief Set whether if we are sampling uniformly within 1 SD or by sampling on the full gaussian directly.
	/// Default FALSE
	void
	set_use_gaussian_sampling(bool prob_sd_sample);

	///@brief Idealize the torsion angles instead of sampling from SD.
	/// Default FALSE
	void
	set_idealize_torsions(bool idealize_torsions);

	/// @brief Use conformer population data to weight sampling.  Default TRUE.
	void
	set_use_conformer_population_stats( bool const setting )
	{
		use_conformer_population_stats_ = setting;
	}

	///@brief Set the LCM to use probabilities for the ASN (or other residue) linkage.
	/// Default False
	void
	set_root_prob_sampling( bool root_prob_sampling );

	///@breif Set everything to default values, including linkage pairs.
	void
	set_defaults();

public:

	///@brief Boolean for if the restype-dependant conformer was found at apply. Resets at successive applies.
	bool
	conformer_found() const;

public:
	void
	show( std::ostream & output=std::cout ) const override;


	/// @brief parse XML tag (to use this Mover in Rosetta Scripts)
	void parse_my_tag(
		utility::tag::TagCOP tag,
		basic::datacache::DataMap & data
	) override;


	//LinkageConformerMover & operator=( LinkageConformerMover const & src );

	/// @brief required in the context of the parser/scripting scheme
	moves::MoverOP
	fresh_instance() const override;

	/// @brief required in the context of the parser/scripting scheme
	protocols::moves::MoverOP
	clone() const override;

	bool reinitialize_for_each_job() const override {
		return true;
	}

	bool reinitialize_for_new_input() const override {
		return true;
	}

	std::string
	get_name() const override;

	static
	std::string
	mover_name();

	static
	void
	provide_xml_schema( utility::tag::XMLSchemaDefinition & xsd );

public: //Functions needed for the citation manager

	/// @brief Provide the citation.
	void provide_citation_info(basic::citation_manager::CitationCollectionList & ) const override;

private:
	//std::pair< core::Size, core::Size > linkage_pair_; Can't check if this exists.

	bool use_sugar_bb_data_if_needed_;
	bool idealize_torsions_;
	bool conformer_found_;
	bool use_gaussian_sampling_;
	bool sample_protein_linkage_;
	bool use_conformer_population_stats_;
	bool random_sampler_ = false;

	simple_moves::BBDihedralSamplerMoverOP phi_sampler_mover_;
	simple_moves::BBDihedralSamplerMoverOP psi_sampler_mover_;
	simple_moves::BBDihedralSamplerMoverOP omega_sampler_mover_;

	core::select::residue_selector::ResidueSelectorCOP selector_ = nullptr;
	bool root_prob_sampling_ = false;

};


std::ostream &operator<< (std::ostream &os, LinkageConformerMover const &mover);

} //carbohydrates
} //protocols

#endif  // protocols_carbohydrates_LinkageConformerMover_hh
