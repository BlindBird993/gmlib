###################################################################################
##
## Copyright (C) 1994 Narvik University College
## Contact: GMlib Online Portal at http://episteme.hin.no
##
## This file is part of the Geometric Modeling Library, GMlib.
##
## GMlib is free software: you can redistribute it and/or modify
## it under the terms of the GNU Lesser General Public License as published by
## the Free Software Foundation, either version 3 of the License, or
## (at your option) any later version.
##
## GMlib is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU Lesser General Public License for more details.
##
## You should have received a copy of the GNU Lesser General Public License
## along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
##
###################################################################################


###############################
# Include the local config file
###############################
-include makeconf.mak

#######################################
# Set config OK, and test loaded config
#######################################
CONFIG_OK = true

# Compile Env
ifeq "$(COMPILE_ENV)" ""
  CONFIG_OK = false
  CONFIG_ERROR += Compile Evironment not set (COMPILE_ENV)! \n
endif

# Project Type Specifics
ifeq "$(PROJECTTYPE)" "lib"
  # Header requirement
  ifeq "$(HEADERS)" ""
    CONFIG_OK = false
    CONFIG_ERROR += No headers Specified (HEADERS)! \n
  endif
else
  ifeq "$(PROJECTTYPE)" "exe"
    # Source requirement
    ifeq "$(SOURCES)" ""
      CONFIG_OK = false
      CONFIG_ERROR += No Sources Specified (SOURCES)! \n
    endif
  else
    ifeq "$(PROJECTTYPE)" ""
      CONFIG_OK = false
      CONFIG_ERROR += Project Type not specified (PROJECTTYPE)! \n
    else
      CONFIG_OK = false
      CONFIG_ERROR += Project Type not supported (PROJECTYPE = '$(PROJECTTYPE)')!
    endif
  endif
endif


# MISC ^^
ifneq "$(CONFIG_OK)" "true"
  CONFIG_ERROR += \n
endif

############################
# Project
############################

####################
# Name (a-z A-Z 0-9 _-)
ifeq "$(PROJECTNAME)" ""
  PROJECTNAME = Unnamed Project
endif

################
# Type (lib | exe)
ifeq "$(PROJECTTYPE)" ""
  PROJECTTYPE = exe
endif



###############################
# Environment Spesific Settings
###############################

#############################
# Linux Environment (default)
ifeq "$(COMPILE_ENV)" "linux"

  ##########
  # Echo CMD
  ECHO = echo

  #########
  # Doxygen
  DOXYGEN = doxygen

  ##########
  # Date str
  DATESTR = `date +%Y%m%d_%H%M`

  ##########
  # Copy CMD
  CP = cp -r

  ############
  # Delete CMD
  RM = rm -rf

  ####################
  # Make Directory CMD
  MKDIR = mkdir

  ######################
  # Change Directory CMD
  CD = cd

else
  ifeq "$(COMPILE_ENV)" "win32"

    ##########
    # Echo CMD
    ECHO = echo

    #########
    # Doxygen
    DOXYGEN = doxygen.exe

    ##########
    # Date str
    DATESTR = `date +%Y%m%d_%H%M`

    ##########
    # Copy CMD
    CP = cp -r

    ############
    # Delete CMD
    RM = rm -rf

    ####################
    # Make Directory CMD
    MKDIR = mkdir

    ######################
    # Change Directory CMD
    CD = cd

  else
    CONFIG_OK = false
    CONFIG_ERROR += Wrong Compile Env. (COMPILE_ENV = '$(COMPILE_ENV)')!
  endif
endif



##############
# Applications
##############

############
# C Compiler
ifeq "$(CC)" ""
  CC = gcc
endif

ifeq "$(CFLAGS)" ""
  CFLAGS = -g -Wall -c
endif

##############
# C++ Compiler
ifeq "$(CXX)" ""
  CXX = $(CC)
endif

ifeq "$(CXXFLAGS)" ""
  CXXFLAGS =$(CFLAGS)
endif

###############
# Object Linker
ifeq "$(LD)" ""
  LD = $(CXX)
endif

ifeq "$(LDFLAGS)" ""
  LDFLAGS = -g -Wall
endif

##################
# Library Compiler
ifeq "$(LSTAT)" ""
  LSTAT = ar
endif

ifeq "$(LSTATFLAGS)" ""
  LSTATFLAGS = -rvcs
endif

