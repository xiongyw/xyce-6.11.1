
# -- process files for this library ------------------------------------------

# class source list
set ( EXT_SOURCES
      ${CMAKE_CURRENT_SOURCE_DIR}/N_DEV_1D_Interface.C 
      ${CMAKE_CURRENT_SOURCE_DIR}/N_DEV_CharonInterface.C 
      ${CMAKE_CURRENT_SOURCE_DIR}/N_DEV_ExternCodeInterface.C 
      ${CMAKE_CURRENT_SOURCE_DIR}/N_DEV_ExternDevice.C 
      ${CMAKE_CURRENT_SOURCE_DIR}/N_DEV_RegisterExternalDevices.C 
      ${CMAKE_CURRENT_SOURCE_DIR}/N_DEV_XyceInterface.C 
      CACHE INTERNAL "X_S" )


# add header files to project
set ( XYCE_INCLUDE_DIRECTORIES ${XYCE_INCLUDE_DIRECTORIES} 
      ${CMAKE_CURRENT_SOURCE_DIR}
      CACHE INTERNAL "X_I" )




# -- build requested libraries -----------------------------------------------
set ( XYCE_PACKAGE_LIBRARIES ${XYCE_PACKAGE_LIBRARIES} 
      EXT 
      CACHE INTERNAL "X_L" )
