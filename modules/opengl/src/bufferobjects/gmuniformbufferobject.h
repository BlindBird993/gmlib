#ifndef GMUNIFORMBUFFEROBJECT_H
#define GMUNIFORMBUFFEROBJECT_H


#include "../gmbufferobject.h"

namespace GMlib {

namespace GL {

  class UniformBufferObject : public BufferObject {
  public:
    explicit UniformBufferObject();

    void create();
    void create( const std::string& name );

  }; // END class UniformBufferObject

} // END namespace GL

} // END namespace GMlib

#endif // GMUNIFORMBUFFEROBJECT_H
