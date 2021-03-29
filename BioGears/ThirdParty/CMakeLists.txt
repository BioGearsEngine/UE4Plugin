cmake_minimum_required(VERSION 3.18)

project (BioGears_and_dependencies)

find_package(Git REQUIRED)

include(ExternalProject)


ExternalProject_Add(log4cpp
  GIT_REPOSITORY https://github.com/StevenAWhite/log4cpp.git
  GIT_TAG 4bc7882
  CMAKE_ARGS   -G ${CMAKE_GENERATOR}
               #-A ${CMAKE_GENERATOR_PLATFORM}
               -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}/  
)

ExternalProject_Add(dirent
  GIT_REPOSITORY https://github.com/StevenAWhite/dirent.git
  GIT_TAG 287ba92
  CMAKE_ARGS  -G ${CMAKE_GENERATOR}
              #-A ${CMAKE_GENERATOR_PLATFORM}
              -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}/
)

ExternalProject_Add(xerces-c
  GIT_REPOSITORY https://github.com/apache/xerces-c.git
  GIT_TAG origin/xerces-3.2.2
  CMAKE_ARGS  -G ${CMAKE_GENERATOR}
              #-A ${CMAKE_GENERATOR_PLATFORM}
              -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}/
)

ExternalProject_Add(eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG tags/3.3.9
  CMAKE_ARGS  -G ${CMAKE_GENERATOR}
              #-A ${CMAKE_GENERATOR_PLATFORM}
              -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}/
)

if (WIN32)
  ExternalProject_Add(xsd
    URL https://www.codesynthesis.com/download/xsd/4.0/windows/i686/xsd-4.0.0-i686-windows.zip
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E make_directory  ${CMAKE_INSTALL_PREFIX}/bin/
    COMMAND       ${CMAKE_COMMAND} -E make_directory  ${CMAKE_INSTALL_PREFIX}/include/xsd/
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ../xsd/bin/xsd.exe  ${CMAKE_INSTALL_PREFIX}/bin/
    COMMAND         ${CMAKE_COMMAND} -E copy_directory ../xsd/libxsd/xsd/ ${CMAKE_INSTALL_PREFIX}/include/xsd
  )
elseif( UNIX AND NOT APPLE)
  ExternalProject_Add(xsd
    URL https://www.codesynthesis.com/download/xsd/4.0/linux-gnu/x86_64/xsd-4.0.0-x86_64-linux-gnu.tar.bz2
    CONFIGURE_COMMAND ""
    BUILD_COMMAND ${CMAKE_COMMAND} -E make_directory  ${CMAKE_INSTALL_PREFIX}/bin/
    COMMAND       ${CMAKE_COMMAND} -E make_directory  ${CMAKE_INSTALL_PREFIX}/include/xsd/
    INSTALL_COMMAND ${CMAKE_COMMAND} -E copy ../xsd/bin/xsd  ${CMAKE_INSTALL_PREFIX}/bin/
    COMMAND         ${CMAKE_COMMAND} -E copy_directory ../xsd/libxsd/xsd/ ${CMAKE_INSTALL_PREFIX}/include/xsd
  )
else( )
  #TODO: Add support for non other OS (Apple Brew)
endif()

ExternalProject_Add_StepDependencies(xsd build xerces-c)

ExternalProject_Add(biogears
  GIT_REPOSITORY #ssh://git@sed-stash.us.ara.com:7999/bg/core.git
             https://github.com/BioGearsEngine/core.git
  GIT_TAG 7.3.2
  CMAKE_ARGS
             -G ${CMAKE_GENERATOR}
             #-A ${CMAKE_GENERATOR_PLATFORM}
             -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
             -DBiogears_BUILD_HOWTOS=OFF
             -DBiogears_BUILD_CIRCUIT_TESTS=OFF
             -DBiogears_BUILD_CIRCUIT_PROFILER=OFF
             -DBiogears_BUILD_TEST_DRIVER=OFF
             -DBiogears_BUILD_WEBSITE=OFF
             -DBiogears_BUILD_TOOLS=OFF
             -DBiogears_PLATFORM_PREFIX=${Biogears_PLATFORM_PREFIX}
             -DBiogears_BREAKOUT_INSTALL=ON
             -DCMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}/
             -DCMAKE_PREFIX_PATH=${CMAKE_INSTALL_PREFIX}/
)
ExternalProject_Add_StepDependencies(biogears build log4cpp)
ExternalProject_Add_StepDependencies(biogears build dirent)
ExternalProject_Add_StepDependencies(biogears build xsd)
ExternalProject_Add_StepDependencies(biogears build eigen)