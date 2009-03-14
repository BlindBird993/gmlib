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



/*! \file gmVSurroundingSphere.h
 *
 *  Interface for the VSurroundingSphere class.
 *
 *  \date   2009-01-27
 */

#ifndef __gmVSURROUNDINGSPHERE_H__
#define __gmVSURROUNDINGSPHERE_H__


#include "gmGLColor.h"
#include "gmVisualizer.h"


namespace GMlib {


  enum GM_VISUALIZER_SS {
    GM_VISUALIZER_SS_SPHERE = 1,
    GM_VISUALIZER_SS_CLEAN  = 2

  };

  template <typename T, int n>
  class VSurroundingSphere : public Visualizer<T,n> {
  public:
    VSurroundingSphere();
    VSurroundingSphere( const VSurroundingSphere<T,n>& copy );

    void                display();
    const GLColor&      getColor( unsigned int mask ) const;
    std::string         getIdentity() const;
    unsigned int        getSpheres() const;
    bool                isWireframe() const;
    void                replot(
      DVector< DVector< Vector<T, 3> > >& p,
      int m, int d
    );
    void                replot(
      DMatrix< DMatrix< Vector<T, 3> > >& p,
      DMatrix< Vector<T, 3> >& normals,
      int m1, int m2, int d1, int d2
    );
    void                setColor( const GLColor& color, unsigned int mask );
    void                setSpheres( unsigned int mask );
    void                setWireframe( bool wireframe );

  private:
    unsigned int        _spheres;

    bool                _wireframe;

    GLColor             _color;
    GLColor             _color_clean;

    void                _init();

  };

} // END namespace GMlib

// Include VSurroundingSphere class function implementations
#include "gmVSurroundingSphere.c"


#endif // __gmVSURROUNDINGSPHERE_H__




