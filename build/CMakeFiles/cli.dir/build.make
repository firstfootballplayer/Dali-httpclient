# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/zjm/clientproj

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/zjm/clientproj/build

# Include any dependencies generated for this target.
include CMakeFiles/cli.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cli.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cli.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cli.dir/flags.make

CMakeFiles/cli.dir/src/Connector.cc.o: CMakeFiles/cli.dir/flags.make
CMakeFiles/cli.dir/src/Connector.cc.o: ../src/Connector.cc
CMakeFiles/cli.dir/src/Connector.cc.o: CMakeFiles/cli.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjm/clientproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cli.dir/src/Connector.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cli.dir/src/Connector.cc.o -MF CMakeFiles/cli.dir/src/Connector.cc.o.d -o CMakeFiles/cli.dir/src/Connector.cc.o -c /home/zjm/clientproj/src/Connector.cc

CMakeFiles/cli.dir/src/Connector.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cli.dir/src/Connector.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjm/clientproj/src/Connector.cc > CMakeFiles/cli.dir/src/Connector.cc.i

CMakeFiles/cli.dir/src/Connector.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cli.dir/src/Connector.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjm/clientproj/src/Connector.cc -o CMakeFiles/cli.dir/src/Connector.cc.s

CMakeFiles/cli.dir/src/HttpClient.cc.o: CMakeFiles/cli.dir/flags.make
CMakeFiles/cli.dir/src/HttpClient.cc.o: ../src/HttpClient.cc
CMakeFiles/cli.dir/src/HttpClient.cc.o: CMakeFiles/cli.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjm/clientproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cli.dir/src/HttpClient.cc.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cli.dir/src/HttpClient.cc.o -MF CMakeFiles/cli.dir/src/HttpClient.cc.o.d -o CMakeFiles/cli.dir/src/HttpClient.cc.o -c /home/zjm/clientproj/src/HttpClient.cc

CMakeFiles/cli.dir/src/HttpClient.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cli.dir/src/HttpClient.cc.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjm/clientproj/src/HttpClient.cc > CMakeFiles/cli.dir/src/HttpClient.cc.i

CMakeFiles/cli.dir/src/HttpClient.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cli.dir/src/HttpClient.cc.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjm/clientproj/src/HttpClient.cc -o CMakeFiles/cli.dir/src/HttpClient.cc.s

CMakeFiles/cli.dir/src/MyXml.cpp.o: CMakeFiles/cli.dir/flags.make
CMakeFiles/cli.dir/src/MyXml.cpp.o: ../src/MyXml.cpp
CMakeFiles/cli.dir/src/MyXml.cpp.o: CMakeFiles/cli.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjm/clientproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cli.dir/src/MyXml.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cli.dir/src/MyXml.cpp.o -MF CMakeFiles/cli.dir/src/MyXml.cpp.o.d -o CMakeFiles/cli.dir/src/MyXml.cpp.o -c /home/zjm/clientproj/src/MyXml.cpp

CMakeFiles/cli.dir/src/MyXml.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cli.dir/src/MyXml.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjm/clientproj/src/MyXml.cpp > CMakeFiles/cli.dir/src/MyXml.cpp.i

CMakeFiles/cli.dir/src/MyXml.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cli.dir/src/MyXml.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjm/clientproj/src/MyXml.cpp -o CMakeFiles/cli.dir/src/MyXml.cpp.s

CMakeFiles/cli.dir/src/Utilities.cpp.o: CMakeFiles/cli.dir/flags.make
CMakeFiles/cli.dir/src/Utilities.cpp.o: ../src/Utilities.cpp
CMakeFiles/cli.dir/src/Utilities.cpp.o: CMakeFiles/cli.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjm/clientproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cli.dir/src/Utilities.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cli.dir/src/Utilities.cpp.o -MF CMakeFiles/cli.dir/src/Utilities.cpp.o.d -o CMakeFiles/cli.dir/src/Utilities.cpp.o -c /home/zjm/clientproj/src/Utilities.cpp

CMakeFiles/cli.dir/src/Utilities.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cli.dir/src/Utilities.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjm/clientproj/src/Utilities.cpp > CMakeFiles/cli.dir/src/Utilities.cpp.i

CMakeFiles/cli.dir/src/Utilities.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cli.dir/src/Utilities.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjm/clientproj/src/Utilities.cpp -o CMakeFiles/cli.dir/src/Utilities.cpp.s

CMakeFiles/cli.dir/src/main.cpp.o: CMakeFiles/cli.dir/flags.make
CMakeFiles/cli.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/cli.dir/src/main.cpp.o: CMakeFiles/cli.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjm/clientproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/cli.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cli.dir/src/main.cpp.o -MF CMakeFiles/cli.dir/src/main.cpp.o.d -o CMakeFiles/cli.dir/src/main.cpp.o -c /home/zjm/clientproj/src/main.cpp

CMakeFiles/cli.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cli.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjm/clientproj/src/main.cpp > CMakeFiles/cli.dir/src/main.cpp.i

CMakeFiles/cli.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cli.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjm/clientproj/src/main.cpp -o CMakeFiles/cli.dir/src/main.cpp.s

