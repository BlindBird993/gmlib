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



/*! \file gmDPLuaScriptCurve.c
 *  \brief Inline DPLuaScriptCurve class implementations
 *
 *  Implementation of the DPLuaScriptCurve class.
 *
 *  \date   2009-09-12
 */

#include <sstream>

namespace GMlib {

  namespace Script {

    namespace Lua {


      template <typename T>
      DPLuaScriptCurve<T>::DPLuaScriptCurve() {

        _closed = false;
        _start = 0;
        _end = 1;
      }


      template <typename T>
      DPLuaScriptCurve<T>::DPLuaScriptCurve( const DPLuaScriptCurve<T>& copy ) : DCurve<T>( copy ), LuaScript( copy ) {}


      template <typename T>
      DPLuaScriptCurve<T>::~DPLuaScriptCurve() {}


      template <typename T>
      void DPLuaScriptCurve<T>::constructResult() {

        luaC::lua_getglobal( _L, "result" ); {

          for( int i = 0; i < this->_p.getDim(); i++ ) {

            std::stringstream si;
            si << i;
            luaC::lua_getfield( _L, -1, si.str().c_str() ); {

              luaC::lua_getfield( _L, -1, "x" );
                this->_p[i][0] = luaC::lua_tonumber( _L, -1 );
              luaC::lua_pop( _L, 1 );

              luaC::lua_getfield( _L, -1, "y" );
                this->_p[i][1] = luaC::lua_tonumber( _L, -1 );
              luaC::lua_pop( _L, 1 );

              luaC::lua_getfield( _L, -1, "z" );
                this->_p[i][2] = luaC::lua_tonumber( _L, -1 );
              luaC::lua_pop( _L, 1 );

            } luaC::lua_pop( _L, 1 );
          }
        } luaC::lua_pop( _L, 1 );
      }


      template <typename T>
      void DPLuaScriptCurve<T>::eval(T t, int d, bool l ) {

        // Set result dimension
        this->_p.setDim( d );

        // Set up variables for lua
        clearVars();
        addVar( LuaVar( t ) );
        addVar( LuaVar( d ) );
        addVar( LuaVar( l ) );

        // Execute
        exec( "eval" );
      }


      template <typename T>
      inline
      T DPLuaScriptCurve<T>::getEndP() {

        return _end;
      }


      template <typename T>
      std::string DPLuaScriptCurve<T>::getIdentity() const {

        return "DPLuaScriptCurve";
      }


      template <typename T>
      inline
      T DPLuaScriptCurve<T>::getStartP() {

        return _start;
      }


      template <typename T>
      inline
      void DPLuaScriptCurve<T>::init() {

        _start = T(0);
        _end = T(1);
        _closed = false;
      }


      template <typename T>
      inline
      bool DPLuaScriptCurve<T>::isClosed() const {

        return _closed;
      }


      template <typename T>
      void DPLuaScriptCurve<T>::setClosed( bool closed ) {

        _closed = closed;
      }


      template <typename T>
      void DPLuaScriptCurve<T>::setParEnd( const T& end ) {

        _end = end;
      }


      template <typename T>
      void DPLuaScriptCurve<T>::setParStart( const T& start ) {

        _start = start;
      }

    } // END namespace Lua

  } // END namespace Script

} // END namespace GMlib

