# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/steve/Downloads/GTechFinal

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/steve/Downloads/GTechFinal/build

# Include any dependencies generated for this target.
include CMakeFiles/gametechp2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/gametechp2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/gametechp2.dir/flags.make

CMakeFiles/gametechp2.dir/Actor.cpp.o: CMakeFiles/gametechp2.dir/flags.make
CMakeFiles/gametechp2.dir/Actor.cpp.o: ../Actor.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/steve/Downloads/GTechFinal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/gametechp2.dir/Actor.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gametechp2.dir/Actor.cpp.o -c /home/steve/Downloads/GTechFinal/Actor.cpp

CMakeFiles/gametechp2.dir/Actor.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gametechp2.dir/Actor.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/steve/Downloads/GTechFinal/Actor.cpp > CMakeFiles/gametechp2.dir/Actor.cpp.i

CMakeFiles/gametechp2.dir/Actor.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gametechp2.dir/Actor.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/steve/Downloads/GTechFinal/Actor.cpp -o CMakeFiles/gametechp2.dir/Actor.cpp.s

CMakeFiles/gametechp2.dir/Actor.cpp.o.requires:

.PHONY : CMakeFiles/gametechp2.dir/Actor.cpp.o.requires

CMakeFiles/gametechp2.dir/Actor.cpp.o.provides: CMakeFiles/gametechp2.dir/Actor.cpp.o.requires
	$(MAKE) -f CMakeFiles/gametechp2.dir/build.make CMakeFiles/gametechp2.dir/Actor.cpp.o.provides.build
.PHONY : CMakeFiles/gametechp2.dir/Actor.cpp.o.provides

CMakeFiles/gametechp2.dir/Actor.cpp.o.provides.build: CMakeFiles/gametechp2.dir/Actor.cpp.o


CMakeFiles/gametechp2.dir/DebugDraw.cpp.o: CMakeFiles/gametechp2.dir/flags.make
CMakeFiles/gametechp2.dir/DebugDraw.cpp.o: ../DebugDraw.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/steve/Downloads/GTechFinal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/gametechp2.dir/DebugDraw.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gametechp2.dir/DebugDraw.cpp.o -c /home/steve/Downloads/GTechFinal/DebugDraw.cpp

CMakeFiles/gametechp2.dir/DebugDraw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gametechp2.dir/DebugDraw.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/steve/Downloads/GTechFinal/DebugDraw.cpp > CMakeFiles/gametechp2.dir/DebugDraw.cpp.i

CMakeFiles/gametechp2.dir/DebugDraw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gametechp2.dir/DebugDraw.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/steve/Downloads/GTechFinal/DebugDraw.cpp -o CMakeFiles/gametechp2.dir/DebugDraw.cpp.s

CMakeFiles/gametechp2.dir/DebugDraw.cpp.o.requires:

.PHONY : CMakeFiles/gametechp2.dir/DebugDraw.cpp.o.requires

CMakeFiles/gametechp2.dir/DebugDraw.cpp.o.provides: CMakeFiles/gametechp2.dir/DebugDraw.cpp.o.requires
	$(MAKE) -f CMakeFiles/gametechp2.dir/build.make CMakeFiles/gametechp2.dir/DebugDraw.cpp.o.provides.build
.PHONY : CMakeFiles/gametechp2.dir/DebugDraw.cpp.o.provides

CMakeFiles/gametechp2.dir/DebugDraw.cpp.o.provides.build: CMakeFiles/gametechp2.dir/DebugDraw.cpp.o


CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o: CMakeFiles/gametechp2.dir/flags.make
CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o: ../DynamicLineDrawer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/steve/Downloads/GTechFinal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o -c /home/steve/Downloads/GTechFinal/DynamicLineDrawer.cpp

CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/steve/Downloads/GTechFinal/DynamicLineDrawer.cpp > CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.i

CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/steve/Downloads/GTechFinal/DynamicLineDrawer.cpp -o CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.s

CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o.requires:

