// -*- mode:c++;tab-width:2;indent-tabs-mode:t;show-trailing-whitespace:t;rm-trailing-spaces:t -*-
// vi: set ts=2 noet:
//
// (c) Copyright Rosetta Commons Member Institutions.
// (c) This file is part of the Rosetta software suite and is made available under license.
// (c) The Rosetta software is developed by the contributing members of the Rosetta Commons.
// (c) For more information, see http://www.rosettacommons.org. Questions about this can be
// (c) addressed to University of Washington CoMotion, email: license@uw.edu.

/// @file   core/chemical/rotamers/StoredRotamerLibrarySpecification.hh
/// @brief  The StoredRotamerLibrarySpecification class says to build a rotamer library from a set of stored coordinates
/// @author Rocco Moretti (rmorettiase@gmail.com)

#ifndef INCLUDED_core_chemical_rotamers_StoredRotamerLibrarySpecification_HH
#define INCLUDED_core_chemical_rotamers_StoredRotamerLibrarySpecification_HH

// Unit headers
#include <core/chemical/rotamers/StoredRotamerLibrarySpecification.fwd.hh>
#include <core/chemical/rotamers/RotamerLibrarySpecification.hh>

// Package headers
#include <core/types.hh>

// Basic headers

// Utility Headers
#include <utility/vector1.hh>

// C++ headers
#include <iosfwd>
#include <map>

#include <numeric/xyzVector.hh> // DO NOT AUTO-REMOVE

#ifdef    SERIALIZATION
// Cereal headers
#include <cereal/types/polymorphic.fwd.hpp>
#endif // SERIALIZATION

namespace core {
namespace chemical {
namespace rotamers {

/// @brief A class which stores atom coordinates for a rotamer library.
/// Internally, this is stored as a list of name:coordinate maps.
/// @details
/// This is intended as an analog to PDBRotamerLibrarySpecifications
/// for those instances where the coordinates are generated internally or
/// programmatically.

class StoredRotamerLibrarySpecification : public RotamerLibrarySpecification {
public:
	StoredRotamerLibrarySpecification();
	StoredRotamerLibrarySpecification(std::istream & input);

	RotamerLibrarySpecificationOP
	clone() const override;

	utility::vector1< std::map< std::string, core::Vector > > const &
	coordinates() const { return coordinates_; }

	/// @brief Add a particular rotamer to the list
	void
	add_rotamer( std::map< std::string, core::Vector > const & rotamer );

	/// @brief Add vector of rotamers to list
	void
	add_rotamers( utility::vector1< std::map< std::string, core::Vector > > const & rotamers );

	core::Real
	get_reference_energy() const {
		return ref_energy_;
	}

	void set_reference_energy( core::Real ref_E_in ) {
		ref_energy_ = ref_E_in;
	}

	/// @brief Set the coordinates list in an all-at-once fashion
	void
	set_rotamers( utility::vector1< std::map< std::string, core::Vector > > const & confs );

	void
	describe( std::ostream & out ) const override;

	std::string
	keyname() const override;

	static std::string library_name();

private:

	utility::vector1< std::map< std::string, core::Vector > > coordinates_;
	core::Real ref_energy_ = 0;

#ifdef    SERIALIZATION
public:
	template< class Archive > void save( Archive & arc ) const;
	template< class Archive > void load( Archive & arc );
#endif // SERIALIZATION

};


} //namespace rotamers
} //namespace chemical
} //namespace core


#ifdef    SERIALIZATION
CEREAL_FORCE_DYNAMIC_INIT( core_chemical_rotamers_StoredRotamerLibrarySpecification )
#endif // SERIALIZATION


#endif
