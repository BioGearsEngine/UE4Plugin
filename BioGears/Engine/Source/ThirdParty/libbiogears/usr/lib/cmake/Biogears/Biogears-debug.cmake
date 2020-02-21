#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Biogears::libbiogears_common" for configuration "Debug"
set_property(TARGET Biogears::libbiogears_common APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Biogears::libbiogears_common PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libbiogears_common_d_st.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS Biogears::libbiogears_common )
list(APPEND _IMPORT_CHECK_FILES_FOR_Biogears::libbiogears_common "${_IMPORT_PREFIX}/lib/libbiogears_common_d_st.lib" )

# Import target "Biogears::libbiogears_cdm" for configuration "Debug"
set_property(TARGET Biogears::libbiogears_cdm APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Biogears::libbiogears_cdm PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/biogears_cdm_d.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/libbiogears_cdm_d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Biogears::libbiogears_cdm )
list(APPEND _IMPORT_CHECK_FILES_FOR_Biogears::libbiogears_cdm "${_IMPORT_PREFIX}/lib/biogears_cdm_d.lib" "${_IMPORT_PREFIX}/bin/libbiogears_cdm_d.dll" )

# Import target "Biogears::libbiogears" for configuration "Debug"
set_property(TARGET Biogears::libbiogears APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(Biogears::libbiogears PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/biogears_d.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/libbiogears_d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS Biogears::libbiogears )
list(APPEND _IMPORT_CHECK_FILES_FOR_Biogears::libbiogears "${_IMPORT_PREFIX}/lib/biogears_d.lib" "${_IMPORT_PREFIX}/bin/libbiogears_d.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
