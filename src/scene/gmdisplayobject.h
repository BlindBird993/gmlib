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

// stl
#include <string>





namespace GMlib {


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




    virtual Vector<float,3>       getDir() const;
    virtual Vector<float,3>       getSide() const;
    virtual Vector<float,3>       getUp() const;
    virtual Point<float,3>        getPos() const;
    void                          set( const Point<float,3>&  pos,
                                       const Vector<float,3>& dir,
                                       const Vector<float,3>& up );

    const HqMatrix<float,3>&      getMatrixToScene() const;
    const HqMatrix<float,3>&      getMatrixToSceneInverse() const;

    const APoint<float,3>&        getLockPos() const;
    double                        getLockDist() const;
    bool                          isLocked() const;
    virtual void                  lock(SceneObject* obj);
    virtual void                  lock(const Point<float,3>& pos);
    virtual void                  lock(double d);
    void                          unLock();

    virtual void                  move(float d);
    virtual void                  move(const Vector<float,3>& t);
    virtual void                  move(char,double);
    virtual void                  move(const Vector<float,2>& t);
    virtual void                  roll(Angle a);
    virtual void                  tilt(Angle a);
    virtual void                  turn(Angle a);

    const HqMatrix<float,3>&      getModelViewMatrix( const Camera *cam, bool local_cs = true ) const;
    const HqMatrix<float,3>&      getModelViewProjectionMatrix( const Camera *cam, bool local_cs = true ) const;
    const HqMatrix<float,3>&      getProjectionMatrix( const Camera* cam ) const;

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

    const GL::GLProgram&          getSelectProgram() const;
    void                          setSelectProgram( const GL::GLProgram& prog );

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
    // Matrices from Scene to this
    HqMatrix<float,3>             _matrix_scene;
    HqMatrix<float,3>             _matrix_scene_inv;

    Point<float,3>                _pos;
    UnitVector<float,3>           _dir;
    UnitVector<float,3>           _side;
    UnitVector<float,3>           _up;

    Point<float,3>                _lock_pos;
    SceneObject*                  _lock_object;
    bool                          _locked;

    bool                          _collapsed;
    Material                      _material;
    Color                         _color;
    bool                          _lighted;
    bool                          _opaque;

    Array<Visualizer*>            _visualizers;
    GL::GLProgram                 _select_prog;

    virtual void                  basisChange( const Vector<float,3>& dir,
                                               const Vector<float,3>& side,
                                               const Vector<float,3>& up,
                                               const Vector<float,3>& pos);

    Point<float,3>                getSceneLockPos();
    void                          updateOrientation(const Point<float,3>& lock_at_p);

    // *****************
    // Virtual functions
    // from SceneObject
    void                          prepareDisplay(const HqMatrix<float,3>& m);
    void                          localSimulate(double dt);



  private:
    void                      init();


    #ifdef GM_STREAM
    public:

      // Stream constructor
      /*! DisplayObject( T_Stream& in, int st)
       *  \brief DisplayObject Stream Constructor
       *
       *  Pending further Documentation
       *
       *  \todo
       *  - Find out why this doesn't work:
       *    DisplayObject( T_Stream& in, int st) : SceneObject( in, st ), _matrix(), _matrix_scene_inv()
       */
      template <typename T_Stream>
  //    DisplayObject( T_Stream& in, int st) : SceneObject( in, st ), _matrix(), _matrix_scene_inv() {
      DisplayObject( T_Stream& in, int st) : SceneObject( in, st ), _matrix_scene_inv() {

        prIn(in);
        init();
        _side	= _up^_dir;
        _locked	= false;
        _lock_object	= 0;
        basisChange(_side, _up, _dir, _pos);
      }


      template <typename T_Stream>
      friend T_Stream& operator<<(T_Stream& out, const DisplayObject& v) {

        out << *((SceneObject*)& v);
        v.prOut(out);
        return out;
      }

      template <typename T_Stream>
      friend T_Stream& operator>>(T_Stream& in, DisplayObject& v) {

        in >> *((SceneObject*)& v);
        v.prIn(in);
        return in;
      }


