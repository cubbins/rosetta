// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file   protocols/ligand_evolution/offspring_factory/OffspringFactory.fwd.hh
/// @brief  Forward declaration of the %OffspringFactory class
/// @author Paul Eisenhuth (eisenhuth451@gmail.com)

#ifndef INCLUDED_protocols_ligand_evolution_OffspringFactory_FWD_HH
#define INCLUDED_protocols_ligand_evolution_OffspringFactory_FWD_HH

// utility headers
#include <utility/pointer/owning_ptr.hh>

namespace protocols {
namespace ligand_evolution {

class OffspringFactory;

typedef utility::pointer::shared_ptr< OffspringFactory > OffspringFactoryOP;
typedef utility::pointer::shared_ptr< OffspringFactory const > OffspringFactoryCOP;

}
}

#endif