#########################
# Qt Meta Object Compiler
ifeq "$(MOC)" ""
  MOC = moc
endif

#####################
# Stream Editor (sed)
SED = sed

######
# Vars
######
ifeq "$(SOURCETMPFILES)" ""
  SOURCETMPFILES = *.cc~ *.hh~ *.cpp~ Makefile~ *.save
endif


######
# Dirs
######
DIR_SRC = src
DIR_DEP = dep
DIR_OBJ = obj
DIR_MOC = moc

DIR_WORK = work
DIR_WORK_DEP = ${DIR_WORK}/${DIR_DEP}
DIR_WORK_OBJ = ${DIR_WORK}/${DIR_OBJ}
DIR_WORK_MOC = ${DIR_WORK}/${DIR_MOC}

DIR_DIST = dist
DIR_DIST_BIN = $(DIR_DIST)/bin
DIR_DIST_INC = $(DIR_DIST)/include
DIR_DIST_LIB = $(DIR_DIST)/lib


######################
# Archiver
ifeq "$(ARCHIVER)" "tar_gzip"
  # tar and gzip
  ARCHIVECMD = tar
  ARCHIVEFLAGS = -czf
  ARCHIVESUFFIX = .tar.gz
else
  # Default ( tar and bzip
  ARCHIVECMD = tar
  ARCHIVEFLAGS = -cjf
  ARCHIVESUFFIX = .tar.bz2
endif

ARCHIVECMDSTR = $(ARCHIVECMD) $(ARCHIVEFLAGS) $(DIR_DIST)/$(PROJECTNAME)_$(DATESTR)$(ARCHIVESUFFIX) $(DIR_DIST)/$(PROJECTNAME)


###############################################################
#          Test Whether the config has been accepted          #
###############################################################
ifeq "$(CONFIG_OK)" "true"

  ########
  # Macros
  ########

  #MOC_H_DIR_PREFIX := $(addprefix $(DIR_SRC)/, $(MOC))
  #MOCS := $(MOC:.h=_MOC.cpp)
  #MOCS_DIR_PREFIX := $(addprefix $(DIR_MOC)/, $(MOC:.h=_MOC.cpp))
  #OBJECTS_MOC := $(addprefix $(DIR_OBJ)/, $(MOCS:.cpp=.o))


  ##################
  # Make sourcelists
  SOURCES_DIR_PREFIX := $(addprefix $(DIR_SRC)/, $(SOURCES))
  HEADERS_DIR_PREFIX := $(addprefix $(DIR_SRC)/, $(HEADERS))
  HEADER_EXTS_DIR_PREFIX := $(addprefix $(DIR_SRC)/, $(HEADER_EXTS))
  OBJECTS := $(addprefix $(DIR_WORK_OBJ)/, $(SOURCES:.cpp=.o))
  DEPS := $(addprefix $(DIR_WORK_DEP)/, $(SOURCES:.cpp=.d))


  ##########################
  # Handle the Moc Step (QT)
  ifneq "$(HEADER_MOCS)" ""
    MOCS := $(addprefix $(DIR_WORK_MOC)/, $(HEADER_MOCS:.h=_MOC.cpp))
    OBJECTS_MOC := $(addprefix $(DIR_WORK_OBJ)/, $(HEADER_MOCS:.h=_MOC.o))
  endif


  #######
  # Rules
  #######

.PHONY: all clean doc maintainer-clean srcclean dep lib exe dist help help_config


  ####################
  # Make All (default)
  ifeq "$(PROJECTTYPE)" "lib"

    # Default if library
all:  $(OBJECTS) $(MOCS) lib
	@- $(ECHO) "Make Complete! ^^"

  else
    ifeq "$(PROJECTTYPE)" "exe"

      # Default if executable
all:  $(OBJECTS) $(MOCS) exe
	@- $(ECHO) "Make Complete! ^^"

    else

      # Default if nothing specified (dummy) :P
all:  $(OBJECTS) $(MOCS)
	@- $(ECHO) "Make Complete! ^^"

    endif
  endif

  #######
  # Clean
clean:
	@- $(ECHO) "Cleaning Work Dir"
	@- if [ -e $(DIR_WORK) ]; then $(RM) $(DIR_WORK); fi;

  ########################
  # Document using doxygen
doc:
	@- $(ECHO) "Generating documentation"
	@- $(DOXYGEN)
	@- $(ECHO) "Documentation Generated :)"

  ###########################################
  # Clean everything, reset for a new rebuild
  # (for maintainers )
