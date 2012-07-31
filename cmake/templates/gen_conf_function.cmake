@VAR_HEADERS_TXT@

foreach( HDR_SET ${HEADERS} )

  list( GET ${HDR_SET} 0 GEN_DIR )
  list( GET ${HDR_SET} 1 GEN_INCLUDE )
  list( GET ${HDR_SET} 2 GEN_FILE )

  set( VAR_HEADER_INCLUDES ${GEN_INCLUDE}/${GEN_FILE} )

  message( "------------------------------------------------------------" )
  message( "TEMPLATE LOC:    ${TEMPLATE_LOC}" )
  message( "DST Path:        ${GEN_DIR}/${GEN_FILE}" )
  message( "INC:             ${VAR_HEADER_INCLUDES}" )
  message( "------------------------------------------------------------" )


#  execute_process( COMMAND ${CMAKE_COMMAND} -E make_directory ${GEN_DIR} )
#  configure_file(
#    ${TEMPLATE_LOC}
#    ${GEN_DIR}/${GEN_FILE}
#    @ONLY
#  )

endforeach()
