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
include ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/depend.make

# Include the progress variables for this target.
include ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/progress.make

# Include the compile flags for this target's objects.
include ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/flags.make

ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o: ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/flags.make
ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o: /home/vipul/ossim-svn/src/ossim/src/apps/ossim-info/ossim-info.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-info && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ossim-info.dir/ossim-info.cpp.o -c /home/vipul/ossim-svn/src/ossim/src/apps/ossim-info/ossim-info.cpp

ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ossim-info.dir/ossim-info.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-info && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/vipul/ossim-svn/src/ossim/src/apps/ossim-info/ossim-info.cpp > CMakeFiles/ossim-info.dir/ossim-info.cpp.i

ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ossim-info.dir/ossim-info.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-info && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/vipul/ossim-svn/src/ossim/src/apps/ossim-info/ossim-info.cpp -o CMakeFiles/ossim-info.dir/ossim-info.cpp.s

ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o.requires:
.PHONY : ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o.requires

ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o.provides: ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o.requires
	$(MAKE) -f ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/build.make ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o.provides.build
.PHONY : ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o.provides

ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o.provides.build: ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o

# Object files for target ossim-info
ossim__info_OBJECTS = \
"CMakeFiles/ossim-info.dir/ossim-info.cpp.o"

# External object files for target ossim-info
ossim__info_EXTERNAL_OBJECTS =

ossim-info: ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o
ossim-info: libossim.so.1.8.12
ossim-info: /usr/lib/libOpenThreads.so
ossim-info: /usr/lib/libjpeg.so
ossim-info: /usr/lib/libtiff.so
ossim-info: /usr/lib/libgeotiff.so
ossim-info: /usr/lib/libOpenThreads.so
ossim-info: /usr/lib/libfreetype.so
ossim-info: /usr/lib/openmpi/lib/libmpi_cxx.so
ossim-info: /usr/lib/openmpi/lib/libmpi.so
ossim-info: /usr/lib/openmpi/lib/libopen-rte.so
ossim-info: /usr/lib/openmpi/lib/libopen-pal.so
ossim-info: /usr/lib/libdl.so
ossim-info: /usr/lib/libnsl.so
ossim-info: /usr/lib/libutil.so
ossim-info: /usr/lib/libm.so
ossim-info: /usr/lib/libz.so
ossim-info: /usr/lib/libdl.so
ossim-info: /usr/lib/libnsl.so
ossim-info: /usr/lib/libutil.so
ossim-info: /usr/lib/libm.so
ossim-info: /usr/lib/libz.so
ossim-info: ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/build.make
ossim-info: ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../../ossim-info"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-info && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ossim-info.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/build: ossim-info
.PHONY : ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/build

ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/requires: ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/ossim-info.cpp.o.requires
.PHONY : ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/requires

ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/clean:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-info && $(CMAKE_COMMAND) -P CMakeFiles/ossim-info.dir/cmake_clean.cmake
.PHONY : ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/clean

ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/depend:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vipul/ossim-svn/src/ossim_package_support/cmake /home/vipul/ossim-svn/src/ossim/src/apps/ossim-info /home/vipul/ossim-svn/src/ossim_package_support/cmake/build /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-info /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ossim/src/apps/ossim-info/CMakeFiles/ossim-info.dir/depend

