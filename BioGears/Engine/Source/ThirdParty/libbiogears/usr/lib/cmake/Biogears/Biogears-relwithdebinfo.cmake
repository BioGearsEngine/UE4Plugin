#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Biogears::libbiogears_common" for configuration "RelWithDebInfo"
set_property(TARGET Biogears::libbiogears_common APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(Biogears::libbiogears_common PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib//RelWithDebInfo/libbiogears_common_st.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Biogears::libbiogears_common )
list(APPEND _IMPORT_CHECK_FILES_FOR_Biogears::libbiogears_common "${_IMPORT_PREFIX}/lib//RelWithDebInfo/libbiogears_common_st.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
