#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Biogears::libbiogears_common" for configuration "Release"
set_property(TARGET Biogears::libbiogears_common APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Biogears::libbiogears_common PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/msvc15/Release/libbiogears_common_st.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Biogears::libbiogears_common )
list(APPEND _IMPORT_CHECK_FILES_FOR_Biogears::libbiogears_common "${_IMPORT_PREFIX}/lib/msvc15/Release/libbiogears_common_st.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