.PHONY : CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o.requires

CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o.provides: CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o.requires
	$(MAKE) -f CMakeFiles/gametechp2.dir/build.make CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o.provides.build
.PHONY : CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o.provides

CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o.provides.build: CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o


CMakeFiles/gametechp2.dir/Game.cpp.o: CMakeFiles/gametechp2.dir/flags.make
CMakeFiles/gametechp2.dir/Game.cpp.o: ../Game.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/steve/Downloads/GTechFinal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/gametechp2.dir/Game.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gametechp2.dir/Game.cpp.o -c /home/steve/Downloads/GTechFinal/Game.cpp

CMakeFiles/gametechp2.dir/Game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gametechp2.dir/Game.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/steve/Downloads/GTechFinal/Game.cpp > CMakeFiles/gametechp2.dir/Game.cpp.i

CMakeFiles/gametechp2.dir/Game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gametechp2.dir/Game.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/steve/Downloads/GTechFinal/Game.cpp -o CMakeFiles/gametechp2.dir/Game.cpp.s

CMakeFiles/gametechp2.dir/Game.cpp.o.requires:

.PHONY : CMakeFiles/gametechp2.dir/Game.cpp.o.requires

CMakeFiles/gametechp2.dir/Game.cpp.o.provides: CMakeFiles/gametechp2.dir/Game.cpp.o.requires
	$(MAKE) -f CMakeFiles/gametechp2.dir/build.make CMakeFiles/gametechp2.dir/Game.cpp.o.provides.build
.PHONY : CMakeFiles/gametechp2.dir/Game.cpp.o.provides

CMakeFiles/gametechp2.dir/Game.cpp.o.provides.build: CMakeFiles/gametechp2.dir/Game.cpp.o


CMakeFiles/gametechp2.dir/audio.c.o: CMakeFiles/gametechp2.dir/flags.make
CMakeFiles/gametechp2.dir/audio.c.o: ../audio.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/steve/Downloads/GTechFinal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/gametechp2.dir/audio.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/gametechp2.dir/audio.c.o   -c /home/steve/Downloads/GTechFinal/audio.c

CMakeFiles/gametechp2.dir/audio.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/gametechp2.dir/audio.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/steve/Downloads/GTechFinal/audio.c > CMakeFiles/gametechp2.dir/audio.c.i

CMakeFiles/gametechp2.dir/audio.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/gametechp2.dir/audio.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/steve/Downloads/GTechFinal/audio.c -o CMakeFiles/gametechp2.dir/audio.c.s

CMakeFiles/gametechp2.dir/audio.c.o.requires:

.PHONY : CMakeFiles/gametechp2.dir/audio.c.o.requires

CMakeFiles/gametechp2.dir/audio.c.o.provides: CMakeFiles/gametechp2.dir/audio.c.o.requires
	$(MAKE) -f CMakeFiles/gametechp2.dir/build.make CMakeFiles/gametechp2.dir/audio.c.o.provides.build
.PHONY : CMakeFiles/gametechp2.dir/audio.c.o.provides

CMakeFiles/gametechp2.dir/audio.c.o.provides.build: CMakeFiles/gametechp2.dir/audio.c.o


CMakeFiles/gametechp2.dir/gui.cc.o: CMakeFiles/gametechp2.dir/flags.make
CMakeFiles/gametechp2.dir/gui.cc.o: ../gui.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/steve/Downloads/GTechFinal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/gametechp2.dir/gui.cc.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gametechp2.dir/gui.cc.o -c /home/steve/Downloads/GTechFinal/gui.cc

CMakeFiles/gametechp2.dir/gui.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gametechp2.dir/gui.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/steve/Downloads/GTechFinal/gui.cc > CMakeFiles/gametechp2.dir/gui.cc.i

CMakeFiles/gametechp2.dir/gui.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gametechp2.dir/gui.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/steve/Downloads/GTechFinal/gui.cc -o CMakeFiles/gametechp2.dir/gui.cc.s

