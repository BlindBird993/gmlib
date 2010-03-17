
TEMPLATE = lib

CONFIG -= qt
CONFIG += staticlib


TARGET = $$TARGET

CONFIG( debug, debug|release ) {
    unix:TARGET = $$join(TARGET,,,_debug)
    win32:TARGET = $$join(TARGET,,,D)
}


#cpp2include.output = $$GMLIB_INCLUDE_PATH/${QMAKE_FILE_NAME}
#cpp2include.input = HEADERS
#cpp2include.commands = $$QMAKE_COPY ${QMAKE_FILE_IN} ${QMAKE_FILE_OUT}
#isEmpty(vcproj):cpp2include.variable_out = PRE_TARGETDEPS
#cpp2include.name = COPY ${QMAKE_FILE_IN}
#cpp2include.CONFIG += no_link
#QMAKE_EXTRA_COMPILERS += cpp2include
