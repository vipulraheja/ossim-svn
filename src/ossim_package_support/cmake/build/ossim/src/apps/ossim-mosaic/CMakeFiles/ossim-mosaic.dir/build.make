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
include ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/depend.make

# Include the progress variables for this target.
include ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/progress.make

# Include the compile flags for this target's objects.
include ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/flags.make

ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o: ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/flags.make
ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o: /home/vipul/ossim-svn/src/ossim/src/apps/ossim-mosaic/ossim-mosaic.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-mosaic && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o -c /home/vipul/ossim-svn/src/ossim/src/apps/ossim-mosaic/ossim-mosaic.cpp

ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-mosaic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/vipul/ossim-svn/src/ossim/src/apps/ossim-mosaic/ossim-mosaic.cpp > CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.i

ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-mosaic && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/vipul/ossim-svn/src/ossim/src/apps/ossim-mosaic/ossim-mosaic.cpp -o CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.s

ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o.requires:
.PHONY : ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o.requires

ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o.provides: ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o.requires
	$(MAKE) -f ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/build.make ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o.provides.build
.PHONY : ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o.provides

ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o.provides.build: ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o

# Object files for target ossim-mosaic
ossim__mosaic_OBJECTS = \
"CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o"

# External object files for target ossim-mosaic
ossim__mosaic_EXTERNAL_OBJECTS =

ossim-mosaic: ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o
ossim-mosaic: libossim.so.1.8.12
ossim-mosaic: /usr/lib/libOpenThreads.so
ossim-mosaic: /usr/lib/libjpeg.so
ossim-mosaic: /usr/lib/libtiff.so
ossim-mosaic: /usr/lib/libgeotiff.so
ossim-mosaic: /usr/lib/libOpenThreads.so
ossim-mosaic: /usr/lib/libfreetype.so
ossim-mosaic: /usr/lib/openmpi/lib/libmpi_cxx.so
ossim-mosaic: /usr/lib/openmpi/lib/libmpi.so
ossim-mosaic: /usr/lib/openmpi/lib/libopen-rte.so
ossim-mosaic: /usr/lib/openmpi/lib/libopen-pal.so
ossim-mosaic: /usr/lib/libdl.so
ossim-mosaic: /usr/lib/libnsl.so
ossim-mosaic: /usr/lib/libutil.so
ossim-mosaic: /usr/lib/libm.so
ossim-mosaic: /usr/lib/libz.so
ossim-mosaic: /usr/lib/libdl.so
ossim-mosaic: /usr/lib/libnsl.so
ossim-mosaic: /usr/lib/libutil.so
ossim-mosaic: /usr/lib/libm.so
ossim-mosaic: /usr/lib/libz.so
ossim-mosaic: ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/build.make
ossim-mosaic: ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../../ossim-mosaic"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-mosaic && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ossim-mosaic.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/build: ossim-mosaic
.PHONY : ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/build

ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/requires: ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/ossim-mosaic.cpp.o.requires
.PHONY : ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/requires

ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/clean:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-mosaic && $(CMAKE_COMMAND) -P CMakeFiles/ossim-mosaic.dir/cmake_clean.cmake
.PHONY : ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/clean

ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/depend:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vipul/ossim-svn/src/ossim_package_support/cmake /home/vipul/ossim-svn/src/ossim/src/apps/ossim-mosaic /home/vipul/ossim-svn/src/ossim_package_support/cmake/build /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-mosaic /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ossim/src/apps/ossim-mosaic/CMakeFiles/ossim-mosaic.dir/depend

