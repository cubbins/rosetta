// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file   core/scoring/methods/RNP_LowResStackData.hh
/// @brief  Statistically derived RNP low resolution protential
/// @author Kalli Kappel

#ifndef INCLUDED_core_scoring_RNP_LowResStackData_hh
#define INCLUDED_core_scoring_RNP_LowResStackData_hh

#include <core/types.hh>

// Unit headers
#include <core/scoring/rna/RNP_LowResStackData.fwd.hh>

// Package headers
#include <core/conformation/Residue.fwd.hh>

// Project headers


// Utility headers

#include <ObjexxFCL/FArray4D.hh>


#include <utility/VirtualBase.hh> // AUTO IWYU For VirtualBase


// C++


namespace core {
namespace scoring {
namespace rna {

////////////////////////////////////////////////////////////////////////////////////////////////////
typedef utility::pointer::shared_ptr< RNP_LowResStackData > RNP_LowResStackDataOP;
class RNP_LowResStackData : public utility::VirtualBase {

public:
	RNP_LowResStackData();

	void
	initialize_rnp_stack_xy();

	void
	evaluate_rnp_stack_xy_score(
		conformation::Residue const & rsd1,
		conformation::Residue const & rsd2,
		Real const & x,
		Real const & y,
		Real & rnp_stack_score
	) const;

private: // data

	Size const max_aa_ = 20;
	Size const max_base_ = 4;
	Size const num_xbins_ = 10;
	Size const num_ybins_ = 10;

	ObjexxFCL::FArray4D < Real > rnp_stack_xy_;

};

} // rna
} // scoring
} // core

#endif
