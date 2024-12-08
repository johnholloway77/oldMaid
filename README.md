# Project 2: Old Maid Card Game

The Old Maid card game has been developed as Project /#2 for the class CPSC-2720 at the Univeristy of Lethbridge, fall

2024.

* Developer and Repo Manager: `John Holloway (holj2721)`

Old Maid is a simple card game that will prompt the user for the number of players, ask the user to name each player and
begin the game. After the game completes the user will be shown in order the players who successfully got rid of their
cards, as well as who is left as the old maid!!

## Dependencies

- `googletest` (version 1.11 or higher): Required for building unit tests
- C++ Compiler: Either
    - `gcc` >= 7.0 or higher
    - `clang` >= 5.0 or higher
    - or any C++ compiler that supports the C++ 17 standard.
- `gmake` if on FreeBSD. Needed because Makefile contains `ifeq` statements, which are not supported by base
  system's `make` utility.

## Build

To build the game, run the following command:

```bash
git clone http://gitlab.cs.uleth.ca/holj2721/project2.git
```

After cloning the repository, navigate to the downloaded directory and run:

```bash
make cardGame
```

*Note:* On FreeBSD you will need to use `gmake` and not the base install `make` for all build, test and documentation
commands on this page

A binary executable will be produced. To start the game simply run the dragonSlayer executable

```bash
./cardGame
```

## Tests and Documentation

### Quality Checks

#### Style Check

The source code adheres the Google C++ coding style.  
To perform a style check on the source code, please run the following command:

  ```bash
  make style
  ```

*Note:* The style check will require the application `cpplint` be installed

#### Static Check

To perform a static analysis of the source code please run the following command

  ```bash
  make static
  ```

*Note:* The static analysis will require that the application `cppcheck` be installed

### Unit Tests

To build and run the unit tests please run the following command:

  ```bash
  make testGame
  ```

This will automatically build and run the googleTest unit tests for the application.

### Active Tests

To check the application for memory leaks, please run the following command:

  ```bash
  make memcheck-game
  ```

This command will run `valgrind` on the cardGame binary, checking for dynamically
allocated memory that has not been freed

To check the unit tests for memory leaks, please run the following command:

  ```bash
  make memcheck-test
  ```

This command will run `valgrind` on the testGame binary.

### Documentation

#### Source Code Documentation

To build documentation for the C++ source code run the following command:

```bash
make docs
```

The file `./docs/code/html/index.html` will be built, providing information on the source code and objects in the game.

*Note:* To build documentation the application Doxygen is required to be installed

#### Coverage Tests and Reports

To build a coverage report for the unit tests, please run the following command

```bash
make coverage
```

A coverage test will be performed, and a report will be generated in the form of an HTML webpage. The application will
be built using `gcov` and `lcov` on Linux, and `llvm-cov` on FreeBSD. While the coverage results should be consistent
across both platforms, the styling of the report may differ depending on the tool used to create it. In both cases, the
report can be viewed by opening `./coverage/index.html`.

## Cleaning Build Directory

#### Clean Everything

To remove all object files and binary executables run the command

```bash
make clean
```

#### Clean Binaries

To remove the executables but leave the existing object files run the command

```bash
make clean-exec
```

#### Clean Objects

To remove only object files, please run the command

```bash
make clean-obj
```

#### Clean Source Code Documents

To remove the documentation on the source code, please run the command

```bash
make clean-docs
```

#### Clean Coverage test

To remove the documentation produced by the coveage test run the command

```bash
make clean-cov
```