# the name of the target operating system
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR "armv8-a")
# which compilers to use for C and C++
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc-7)
set(CMAKE_C_FLAGS "-march=armv8-a+simd  --std=c11 -fPIC")
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++-7)
set(CMAKE_CXX_FLAGS "-march=armv8-a+simd  --std=c++14 -fPIC")

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
