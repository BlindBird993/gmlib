
API_PATH_STR = doc/API/doxygen

  ############################################
  # Create Developer API Doxygen Documentation
doxDev:
	@- $(ECHO) "Generating Developer API documentation"
	@- $(MKDIR) -p $(API_PATH_STR)/developer
	@- $(DOXYGEN) DoxyfileDevAPI
	@- $(ECHO) "Documentation Generated :)"

  #######################################
  # Create User API Doxygen Documentation
doxUsr:
	@- $(ECHO) "Generating User API Documentation"
	@- $(MKDIR) -p $(API_PATH_STR)/user
	@- $(DOXYGEN) DoxyfileUsrAPI
	@- $(ECHO) "Documentation Generated :)"
