#ifndef GMUNIFORMBUFFEROBJECT_H
#define GMUNIFORMBUFFEROBJECT_H


#include "../gmbufferobject.h"

namespace GMlib {

  class UniformBufferObject : public BufferObject {
  public:
    explicit UniformBufferObject();
    explicit UniformBufferObject( const std::string& name );
  };

} // END namespace GMlib

#endif // GMUNIFORMBUFFEROBJECT_H
