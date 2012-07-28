#ifndef __gmSELECTORGRIDVISUALIZER_H__
#define __gmSELECTORGRIDVISUALIZER_H__


#include "../visualizer/gmvisualizer.h"

// gmlib::core
#include "../../core/containers/gmdmatrix.h"

namespace GMlib {

  template <typename T, int n>
  class Selector;

  template <typename T>
  class SelectorGridVisualizer : public Visualizer {
  public:
    SelectorGridVisualizer();
    ~SelectorGridVisualizer();

    void                          display( Camera* cam );
    void                          reset();
    void                          setSelectors( DVector< Vector<T,3> >& c );
    void                          setSelectors( DMatrix< Vector<T,3> >& c );
    void                          update();

  protected:
    GLProgram                     _prog;
    GLuint                        _ibo;
    GLuint                        _vbo;
    int                           _no_indices;

    DVector< Vector<T,3>* >       _c;

  private:
    void                          _fillVBO();

  }; // END class SelectorGridVisualizer

} // END namespace GMlib

// Implementations
#include "gmselectorgridvisualizer.c"


#endif // __gmSELECTORGRIDVISUALIZER_H__
