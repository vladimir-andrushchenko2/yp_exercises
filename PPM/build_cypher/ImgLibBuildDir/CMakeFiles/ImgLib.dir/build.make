# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.20.0/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.20.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/vladi/Desktop/workdir/yp_exercises/PPM/Cypher

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher

# Include any dependencies generated for this target.
include ImgLibBuildDir/CMakeFiles/ImgLib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include ImgLibBuildDir/CMakeFiles/ImgLib.dir/compiler_depend.make

# Include the progress variables for this target.
include ImgLibBuildDir/CMakeFiles/ImgLib.dir/progress.make

# Include the compile flags for this target's objects.
include ImgLibBuildDir/CMakeFiles/ImgLib.dir/flags.make

ImgLibBuildDir/CMakeFiles/ImgLib.dir/img_lib.cpp.o: ImgLibBuildDir/CMakeFiles/ImgLib.dir/flags.make
ImgLibBuildDir/CMakeFiles/ImgLib.dir/img_lib.cpp.o: /Users/vladi/Desktop/workdir/yp_exercises/PPM/ImgLib/img_lib.cpp
ImgLibBuildDir/CMakeFiles/ImgLib.dir/img_lib.cpp.o: ImgLibBuildDir/CMakeFiles/ImgLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ImgLibBuildDir/CMakeFiles/ImgLib.dir/img_lib.cpp.o"
	cd /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/ImgLibBuildDir && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ImgLibBuildDir/CMakeFiles/ImgLib.dir/img_lib.cpp.o -MF CMakeFiles/ImgLib.dir/img_lib.cpp.o.d -o CMakeFiles/ImgLib.dir/img_lib.cpp.o -c /Users/vladi/Desktop/workdir/yp_exercises/PPM/ImgLib/img_lib.cpp

ImgLibBuildDir/CMakeFiles/ImgLib.dir/img_lib.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ImgLib.dir/img_lib.cpp.i"
	cd /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/ImgLibBuildDir && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vladi/Desktop/workdir/yp_exercises/PPM/ImgLib/img_lib.cpp > CMakeFiles/ImgLib.dir/img_lib.cpp.i

ImgLibBuildDir/CMakeFiles/ImgLib.dir/img_lib.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ImgLib.dir/img_lib.cpp.s"
	cd /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/ImgLibBuildDir && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vladi/Desktop/workdir/yp_exercises/PPM/ImgLib/img_lib.cpp -o CMakeFiles/ImgLib.dir/img_lib.cpp.s

ImgLibBuildDir/CMakeFiles/ImgLib.dir/ppm_image.cpp.o: ImgLibBuildDir/CMakeFiles/ImgLib.dir/flags.make
ImgLibBuildDir/CMakeFiles/ImgLib.dir/ppm_image.cpp.o: /Users/vladi/Desktop/workdir/yp_exercises/PPM/ImgLib/ppm_image.cpp
ImgLibBuildDir/CMakeFiles/ImgLib.dir/ppm_image.cpp.o: ImgLibBuildDir/CMakeFiles/ImgLib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object ImgLibBuildDir/CMakeFiles/ImgLib.dir/ppm_image.cpp.o"
	cd /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/ImgLibBuildDir && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT ImgLibBuildDir/CMakeFiles/ImgLib.dir/ppm_image.cpp.o -MF CMakeFiles/ImgLib.dir/ppm_image.cpp.o.d -o CMakeFiles/ImgLib.dir/ppm_image.cpp.o -c /Users/vladi/Desktop/workdir/yp_exercises/PPM/ImgLib/ppm_image.cpp

ImgLibBuildDir/CMakeFiles/ImgLib.dir/ppm_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ImgLib.dir/ppm_image.cpp.i"
	cd /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/ImgLibBuildDir && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/vladi/Desktop/workdir/yp_exercises/PPM/ImgLib/ppm_image.cpp > CMakeFiles/ImgLib.dir/ppm_image.cpp.i

ImgLibBuildDir/CMakeFiles/ImgLib.dir/ppm_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ImgLib.dir/ppm_image.cpp.s"
	cd /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/ImgLibBuildDir && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/vladi/Desktop/workdir/yp_exercises/PPM/ImgLib/ppm_image.cpp -o CMakeFiles/ImgLib.dir/ppm_image.cpp.s

# Object files for target ImgLib
ImgLib_OBJECTS = \
"CMakeFiles/ImgLib.dir/img_lib.cpp.o" \
"CMakeFiles/ImgLib.dir/ppm_image.cpp.o"

# External object files for target ImgLib
ImgLib_EXTERNAL_OBJECTS =

ImgLibBuildDir/libImgLib.a: ImgLibBuildDir/CMakeFiles/ImgLib.dir/img_lib.cpp.o
ImgLibBuildDir/libImgLib.a: ImgLibBuildDir/CMakeFiles/ImgLib.dir/ppm_image.cpp.o
ImgLibBuildDir/libImgLib.a: ImgLibBuildDir/CMakeFiles/ImgLib.dir/build.make
ImgLibBuildDir/libImgLib.a: ImgLibBuildDir/CMakeFiles/ImgLib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libImgLib.a"
	cd /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/ImgLibBuildDir && $(CMAKE_COMMAND) -P CMakeFiles/ImgLib.dir/cmake_clean_target.cmake
	cd /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/ImgLibBuildDir && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ImgLib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
ImgLibBuildDir/CMakeFiles/ImgLib.dir/build: ImgLibBuildDir/libImgLib.a
.PHONY : ImgLibBuildDir/CMakeFiles/ImgLib.dir/build

ImgLibBuildDir/CMakeFiles/ImgLib.dir/clean:
	cd /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/ImgLibBuildDir && $(CMAKE_COMMAND) -P CMakeFiles/ImgLib.dir/cmake_clean.cmake
.PHONY : ImgLibBuildDir/CMakeFiles/ImgLib.dir/clean

ImgLibBuildDir/CMakeFiles/ImgLib.dir/depend:
	cd /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/vladi/Desktop/workdir/yp_exercises/PPM/Cypher /Users/vladi/Desktop/workdir/yp_exercises/PPM/ImgLib /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/ImgLibBuildDir /Users/vladi/Desktop/workdir/yp_exercises/PPM/build_cypher/ImgLibBuildDir/CMakeFiles/ImgLib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : ImgLibBuildDir/CMakeFiles/ImgLib.dir/depend

