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
include ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/depend.make

# Include the progress variables for this target.
include ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/progress.make

# Include the compile flags for this target's objects.
include ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/flags.make

ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o: ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/flags.make
ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o: /home/vipul/ossim-svn/src/ossim/src/apps/ossim-btoa/ossim-btoa.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-btoa && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o -c /home/vipul/ossim-svn/src/ossim/src/apps/ossim-btoa/ossim-btoa.cpp

ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-btoa && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/vipul/ossim-svn/src/ossim/src/apps/ossim-btoa/ossim-btoa.cpp > CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.i

ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-btoa && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/vipul/ossim-svn/src/ossim/src/apps/ossim-btoa/ossim-btoa.cpp -o CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.s

ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o.requires:
.PHONY : ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o.requires

ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o.provides: ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o.requires
	$(MAKE) -f ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/build.make ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o.provides.build
.PHONY : ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o.provides

ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o.provides.build: ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o

# Object files for target ossim-btoa
ossim__btoa_OBJECTS = \
"CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o"

# External object files for target ossim-btoa
ossim__btoa_EXTERNAL_OBJECTS =

ossim-btoa: ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o
ossim-btoa: libossim.so.1.8.12
ossim-btoa: /usr/lib/libOpenThreads.so
ossim-btoa: /usr/lib/libjpeg.so
ossim-btoa: /usr/lib/libtiff.so
ossim-btoa: /usr/lib/libgeotiff.so
ossim-btoa: /usr/lib/libOpenThreads.so
ossim-btoa: /usr/lib/libfreetype.so
ossim-btoa: /usr/lib/openmpi/lib/libmpi_cxx.so
ossim-btoa: /usr/lib/openmpi/lib/libmpi.so
ossim-btoa: /usr/lib/openmpi/lib/libopen-rte.so
ossim-btoa: /usr/lib/openmpi/lib/libopen-pal.so
ossim-btoa: /usr/lib/libdl.so
ossim-btoa: /usr/lib/libnsl.so
ossim-btoa: /usr/lib/libutil.so
ossim-btoa: /usr/lib/libm.so
ossim-btoa: /usr/lib/libz.so
ossim-btoa: /usr/lib/libdl.so
ossim-btoa: /usr/lib/libnsl.so
ossim-btoa: /usr/lib/libutil.so
ossim-btoa: /usr/lib/libm.so
ossim-btoa: /usr/lib/libz.so
ossim-btoa: ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/build.make
ossim-btoa: ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../../ossim-btoa"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-btoa && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ossim-btoa.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/build: ossim-btoa
.PHONY : ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/build

ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/requires: ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/ossim-btoa.cpp.o.requires
.PHONY : ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/requires

ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/clean:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-btoa && $(CMAKE_COMMAND) -P CMakeFiles/ossim-btoa.dir/cmake_clean.cmake
.PHONY : ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/clean

ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/depend:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vipul/ossim-svn/src/ossim_package_support/cmake /home/vipul/ossim-svn/src/ossim/src/apps/ossim-btoa /home/vipul/ossim-svn/src/ossim_package_support/cmake/build /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-btoa /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ossim/src/apps/ossim-btoa/CMakeFiles/ossim-btoa.dir/depend

