# Template for CPSC2720 Assignments, Labs, and Projects

Last Updated: 2023-09-21 by Ibrahim Abdoulahi &lt;ibrahim.abdoulahi@uleth.ca&gt;

Notes:

* The Makefile and .gitlab-ci.yml files are set up to run on Ubuntu.
* The .gitlab-ci.yml file uses the targets in the Makefile.
* These are the tools/commands/apps used:
  * Compiler: g++
  * Version: c++14
  * Style Check: cpplint 1.6.1
  * Static Check: cppcheck 2.7
  * Coverage Check: 
    * gcov (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0
    * lcov 1.14
  * Memory Check: valgrind 3.18.1
  * Unit Test: gtest v.1.11.0 
  * Documentation: doxygen 1.9.1-Ounbuntu2

Certain assumptions have been made:
* One repo contains the files for one project.
* All unit testing files are found in <code>test/</code> including <code>main.cpp</code>.
* All header files for the project are found in <code>include/</code> and named <code>*.h</code>, every class must have a header file.
* All project source files for the project are named <code>*.cpp</code>.
  * Any needed source files that correspond to header files are found in <code>src/</code>.
  * There is a <code>main.cpp</code> found in <code>src/project/</code>.
