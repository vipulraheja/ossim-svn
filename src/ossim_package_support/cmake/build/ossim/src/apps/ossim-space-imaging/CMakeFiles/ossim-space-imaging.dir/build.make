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
include ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/depend.make

# Include the progress variables for this target.
include ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/progress.make

# Include the compile flags for this target's objects.
include ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/flags.make

ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o: ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/flags.make
ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o: /home/vipul/ossim-svn/src/ossim/src/apps/ossim-space-imaging/ossim-space-imaging.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-space-imaging && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o -c /home/vipul/ossim-svn/src/ossim/src/apps/ossim-space-imaging/ossim-space-imaging.cpp

ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-space-imaging && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/vipul/ossim-svn/src/ossim/src/apps/ossim-space-imaging/ossim-space-imaging.cpp > CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.i

ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-space-imaging && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/vipul/ossim-svn/src/ossim/src/apps/ossim-space-imaging/ossim-space-imaging.cpp -o CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.s

ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o.requires:
.PHONY : ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o.requires

ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o.provides: ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o.requires
	$(MAKE) -f ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/build.make ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o.provides.build
.PHONY : ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o.provides

ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o.provides.build: ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o

# Object files for target ossim-space-imaging
ossim__space__imaging_OBJECTS = \
"CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o"

# External object files for target ossim-space-imaging
ossim__space__imaging_EXTERNAL_OBJECTS =

ossim-space-imaging: ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o
ossim-space-imaging: libossim.so.1.8.12
ossim-space-imaging: /usr/lib/libOpenThreads.so
ossim-space-imaging: /usr/lib/libjpeg.so
ossim-space-imaging: /usr/lib/libtiff.so
ossim-space-imaging: /usr/lib/libgeotiff.so
ossim-space-imaging: /usr/lib/libOpenThreads.so
ossim-space-imaging: /usr/lib/libfreetype.so
ossim-space-imaging: /usr/lib/openmpi/lib/libmpi_cxx.so
ossim-space-imaging: /usr/lib/openmpi/lib/libmpi.so
ossim-space-imaging: /usr/lib/openmpi/lib/libopen-rte.so
ossim-space-imaging: /usr/lib/openmpi/lib/libopen-pal.so
ossim-space-imaging: /usr/lib/libdl.so
ossim-space-imaging: /usr/lib/libnsl.so
ossim-space-imaging: /usr/lib/libutil.so
ossim-space-imaging: /usr/lib/libm.so
ossim-space-imaging: /usr/lib/libz.so
ossim-space-imaging: /usr/lib/libdl.so
ossim-space-imaging: /usr/lib/libnsl.so
ossim-space-imaging: /usr/lib/libutil.so
ossim-space-imaging: /usr/lib/libm.so
ossim-space-imaging: /usr/lib/libz.so
ossim-space-imaging: ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/build.make
ossim-space-imaging: ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../../ossim-space-imaging"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-space-imaging && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ossim-space-imaging.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/build: ossim-space-imaging
.PHONY : ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/build

ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/requires: ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/ossim-space-imaging.cpp.o.requires
.PHONY : ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/requires

ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/clean:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-space-imaging && $(CMAKE_COMMAND) -P CMakeFiles/ossim-space-imaging.dir/cmake_clean.cmake
.PHONY : ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/clean

ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/depend:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vipul/ossim-svn/src/ossim_package_support/cmake /home/vipul/ossim-svn/src/ossim/src/apps/ossim-space-imaging /home/vipul/ossim-svn/src/ossim_package_support/cmake/build /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-space-imaging /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ossim/src/apps/ossim-space-imaging/CMakeFiles/ossim-space-imaging.dir/depend

