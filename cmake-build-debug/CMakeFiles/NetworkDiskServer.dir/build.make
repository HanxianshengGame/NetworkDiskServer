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
CMAKE_SOURCE_DIR = /home/handling/NetworkDiskServer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/handling/NetworkDiskServer/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/NetworkDiskServer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/NetworkDiskServer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/NetworkDiskServer.dir/flags.make

CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o: CMakeFiles/NetworkDiskServer.dir/flags.make
CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o: ../source/ChildThreadWork.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/handling/NetworkDiskServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o   -c /home/handling/NetworkDiskServer/source/ChildThreadWork.c

CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/handling/NetworkDiskServer/source/ChildThreadWork.c > CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.i

CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/handling/NetworkDiskServer/source/ChildThreadWork.c -o CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.s

CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o.requires:

.PHONY : CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o.requires

CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o.provides: CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o.requires
	$(MAKE) -f CMakeFiles/NetworkDiskServer.dir/build.make CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o.provides.build
.PHONY : CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o.provides

CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o.provides.build: CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o


CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o: CMakeFiles/NetworkDiskServer.dir/flags.make
CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o: ../source/DataBaseWork.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/handling/NetworkDiskServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o   -c /home/handling/NetworkDiskServer/source/DataBaseWork.c

CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/handling/NetworkDiskServer/source/DataBaseWork.c > CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.i

CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/handling/NetworkDiskServer/source/DataBaseWork.c -o CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.s

CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o.requires:

.PHONY : CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o.requires

CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o.provides: CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o.requires
	$(MAKE) -f CMakeFiles/NetworkDiskServer.dir/build.make CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o.provides.build
.PHONY : CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o.provides

CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o.provides.build: CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o


CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o: CMakeFiles/NetworkDiskServer.dir/flags.make
CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o: ../source/Epoll.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/handling/NetworkDiskServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o   -c /home/handling/NetworkDiskServer/source/Epoll.c

CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/handling/NetworkDiskServer/source/Epoll.c > CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.i

CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/handling/NetworkDiskServer/source/Epoll.c -o CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.s

CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o.requires:

.PHONY : CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o.requires

CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o.provides: CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o.requires
	$(MAKE) -f CMakeFiles/NetworkDiskServer.dir/build.make CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o.provides.build
.PHONY : CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o.provides

CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o.provides.build: CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o


CMakeFiles/NetworkDiskServer.dir/source/main.c.o: CMakeFiles/NetworkDiskServer.dir/flags.make
CMakeFiles/NetworkDiskServer.dir/source/main.c.o: ../source/main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/handling/NetworkDiskServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/NetworkDiskServer.dir/source/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NetworkDiskServer.dir/source/main.c.o   -c /home/handling/NetworkDiskServer/source/main.c

CMakeFiles/NetworkDiskServer.dir/source/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NetworkDiskServer.dir/source/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/handling/NetworkDiskServer/source/main.c > CMakeFiles/NetworkDiskServer.dir/source/main.c.i

CMakeFiles/NetworkDiskServer.dir/source/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NetworkDiskServer.dir/source/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/handling/NetworkDiskServer/source/main.c -o CMakeFiles/NetworkDiskServer.dir/source/main.c.s

CMakeFiles/NetworkDiskServer.dir/source/main.c.o.requires:

.PHONY : CMakeFiles/NetworkDiskServer.dir/source/main.c.o.requires

CMakeFiles/NetworkDiskServer.dir/source/main.c.o.provides: CMakeFiles/NetworkDiskServer.dir/source/main.c.o.requires
	$(MAKE) -f CMakeFiles/NetworkDiskServer.dir/build.make CMakeFiles/NetworkDiskServer.dir/source/main.c.o.provides.build
.PHONY : CMakeFiles/NetworkDiskServer.dir/source/main.c.o.provides

CMakeFiles/NetworkDiskServer.dir/source/main.c.o.provides.build: CMakeFiles/NetworkDiskServer.dir/source/main.c.o


CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o: CMakeFiles/NetworkDiskServer.dir/flags.make
CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o: ../source/MessageProtocol.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/handling/NetworkDiskServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o   -c /home/handling/NetworkDiskServer/source/MessageProtocol.c

CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/handling/NetworkDiskServer/source/MessageProtocol.c > CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.i

CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/handling/NetworkDiskServer/source/MessageProtocol.c -o CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.s

CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o.requires:

.PHONY : CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o.requires

CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o.provides: CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o.requires
	$(MAKE) -f CMakeFiles/NetworkDiskServer.dir/build.make CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o.provides.build
.PHONY : CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o.provides

CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o.provides.build: CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o


CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o: CMakeFiles/NetworkDiskServer.dir/flags.make
CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o: ../source/MyLog.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/handling/NetworkDiskServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building C object CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o   -c /home/handling/NetworkDiskServer/source/MyLog.c

CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/handling/NetworkDiskServer/source/MyLog.c > CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.i

CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/handling/NetworkDiskServer/source/MyLog.c -o CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.s

CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o.requires:

.PHONY : CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o.requires

CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o.provides: CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o.requires
	$(MAKE) -f CMakeFiles/NetworkDiskServer.dir/build.make CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o.provides.build
.PHONY : CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o.provides

CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o.provides.build: CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o


CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o: CMakeFiles/NetworkDiskServer.dir/flags.make
CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o: ../source/TaskQueue.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/handling/NetworkDiskServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building C object CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o   -c /home/handling/NetworkDiskServer/source/TaskQueue.c

CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/handling/NetworkDiskServer/source/TaskQueue.c > CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.i

CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/handling/NetworkDiskServer/source/TaskQueue.c -o CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.s

CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o.requires:

.PHONY : CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o.requires

CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o.provides: CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o.requires
	$(MAKE) -f CMakeFiles/NetworkDiskServer.dir/build.make CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o.provides.build
.PHONY : CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o.provides

CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o.provides.build: CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o


CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o: CMakeFiles/NetworkDiskServer.dir/flags.make
CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o: ../source/TCPServer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/handling/NetworkDiskServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building C object CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o   -c /home/handling/NetworkDiskServer/source/TCPServer.c

CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/handling/NetworkDiskServer/source/TCPServer.c > CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.i

CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/handling/NetworkDiskServer/source/TCPServer.c -o CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.s

CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o.requires:

.PHONY : CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o.requires

CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o.provides: CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o.requires
	$(MAKE) -f CMakeFiles/NetworkDiskServer.dir/build.make CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o.provides.build
.PHONY : CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o.provides

CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o.provides.build: CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o


# Object files for target NetworkDiskServer
NetworkDiskServer_OBJECTS = \
"CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o" \
"CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o" \
"CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o" \
"CMakeFiles/NetworkDiskServer.dir/source/main.c.o" \
"CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o" \
"CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o" \
"CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o" \
"CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o"

# External object files for target NetworkDiskServer
NetworkDiskServer_EXTERNAL_OBJECTS =

NetworkDiskServer: CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o
NetworkDiskServer: CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o
NetworkDiskServer: CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o
NetworkDiskServer: CMakeFiles/NetworkDiskServer.dir/source/main.c.o
NetworkDiskServer: CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o
NetworkDiskServer: CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o
NetworkDiskServer: CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o
NetworkDiskServer: CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o
NetworkDiskServer: CMakeFiles/NetworkDiskServer.dir/build.make
NetworkDiskServer: CMakeFiles/NetworkDiskServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/handling/NetworkDiskServer/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking C executable NetworkDiskServer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/NetworkDiskServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/NetworkDiskServer.dir/build: NetworkDiskServer

.PHONY : CMakeFiles/NetworkDiskServer.dir/build

CMakeFiles/NetworkDiskServer.dir/requires: CMakeFiles/NetworkDiskServer.dir/source/ChildThreadWork.c.o.requires
CMakeFiles/NetworkDiskServer.dir/requires: CMakeFiles/NetworkDiskServer.dir/source/DataBaseWork.c.o.requires
CMakeFiles/NetworkDiskServer.dir/requires: CMakeFiles/NetworkDiskServer.dir/source/Epoll.c.o.requires
CMakeFiles/NetworkDiskServer.dir/requires: CMakeFiles/NetworkDiskServer.dir/source/main.c.o.requires
CMakeFiles/NetworkDiskServer.dir/requires: CMakeFiles/NetworkDiskServer.dir/source/MessageProtocol.c.o.requires
CMakeFiles/NetworkDiskServer.dir/requires: CMakeFiles/NetworkDiskServer.dir/source/MyLog.c.o.requires
CMakeFiles/NetworkDiskServer.dir/requires: CMakeFiles/NetworkDiskServer.dir/source/TaskQueue.c.o.requires
CMakeFiles/NetworkDiskServer.dir/requires: CMakeFiles/NetworkDiskServer.dir/source/TCPServer.c.o.requires

.PHONY : CMakeFiles/NetworkDiskServer.dir/requires

CMakeFiles/NetworkDiskServer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/NetworkDiskServer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/NetworkDiskServer.dir/clean

CMakeFiles/NetworkDiskServer.dir/depend:
	cd /home/handling/NetworkDiskServer/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/handling/NetworkDiskServer /home/handling/NetworkDiskServer /home/handling/NetworkDiskServer/cmake-build-debug /home/handling/NetworkDiskServer/cmake-build-debug /home/handling/NetworkDiskServer/cmake-build-debug/CMakeFiles/NetworkDiskServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/NetworkDiskServer.dir/depend

