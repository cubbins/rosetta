// Core headers
#include <core/pose/Pose.hh>
#include <core/import_pose/import_pose.hh>
#include <core/conformation/Conformation.hh>
#include <core/conformation/Residue.fwd.hh>
#include <core/id/AtomID.hh>

// Protocol headers
#include <protocols/loops/Loop.hh>

// Utility headers
#include <devel/init.hh>

using namespace std;

using core::Size;
using core::Real;
using core::pose::Pose;
using core::import_pose::pose_from_file;
using core::conformation::Conformation;
using core::conformation::Residue;
using core::id::AtomID;

using protocols::loops::Loop;

AtomID id_from_index(Loop const & loop, Size index) { // {{{1
	return AtomID(
			((index - 1) % 3) + 1,
			((index - 1) / 3) + loop.start());
}

void print_internal_coordinates( // {{{1
		Pose const & pose, Loop const & loop) {

	Conformation const &conformation = pose.conformation();
	AtomID ids[4];

	Size num_atoms = 3 * loop.length();
	Size num_bond_lengths = num_atoms - 1;
	Size num_bond_angles = num_atoms - 2;
	Size num_torsion_angles = num_atoms - 3;

	cout << "Bond Lengths" << endl;
	cout << "============" << endl;
	for (Size index = 1; index <= num_bond_lengths; index++) {
		ids[0] = id_from_index(loop, index + 0);
		ids[1] = id_from_index(loop, index + 1);

		cout << conformation.bond_length(ids[0], ids[1]) << endl;
	}
	cout << endl;
	cout << "Bond Angles" << endl;
	cout << "===========" << endl;
	for (Size index = 1; index <= num_bond_angles; index++) {
		ids[0] = id_from_index(loop, index + 0);
		ids[1] = id_from_index(loop, index + 1);
		ids[2] = id_from_index(loop, index + 2);

		cout << conformation.bond_angle(ids[0], ids[1], ids[2]) << endl;
	}
	cout << endl;
	cout << "Torsion Angles" << endl;
	cout << "==============" << endl;
	for (Size index = 1; index <= num_torsion_angles; index++) {
		ids[0] = id_from_index(loop, index + 0);
		ids[1] = id_from_index(loop, index + 1);
		ids[2] = id_from_index(loop, index + 2);
		ids[3] = id_from_index(loop, index + 3);

		cout << conformation.torsion_angle(ids[0], ids[1], ids[2], ids[3]) << endl;
	}
	cout << endl;
}
// }}}1

Pose copy_using_constructor( // {{{1
		Pose const & full_pose,
		Loop const & loop) {

	return Pose(full_pose, loop.start(), loop.stop());
}

Pose copy_each_residue( // {{{1
		Pose const & full_pose,
		Loop const & loop) {

	Pose loop_pose;

	for (Size i = loop.start(); i <= loop.stop(); i++) {
		Residue const & residue = full_pose.residue(i);
		loop_pose.append_residue_by_bond(residue);
	}

	return loop_pose;
}
// }}}1

int main(int argc, char** argv) {

	devel::init(argc, argv);

	Pose full_pose, loop_pose;
	Loop loop(308, 319);
	Loop small_loop(1, 12);

	pose_from_file(full_pose, "structures/kic/1srp.pdb", core::import_pose::PDB_file);

	/*
	for (int i = 0; i < 100; i++) {
		Pose copied_pose(full_pose);
	}

	for (int i = 0; i < 100; i++) {
		Pose loop_pose = copy_using_constructor(full_pose, loop);
	}

	for (int i = 0; i < 100; i++) {
		Pose loop_pose = copy_each_residue(full_pose, loop);
	}
	*/

	loop_pose = copy_each_residue(full_pose, loop);
	loop_pose.set_phi(1, 10);
	loop_pose.set_psi(1, 20);
	loop_pose.set_phi(2, 30);
	loop_pose.set_psi(2, 40);

	cout << "FULL POSE" << endl;
	print_internal_coordinates(full_pose, loop);

	cout << "LOOP POSE" << endl;
	print_internal_coordinates(loop_pose, small_loop);
}


