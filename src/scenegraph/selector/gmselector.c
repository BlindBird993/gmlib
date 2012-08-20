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



/*! \file gmselector.c
 *  \brief Pending Description
 *
 *  Detailed File Description
 */



#include "../displayobjects/gmsphere3d.h"

namespace GMlib {


  /*! Selector<T,n>::Selector( Point<T,n>& mp, int id, SceneObject* parent, T r, const Color& c, Selector<T,n>* root )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  Selector<T,n>::Selector( Point<T,n>& mp, int id, SceneObject* parent, T r, const Color& c, Selector<T,n>* root )
    : _position(mp), _display( "color" ),
    _bo_cube( "std_rep_cube" ), _bo_cube_indices( "std_rep_cube_indices" ),
    _bo_cube_frame_indices( "std_rep_frame_indices" )
  {

    Sphere<float,3> ts(Point<float,3>(float(0)),0.866);
    setSurroundingSphere(ts);
    _type_id	= GM_SO_TYPE_SELECTOR;
    _id			= id;
    _parent		= parent;
    _enabled			= true;
    _default	= c;
    _marked		= c.getInverse();
    _selected	= false;
    _root		= root;
    translate( _position.toFloat() );
    if(r != 1.0) scale(Vector3D<float>(r,r,r));
  }


  /*! Selector<T,n>::Selector(const Selector<T,n>& s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  Selector<T,n>::Selector(const Selector<T,n>& s)
    : DisplayObject(s), _position( s._position ), _display( "color" ),
    _bo_cube( "std_rep_cube" ), _bo_cube_indices( "std_rep_cube_indices" ),
    _bo_cube_frame_indices( "std_rep_frame_indices" )
   {

    _type_id	= GM_SO_TYPE_SELECTOR;
    _id			= s._id;
    _parent		= s._parent;
    _enabled			= s._enabled;
    _default	= s._default;
    _marked		= s._marked;
    _root		= s._root;
  }

  /*!virtual Selector<T,n>::~Selector()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  Selector<T,n>::~Selector() {}

  /*! void Selector<T,n>::allEnable()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  all children on
   */
  template <typename T, int n>
  void Selector<T,n>::allEnable() {

    for(int i=0; i<_children.getSize(); i++)
    {
      Selector<T,n> *s=dynamic_cast<Selector<T,n> *>(_children[i]);
      if(s)
        s->enableAll();
    }
  }


  /*! void Selector<T,n>::allDisable()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  all children off
   */
  template <typename T, int n>
  void Selector<T,n>::allDisable() {

    for(int i=0; i<_children.getSize(); i++)
    {
      Selector<T,n> *s=dynamic_cast<Selector<T,n> *>(_children[i]);
      if(s)
        s->disableAll();
    }
  }




  /*! void	Selector<T,n>::disable()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::disable() {

    _enabled=false;
    allEnable();

    if(_root)
      _root->enable();
  }


  /*! void	Selector<T,n>::disableAll()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::disableAll() {

    _enabled = false;
    allEnable();
  }


  /*! virtual void	Selector<T,n>::edit()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::edit() {

    _parent->selectEvent(_id);
  }


  /*! void	Selector<T,n>::editPos(Vector<float,3> dp)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::editPos(Vector<float,3> dp) {

    HqMatrix<float,3> invmat = _present;
    invmat.invertOrthoNormal();
    _position+=Point<T,n>(invmat*dp);
    translate(invmat*dp);
    _parent->edit(_id);
  }


  /*! void	Selector<T,n>::enable()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::enable() {

    _enabled=true;

    if( _root )
      _root->disable();

    allDisable();
  }


  /*! void	Selector<T,n>::enableAll()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void	Selector<T,n>::enableAll() {

    _enabled = true;
    allEnable();
  }

  template <typename T, int n>
  inline
  int Selector<T,n>::getId() const {

    return _id;
  }

  /*! std::string	Selector<T,n>::getIdentity() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  std::string	Selector<T,n>::getIdentity() const {

    return "Selector";
  }

  template <typename T, int n>
  inline
  const Point<T,n>& Selector<T,n>::getPosition() const {

    return _position;
  }


  /*! bool	Selector<T,n>::isEnabled() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  Is the children or my self on?
   */
  template <typename T, int n>
  bool	Selector<T,n>::isEnabled() const {

    for(int i=0; i<_children.getSize(); i++)
    {
      Selector<T,n> *s=dynamic_cast<Selector<T,n> *>(this->_children[i]);
      if(s)
        if(s->isEnabled())
          return true;
    }
    return _enabled;
  }


  /*! void Selector<T,n>::localDisplay()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  void Selector<T,n>::localDisplay( Camera* cam ) {

    if( _enabled ) {

      glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

      _display.bind();

      _display.setUniform( "u_mvpmat", getModelViewProjectionMatrix(cam), 1, true );

      GLuint vert_loc = _display.getAttributeLocation( "in_vertex" );

      Color blend_color = GMcolor::LightGreen;
      blend_color.setAlpha( 0.5 );

      _display.setUniform( "u_selected", isSelected() );

      _bo_cube.enableVertexArrayPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );

      _bo_cube_frame_indices.bind(); {

        const GLsizei frame_stride = 2 * sizeof(GLushort);

        glLineWidth( 1.0f );
        _display.setUniform( "u_color", GMcolor::Green );
        glDrawElements( GL_LINES, 24, GL_UNSIGNED_SHORT, (const GLvoid*)(0x0) );

      } _bo_cube_frame_indices.unbind();

      glEnable( GL_BLEND ); {

        glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
        _display.setUniform( "u_color", blend_color );
        _bo_cube_indices.bind();
          glDrawElements( GL_QUADS, 24, GL_UNSIGNED_SHORT, 0x0 );
        _bo_cube_indices.unbind();

      }glDisable( GL_BLEND );

      _bo_cube.disableVertexArrayPointer( vert_loc );

      _display.unbind();
    }
  }


  /*! void Selector<T,n>::localSelect()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  void Selector<T,n>::localSelect() {

    if( _enabled ) {

      GLuint vert_loc = getSelectProgram().getAttributeLocation( "in_vertex" );
      _bo_cube.enableVertexArrayPointer( vert_loc, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*)0x0 );
      _bo_cube_indices.bind();
        glDrawElements( GL_QUADS, 24, GL_UNSIGNED_SHORT, 0x0 );
      _bo_cube_indices.unbind();
      _bo_cube.disableVertexArrayPointer( vert_loc );
    }
  }


  /*! bool Selector<T,n>::toggle()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  visibility
   */
  template <typename T, int n>
  inline
  bool Selector<T,n>::toggle() {

    _enabled=!_enabled;
    return _enabled;
  }


  /*! void Selector<T,n>::update()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void Selector<T,n>::update() {

    Vector<T,n> d= _position - _pos;
    translate(d.toFloat());
    for(int i=0; i<_children.getSize(); i++)
    {
      Selector<T,n> *s = dynamic_cast<Selector<T,n> *>(_children[i]);
      if(s)  s->translate(-d.toFloat());  // don't bring children
    }
  }


  /*! void Selector<T,n>::update( const Point<T,n>& p )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  template <typename T, int n>
  inline
  void Selector<T,n>::update( const Point<T,n>& p ) {

    Vector<T,n> d=p-_position;
    _position=p;
    translate(d.toFloat());
    for(int i=0; i<_children.getSize(); i++)
    {
      Selector<T,n> *s = dynamic_cast<Selector<T,n> *>(_children[i]);
      if(s)  s->translate(-d.toFloat());  // don't bring children
    }
  }

}
