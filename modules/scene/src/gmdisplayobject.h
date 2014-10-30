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



/*! \file gmdisplayobject.h
 *  \brief Pending Detailed Documentation
 *
 *  Interface to the Display Object class
 *
 *  \todo
 *  - Move variable documentation physicaly out of the header file.
 *  - Translage documentattion text for the class
 */



#ifndef __gmDISPLAYOBJECT_H__
#define __gmDISPLAYOBJECT_H__


#include "gmsceneobject.h"

// gmlib
#include <opengl/gmprogram.h>

// stl
#include <string>





namespace GMlib {


  class Visualizer;


  /*! \class DisplayObject gmdisplayobject.h <gmDisplayObject>
   *  \brief The DisplayObject Class
   *
   *  Pending Documentation
   */
  class DisplayObject : public SceneObject {
  public:
    DisplayObject(
      const Point<float,3>&  pos = Point<float,3>(0,0,0),
      const Vector<float,3>& dir = Vector<float,3>(1,0,0),
      const Vector<float,3>& up  = Vector<float,3>(0,0,1)
    );

    DisplayObject(
      const Point<float,3>&  lock_pos,
      const Point<float,3>&  pos = Point<float,3>(0,0,0),
      const Vector<float,3>& up  = Vector<float,3>(0,0,1)
    );

    DisplayObject(
      SceneObject* lock_object,
      const Point<float,3>&  pos = Point<float,3>(0,0,0),
      const Vector<float,3>& up  = Vector<float,3>(0,0,1)
    );

    DisplayObject(const DisplayObject& s);
    virtual ~DisplayObject();









    Array<Visualizer*>&           getVisualizers();
    const Array<Visualizer*>&     getVisualizers() const;
    virtual void                  insertVisualizer( Visualizer* visualizer );
    virtual void                  removeVisualizer( Visualizer* visualizer );

    const Color&                  getColor() const;
    Color&                        getColor();
    void                          setColor( const Color& c );
    const Material&               getMaterial() const;
    Material&                     getMaterial();
    virtual void                  setMaterial(const Material& m);

    bool                          isCollapsed() const;
    virtual void                  setCollapsed(bool c);
    virtual bool                  toggleCollapsed();
    bool                          isLighted() const;
    void                          setLighted( bool lighted );
    bool                          isOpaque() const;
    void                          setOpaque( bool o );

    // Virtual from SceneObject
    virtual void                  rotate(Angle a, const Vector<float,3>& rot_axel);
    virtual void                  rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    virtual void                  rotate(const UnitQuaternion<float>& q);
    virtual void                  rotateGlobal(Angle a, const Vector<float,3>& rot_axel);
    virtual void                  rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    virtual void                  rotateGlobal(const UnitQuaternion<float>& q);
    virtual void                  translate(const Vector<float,3>& trans_vector);
    virtual void                  translateGlobal(const Vector<float,3>& trans_vector);


  protected:


    Array<Visualizer*>            _visualizers;



    // *****************
    // Virtual functions
    // from SceneObject
    void                          localSimulate(double dt);



//  private:


//    #ifdef GM_STREAM
//    public:

//      // Stream constructor
//      /*! DisplayObject( T_Stream& in, int st)
//       *  \brief DisplayObject Stream Constructor
//       *
//       *  Pending further Documentation
//       *
//       *  \todo
//       *  - Find out why this doesn't work:
//       *    DisplayObject( T_Stream& in, int st) : SceneObject( in, st ), _matrix(), _matrix_scene_inv()
//       */
//      template <typename T_Stream>
//      DisplayObject( T_Stream& in, int st) : SceneObject( in, st ) {

//        prIn(in);
//        init();
//        _side	= _up^_dir;
//        _locked	= false;
//        _lock_object	= 0;
//        basisChange(_side, _up, _dir, _pos);
//      }


//      template <typename T_Stream>
//      friend T_Stream& operator<<(T_Stream& out, const DisplayObject& v) {

//        out << *((SceneObject*)& v);
//        v.prOut(out);
//        return out;
//      }

//      template <typename T_Stream>
//      friend T_Stream& operator>>(T_Stream& in, DisplayObject& v) {

//        in >> *((SceneObject*)& v);
//        v.prIn(in);
//        return in;
//      }


//    private:
//      //, const DisplayObject& v)
//      template <typename T_Stream>
//      void prOut(T_Stream& out) const {

//        out << _pos << GMseparator::Object << _dir << GMseparator::Object << _up << GMseparator::Object;
//      }

//      //, DisplayObject& v)
//      template <typename T_Stream>
//      void prIn(T_Stream& in) {

//        static Separator os(GMseparator::Object);
//        in >> _pos >> os >> _dir >> os >> _up >> os;
//      }
//    #endif

  }; // END DisplayObject class

















  inline
  bool DisplayObject::isCollapsed() const {

    return _collapsed;
  }


  inline
  bool DisplayObject::isOpaque() const {

    return _opaque;
  }

  inline
  void DisplayObject::setCollapsed(bool c) {

    _collapsed = c;
  }


  inline
  void DisplayObject::setOpaque( bool o ) {

    _opaque = o;
  }

  inline
  bool DisplayObject::toggleCollapsed() {

    return _collapsed = !_collapsed;
  }



} // END namespace GMlib

#endif // __gmDISPLAYOBJECT_H__