CMakeFiles/cli.dir/src/managesql.cpp.o: CMakeFiles/cli.dir/flags.make
CMakeFiles/cli.dir/src/managesql.cpp.o: ../src/managesql.cpp
CMakeFiles/cli.dir/src/managesql.cpp.o: CMakeFiles/cli.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjm/clientproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/cli.dir/src/managesql.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cli.dir/src/managesql.cpp.o -MF CMakeFiles/cli.dir/src/managesql.cpp.o.d -o CMakeFiles/cli.dir/src/managesql.cpp.o -c /home/zjm/clientproj/src/managesql.cpp

CMakeFiles/cli.dir/src/managesql.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cli.dir/src/managesql.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjm/clientproj/src/managesql.cpp > CMakeFiles/cli.dir/src/managesql.cpp.i

CMakeFiles/cli.dir/src/managesql.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cli.dir/src/managesql.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjm/clientproj/src/managesql.cpp -o CMakeFiles/cli.dir/src/managesql.cpp.s

CMakeFiles/cli.dir/src/myHttpclient.cpp.o: CMakeFiles/cli.dir/flags.make
CMakeFiles/cli.dir/src/myHttpclient.cpp.o: ../src/myHttpclient.cpp
CMakeFiles/cli.dir/src/myHttpclient.cpp.o: CMakeFiles/cli.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjm/clientproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/cli.dir/src/myHttpclient.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cli.dir/src/myHttpclient.cpp.o -MF CMakeFiles/cli.dir/src/myHttpclient.cpp.o.d -o CMakeFiles/cli.dir/src/myHttpclient.cpp.o -c /home/zjm/clientproj/src/myHttpclient.cpp

CMakeFiles/cli.dir/src/myHttpclient.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cli.dir/src/myHttpclient.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjm/clientproj/src/myHttpclient.cpp > CMakeFiles/cli.dir/src/myHttpclient.cpp.i

CMakeFiles/cli.dir/src/myHttpclient.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cli.dir/src/myHttpclient.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjm/clientproj/src/myHttpclient.cpp -o CMakeFiles/cli.dir/src/myHttpclient.cpp.s

CMakeFiles/cli.dir/src/tinyxml2.cpp.o: CMakeFiles/cli.dir/flags.make
CMakeFiles/cli.dir/src/tinyxml2.cpp.o: ../src/tinyxml2.cpp
CMakeFiles/cli.dir/src/tinyxml2.cpp.o: CMakeFiles/cli.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/zjm/clientproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/cli.dir/src/tinyxml2.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cli.dir/src/tinyxml2.cpp.o -MF CMakeFiles/cli.dir/src/tinyxml2.cpp.o.d -o CMakeFiles/cli.dir/src/tinyxml2.cpp.o -c /home/zjm/clientproj/src/tinyxml2.cpp

CMakeFiles/cli.dir/src/tinyxml2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/cli.dir/src/tinyxml2.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/zjm/clientproj/src/tinyxml2.cpp > CMakeFiles/cli.dir/src/tinyxml2.cpp.i

CMakeFiles/cli.dir/src/tinyxml2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/cli.dir/src/tinyxml2.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/zjm/clientproj/src/tinyxml2.cpp -o CMakeFiles/cli.dir/src/tinyxml2.cpp.s

# Object files for target cli
cli_OBJECTS = \
"CMakeFiles/cli.dir/src/Connector.cc.o" \
"CMakeFiles/cli.dir/src/HttpClient.cc.o" \
"CMakeFiles/cli.dir/src/MyXml.cpp.o" \
"CMakeFiles/cli.dir/src/Utilities.cpp.o" \
"CMakeFiles/cli.dir/src/main.cpp.o" \
"CMakeFiles/cli.dir/src/managesql.cpp.o" \
"CMakeFiles/cli.dir/src/myHttpclient.cpp.o" \
"CMakeFiles/cli.dir/src/tinyxml2.cpp.o"

# External object files for target cli
cli_EXTERNAL_OBJECTS =

../bin/cli: CMakeFiles/cli.dir/src/Connector.cc.o
../bin/cli: CMakeFiles/cli.dir/src/HttpClient.cc.o
../bin/cli: CMakeFiles/cli.dir/src/MyXml.cpp.o
../bin/cli: CMakeFiles/cli.dir/src/Utilities.cpp.o
../bin/cli: CMakeFiles/cli.dir/src/main.cpp.o
../bin/cli: CMakeFiles/cli.dir/src/managesql.cpp.o
../bin/cli: CMakeFiles/cli.dir/src/myHttpclient.cpp.o
../bin/cli: CMakeFiles/cli.dir/src/tinyxml2.cpp.o
../bin/cli: CMakeFiles/cli.dir/build.make
../bin/cli: /usr/lib/x86_64-linux-gnu/libcurl.so
../bin/cli: /usr/lib/x86_64-linux-gnu/libmysqlclient.so
../bin/cli: /usr/lib/x86_64-linux-gnu/libpthread.so
../bin/cli: src/base/liblibmevent_base.so
../bin/cli: src/net/liblibmevent_net.so
../bin/cli: /usr/lib/x86_64-linux-gnu/libpthread.so
../bin/cli: CMakeFiles/cli.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/zjm/clientproj/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable ../bin/cli"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cli.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cli.dir/build: ../bin/cli
.PHONY : CMakeFiles/cli.dir/build

CMakeFiles/cli.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cli.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cli.dir/clean

CMakeFiles/cli.dir/depend:
	cd /home/zjm/clientproj/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/zjm/clientproj /home/zjm/clientproj /home/zjm/clientproj/build /home/zjm/clientproj/build /home/zjm/clientproj/build/CMakeFiles/cli.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cli.dir/depend
