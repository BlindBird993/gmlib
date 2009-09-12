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



/*! \file gmDPLuaScriptSurf.h
 *
 *  Interface for the gmDPLuaScriptSurf class.
 *
 *  \date   2008-09-04
 */

#ifndef __gmDPLUASCRIPTSURF_H__
#define __gmDPLUASCRIPTSURF_H__

// STL
#include <string>

// GMlib
#include "gmDSurf.h"
#include "gmScript.h"

# ifdef GM_SCRIPT_LUA

namespace GMlib {

  namespace Script {

    namespace Lua {

      template <typename T>
      class DPLuaScriptSurf : public DSurf<T>, public LuaScript {
      public:
        DPLuaScriptSurf();
        DPLuaScriptSurf( const DPLuaScriptSurf<T>& copy );
        virtual ~DPLuaScriptSurf();

        void            setClosedU( bool closed );
        void            setClosedV( bool closed );
        void            setParEndU( const T& end );
        void            setParEndV( const T& end );
        void            setParStartU( const T& start );
        void            setParStartV( const T& start );

      protected:
        void            constructResult();
        void            eval(T u, T v, int d1, int d2, bool lu = true, bool lv = true );
        T               getEndPV();
        T               getEndPU();
        std::string     getIdentity() const;
        T               getStartPU();
        T               getStartPV();
        void            init();
        bool            isClosedU() const;
        bool            isClosedV() const;

        bool            _closed_u;
        bool            _closed_v;
        T               _end_u;
        T               _end_v;
        T               _start_u;
        T               _start_v;

      }; // END class DPLuaScriptSurf

    } // END namespace Lua

  } // END namespace Script

} // END namespace GMlib

// Include DPLuaScriptSurf class function implementations
#include "gmDPLuaScriptSurf.c"

# endif // GM_SCRIPT_LUA

#endif // __gmDPLUASCRIPTSURF_H__

