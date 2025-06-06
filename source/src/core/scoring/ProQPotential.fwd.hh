// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file   core/scoring/ProQPotential.fwd.hh
/// @brief   Membrane Potential
/// @author Bjorn Wallner


#ifndef INCLUDED_core_scoring_ProQPotential_fwd_hh
#define INCLUDED_core_scoring_ProQPotential_fwd_hh


// Unit headers
#include <utility/pointer/owning_ptr.hh>

// Package headers

// Project headers

// Utility headers

// C++


namespace core {
namespace scoring {

class ProQPotential;
typedef utility::pointer::shared_ptr< ProQPotential > ProQPotentialOP;

} // ns scoring
} // ns core

#endif
