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
include ossimPlanet/CMakeFiles/ossimplanettest.dir/depend.make

# Include the progress variables for this target.
include ossimPlanet/CMakeFiles/ossimplanettest.dir/progress.make

# Include the compile flags for this target's objects.
include ossimPlanet/CMakeFiles/ossimplanettest.dir/flags.make

ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o: ossimPlanet/CMakeFiles/ossimplanettest.dir/flags.make
ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o: /home/vipul/ossim-svn/src/ossimPlanet/examples/ossimplanettest/ossimplanettest.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimPlanet && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o -c /home/vipul/ossim-svn/src/ossimPlanet/examples/ossimplanettest/ossimplanettest.cpp

ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimPlanet && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/vipul/ossim-svn/src/ossimPlanet/examples/ossimplanettest/ossimplanettest.cpp > CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.i

ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimPlanet && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/vipul/ossim-svn/src/ossimPlanet/examples/ossimplanettest/ossimplanettest.cpp -o CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.s

ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o.requires:
.PHONY : ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o.requires

ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o.provides: ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o.requires
	$(MAKE) -f ossimPlanet/CMakeFiles/ossimplanettest.dir/build.make ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o.provides.build
.PHONY : ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o.provides

ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o.provides.build: ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o

# Object files for target ossimplanettest
ossimplanettest_OBJECTS = \
"CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o"

# External object files for target ossimplanettest
ossimplanettest_EXTERNAL_OBJECTS =

ossimplanettest: ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o
ossimplanettest: libossimPlanet.so.1.8.12
ossimplanettest: libossimPredator.so.1.8.12
ossimplanettest: /usr/lib/libswscale.so
ossimplanettest: libossim.so.1.8.12
ossimplanettest: /usr/lib/libtiff.so
ossimplanettest: /usr/lib/libgeotiff.so
ossimplanettest: /usr/lib/libfreetype.so
ossimplanettest: /usr/lib/openmpi/lib/libmpi_cxx.so
ossimplanettest: /usr/lib/openmpi/lib/libmpi.so
ossimplanettest: /usr/lib/openmpi/lib/libopen-rte.so
ossimplanettest: /usr/lib/openmpi/lib/libopen-pal.so
ossimplanettest: /usr/lib/libdl.so
ossimplanettest: /usr/lib/libnsl.so
ossimplanettest: /usr/lib/libutil.so
ossimplanettest: /usr/lib/libm.so
ossimplanettest: /usr/lib/libdl.so
ossimplanettest: /usr/lib/libnsl.so
ossimplanettest: /usr/lib/libutil.so
ossimplanettest: /usr/lib/libm.so
ossimplanettest: /usr/lib/libosgViewer.so
ossimplanettest: /usr/lib/libosgDB.so
ossimplanettest: /usr/lib/libosgGA.so
ossimplanettest: /usr/lib/libosgText.so
ossimplanettest: /usr/lib/libosgUtil.so
ossimplanettest: /usr/lib/libosg.so
ossimplanettest: /usr/lib/libOpenThreads.so
ossimplanettest: /usr/lib/libjpeg.so
ossimplanettest: libwms.so.1.8.12
ossimplanettest: /usr/lib/libcurl.so
ossimplanettest: /usr/lib/libexpat.so
ossimplanettest: /usr/local/lib/libgpstk.so
ossimplanettest: /usr/lib/libz.so
ossimplanettest: /usr/lib/libGLU.so
ossimplanettest: /usr/lib/libGL.so
ossimplanettest: /usr/lib/libSM.so
ossimplanettest: /usr/lib/libICE.so
ossimplanettest: /usr/lib/libX11.so
ossimplanettest: /usr/lib/libXext.so
ossimplanettest: /usr/lib/libavformat.so
ossimplanettest: /usr/lib/libavdevice.so
ossimplanettest: /usr/lib/libavcodec.so
ossimplanettest: /usr/lib/libavutil.so
ossimplanettest: ossimPlanet/CMakeFiles/ossimplanettest.dir/build.make
ossimplanettest: ossimPlanet/CMakeFiles/ossimplanettest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../ossimplanettest"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimPlanet && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ossimplanettest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ossimPlanet/CMakeFiles/ossimplanettest.dir/build: ossimplanettest
.PHONY : ossimPlanet/CMakeFiles/ossimplanettest.dir/build

ossimPlanet/CMakeFiles/ossimplanettest.dir/requires: ossimPlanet/CMakeFiles/ossimplanettest.dir/examples/ossimplanettest/ossimplanettest.cpp.o.requires
.PHONY : ossimPlanet/CMakeFiles/ossimplanettest.dir/requires

ossimPlanet/CMakeFiles/ossimplanettest.dir/clean:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimPlanet && $(CMAKE_COMMAND) -P CMakeFiles/ossimplanettest.dir/cmake_clean.cmake
.PHONY : ossimPlanet/CMakeFiles/ossimplanettest.dir/clean

ossimPlanet/CMakeFiles/ossimplanettest.dir/depend:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vipul/ossim-svn/src/ossim_package_support/cmake /home/vipul/ossim-svn/src/ossimPlanet /home/vipul/ossim-svn/src/ossim_package_support/cmake/build /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimPlanet /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimPlanet/CMakeFiles/ossimplanettest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ossimPlanet/CMakeFiles/ossimplanettest.dir/depend

