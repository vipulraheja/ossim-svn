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
include ossimQt4/CMakeFiles/iview.dir/depend.make

# Include the progress variables for this target.
include ossimQt4/CMakeFiles/iview.dir/progress.make

# Include the compile flags for this target's objects.
include ossimQt4/CMakeFiles/iview.dir/flags.make

ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o: ossimQt4/CMakeFiles/iview.dir/flags.make
ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o: /home/vipul/ossim-svn/src/ossim_qt4/apps/iview/iview.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4 && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/iview.dir/apps/iview/iview.cpp.o -c /home/vipul/ossim-svn/src/ossim_qt4/apps/iview/iview.cpp

ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/iview.dir/apps/iview/iview.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/vipul/ossim-svn/src/ossim_qt4/apps/iview/iview.cpp > CMakeFiles/iview.dir/apps/iview/iview.cpp.i

ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/iview.dir/apps/iview/iview.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/vipul/ossim-svn/src/ossim_qt4/apps/iview/iview.cpp -o CMakeFiles/iview.dir/apps/iview/iview.cpp.s

ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o.requires:
.PHONY : ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o.requires

ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o.provides: ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o.requires
	$(MAKE) -f ossimQt4/CMakeFiles/iview.dir/build.make ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o.provides.build
.PHONY : ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o.provides

ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o.provides.build: ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o

ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o: ossimQt4/CMakeFiles/iview.dir/flags.make
ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o: ossimQt4/qrc_app.cxx
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4 && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/iview.dir/qrc_app.cxx.o -c /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4/qrc_app.cxx

ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/iview.dir/qrc_app.cxx.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4/qrc_app.cxx > CMakeFiles/iview.dir/qrc_app.cxx.i

ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/iview.dir/qrc_app.cxx.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4 && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4/qrc_app.cxx -o CMakeFiles/iview.dir/qrc_app.cxx.s

ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o.requires:
.PHONY : ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o.requires

ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o.provides: ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o.requires
	$(MAKE) -f ossimQt4/CMakeFiles/iview.dir/build.make ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o.provides.build
.PHONY : ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o.provides

ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o.provides.build: ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o

ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/ImageLinkerSplash.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/Splash.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/alignbottom.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/alignleft.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/alignright.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/aligntop.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/connection.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/dataextract.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/datastore.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/display.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/editcopy.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/editcut.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/editpaste.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/filenew.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/fileopen.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/filesave.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/fingerup.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/histogram.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/iviewsplash.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/print.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/redo.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/resetproperty.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/searchfind.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/tilecascade.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/undo.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/zoom.png
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/../images/pan.png
ossimQt4/qrc_app.cxx: ossimQt4/apps/app.qrc.depends
ossimQt4/qrc_app.cxx: /home/vipul/ossim-svn/src/ossim_qt4/apps/app.qrc
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating qrc_app.cxx"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4 && /usr/bin/rcc -name app -o /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4/qrc_app.cxx /home/vipul/ossim-svn/src/ossim_qt4/apps/app.qrc

# Object files for target iview
iview_OBJECTS = \
"CMakeFiles/iview.dir/apps/iview/iview.cpp.o" \
"CMakeFiles/iview.dir/qrc_app.cxx.o"

# External object files for target iview
iview_EXTERNAL_OBJECTS =

iview: ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o
iview: ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o
iview: libossimQt.so.1.8.12
iview: libossim.so.1.8.12
iview: /usr/lib/libgeotiff.so
iview: /usr/lib/libfreetype.so
iview: /usr/lib/openmpi/lib/libmpi_cxx.so
iview: /usr/lib/openmpi/lib/libmpi.so
iview: /usr/lib/openmpi/lib/libopen-rte.so
iview: /usr/lib/openmpi/lib/libopen-pal.so
iview: /usr/lib/libdl.so
iview: /usr/lib/libnsl.so
iview: /usr/lib/libutil.so
iview: /usr/lib/libm.so
iview: /usr/lib/libdl.so
iview: /usr/lib/libnsl.so
iview: /usr/lib/libutil.so
iview: /usr/lib/libm.so
iview: /usr/lib/libosg.so
iview: /usr/lib/libOpenThreads.so
iview: /usr/lib/libjpeg.so
iview: /usr/lib/libz.so
iview: /usr/lib/libQt3Support.so
iview: /usr/lib/libQtGui.so
iview: /usr/lib/libQtXml.so
iview: /usr/lib/libQtSql.so
iview: /usr/lib/libQtNetwork.so
iview: /usr/lib/libQtCore.so
iview: /usr/lib/libtiff.so
iview: ossimQt4/CMakeFiles/iview.dir/build.make
iview: ossimQt4/CMakeFiles/iview.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../iview"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/iview.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ossimQt4/CMakeFiles/iview.dir/build: iview
.PHONY : ossimQt4/CMakeFiles/iview.dir/build

ossimQt4/CMakeFiles/iview.dir/requires: ossimQt4/CMakeFiles/iview.dir/apps/iview/iview.cpp.o.requires
ossimQt4/CMakeFiles/iview.dir/requires: ossimQt4/CMakeFiles/iview.dir/qrc_app.cxx.o.requires
.PHONY : ossimQt4/CMakeFiles/iview.dir/requires

ossimQt4/CMakeFiles/iview.dir/clean:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4 && $(CMAKE_COMMAND) -P CMakeFiles/iview.dir/cmake_clean.cmake
.PHONY : ossimQt4/CMakeFiles/iview.dir/clean

ossimQt4/CMakeFiles/iview.dir/depend: ossimQt4/qrc_app.cxx
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vipul/ossim-svn/src/ossim_package_support/cmake /home/vipul/ossim-svn/src/ossim_qt4 /home/vipul/ossim-svn/src/ossim_package_support/cmake/build /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4 /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/ossimQt4/CMakeFiles/iview.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ossimQt4/CMakeFiles/iview.dir/depend

