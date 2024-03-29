# the name of the target operating system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR "armv7-a")
# which compilers to use for C and C++
set(CMAKE_C_COMPILER arm-linux-gnueabihf-gcc-7)
set(CMAKE_C_FLAGS "-march=armv7-a")# -mfpu=neon-vfpv4 --std=c11 -fPIC")
set(CMAKE_CXX_COMPILER arm-linux-gnueabihf-g++-7)
set(CMAKE_CXX_FLAGS "-march=armv7-a")#-mfpu=neon-vfpv4 --std=c++14 -fPIC")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
