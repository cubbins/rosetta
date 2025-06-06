// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file protocols/simple_filters/LongestContinuousPolarSegmentFilterCreator.hh
/// @brief This filter computes the longest continuous stretch of polar residues within a pose or selection.
/// @author Vikram K. Mulligan (vmullig@uw.edu)

#ifndef INCLUDED_protocols_simple_filters_LongestContinuousPolarSegmentFilterCreator_hh
#define INCLUDED_protocols_simple_filters_LongestContinuousPolarSegmentFilterCreator_hh

#include <protocols/filters/FilterCreator.hh>
//#include <utility/tag/XMLSchemaGeneration.fwd.hh> //transcluded from FilterCreator.hh

namespace protocols {
namespace simple_filters {

class LongestContinuousPolarSegmentFilterCreator : public protocols::filters::FilterCreator {
public:
	protocols::filters::FilterOP create_filter() const override;
	std::string keyname() const override;
	void provide_xml_schema( utility::tag::XMLSchemaDefinition & xsd ) const override;

};

} //protocols
} //simple_filters

#endif //INCLUDED_protocols_simple_filters_LongestContinuousPolarSegmentFilter_fwd_hh
