# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vipul/ossim-svn/src/ossim_package_support/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vipul/ossim-svn/src/ossim_package_support/cmake/build

# Include any dependencies generated for this target.
include ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/depend.make

# Include the progress variables for this target.
include ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/progress.make

# Include the compile flags for this target's objects.
include ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/flags.make

ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o: ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/flags.make
ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o: /home/vipul/ossim-svn/src/ossim/src/apps/ossim-chgkwval/ossim-chgkwval.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-chgkwval && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o -c /home/vipul/ossim-svn/src/ossim/src/apps/ossim-chgkwval/ossim-chgkwval.cpp

ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-chgkwval && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/vipul/ossim-svn/src/ossim/src/apps/ossim-chgkwval/ossim-chgkwval.cpp > CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.i

ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-chgkwval && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/vipul/ossim-svn/src/ossim/src/apps/ossim-chgkwval/ossim-chgkwval.cpp -o CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.s

ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o.requires:
.PHONY : ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o.requires

ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o.provides: ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o.requires
	$(MAKE) -f ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/build.make ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o.provides.build
.PHONY : ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o.provides

ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o.provides.build: ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o

# Object files for target ossim-chgkwval
ossim__chgkwval_OBJECTS = \
"CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o"

# External object files for target ossim-chgkwval
ossim__chgkwval_EXTERNAL_OBJECTS =

ossim-chgkwval: ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o
ossim-chgkwval: libossim.so.1.8.12
ossim-chgkwval: /usr/lib/libOpenThreads.so
ossim-chgkwval: /usr/lib/libjpeg.so
ossim-chgkwval: /usr/lib/libtiff.so
ossim-chgkwval: /usr/lib/libgeotiff.so
ossim-chgkwval: /usr/lib/libOpenThreads.so
ossim-chgkwval: /usr/lib/libfreetype.so
ossim-chgkwval: /usr/lib/openmpi/lib/libmpi_cxx.so
ossim-chgkwval: /usr/lib/openmpi/lib/libmpi.so
ossim-chgkwval: /usr/lib/openmpi/lib/libopen-rte.so
ossim-chgkwval: /usr/lib/openmpi/lib/libopen-pal.so
ossim-chgkwval: /usr/lib/libdl.so
ossim-chgkwval: /usr/lib/libnsl.so
ossim-chgkwval: /usr/lib/libutil.so
ossim-chgkwval: /usr/lib/libm.so
ossim-chgkwval: /usr/lib/libz.so
ossim-chgkwval: /usr/lib/libdl.so
ossim-chgkwval: /usr/lib/libnsl.so
ossim-chgkwval: /usr/lib/libutil.so
ossim-chgkwval: /usr/lib/libm.so
ossim-chgkwval: /usr/lib/libz.so
ossim-chgkwval: ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/build.make
ossim-chgkwval: ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../../ossim-chgkwval"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-chgkwval && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ossim-chgkwval.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/build: ossim-chgkwval
.PHONY : ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/build

ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/requires: ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/ossim-chgkwval.cpp.o.requires
.PHONY : ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/requires

ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/clean:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-chgkwval && $(CMAKE_COMMAND) -P CMakeFiles/ossim-chgkwval.dir/cmake_clean.cmake
.PHONY : ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/clean

ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/depend:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vipul/ossim-svn/src/ossim_package_support/cmake /home/vipul/ossim-svn/src/ossim/src/apps/ossim-chgkwval /home/vipul/ossim-svn/src/ossim_package_support/cmake/build /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-chgkwval /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ossim/src/apps/ossim-chgkwval/CMakeFiles/ossim-chgkwval.dir/depend

