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

    virtual void          display();
    DISPLAY_MODE          getDisplayMode() const;
    const GL::GLProgram&      getRenderProgram() const;
    const GL::GLProgram&      getSelectProgram() const;
    void                  glSetDisplayMode() const;

    virtual void          select();
    virtual void          set( DisplayObject* obj );
    void                  setDisplayMode( DISPLAY_MODE display_mode );
    void                  setRenderProgram( const GL::GLProgram& prog );
    void                  setSelectProgram( const GL::GLProgram& prog );

    virtual void          simulate( double dt );
    void                  toggleDisplayMode();

    virtual bool          operator == ( const Visualizer* v ) const;


  protected:
    DisplayObject           *_obj;

    DISPLAY_MODE          _display_mode;

    GL::GLProgram             _render_prog;

  private:
    void                  _init();
  };



} // END namespace GMlib


#endif // __gmVISUALIZER_H__