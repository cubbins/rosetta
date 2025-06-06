// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.
/// @author Rhiju Das

#ifndef INCLUDED_protocols_rna_RNA_LoopCloser_fwd_hh
#define INCLUDED_protocols_rna_RNA_LoopCloser_fwd_hh


#include <utility/pointer/owning_ptr.hh>


namespace protocols {
namespace rna {
namespace movers {

class RNA_LoopCloser;
typedef utility::pointer::shared_ptr< RNA_LoopCloser > RNA_LoopCloserOP;
typedef utility::pointer::shared_ptr< RNA_LoopCloser const > RNA_LoopCloserCOP;

} //movers
} //rna
} //protocols

#endif
