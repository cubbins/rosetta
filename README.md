
5/25/2025

    printf("\n **** cubbins hello from remodel.cc in src/apps/public/remodel.cc **** \n");
-note: add two blank spaces after a line to force a line break and carriage feed-  
this compiles only one file as type static:    
 ./scons.py -j4 mode=release bin extras=static  
yet, compiles with type as default, given prior new edit:  
  ./scons.py -j4 mode=release bin  
for this source code: src/apps/public/remodel.cc  
producing this executable: build/src/release/linux/5.15/64/x86/gcc/11/default/remodel.default.linuxgccrelease  
  g++ -o build/src/release/linux/5.15/64/x86/gcc/11/default/remodel.default.linuxgccrelease...    
must be in this directory to execute:   
/home/cubbins/rosetta/tests/integration/new/remodel#  
and, execute with this command in said directory:  
/home/cubbins/rosetta/source/bin/remodel.default.linuxgccrelease -database /home/cubbins/rosetta/database -s 2ci2.renumbered.pdb -remodel:blueprint blueprint.2ci2.remodel -run:chain A -remodel:num_trajectory 2 -overwrite -remodel:quick_and_dirty -testing:INTEGRATION_TEST -out:prefix test1_  
result references provided as:   
basic.citation_manager.CitationManager:  
The following Rosetta modules were used during this run of Rosetta, and should be cited:  

RemodelMover Mover's citation(s):  
Huang PS, Ban YE, Richter F, Andre I, Vernon R, Schief WR, and Baker D.  (2011).  RosettaRemodel: a generalized framework for flexible backbone protein design.  PLoS One 6(8):e24109.  doi: 10.1371/journal.pone.0024109.  
  


Rosetta Biomolecular Modeling Library
=====================================

The Rosetta software suite includes algorithms for computational modeling and analysis of protein structures. It has enabled notable scientific advances in computational biology, including de novo protein design, enzyme design, ligand docking, and structure prediction of biological macromolecules and macromolecular complexes.

Rosetta is maintained by the RosettaCommons, a collaboration of 50+ academic research groups, who have been developing Rosetta for over 20 years.
See <https://www.rosettacommons.org> for more information about Rosetta and the RosettaCommons.

Rosetta Code
============

While the Rosetta source code is published on GitHub, it is not "Open Source" (according to the OSI definition). Most notably, use for commercial purposes requires purchase of a separate license. See LICENSE.md for further information.

The main GitHub repository on https://github.com/RosettaCommons/rosetta integrates all the Rosetta-associated code base.
It should be noted that many parts of Rosetta are structured as separate GitHub repositories, which the main repository conveniently presents as submodules.
A significant number are external software packages that Rosetta is redistributing, which helps synchronize development to exact versions of those external softwares across software distributions
and thus support users and developers in their communication.

It is not required to manually retrieve those subprojects.
Instead, the scons build management will auto-retrieve only those external repositories that are required for the build.
The retrieval of external source trees is independent from the software that may already be installed via the Operating System, which is intentional.

``` sh
git clone https://github.com/RosettaCommons/rosetta
```
and change to that directory
``` sh
cd rosetta
```

Getting Started Using Rosetta
=============================

Start here: https://www.rosettacommons.org/docs/latest/getting_started/Getting-Started