    private:
      //, const DisplayObject& v)
      template <typename T_Stream>
      void prOut(T_Stream& out) const {

        out << _pos << GMseparator::Object << _dir << GMseparator::Object << _up << GMseparator::Object;
      }

      //, DisplayObject& v)
      template <typename T_Stream>
      void prIn(T_Stream& in) {

        static Separator os(GMseparator::Object);
        in >> _pos >> os >> _dir >> os >> _up >> os;
      }
    #endif

  }; // END DisplayObject class













  /*! void DisplayObject::basisChange( const Vector<float,3>& x, const Vector<float,3>& y, const Vector<float,3>& z, const Vector<float,3>& p )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void DisplayObject::basisChange( const Vector<float,3>& x, const Vector<float,3>& y, const Vector<float,3>& z, const Vector<float,3>& p ) {

    static Vector<float,4> nx, ny, nz, np;
    memcpy( nx.getPtr(), z.getPtr(), 12 );
    memcpy( ny.getPtr(), x.getPtr(), 12 );
    memcpy( nz.getPtr(), y.getPtr(), 12 );
    memcpy( np.getPtr(), p.getPtr(), 12 );
    nx[3] = ny[3] = nz[3] = 0.0f;
    np[3] = 1.0f;

    _matrix.setCol( nx, 0 );
    _matrix.setCol( ny, 1 );
    _matrix.setCol( nz, 2 );
    _matrix.setCol( np, 3 );
  }


  /*! Vector<float,3>	DisplayObject::getDir()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In scene coordinates **
   */
  inline
  Vector<float,3>	DisplayObject::getDir() const	{

    return _matrix_scene*_dir;
  }

  /*! Point<float,3>	DisplayObject::getLockPos()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In the coordinates of the scene. **
   */
  inline
  const APoint<float,3>& DisplayObject::getLockPos() const {

    if(_lock_object)
      return  _lock_object->getCenterPos();
    else
      return  _lock_pos;
  }


  /*! Pdouble DisplayObject::getLockDist()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  double DisplayObject::getLockDist() const {

    if(_locked)
      return  ( getLockPos()-getPos() ).getLength();
    else
      return  0.0;
  }

  inline
  const HqMatrix<float,3>& DisplayObject::getMatrixToScene() const {

    return _matrix_scene;
  }

  inline
  const HqMatrix<float,3>&  DisplayObject::getMatrixToSceneInverse() const {

    return _matrix_scene_inv;
  }


  /*! Point<float,3> DisplayObject::getPos()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In scene coordinates **
   */
  inline
  Point<float,3> DisplayObject::getPos() const {

    return _matrix_scene * _pos;
  }


  /*! Vector<float,3>	DisplayObject::getSide()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In scene coordinates **
   */
  inline
  Vector<float,3>	DisplayObject::getSide() const {

    return _matrix_scene * _side;
  }


  /*! Vector<float,3>	DisplayObject::getUp()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   *  ** In scene coordinates **
   */
  inline
  Vector<float,3>	DisplayObject::getUp() const {

    return _matrix_scene * _up;
  }


  /*! bool DisplayObject::isLocked()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool DisplayObject::isLocked() const {

    return _locked;
  }


  /*! Point<float,3> DisplayObject::getSceneLockPos()
   *  \brief Get Lock Position in Scene Coordinates
   *
   *  Get Lock Position in Scene coordinates
   */
  inline
  Point<float,3> DisplayObject::getSceneLockPos() {

    if(_lock_object)
      return _matrix_scene_inv * _lock_object->getCenterPos();
    else
      return _matrix_scene_inv * _lock_pos;
  }

  /*! void DisplayObject::updateOrientation(const Point<float,3>& lock_pos )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void DisplayObject::updateOrientation(const Point<float,3>& lock_pos ) {

    _dir		= lock_pos - _pos;
    _up			= _up - (_up * _dir) * _dir;
    _side		= _up ^ _dir;
  }

  inline
  const GL::GLProgram &DisplayObject::getSelectProgram() const {

    return _select_prog;
  }

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
