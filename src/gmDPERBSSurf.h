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



/*! \file gmDPERBSSurf.h
 *
 *  Interface for the gmDPERBSSurf class.
 *
 *  \date   2008-10-28
 */

#ifndef __gmDPERBSSURF_H__
#define __gmDPERBSSURF_H__


// GMlib includes+
#include "gmDSurf.h"
#include "gmPERBSSurf.h"


namespace GMlib {


  template <typename T>
  class DPERBSSurf : public DSurf<T> {
  public:
    DPERBSSurf( PSurf<T,3>* g, int no_locals_u, int no_locals_v, int d1, int d2 );
    DPERBSSurf( const DPERBSSurf<T>& copy );
    DPERBSSurf( const PERBSSurf<T,3>& copy );
    DPERBSSurf( PERBSSurf<T,3>* copy );
    virtual ~DPERBSSurf();


    void                      edit( SceneObject *obj );
    string                    getIdentity() const;
    virtual PERBSSurf<T,3>*   getPERBSSurf();
    virtual void              hideLocalPatches();
    bool                      isLocalPatchesVisible() const;
    virtual void              showLocalPatches( bool collapsed = true );

  protected:
    PERBSSurf<T,3>            *_l_ref;
    DMatrix< DSurf<T>* >      _p;
    bool                      _p_visible;

    virtual void              init();
    void                      localDisplay();
    virtual void              visualizeLocalPatch( PSurf<T,3>* p, int i, int j, int n, int m, bool collapsed );
    virtual void              visualizeLocalPatchInit( int i, int j, int n, int m, bool collapsed );

  };




} // END namepace GMlib

// Include DPERBSSurf class function implementations
#include "gmDPERBSSurf.c"


#endif // __gmDPERBSSURF_H__



