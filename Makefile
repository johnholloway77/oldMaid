# JHolloway is writing this on FreeBSD, but it's going to compile on Linux using GCC
# Horray for linux jails and cross platform compilation!!
UNAME_S := $(shell uname -s)

# Output binary
BINARY = cardGame
GTEST_BINARY = testGame

#directories
SRC_DIR = src
PROJECT_SRC_DIR = src/project
GTEST_INCLUDE_DIR = /usr/local/include
SRC_INCLUDE_DIR = ./include
GTEST_DIR = test
SOURCES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(PROJECT_SRC_DIR)/*.cpp)
GTEST_SOURCES= $(wildcard ${GTEST_DIR}/*.cpp) $(wildcard ${SRC_DIR}/*.cpp)

# Compiler variables and flags will depend if running on FreeBSD or Linux because John wants to learn cross compilation.
ifeq ($(UNAME_S), FreeBSD)
    CXX := clang++
    INCLUDE = -I ${SRC_INCLUDE_DIR} -I ${GTEST_INCLUDE_DIR}
    CXXWITHCOVERAGEFLAGS = ${CXXFLAGS} -fprofile-instr-generate -fcoverage-mapping  #-fprofile-arcs -ftest-coverage
else
    CXX := g++
    INCLUDE = -I ${SRC_INCLUDE_DIR}
	CXXWITHCOVERAGEFLAGS = ${CXXFLAGS} -fprofile-arcs -ftest-coverage
endif
CXXFLAGS := -Wall -Wextra -std=c++17
DEBUG := -g -O0
LIBS :=
GTEST_LIB:= -lgtest

# Object files (generated from source files)
OBJECTS = $(SOURCES:.cpp=.o)
GTEST_OBJECTS = $(GTEST_SOURCES:.cpp=.o)

# Tool variables
STATIC_ANALYSIS = cppcheck
STYLE_CHECK = cpplint
DESIGN_DIR = docs/design
DOXY_DIR = docs
COVERAGE_DIR = coverage
COVERAGE_RESULTS = results.coverage
ifeq ($(UNAME_S), FreeBSD)
COV = llvm-cov
else
GCOV = gcov
LCOV = lcov
endif

################################################################################
# Test targets
################################################################################

# Rule to link the binary
$(BINARY): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJECTS)

${GTEST_BINARY}: $(GTEST_OBJECTS)
	${CXX} $(CXXFLAGS) $(DEBUGFLAGS) $(INCLUDE) -o $@ $^ -L/usr/local/lib ${GTEST_LIB} ${LIBS}

# Rule to compile .cpp files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

# To perform the static check
static:
	${STATIC_ANALYSIS} --verbose --enable=all ${SRC_DIR} ${GTEST_DIR} \
	${SRC_INCLUDE_DIR} --suppress=missingIncludeSystem --error-exitcode=1

# To perform the style check
style:
	${STYLE_CHECK} --recursive ${SRC_DIR}/* ${GTEST_DIR}/* ${SRC_INCLUDE_DIR}/*

#Check for memory leaks with Valgrind. Off to Valhalla we go!!
memcheck-test: ${GTEST_BINARY}
	valgrind --tool=memcheck --leak-check=yes --error-exitcode=1 ./${GTEST_BINARY} ${LIBS}

test: ${GTEST_BINARY}
	./${GTEST_BINARY}

.PHONY: docs
docs: ${PROJECT_SRC_DIR}
	doxygen ${DOXY_DIR}/doxyfile

compile: $(BINARY)

#debug for John to fight this program in gdb
debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(BINARY)

# To perform the code coverage checks
ifeq ($(UNAME_S), FreeBSD)

.PHONY: coverage
coverage: clean-exec clean-cov
	${CXX} $(CXXWITHCOVERAGEFLAGS) $(INCLUDE) -L/usr/local/lib -o ${GTEST_BINARY} ${GTEST_DIR}/*.cpp ${SRC_DIR}/*.cpp ${GTEST_LIB} ${LIBS}
	LLVM_PROFILE_FILE="coverage.profraw" ./${GTEST_BINARY}
	# Determine code coverage
	llvm-profdata merge -sparse coverage.profraw -o coverage.profdata
	llvm-cov show ./${GTEST_BINARY} -instr-profile=coverage.profdata -format=html -output-dir=${COVERAGE_DIR} -ignore-filename-regex="/usr/local/include/gtest/.*"

	gmake clean-obj
	gmake clean-temp
else
.PHONY: coverage
coverage: clean-exec clean-cov
	${CXX} $(CXXWITHCOVERAGEFLAGS) $(INCLUDE) -L/usr/local/lib -o ${GTEST_BINARY} ${GTEST_DIR}/*.cpp ${SRC_DIR}/*.cpp ${GTEST_LIB} ${LIBS}
	./${GTEST_BINARY}

    # Determine code coverage
	${LCOV} --capture --gcov-tool ${GCOV} --directory . --output-file \
	${COVERAGE_RESULTS} --rc lcov_branch_coverage=1
	# Only show code coverage for the source code files (not library files)
	${LCOV} --extract ${COVERAGE_RESULTS} */${SRC_DIR}/* */${GTEST_DIR}/* -o \
	${COVERAGE_RESULTS}
	#Generate the HTML reports
	genhtml ${COVERAGE_RESULTS} --output-directory ${COVERAGE_DIR}
	#Remove all of the generated files from gcov
	make clean-temp
endif

################################################################################
# Clean-up targets
################################################################################

# Clean up the binary and object files
.PHONY: clean
clean:
	rm -rf $(BINARY) $(OBJECTS) $(GTEST_BINARY)  $(GTEST_OBJECTS)

# Clean only the object files
.PHONY: clean-obj
clean-obj:
	rm -rf $(OBJECTS) $(GTEST_OBJECTS)

# Clean only the executable files
.PHONY: clean-exec
clean-exec:
	rm -f $(GTEST_BINARY) $(BINARY)

.PHONY: clean-docs
clean-docs:
	rm -rf docs/code/html


ifeq ($(UNAME_S), FreeBSD)

.PHONY: clean-cov
clean-cov:
	rm -rf *.profdata *profraw ${COVERAGE_RESULTS} ${COVERAGE_DIR}

else
.PHONY: clean-cov
clean-cov:
	rm -rf *.gcov *.gcda *.gcno ${COVERAGE_RESULTS} ${COVERAGE_DIR}

endif



ifeq ($(UNAME_S), FreeBSD)

.PHONY: clean-temp
clean-temp:
	rm -rf *.profdata *profraw

else

.PHONY: clean-temp
clean-temp:
	rm -rf *~ \#* .\#* \
	${SRC_DIR}/*~ ${SRC_DIR}/\#* ${SRC_DIR}/.\#* \
	${GTEST_INCLUDE_DIR}/*~ ${GTEST_INCLUDE_DIR}/\#* ${GTEST_INCLUDE_DIR}/.\#* \
	${SRC_INCLUDE_DIR}/*~ ${SRC_INCLUDE_DIR}/\#* ${SRC_INCLUDE_DIR}/.\#* \
	${PROJECT_SRC_DIR}/*~ ${PROJECT_SRC_DIR}/\#* ${PROJECT_SRC_DIR}/.\#* \
	${DESIGN_DIR}/*~ ${DESIGN_DIR}/\#* ${DESIGN_DIR}/.\#* \
	*.gcov *.gcda *.gcno

endif