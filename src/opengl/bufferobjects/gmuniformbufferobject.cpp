#include "gmuniformbufferobject.h"

namespace GMlib {

namespace GL {

  UniformBufferObject::UniformBufferObject() : BufferObject( GL_UNIFORM_BUFFER ) {}

  UniformBufferObject::UniformBufferObject(const std::string &name) :
    BufferObject( name, GL_UNIFORM_BUFFER ) {}

} // END namespace GL

} // END namespace GMlib
