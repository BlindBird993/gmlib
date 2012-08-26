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



/*! \file gmselectorgrid.h
 *  \brief Interface to the SelectorGrid class
 *
 *  Interface to the SelectorGrid class
 */


#ifndef __gmSELECTORGRID_H__
#define __gmSELECTORGRID_H__


#include "gmselector.h"

// gmlib
#include <core/containers/gmdmatrix.h>


namespace GMlib {

  /*! \class SelectorGrid gmselectorgrid.h <gmSelectorGrid>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  class SelectorGrid : public Selector<T,n> {
  public:
    SelectorGrid( Point<T,n>& mp, SceneObject* parent, const Color& c = Color(0.5,0.5,0.9));
    ~SelectorGrid();

    void add(Point<T,n>& p1, Point<T,n>& p2);
    void setSelectors( DMatrix< Vector<T,n> >& selectors );

  protected:
    GLProgram   _prog;
    GLuint      _vbo;
    GLuint      _ibo;

    Array<Point<T,n>* > _c;
    DMatrix< Vector<T,n> > *_selectors;


    void localDisplay( Camera* cam );
    void localSelect( Camera* cam, const Color& name );

  private:
    void    _updateIBO();
    void    _updateVBO();
    void    _allocateBOs();

  }; // END class SelectorGrid

} // END namespace GMlib


#include "gmselectorgrid.c"



#endif // __gmSELECTORGRID_H__
