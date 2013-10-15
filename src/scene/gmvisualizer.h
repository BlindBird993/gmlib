/**********************************************************************************
**
** Copyright (C) 1994 Narvik University College
** Contact: GMlib Online Portal at http://episteme.hin.no
**
** This file is part of the Geometric Modeling Library, GMlib.
**
** GMlib is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** GMlib is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with GMlib.  If not, see <http://www.gnu.org/licenses/>.
**
**********************************************************************************/



/*! \file gmvisualizer.h
 *
 *  Interface for the Visualizer class.
 */

#ifndef __gmVISUALIZER_H__
#define __gmVISUALIZER_H__


// gmlib
#include <core/utils/gmcolor.h>
#include <opengl/glsl/gmglprogram.h>

// stl
#include <string>


// Visualizer macros
#define GM_DECLARE_VISUALIZER_MAKECOPY( CNAME ) \
  Visualizer* makeCopy() const { \
    return new CNAME(*this); \
  }

#define GM_VISUALIZER( CNAME ) \
  public: \
    GM_DECLARE_VISUALIZER_MAKECOPY( CNAME ) \
  private:



namespace GMlib {

  class Camera;
  class DisplayObject;

  class Visualizer {
  public:
    enum DISPLAY_MODE {
      DISPLAY_MODE_SHADED       = 0x01,
      DISPLAY_MODE_WIREFRAME    = 0x02
    };

    Visualizer();
    Visualizer( const Visualizer& v );
    virtual ~Visualizer();

    virtual Visualizer*       makeCopy() const = 0;

    virtual void              render( const DisplayObject* obj, const Camera* cam ) const;
    virtual void              renderGeometry( const GL::GLProgram& prog, const DisplayObject* obj, const Camera* cam ) const;

    const GL::GLProgram&      getRenderProgram() const;
    void                      setRenderProgram( const GL::GLProgram& prog );

    DISPLAY_MODE              getDisplayMode() const;
    void                      setDisplayMode( DISPLAY_MODE display_mode );
    void                      toggleDisplayMode();

    void                      glSetDisplayMode() const;

    virtual void              simulate( double dt );

    virtual bool              operator == ( const Visualizer* v ) const;


  private:
    DISPLAY_MODE              _display_mode;

    GL::GLProgram             _render_prog;
  };



} // END namespace GMlib


#endif // __gmVISUALIZER_H__