CMakeFiles/gametechp2.dir/gui.cc.o.requires:

.PHONY : CMakeFiles/gametechp2.dir/gui.cc.o.requires

CMakeFiles/gametechp2.dir/gui.cc.o.provides: CMakeFiles/gametechp2.dir/gui.cc.o.requires
	$(MAKE) -f CMakeFiles/gametechp2.dir/build.make CMakeFiles/gametechp2.dir/gui.cc.o.provides.build
.PHONY : CMakeFiles/gametechp2.dir/gui.cc.o.provides

CMakeFiles/gametechp2.dir/gui.cc.o.provides.build: CMakeFiles/gametechp2.dir/gui.cc.o


CMakeFiles/gametechp2.dir/physics.cpp.o: CMakeFiles/gametechp2.dir/flags.make
CMakeFiles/gametechp2.dir/physics.cpp.o: ../physics.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/steve/Downloads/GTechFinal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/gametechp2.dir/physics.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gametechp2.dir/physics.cpp.o -c /home/steve/Downloads/GTechFinal/physics.cpp

CMakeFiles/gametechp2.dir/physics.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gametechp2.dir/physics.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/steve/Downloads/GTechFinal/physics.cpp > CMakeFiles/gametechp2.dir/physics.cpp.i

CMakeFiles/gametechp2.dir/physics.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gametechp2.dir/physics.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/steve/Downloads/GTechFinal/physics.cpp -o CMakeFiles/gametechp2.dir/physics.cpp.s

CMakeFiles/gametechp2.dir/physics.cpp.o.requires:

.PHONY : CMakeFiles/gametechp2.dir/physics.cpp.o.requires

CMakeFiles/gametechp2.dir/physics.cpp.o.provides: CMakeFiles/gametechp2.dir/physics.cpp.o.requires
	$(MAKE) -f CMakeFiles/gametechp2.dir/build.make CMakeFiles/gametechp2.dir/physics.cpp.o.provides.build
.PHONY : CMakeFiles/gametechp2.dir/physics.cpp.o.provides

CMakeFiles/gametechp2.dir/physics.cpp.o.provides.build: CMakeFiles/gametechp2.dir/physics.cpp.o


CMakeFiles/gametechp2.dir/state.cpp.o: CMakeFiles/gametechp2.dir/flags.make
CMakeFiles/gametechp2.dir/state.cpp.o: ../state.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/steve/Downloads/GTechFinal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/gametechp2.dir/state.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gametechp2.dir/state.cpp.o -c /home/steve/Downloads/GTechFinal/state.cpp

CMakeFiles/gametechp2.dir/state.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gametechp2.dir/state.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/steve/Downloads/GTechFinal/state.cpp > CMakeFiles/gametechp2.dir/state.cpp.i

CMakeFiles/gametechp2.dir/state.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gametechp2.dir/state.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/steve/Downloads/GTechFinal/state.cpp -o CMakeFiles/gametechp2.dir/state.cpp.s

CMakeFiles/gametechp2.dir/state.cpp.o.requires:

.PHONY : CMakeFiles/gametechp2.dir/state.cpp.o.requires

CMakeFiles/gametechp2.dir/state.cpp.o.provides: CMakeFiles/gametechp2.dir/state.cpp.o.requires
	$(MAKE) -f CMakeFiles/gametechp2.dir/build.make CMakeFiles/gametechp2.dir/state.cpp.o.provides.build
.PHONY : CMakeFiles/gametechp2.dir/state.cpp.o.provides

CMakeFiles/gametechp2.dir/state.cpp.o.provides.build: CMakeFiles/gametechp2.dir/state.cpp.o


# Object files for target gametechp2
gametechp2_OBJECTS = \
"CMakeFiles/gametechp2.dir/Actor.cpp.o" \
"CMakeFiles/gametechp2.dir/DebugDraw.cpp.o" \
"CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o" \
"CMakeFiles/gametechp2.dir/Game.cpp.o" \
"CMakeFiles/gametechp2.dir/audio.c.o" \
"CMakeFiles/gametechp2.dir/gui.cc.o" \
"CMakeFiles/gametechp2.dir/physics.cpp.o" \
"CMakeFiles/gametechp2.dir/state.cpp.o"

