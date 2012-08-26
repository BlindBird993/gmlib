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



/*! \file gmvisualizer.cpp
 *  \brief Visualizer class function implementations
 *
 *  Implementation of the Visualizer class.
 */


#include "gmvisualizer.h"

#include "../gmsceneobject.h"



namespace GMlib {

  Visualizer::Visualizer() : _render_prog("default") {

    _display_mode = DISPLAY_MODE_SHADED;
  }

  Visualizer::Visualizer( const Visualizer& copy ) :
    _render_prog( copy._render_prog ) {

    _display_mode = copy._display_mode;
  }

  Visualizer::~Visualizer() {}

  void Visualizer::_init() {

    _obj = 0x0;
  }

  void Visualizer::display() {}

  Visualizer::DISPLAY_MODE Visualizer::getDisplayMode() const {

    return _display_mode;
  }

  std::string Visualizer::getIdentity() const {

    return "Visualizer Base";
  }

  const GLProgram &Visualizer::getRenderProgram() const {

    return _render_prog;
  }

  const GLProgram& Visualizer::getSelectProgram() const {

    return _obj->getSelectProgram();
  }

  void Visualizer::glSetDisplayMode() const {

    if( this->_display_mode == Visualizer::DISPLAY_MODE_SHADED )
      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    else if( this->_display_mode == Visualizer::DISPLAY_MODE_WIREFRAME )
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
  }

  void Visualizer::select() {}

  void Visualizer::set( SceneObject* obj ) {

    _obj = obj;
  }

  void Visualizer::setDisplayMode( Visualizer::DISPLAY_MODE display_mode) {

    _display_mode = display_mode;
  }

  void Visualizer::setRenderProgram(const GLProgram &prog) {

    _render_prog = prog;
  }

  void Visualizer::setSelectProgram(const GLProgram &prog)
  {
    _obj->setSelectProgram( prog );
  }

  void Visualizer::simulate( double /*dt*/ ) {}

  void Visualizer::toggleDisplayMode() {

    if( _display_mode == Visualizer::DISPLAY_MODE_SHADED )
      _display_mode = Visualizer::DISPLAY_MODE_WIREFRAME;
    else
      _display_mode = Visualizer::DISPLAY_MODE_SHADED;
  }

  bool Visualizer::operator == ( const Visualizer* v ) const {

    if( this == v )
      return true;

    return false;
  }

} // END namespace GMlib
