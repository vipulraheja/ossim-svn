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
include ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/depend.make

# Include the progress variables for this target.
include ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/progress.make

# Include the compile flags for this target's objects.
include ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/flags.make

ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o: ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/flags.make
ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o: /home/vipul/ossim-svn/src/ossim/src/apps/ossim-img2md/ossim-img2md.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-img2md && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o -c /home/vipul/ossim-svn/src/ossim/src/apps/ossim-img2md/ossim-img2md.cpp

ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-img2md && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/vipul/ossim-svn/src/ossim/src/apps/ossim-img2md/ossim-img2md.cpp > CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.i

ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-img2md && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/vipul/ossim-svn/src/ossim/src/apps/ossim-img2md/ossim-img2md.cpp -o CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.s

ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o.requires:
.PHONY : ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o.requires

ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o.provides: ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o.requires
	$(MAKE) -f ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/build.make ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o.provides.build
.PHONY : ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o.provides

ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o.provides.build: ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o

# Object files for target ossim-img2md
ossim__img2md_OBJECTS = \
"CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o"

# External object files for target ossim-img2md
ossim__img2md_EXTERNAL_OBJECTS =

ossim-img2md: ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o
ossim-img2md: libossim.so.1.8.12
ossim-img2md: /usr/lib/libOpenThreads.so
ossim-img2md: /usr/lib/libjpeg.so
ossim-img2md: /usr/lib/libtiff.so
ossim-img2md: /usr/lib/libgeotiff.so
ossim-img2md: /usr/lib/libOpenThreads.so
ossim-img2md: /usr/lib/libfreetype.so
ossim-img2md: /usr/lib/openmpi/lib/libmpi_cxx.so
ossim-img2md: /usr/lib/openmpi/lib/libmpi.so
ossim-img2md: /usr/lib/openmpi/lib/libopen-rte.so
ossim-img2md: /usr/lib/openmpi/lib/libopen-pal.so
ossim-img2md: /usr/lib/libdl.so
ossim-img2md: /usr/lib/libnsl.so
ossim-img2md: /usr/lib/libutil.so
ossim-img2md: /usr/lib/libm.so
ossim-img2md: /usr/lib/libz.so
ossim-img2md: /usr/lib/libdl.so
ossim-img2md: /usr/lib/libnsl.so
ossim-img2md: /usr/lib/libutil.so
ossim-img2md: /usr/lib/libm.so
ossim-img2md: /usr/lib/libz.so
ossim-img2md: ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/build.make
ossim-img2md: ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../../../ossim-img2md"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-img2md && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ossim-img2md.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/build: ossim-img2md
.PHONY : ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/build

ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/requires: ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/ossim-img2md.cpp.o.requires
.PHONY : ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/requires

ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/clean:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-img2md && $(CMAKE_COMMAND) -P CMakeFiles/ossim-img2md.dir/cmake_clean.cmake
.PHONY : ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/clean

ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/depend:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vipul/ossim-svn/src/ossim_package_support/cmake /home/vipul/ossim-svn/src/ossim/src/apps/ossim-img2md /home/vipul/ossim-svn/src/ossim_package_support/cmake/build /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-img2md /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ossim/src/apps/ossim-img2md/CMakeFiles/ossim-img2md.dir/depend