maintainer-clean: clean
	@- $(ECHO) "Cleaning Dist"
	@- if [ -e $(DIR_DIST) ]; then $(RM) $(DIR_DIST); fi;
	@- $(ECHO) "**All Clean ^^"

  ##############
  # Clean Source
srcclean:
	@- $(ECHO) "Cleaning Sources"
	@- $(CD) $(DIR_SRC); $(RM) $(SOURCETMPFILES)
	@- $(ECHO) "Sources Clean"

###################
# Make Dependencies
dep: $(DEPS)
	@- $(ECHO) "Dependency Files Generated"

  ###################
  # Load Dependencies
  # (include)
  DEP_LOAD = $(wildcard  $(DIR_DEP)/*.d)
  include $(foreach dep, $(DEP_LOAD), $(dep))

  ################
  # Create Release
  ifeq "$(PROJECTTYPE)" "lib"

    ###########
    # (library)
lib: $(OBJECTS)
	@- $(ECHO) "Creating Static libs"
	@- if [ ! -e $(DIR_DIST) ]; then $(MKDIR) $(DIR_DIST); fi;
	@- if [ ! -e $(DIR_DIST_INC) ]; then $(MKDIR) $(DIR_DIST_INC); fi;
	@- if [ ! -e $(DIR_DIST_LIB) ]; then $(MKDIR) $(DIR_DIST_LIB); fi;
	@- $(LSTAT) $(LSTATFLAGS) $(DIR_DIST_LIB)/lib$(PROJECTNAME).a $(OBJECTS) $(OBJECTS_MOC)
	@- $(ECHO) "Copying Headers"
	@- $(CP) $(HEADERS_DIR_PREFIX) $(DIR_DIST_INC)/
    ifneq "$(HEADER_EXTS)" ""
	@- $(ECHO) "Copying Header Exts"
	@- $(CP) $(HEADER_EXTS_DIR_PREFIX) $(DIR_DIST_INC)/
    endif
	@- $(ECHO) "Library Made"

  else
    ifeq "$(PROJECTTYPE)" "exe"

      ##############
      # (executable)
exe: $(OBJECTS)
	@- $(ECHO) "Compiling Executable"
	@- $(ECHO) "LD:      $(LD)"
	@- $(ECHO) "LDFLAGS: $(LDFLAGS)"
	@- $(ECHO) "OBJECTS: $(OBJECTS)"
	@- $(ECHO) "CMD:     $(CXX) $(LDFLAGS) $(INCPATHS) $(LIBPATHS) $(LIBS_SHARED) -o $(DIR_DIST)/$(PROJECTNAME)_EXECUTABLE $(OBJECTS) $(OBJECTS_MOC) $(LIBS_STATIC)"
	@- if [ ! -e $(DIR_DIST) ]; then $(MKDIR) $(DIR_DIST); fi;
	@- $(CXX) $(LDFLAGS) $(INCPATHS) $(LIBPATHS) $(LIBS_SHARED) -o $(DIR_DIST)/$(PROJECTNAME)_EXECUTABLE $(OBJECTS) $(OBJECTS_MOC) $(LIBS_STATIC)
	@- $(ECHO) "Executable Made"

    endif
  endif

  ########################
  # Create Release Package
  # bziped and gziped tar
  ifeq "$(PROJECTTYPE)" "lib"

dist: lib
	@- $(ECHO) "Packing Distribution..."
	@- if [ ! -e $(DIR_DIST)/$(PROJECTNAME) ]; then $(MKDIR) $(DIR_DIST)/$(PROJECTNAME); fi;
	@- $(CP) $(DIR_DIST_INC) $(DIR_DIST_LIB) $(DIR_DIST)/$(PROJECTNAME)/ -R
	@- $(ARCHIVECMDSTR)
	@- rm -rf $(DIR_DIST)/$(PROJECTNAME)
	@- $(ECHO) "Distribution Packed (LIBRARY)"

  else
    ifeq "$(PROJECTTYPE)" "exe"

dist: exe
	@- $(ECHO) "Packing Distribution..."
	@- if [ ! -e $(DIR_DIST)/$(PROJECTNAME) ]; then $(MKDIR) $(DIR_DIST)/$(PROJECTNAME); fi;
	@- $(CP) $(DIR_DIST)/$(PROJECTNAME)_EXECUTABLE $(DIR_DIST)/$(PROJECTNAME)/$(PROJECTNAME)
	@- $(ARCHIVECMDSTR)
	@- rm -rf $(DIR_DIST)/$(PROJECTNAME)
	@- $(ECHO) "Distribution Packed (EXECUTABLE)"

    endif
  endif

  ###########################
  # Compile Meta Objects (QT)
  ifneq "$(HEADER_MOCS)" ""

${DIR_WORK_MOC}/%_MOC.cpp: $(DIR_SRC)/%.h
	@- $(ECHO) "Executing the MOC step on: $* ($@)"
	@- if [ ! -e $(DIR_WORK) ]; then $(MKDIR) $(DIR_WORK); fi;
	@- if [ ! -e $(DIR_WORK_MOC) ]; then $(MKDIR) $(DIR_WORK_MOC); fi;
	@  $(CD) $(DIR_WORK_MOC); $(MOC) ../../$(DIR_SRC)/$*.h > $*_MOC.cpp
	@- $(ECHO) "Creating MOC Object for $*"
	@  $(CXX) $(CXXFLAGS) $(INCPATHS) -o $(DIR_WORK_OBJ)/$*_MOC.o $@

  endif

  ###############
  # Objects (C++)
${DIR_WORK_OBJ}/%.o: $(DIR_SRC)/%.cpp $(DIR_WORK_DEP)/%.d
	@- $(ECHO) "Making Obj $* ($@)"
	@- if [ ! -e $(DIR_WORK) ]; then $(MKDIR) $(DIR_WORK); fi;
	@- if [ ! -e $(DIR_WORK_OBJ) ]; then $(MKDIR) $(DIR_WORK_OBJ); fi;
	@  $(CXX) $(CXXFLAGS) $(INCPATHS) -o $@ $<

  ####################
  # Dependencies (C++)
$(DIR_WORK_DEP)/%.d: $(DIR_SRC)/%.cpp
	@- $(ECHO) "Making Dep $* ($@)"
	@- if [ ! -e $(DIR_WORK) ]; then $(MKDIR) $(DIR_WORK); fi;
	@- if [ ! -e $(DIR_WORK_DEP) ]; then $(MKDIR) $(DIR_WORK_DEP); fi;
	@ $(CXX) -M $(INCPATHS) $< | $(SED) 's/$(subst /,\/,$(notdir $*))\.o/$(subst /,\/,$(DIR_WORK_OBJ)/$*\.o) $(subst /,\/,$(DIR_WORK_DEP))\/$(subst /,\/,$*\.d)/' > $@
#	@ $(CXX) -MM            $< | $(SED) 's/$(subst /,\/,$(notdir $*))\.o/$(subst /,\/,$(DIR_WORK_OBJ)/$*\.o) $(subst /,\/,$(DIR_WORK_DEP))\/$(subst /,\/,$*\.d)/' > $@

-include makeconf_custome_rules.mak

else

  # Backup Var :P
  ECHO = echo -e

all:

%:
	@- $(ECHO) "Config Error:"
	@- $(ECHO) " $(CONFIG_ERROR)"
	@- $(ECHO) " \n"

endif #END CONFIG_OK test

  ###########
  # Help
help:
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  Help                                                  "
	@- $(ECHO) "  ====                                                  "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  Help Targets:                                         "
	@- $(ECHO) "  - help_config                                         "
	@- $(ECHO) "  - help_config_VAR (see help_config)                   "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  Build Targets:                                        "
	@- $(ECHO) "  - all (default)                                       "
	@- $(ECHO) "    Default target, compile and/or link $(PROJECTNAME)  "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - dep                                                 "
	@- $(ECHO) "    Make dependencies (implemented in default target)   "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - exe                                                 "
	@- $(ECHO) "    Compile and link the Binary Executable if this is   "
	@- $(ECHO) "    a executable program project                        "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - lib                                                 "
	@- $(ECHO) "    Compile and link a static library if this is a      "
	@- $(ECHO) "    library project                                     "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - dist                                                "
	@- $(ECHO) "    Make distribution: runs bin target and packs the    "
	@- $(ECHO) "    result as a distribution package (gzip/bzip2)       "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  Clean Targets:                                        "
	@- $(ECHO) "  - clean                                               "
	@- $(ECHO) "    Normal clean, cleaning for the build process        "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - maintainer-clean                                    "
	@- $(ECHO) "    Clean for maintainers, cleans everything            "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - srcclean                                            "
	@- $(ECHO) "    Cleanup sourcecode tmp and swap files               "
	@- $(ECHO) "                                                        "


  ###########
  # Help
help_config:
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  Help: Config                                          "
	@- $(ECHO) "  ============                                          "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  For more info on each variable, type:                 "
	@- $(ECHO) "   help_config_VAR                                      "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  Required Variables                                    "
	@- $(ECHO) "  - COMPILE_ENV                                         "
	@- $(ECHO) "    [ linux | win32 ]                                   "
	@- $(ECHO) "    The environment to compile under.                   "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - PROJECTTYPE                                         "
	@- $(ECHO) "    [ exe | lib ]                                       "
	@- $(ECHO) "    Type of project, executable or library.             "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - SOURCES (only required for exe-project)             "
	@- $(ECHO) "    The sourcefiles to be compiled                      "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - HEADERS (only required for lib-project)             "
	@- $(ECHO) "    Local headers to include in compilation             "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  Optional Variables                                    "
	@- $(ECHO) "  - HEADER_EXTS                                         "
	@- $(ECHO) "  - HEADER_MOCS                                         "
	@- $(ECHO) "  - CC/CFLAGS                                           "
	@- $(ECHO) "  - CXX/CXXFLAGS                                        "
	@- $(ECHO) "  - LD/LDFLAGS                                          "
	@- $(ECHO) "  - LSTAT                                               "
	@- $(ECHO) "  - LSTATFLAGS                                          "
	@- $(ECHO) "  - ARCHIVER                                            "
	@- $(ECHO) "  - ARCHIVERFLAGS                                       "
	@- $(ECHO) "  - INCPATHS                                            "
	@- $(ECHO) "  - LIBPATHS                                            "
	@- $(ECHO) "  - SOURCETMPFILES                                      "
	@- $(ECHO) "  - LIBS_SHARED                                         "
	@- $(ECHO) "  - LIBS_STATIC                                         "
	@- $(ECHO) "                                                        "


  ###########
  # Help
help_print_vars:
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  Help: Print Vars                                      "
	@- $(ECHO) "  ============                                          "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - COMPILE_ENV                                         "
	@- $(ECHO) "    $(COMPILE_ENV)                                      "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - PROJECTTYPE                                         "
	@- $(ECHO) "    $(PROJECTTYPE)                                      "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - CC/CXX                                              "
	@- $(ECHO) "    CC:             $(CC)                               "
	@- $(ECHO) "    CXX:            $(CXX)                              "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - CFLAGS/CXXFLAGS                                     "
	@- $(ECHO) "    CFLAGS:         $(CFLAGS)                           "
	@- $(ECHO) "    CXXFLAGS:       $(CXXFLAGS)                         "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - LD/LDFLAGS                                          "
	@- $(ECHO) "    LD:             $(LD)                               "
	@- $(ECHO) "    LDFLAGS:        $(LDFLAGS)                          "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - LSTAT/LSTATFLAGS                                    "
	@- $(ECHO) "    LSTAT:          $(LDFLAGS)                          "
	@- $(ECHO) "    LSTATFLAGS:     $(LSTATFLAGS)                       "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - ARCHIVER/ARCHIVERFLAGS                              "
	@- $(ECHO) "    ARCHIVER:       $(ARCHIVER)                         "
	@- $(ECHO) "    ARCHIVERFLAGS:  $(ARCHIVERFLAGS)                    "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - PATHS                                               "
	@- $(ECHO) "    INCPATHS:       $(INCPATHS)                         "
	@- $(ECHO) "    LIBPATHS:       $(LIBPATHS)                         "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - INCLUDED LIBS                                       "
	@- $(ECHO) "    LIBS_SHARED: $(LIBS_SHARED)                         "
	@- $(ECHO) "    LIBS_STATIC: $(LIBS_STATIC)                         "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - SOURCETMPFILES                                      "
	@- $(ECHO) "    $(SOURCETMPFILES)                                   "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - SOURCES                                             "
	@- $(ECHO) "    $(SOURCES)                                          "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - HEADERS                                             "
	@- $(ECHO) "    $(HEADERS)                                          "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - HEADER_EXTS                                         "
	@- $(ECHO) "    $(HEADER_EXTS)                                      "
	@- $(ECHO) "                                                        "
	@- $(ECHO) "  - HEADER_MOCS                                         "
	@- $(ECHO) "    $(HEADER_MOCS)                                      "







