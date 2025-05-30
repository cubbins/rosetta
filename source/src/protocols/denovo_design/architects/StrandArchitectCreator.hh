// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file   protocols/denovo_design/architects/StrandArchitectCreator.hh
/// @brief  Class for instantiating a particular DeNovoArchitect
/// @author Tom Linsky ( tlinsky at uw dot edu )

#ifndef INCLUDED_protocols_denovo_design_architects_StrandArchitectCreator_HH
#define INCLUDED_protocols_denovo_design_architects_StrandArchitectCreator_HH

// Package headers
#include <protocols/denovo_design/architects/DeNovoArchitectCreator.hh>
#include <protocols/denovo_design/architects/DeNovoArchitect.fwd.hh>

// Utility headers

// C++ headers
#include <string>

namespace protocols {
namespace denovo_design {
namespace architects {

class StrandArchitectCreator : public DeNovoArchitectCreator {
public:
	/// @brief Instantiate a particular DeNovoArchitect
	DeNovoArchitectOP
	create_architect( std::string const & architect_id ) const override;

	/// @brief Return a string that will be used to instantiate the particular DeNovoArchitect
	std::string
	keyname() const override;

	void
	provide_xml_schema( utility::tag::XMLSchemaDefinition & xsd ) const override;

};

} //namespace architects
} //namespace denovo_design
} //namespace protocols

#endif
