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



/*! \file gmviewset.h
 *
 */

#ifndef __gmVIEWSET_H__
#define __gmVIEWSET_H__


#include "gmview.h"

// gmlib::core
#include <core/containers/gmarray.h>
#include <core/types/gmpoint2d.h>

namespace GMlib {


  class Camera;


  /*! \class ViewSet gmwindow.h <gmWindow>
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  class ViewSet {
  public:
    ViewSet(Camera* cam=0);
    ViewSet(const ViewSet& viewset);
    ~ViewSet();

    int  								getSize();
    Point2D<int> 				getViewPortSize();
    void 								prepare(int w, int h);
    void 								removeCamera(Camera*);

    ViewSet& 						operator=(const ViewSet& viewset);
    bool 								operator<(const ViewSet& viewset)const;


  private:
    friend class GMWindow;

    int									_vp_w; // ViewPort size ( Width )
    int 								_vp_h;	// Viewport size ( height )
    Array<Camera*>			_cameras;
    Array<ViewBorder*>	_borders;
    View								_root;
    Color							_border_color;

    Array<ViewBorder*>	_selected_borders;


    void 								drawBorder();

  public:
    void 								drawCamera(bool stereo=false);

  private:
    bool 								find(int x, int y, Camera*& cam);
    bool 								insertCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically=true, double d=0.5);
    void 								moveBorder(int x, int y);
    void 								removeCamera(int i);
    void 								reset();
    void 								setBorderColor(const Color& bc);

    Camera* 						operator[](int i);

  }; // END class ViewSet






















  /*! Point2D<int> ViewSet::getViewPortSize()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  Point2D<int> ViewSet::getViewPortSize() {

    return Point2D<int>(_vp_w, _vp_h);
  }


  /*! bool ViewSet::operator<(const ViewSet& viewset) const
   *	\brief DUMMY!!
   *
   *	Pending Documentation
   *
   *	\todo Remove if not needed!
   */
  inline
  bool ViewSet::operator < ( const ViewSet& /* viewset */ ) const {

    return true;
  }


  /*! void ViewSet::_drawBorder()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewSet::drawBorder() {

//    if(_borders.getSize()>0)
//    {
//      glDisable(GL_LIGHTING);
//      glMatrixMode(GL_PROJECTION);
//      glLoadIdentity();
//      glOrtho( 0, _vp_w, 0, _vp_h, -1, 1 );
//      glMatrixMode(GL_MODELVIEW);
//      glViewport( 0, 0, _vp_w, _vp_h );
//      glColor( _border_color );
//      for( int i=0; i< _borders.getSize(); i++ ) _borders[i]->display();
//      glEnable(GL_LIGHTING);
//    }
  }


  /*! bool ViewSet::_insertCamera(Camera* cam_to_split, Camera* new_cam, bool split_verticaly, double d)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool ViewSet::insertCamera(Camera* cam_to_split, Camera* new_cam, bool split_vertically, double d) {

    if(_cameras.exist(new_cam))
      return false;
    else if(!_cameras.exist(cam_to_split))
      return false;
    else
    {
      _cameras += new_cam;
      if(_cameras.getSize()>2)
        _root.splitCamera(cam_to_split,new_cam,split_vertically,d);
      else
        _root.split( new_cam,split_vertically,d);
      _borders.resetSize();
      _root.prepare( 0, 0,_vp_w, _vp_h, _borders);
      return true;
    }
  }


  /*! void ViewSet::_moveBorder(int x, int y)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewSet::moveBorder(int x, int y) {

    for( int i = 0; i < _selected_borders.getSize(); i++ )
      _selected_borders[i]->move(x,y);
    prepare(_vp_w,_vp_h);
  }


  /*! void ViewSet::_prepare(int w, int h)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewSet::prepare(int w, int h) {

    std::cout << "ViewSet::prepare (w,h): (" << w << "," << h << ")" << std::endl;
    _vp_w = w; _vp_h = h;
    _borders.resetSize();
    _root.prepare(0,0, _vp_w, _vp_h, _borders );
  }


  /*! void ViewSet::removeCamera(Camera* cam)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewSet::removeCamera(Camera* cam) {

    if(_cameras.getSize() > 1)
    {
      int i = _cameras.getIndex(cam);
      if(i>=0) removeCamera(i);
    }
  }


  /*! void ViewSet::_removeCamera(int i)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void ViewSet::removeCamera(int i) {

    if( _cameras.getSize() > 1 ){

      _root.removeCamera(_cameras[i]);
      _cameras.removeIndex(i);
      prepare( _vp_w,_vp_h );
    }
  }


} // END namespace GMlib





#endif // __gmVIEWSET_H__
