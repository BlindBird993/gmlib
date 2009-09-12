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



/*! \file gmDPLuaScriptCurve.h
 *
 *  Interface for the gmDPLuaScriptCurve class.
 *
 *  \date   2008-09-12
 */

#ifndef __gmDPLUASCRIPTCURVE_H__
#define __gmDPLUASCRIPTCURVE_H__

// STL
#include <string>

// GMlib
#include "gmDCurve.h"
#include "gmScript.h"

# ifdef GM_SCRIPT_LUA

namespace GMlib {

  namespace Script {

    namespace Lua {

      template <typename T>
      class DPLuaScriptCurve : public DCurve<T>, public LuaScript {
      public:
        DPLuaScriptCurve();
        DPLuaScriptCurve( const DPLuaScriptCurve<T>& copy );
        virtual ~DPLuaScriptCurve();

        void            setClosed( bool closed );
        void            setParEnd( const T& end );
        void            setParStart( const T& start );

      protected:
        void            constructResult();
        void            eval(T t, int d, bool l = true );
        T               getEndP();
        std::string     getIdentity() const;
        T               getStartP();
        void            init();
        bool            isClosed() const;

        bool            _closed;
        T               _end;
        T               _start;

      }; // END class DPLuaScriptCurve

    } // END namespace Lua

  } // END namespace Script

} // END namespace GMlib

// Include DPLuaScriptCurve class function implementations
#include "gmDPLuaScriptCurve.c"

# endif // GM_SCRIPT_LUA

#endif // __gmDPLUASCRIPTCURVE_H__


