#include "gmuniformbufferobject.h"

namespace GMlib {

namespace GL {

  UniformBufferObject::UniformBufferObject()
    : BufferObject( GL_UNIFORM_BUFFER, GL_UNIFORM_BUFFER_BINDING ) {}

  UniformBufferObject::UniformBufferObject(const std::string &name) :
    BufferObject( name, GL_UNIFORM_BUFFER, GL_UNIFORM_BUFFER_BINDING ) {}

} // END namespace GL

} // END namespace GMlib