# External object files for target gametechp2
gametechp2_EXTERNAL_OBJECTS =

gametechp2: CMakeFiles/gametechp2.dir/Actor.cpp.o
gametechp2: CMakeFiles/gametechp2.dir/DebugDraw.cpp.o
gametechp2: CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o
gametechp2: CMakeFiles/gametechp2.dir/Game.cpp.o
gametechp2: CMakeFiles/gametechp2.dir/audio.c.o
gametechp2: CMakeFiles/gametechp2.dir/gui.cc.o
gametechp2: CMakeFiles/gametechp2.dir/physics.cpp.o
gametechp2: CMakeFiles/gametechp2.dir/state.cpp.o
gametechp2: CMakeFiles/gametechp2.dir/build.make
gametechp2: /usr/local/lib/libBulletDynamics.a
gametechp2: /usr/local/lib/libBulletCollision.a
gametechp2: /usr/local/lib/libLinearMath.a
gametechp2: /usr/local/lib/libBulletSoftBody.a
gametechp2: libOgreImgui.a
gametechp2: /usr/local/lib/libOgreBites.so.1.11.2
gametechp2: /usr/local/lib/libOgreHLMS.so.1.11.2
gametechp2: /usr/local/lib/libOgreMeshLodGenerator.so.1.11.2
gametechp2: /usr/local/lib/libOgreOverlay.so.1.11.2
gametechp2: /usr/local/lib/libOgreProperty.so.1.11.2
gametechp2: /usr/local/lib/libOgreRTShaderSystem.so.1.11.2
gametechp2: /usr/local/lib/libOgreTerrain.so.1.11.2
gametechp2: /usr/local/lib/libOgrePaging.so.1.11.2
gametechp2: /usr/local/lib/libOgreVolume.so.1.11.2
gametechp2: /usr/local/lib/libOgreMain.so.1.11.2
gametechp2: /usr/local/lib/libfreetype.so
gametechp2: CMakeFiles/gametechp2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/steve/Downloads/GTechFinal/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable gametechp2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gametechp2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/gametechp2.dir/build: gametechp2

.PHONY : CMakeFiles/gametechp2.dir/build

CMakeFiles/gametechp2.dir/requires: CMakeFiles/gametechp2.dir/Actor.cpp.o.requires
CMakeFiles/gametechp2.dir/requires: CMakeFiles/gametechp2.dir/DebugDraw.cpp.o.requires
CMakeFiles/gametechp2.dir/requires: CMakeFiles/gametechp2.dir/DynamicLineDrawer.cpp.o.requires
CMakeFiles/gametechp2.dir/requires: CMakeFiles/gametechp2.dir/Game.cpp.o.requires
CMakeFiles/gametechp2.dir/requires: CMakeFiles/gametechp2.dir/audio.c.o.requires
CMakeFiles/gametechp2.dir/requires: CMakeFiles/gametechp2.dir/gui.cc.o.requires
CMakeFiles/gametechp2.dir/requires: CMakeFiles/gametechp2.dir/physics.cpp.o.requires
CMakeFiles/gametechp2.dir/requires: CMakeFiles/gametechp2.dir/state.cpp.o.requires

.PHONY : CMakeFiles/gametechp2.dir/requires

CMakeFiles/gametechp2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/gametechp2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/gametechp2.dir/clean

CMakeFiles/gametechp2.dir/depend:
	cd /home/steve/Downloads/GTechFinal/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/steve/Downloads/GTechFinal /home/steve/Downloads/GTechFinal /home/steve/Downloads/GTechFinal/build /home/steve/Downloads/GTechFinal/build /home/steve/Downloads/GTechFinal/build/CMakeFiles/gametechp2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/gametechp2.dir/depend