The fastest way to address your scientific modeling challenge at hand may be with the official Docker images.
Accessible from the official Docker hub at https://hub.docker.com/r/rosettacommons/rosetta,
the images have both Rosetta and PyRosetta pre-installed, such that Rosetta tutorials can be followed.
You may also conveniently inspect the Dockerfiles
(see [docker/README.md](https://github.com/RosettaCommons/rosetta/blob/main/docker/README.md))
as a templated for the Rosetta installation on your local system.

Questions about how to use Rosetta are best directed to the RosettaCommons forums <https://www.rosettacommons.org/forum>

Installing using Conda
----------------------

Rosetta binaries are avaliable as a `rosetta` Conda package in the **RosettaCommons Conda Channel**. All binaries are built using `serialization` and `cxx11thread` extras. Currently RosettaCommons has two mirrors of this channel. To use them please edit `~/.condarc` and add snippets for either East or West mirrors:

Example `~/.condarc` for US WEST coast (if unsure use this mirror): 

```
channels: 
- https://conda.rosettacommons.org
- conda-forge
```

Example `~/.condarc` for US EAST coast:

```
channels: 
- https://conda.graylab.jhu.edu
- conda-forge
```


Compiling Rosetta
-----------------

To use Rosetta without Docker, or to modify and extend Rosetta yourself, you can compile the Rosetta source tree yourself.
(See also <https://www.rosettacommons.org/docs/latest/build_documentation/Build-Documentation> for details.)

The Rosetta source tree ships with all its run-time dependencies, just when building you
need to install the C++ compiler (g++ or clang). Also you need the scripting language Python to be installed,
The compilation is then performed by:

``` sh
$ cd source
$ ./scons.py -j<NumOfJobs> mode=release bin
```

The Rosetta source tree is big and uses a series of advanced features of the C++ language.
While we endeavor to support most compilers where possible, some C++ compilers may not yet perfectly master these features.
Later versions of those compilers may have that fixed.
Please let us know if you run into issues.

Docker
======

Official Rosetta/PyRosetta images could be found at https://hub.docker.com/r/rosettacommons/rosetta.
Both `serial` and `mpi` Rosetta builds provided as well as the number of PyRosetta builds including fully functional Jupyter setups with PyRosetta pre-installed and experimenta builds with `libtorch` and `tensorflow` integration.
Please see https://hub.docker.com/r/rosettacommons/rosetta for more information.

Various reference Docker files could be found in `rosetta/docker` dir.

PyRosetta
=========

PyRosetta are Python bindings to the Rosetta library. These can be built from the Rosetta source code.

See <https://www.pyrosetta.org> for more information about PyRosetta.

The Docker image referenced above already ships with PyRosetta.
To prepare the PyRosetta Python module locally from this source tree,
you need
 * a C++ compiler, like the one you used to compile the other parts of Rosetta
 * the Ninja ([conda](https://anaconda.org/conda-forge/ninja), [Debian](https://tracker.debian.org/pkg/ninja-build)) build management tool
 * and also CMake ([conda](https://anaconda.org/conda-forge/cmake), [Debian](https://tracker.debian.org/pkg/cmake))
which should all be readily available from your regular Linux distribution.

``` sh
$ cd source/src/python/PyRosetta
$ python3 build.py -j24 --create-package $HOME/my_pyrosetta_package
$ cd $HOME/my_pyrosetta_package/setup
$ python3 setup.py install
```

Developing Rosetta
==================

We welcome contributions to improve Rosetta. We use a fork-and-PR system for contribution.
To contribute to Rosetta, please fork the Rosetta repo(s) under your own Github user space.
You can then develop your additions in your own space. Once you're ready to contribute it back, open a PR agaist the main Rosetta repos.
You will need to sign the Rosetta Contributor License Agreement before your contribution can be accepted.

See CONTRIBUTING.md for more details.

Rosetta Code Organization
=========================

Due to its size, Rosetta uses git submodules to help in organization.

The main repository (RosettaCommons/rosetta) contains the Rosetta source code, database, unit test and integration tests
* rosetta/source/src -- The Rosetta source
* rosetta/database/ -- The Rosetta database (used during runtime)
* rosetta/source/test/ -- The compiled unit tests
* rosetta/tests/integration/ -- The integration tests
* rosetta/source/bin/ -- The location of the (symlinks to) the Rosetta executables -- (created during compilation)
* rosetta/source/build/ -- The location of the built libraries -- (created during compilation)

Additional information is located in submodules:
* rosetta/documentation/ -- https://github.com/RosettaCommons/documentation -- Source for the online documentation
* rosetta/demos/ -- https://github.com/RosettaCommons/demos -- Various demos on using Rosetta
* rosetta/tools/ -- https://github.com/RosettaCommons/tools -- Additional helper scripts and protocols
* rosetta/rosetta_scripts_scripts -- https://github.com/RosettaCommons/rosetta_scripts_scripts -- Example XML scripts for use with RosettaScripts
* rosetta/pyrosetta_scripts -- https://github.com/RosettaCommons/pyrosetta_scripts -- Example PyRosetta scripts
* rosetta/PyRosetta.notebooks -- https://github.com/RosettaCommons/PyRosetta.notebooks -- Example Jupyter notebooks using PyRosetta.
* rosetta/source/external/... -- Various 'venderized' external dependencies

The default clone does not pull down submodules, leaving an empty directory. 
The compilation script will automatically clone the submodules needed for compilation, but not others.
To obtain the contents of submodules which aren't currently cloned:

    git submodule update --init -- ./submodule_directory_name
    # e.g. git submodule update --init -- ./tools/

or if you want to get all the submodules

    git submodule update --init --recursive
