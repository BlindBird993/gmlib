
#include( ../gmlib.pri )



DOXYGEN = doxygen
DOXYFILE = doc/DoxyfileDevAPI

doc.target = doc
doc.output = doxygen/developer
doc.commands = cd doc; $$DOXYGEN
doc.depends = FORCE

#QMAKE_EXTRA_COMPILERS += dox
QMAKE_EXTRA_TARGETS += doc
