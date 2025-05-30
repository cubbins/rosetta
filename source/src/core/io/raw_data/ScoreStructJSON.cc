// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file core/io/raw_data/ScoreStructJSON.cc
///
/// @brief Write out only score information in JSON format
/// @author Luki Goldschmidt

// mini headers
#include <core/io/raw_data/ScoreStructJSON.hh>
#include <utility/json_spirit/json_spirit_writer.h>
#include <core/pose/Pose.hh>

// C++ Headers
#include <map>

#include <utility/json_spirit/json_spirit_writer_options.h> // AUTO IWYU For remove_trailing_zeros

namespace core {
namespace io {
namespace raw_data {

ScoreStructJSON::ScoreStructJSON( std::string const & tag ) {
	decoy_tag_ = tag;
}

void ScoreStructJSON::print_scores(
	std::ostream& out,
	std::map < std::string, core::Real > const & score_map,
	std::map < std::string, std::string > const & string_map
) const
{
	using utility::json_spirit::Pair;

	utility::json_spirit::Object record;

	// Meta data
	if ( !decoy_tag_.empty() ) {
		record.push_back( Pair( "decoy", decoy_tag_ ) );
	}

	// Scores
	for ( auto const & it : score_map ) {
		record.push_back( Pair( it.first, it.second ) );
	}

	for ( auto const & it : string_map ) {
		record.push_back( Pair( it.first, it.second ) );
	}

	utility::json_spirit::write( utility::json_spirit::Value( record ), out, utility::json_spirit::remove_trailing_zeros );
	out << std::endl;

} // print_scores

} // namespace silent
} // namespace io
} // namespace core
