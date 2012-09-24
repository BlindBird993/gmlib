#include "gmuniformbufferobject.h"

namespace GMlib {

  UniformBufferObject::UniformBufferObject() : BufferObject( GL_UNIFORM_BUFFER ) {}

  UniformBufferObject::UniformBufferObject(const std::string &name) :
    BufferObject( name, GL_UNIFORM_BUFFER ) {}


} // END namespace GMlib
