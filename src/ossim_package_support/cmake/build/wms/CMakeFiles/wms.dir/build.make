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
include wms/CMakeFiles/wms.dir/depend.make

# Include the progress variables for this target.
include wms/CMakeFiles/wms.dir/progress.make

# Include the compile flags for this target's objects.
include wms/CMakeFiles/wms.dir/flags.make

wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o: /home/vipul/ossim-svn/src/libwms/src/wmsCurlMemoryStream.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/wmsCurlMemoryStream.cpp

wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/wmsCurlMemoryStream.cpp > CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.i

wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/wmsCurlMemoryStream.cpp -o CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.s

wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o.requires

wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o.provides: wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o.provides

wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o

wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o: /home/vipul/ossim-svn/src/libwms/src/wmsMemoryStream.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/wmsMemoryStream.cpp

wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/wmsMemoryStream.cpp > CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.i

wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/wmsMemoryStream.cpp -o CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.s

wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o.requires

wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o.provides: wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o.provides

wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o

wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o: /home/vipul/ossim-svn/src/libwms/src/wmsStyle.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/wmsStyle.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/wmsStyle.cpp

wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/wmsStyle.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/wmsStyle.cpp > CMakeFiles/wms.dir/src/wmsStyle.cpp.i

wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/wmsStyle.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/wmsStyle.cpp -o CMakeFiles/wms.dir/src/wmsStyle.cpp.s

wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o.requires

wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o.provides: wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o.provides

wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o: /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesParser.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesParser.cpp

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesParser.cpp > CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.i

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesParser.cpp -o CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.s

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o.requires

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o.provides: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o.provides

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o

wms/CMakeFiles/wms.dir/src/iso8601.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/iso8601.cpp.o: /home/vipul/ossim-svn/src/libwms/src/iso8601.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/iso8601.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/iso8601.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/iso8601.cpp

wms/CMakeFiles/wms.dir/src/iso8601.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/iso8601.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/iso8601.cpp > CMakeFiles/wms.dir/src/iso8601.cpp.i

wms/CMakeFiles/wms.dir/src/iso8601.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/iso8601.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/iso8601.cpp -o CMakeFiles/wms.dir/src/iso8601.cpp.s

wms/CMakeFiles/wms.dir/src/iso8601.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/iso8601.cpp.o.requires

wms/CMakeFiles/wms.dir/src/iso8601.cpp.o.provides: wms/CMakeFiles/wms.dir/src/iso8601.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/iso8601.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/iso8601.cpp.o.provides

wms/CMakeFiles/wms.dir/src/iso8601.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/iso8601.cpp.o

wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o: /home/vipul/ossim-svn/src/libwms/src/wmsNotify.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/wmsNotify.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/wmsNotify.cpp

wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/wmsNotify.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/wmsNotify.cpp > CMakeFiles/wms.dir/src/wmsNotify.cpp.i

wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/wmsNotify.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/wmsNotify.cpp -o CMakeFiles/wms.dir/src/wmsNotify.cpp.s

wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o.requires

wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o.provides: wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o.provides

wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o: /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesState.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesState.cpp

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesState.cpp > CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.i

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesState.cpp -o CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.s

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o.requires

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o.provides: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o.provides

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o

wms/CMakeFiles/wms.dir/src/wms.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/wms.cpp.o: /home/vipul/ossim-svn/src/libwms/src/wms.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/wms.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/wms.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/wms.cpp

wms/CMakeFiles/wms.dir/src/wms.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/wms.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/wms.cpp > CMakeFiles/wms.dir/src/wms.cpp.i

wms/CMakeFiles/wms.dir/src/wms.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/wms.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/wms.cpp -o CMakeFiles/wms.dir/src/wms.cpp.s

wms/CMakeFiles/wms.dir/src/wms.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/wms.cpp.o.requires

wms/CMakeFiles/wms.dir/src/wms.cpp.o.provides: wms/CMakeFiles/wms.dir/src/wms.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/wms.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/wms.cpp.o.provides

wms/CMakeFiles/wms.dir/src/wms.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/wms.cpp.o

wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o: /home/vipul/ossim-svn/src/libwms/src/wmsClient.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/wmsClient.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/wmsClient.cpp

wms/CMakeFiles/wms.dir/src/wmsClient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/wmsClient.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/wmsClient.cpp > CMakeFiles/wms.dir/src/wmsClient.cpp.i

wms/CMakeFiles/wms.dir/src/wmsClient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/wmsClient.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/wmsClient.cpp -o CMakeFiles/wms.dir/src/wmsClient.cpp.s

wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o.requires

wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o.provides: wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o.provides

wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o

wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o: /home/vipul/ossim-svn/src/libwms/src/wmsUrl.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/wmsUrl.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/wmsUrl.cpp

wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/wmsUrl.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/wmsUrl.cpp > CMakeFiles/wms.dir/src/wmsUrl.cpp.i

wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/wmsUrl.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/wmsUrl.cpp -o CMakeFiles/wms.dir/src/wmsUrl.cpp.s

wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o.requires

wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o.provides: wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o.provides

wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o

wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o: /home/vipul/ossim-svn/src/libwms/src/wmsReferenced.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/wmsReferenced.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/wmsReferenced.cpp

wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/wmsReferenced.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/wmsReferenced.cpp > CMakeFiles/wms.dir/src/wmsReferenced.cpp.i

wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/wmsReferenced.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/wmsReferenced.cpp -o CMakeFiles/wms.dir/src/wmsReferenced.cpp.s

wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o.requires

wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o.provides: wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o.provides

wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o: wms/CMakeFiles/wms.dir/flags.make
wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o: /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesRoot.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -o CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o -c /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesRoot.cpp

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.i"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -E /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesRoot.cpp > CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.i

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.s"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -DWMS_LIBRARY -S /home/vipul/ossim-svn/src/libwms/src/wmsCapabilitiesRoot.cpp -o CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.s

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o.requires:
.PHONY : wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o.requires

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o.provides: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o.requires
	$(MAKE) -f wms/CMakeFiles/wms.dir/build.make wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o.provides.build
.PHONY : wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o.provides

wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o.provides.build: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o

# Object files for target wms
wms_OBJECTS = \
"CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o" \
"CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o" \
"CMakeFiles/wms.dir/src/wmsStyle.cpp.o" \
"CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o" \
"CMakeFiles/wms.dir/src/iso8601.cpp.o" \
"CMakeFiles/wms.dir/src/wmsNotify.cpp.o" \
"CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o" \
"CMakeFiles/wms.dir/src/wms.cpp.o" \
"CMakeFiles/wms.dir/src/wmsClient.cpp.o" \
"CMakeFiles/wms.dir/src/wmsUrl.cpp.o" \
"CMakeFiles/wms.dir/src/wmsReferenced.cpp.o" \
"CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o"

# External object files for target wms
wms_EXTERNAL_OBJECTS =

libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/iso8601.cpp.o
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/wms.cpp.o
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o
libwms.so.1.8.12: /usr/lib/libcurl.so
libwms.so.1.8.12: /usr/lib/libexpat.so
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/build.make
libwms.so.1.8.12: wms/CMakeFiles/wms.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX shared library ../libwms.so"
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wms.dir/link.txt --verbose=$(VERBOSE)
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && $(CMAKE_COMMAND) -E cmake_symlink_library ../libwms.so.1.8.12 ../libwms.so.1 ../libwms.so

libwms.so.1: libwms.so.1.8.12

libwms.so: libwms.so.1.8.12

# Rule to build all files generated by this target.
wms/CMakeFiles/wms.dir/build: libwms.so
.PHONY : wms/CMakeFiles/wms.dir/build

wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/wmsCurlMemoryStream.cpp.o.requires
wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/wmsMemoryStream.cpp.o.requires
wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/wmsStyle.cpp.o.requires
wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesParser.cpp.o.requires
wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/iso8601.cpp.o.requires
wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/wmsNotify.cpp.o.requires
wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesState.cpp.o.requires
wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/wms.cpp.o.requires
wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/wmsClient.cpp.o.requires
wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/wmsUrl.cpp.o.requires
wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/wmsReferenced.cpp.o.requires
wms/CMakeFiles/wms.dir/requires: wms/CMakeFiles/wms.dir/src/wmsCapabilitiesRoot.cpp.o.requires
.PHONY : wms/CMakeFiles/wms.dir/requires

wms/CMakeFiles/wms.dir/clean:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms && $(CMAKE_COMMAND) -P CMakeFiles/wms.dir/cmake_clean.cmake
.PHONY : wms/CMakeFiles/wms.dir/clean

wms/CMakeFiles/wms.dir/depend:
	cd /home/vipul/ossim-svn/src/ossim_package_support/cmake/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vipul/ossim-svn/src/ossim_package_support/cmake /home/vipul/ossim-svn/src/libwms /home/vipul/ossim-svn/src/ossim_package_support/cmake/build /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms /home/vipul/ossim-svn/src/ossim_package_support/cmake/build/wms/CMakeFiles/wms.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : wms/CMakeFiles/wms.dir/depend

