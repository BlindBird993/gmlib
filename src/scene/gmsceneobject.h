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



/*! \file gmsceneobject.h
 *  \brief Interface to the Scene Object class
 *
 *  Pending Detailed Documentation
 *
 *  \todo
 *  - Move variable documentation physicaly out of the header file.
 *  - Translage documentation text for the class, from Norwegian to English
 */

#ifndef __gmSCENEOBJECT_H__
#define __gmSCENEOBJECT_H__


/////////////////////

// getIdentity
#define GM_DECLARE_SO_IDENTITY( CNAME ) \
  std::string getIdentity() const { \
    return #CNAME; \
  }

// makeCopy
#define GM_DECLARE_SO_MAKECOPY( CNAME ) \
  SceneObject* makeCopy() { \
    return new CNAME(*this); \
  }

#define GM_DECLARE_SO_MAKECOPY_NULL() \
  SceneObject* makeCopy() { \
    return 0x0; \
  }


// SceneObject macros
#define GM_SCENEOBJECT( CNAME ) \
  public: \
    GM_DECLARE_SO_IDENTITY( CNAME ) \
    GM_DECLARE_SO_MAKECOPY( CNAME ) \
  private:

#define GM_SCENEOBJECT_NULL( CNAME ) \
  public: \
    GM_DECLARE_SO_IDENTITY( CNAME ) \
    GM_DECLARE_SO_MAKECOPY_NULL() \
  private:

//////////////////



#include "gmfrustum.h"
#include "gmscaleobject.h"
#include "utils/gmmaterial.h"
#include "visualizer/gmvisualizer.h"

// stl
#include <string>





namespace GMlib{


  class Camera;
  class Scene;
  class Light;
  class Visualizer;


  enum GM_SO_TYPE {

    // Basic Types
    GM_SO_TYPE_SCENEOBJECT                    = 0x0001,
    GM_SO_TYPE_CAMERA                         = 0x0002,
    GM_SO_TYPE_LIGHT                          = 0x0003,
    GM_SO_TYPE_SELECTOR                       = 0x0050,
    GM_SO_TYPE_SELECTOR_GRID                  = 0x0051,

    // Point
    GM_SO_TYPE_POINT                          = 0x0200,

    // Curves
    GM_SO_TYPE_CURVE                          = 0x1000,
    GM_SO_TYPE_CURVE_BEZIER                   = 0x1001,
    GM_SO_TYPE_CURVE_BSPLINE                  = 0x1002,
    GM_SO_TYPE_CURVE_ERBS                     = 0x1003,

    // Surfaces
    GM_SO_TYPE_SURFACE                        = 0x2000,
    GM_SO_TYPE_SURFACE_BEZIER                 = 0x2001,
    GM_SO_TYPE_SURFACE_BSPLINE                = 0x2002,
    GM_SO_TYPE_SURFACE_ERBS                   = 0x2003,

    // Volumes
    GM_SO_TYPE_VOLUME                         = 0x3000,

    // Flows
    GM_SO_TYPE_FLOW                           = 0x4000
  };







  /*! \class SceneObject gmsceneobject.h <gmSceneObject>
   *  \brief SceneObject is the base class for anything that steps onto a Scene
   *
   * 	It contains as private, a unique name for indentification used in Select(), and an array containg all its children.
   *
   * 	Further, as protected members, two matrices for local transformation of the object, and a SurroundingSphere that always should be made.
   *
   *
   * 				Det er to virtuelle funksjoner localDisplay og localSelect
   * 					som alle avledede klasser må ha sin versjon av.
   * 				Arbeidsdelingen er slik at display og select foretar
   * 					transformasjonen lagret i matrix, og displayer alle
   * 					sub-objektene til objektet. Men etter transformasjonen
   * 					og før sub-objektene displayes kalles localDisplay
   * 					(eventuelt localSelect). I localDisplay kan en så
   * 					displaye det som ikke displayes i sub-objektene og/eller
   * 					foreta transformasjoner av sub-objekter for
   * 					å simulere bevegelser.
   * 				Det er også en insertSubObject-funksjon som avledede klasser
   * 				    kan bruke for å lage sub-objekt. Hvis en avledet klasse
   * 					trenger tilgang til et objekt for bevegelsessimulering
   * 					bør den lage en egen peker for det.
   * 		public:
   * 				Konstuktør med mulige default verdier og sletter
   * 				En display funksjon for displaying av objektet.
   * 				En select funksjon for plukking(select) av objektet med mus.
   * 				En simulate funksjon for at objektet kan bevege subobjekter.
   * 				En find funksjon for å finne en funksjon med et gitt navn.
   * 				En rotate, scale og translate funksjon for å
   * 				   posisjonere objektet relativt i forhold til morsobjektet
   */
  class SceneObject {
  public:

    mutable const SceneObject                 *_copy_of;    //! Internal variable for use when coping the object.

    SceneObject(
      const Vector<float,3>& trans  = Vector3D<float>(0,0,0),
      const Point<float,3>&  scale  = Point3D<float>(1,1,1),
      const Vector<float,3>& rotate = Vector3D<float>(1,0,0),
      Angle a=0);

    SceneObject( const SceneObject& d );
    virtual ~SceneObject();

    virtual SceneObject*        makeCopy() = 0;
    virtual std::string         getIdentity() const = 0;

    virtual void                edit(int selector_id);
    virtual void                edit(SceneObject* lp);
    virtual void                edit();
    virtual void                editPos(Vector<float,3> delta);
    virtual void                enableChildren( bool enable = true );
    SceneObject*                find(unsigned int name);
    bool                        flipSelected();
    Point<float,3>              getCenterPos() const;
    Array<SceneObject*>&        getChildren();
    const Color&                getColor() const;
    Color&                      getColor();
    const Material&             getMaterial() const;
    Material&                   getMaterial();
    virtual const HqMatrix<float,3>&  getMatrix() const;
    virtual HqMatrix<float,3>&  getMatrix();
    const HqMatrix<float,3>&    getMatrixGlobal() const;
    const HqMatrix<float,3>&    getMatrixParentGlobal() const;
    const HqMatrix<float,3>&    getModelViewMatrix( const Camera *cam, bool local_cs = true ) const;
    const HqMatrix<float,3>&    getModelViewProjectionMatrix( const Camera *cam, bool local_cs = true ) const;
    unsigned int                getName() const;
    SceneObject*                getParent() const;
    const HqMatrix<float,3>&    getProjectionMatrix( const Camera* cam ) const;
    Scene*                      getScene() const;
    const GLProgram&            getSelectProgram() const;
    bool                        getSelected() const;
    Sphere<float,3>             getSurroundingSphere() const;
    Sphere<float,3>             getSurroundingSphereClean() const;
    int                         getTypeId() const;
    virtual unsigned int        getVirtualName() const;
    Array<Visualizer*>&         getVisualizers();
    const Array<Visualizer*>&   getVisualizers() const;
    void                        insert(SceneObject* obj);
    virtual void                insertVisualizer( Visualizer* visualizer );
    bool                        isCollapsed() const;
    bool                        isLighted() const;
    bool                        isOpaque() const;
    bool                        isPart() const;
    bool                        isSelected() const;
    virtual bool                isVisible() const;
    void                        remove(SceneObject* obj);
    virtual void                removeVisualizer( Visualizer* visualizer );
    virtual void                rotate(Angle a, const Vector<float,3>& rot_axel);
    virtual void                rotate(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    virtual void                rotateGlobal(Angle a, const Vector<float,3>& rot_axel);
    virtual void                rotateGlobal(Angle a, const Point<float,3>& p,const UnitVector<float,3>& d);
    virtual void                scale(const Point<float,3>& scale_factor);
    virtual void                selectEvent(int selector_id);
    virtual void                setCollapsed(bool c);
    void                        setColor( const Color& c );
    void                        setIsPart( bool part );
    void                        setLighted( bool lighted );
    virtual void                setMaterial(const Material& m);
    void                        setMatrix( const HqMatrix<float,3>& mat );
    void                        setOpaque( bool o );
    void                        setParent(SceneObject* obj);
    virtual void                setSelected(bool s);
    void                        setSelectProgram( const GLProgram& prog );
    virtual void                setVisible( bool v, int prop = 0 );
    void                        setStandardRepVisualizer( Visualizer* visu = 0x0 );
    virtual bool                toggleCollapsed();
    virtual bool                toggleVisible();
    virtual void                translate(const Vector<float,3>& trans_vector);
    virtual void                translateGlobal(const Vector<float,3>& trans_vector);

  protected:
    friend class Scene;

    bool                        _is_part;  //! true if the object is seen as a part of a larger object

    int                         _type_id;
    Array<SceneObject*>	        _children;
    //! The scene of the display hiearchy
    Scene*                      _scene;
    //! the mother in the hierarchy (tree). moved here from private
    SceneObject*                _parent;
    //! The difference matrix from mother to this.
    HqMatrix<float,3>           _matrix;
    //! The difference matrix from global to this.
    HqMatrix<float,3>           _present;
    //! The scaling for this and the children.
  public:
    ScaleObject                 _scale;
  protected:
    //! Using local coordinate system, default is true
    bool                        _local_cs;
    //! This variable is only for camera.
    bool                        _active;
    //! for this object
    Sphere<float,3>             _global_sphere;
    //! included all children
    Sphere<float,3>             _global_total_sphere;
    bool                        _selected;
    //! culling on invisible items
    bool                        _visible;

    bool                        _collapsed;

    Material                    _material;
    Color                       _color;
    bool                        _lighted;
    bool                        _opaque;

    Array<Visualizer*>          _visualizers;
    Visualizer                  *_std_rep_visu;

    virtual void                localDisplay();
    virtual void                localSelect();
    virtual void                localSimulate(double dt);
    void                        reset();
    void                        setSurroundingSphere( const Sphere<float,3>& b );
    void                        updateSurroundingSphere( const Point<float,3>& p );


    virtual void                simulate( double dt );

  protected:
//  private:
    static unsigned int         _free_name;	//! For automatisk name-generations.
    unsigned int                _name;		//! Unic name for this object, used for selecting
    Sphere<float,3>             _sphere;	//! Surrounding sphere for this object

    GLProgram                   _select_prog;


    int                         prepare(Array<Light*>& obj, Array<HqMatrix<float,3> >& mat, Scene* s, SceneObject* mother = 0);
    virtual void                prepareDisplay(const HqMatrix<float,3>& m);

  public:
    virtual void                culling( Array<SceneObject*>&, const Frustum& );
    void                        fillObj( Array<SceneObject*>& );
    void                        display( Camera* cam );
    void                        displaySelection( Camera* cam );
    void                        select(int what = -1, Camera* cam = 0x0 );



  // *****************************
  // IOSTREAM overloaded operators

  #ifdef GM_STREAM

  public:

    template <typename T_Stream>
    friend T_Stream& operator << ( T_Stream& out, SceneObject& s ) {

      out << s._type_id << GMseparator::Object;
      out << s._matrix  << GMseparator::Object
          << s._scale   << GMseparator::Object;

  /*		if(st)
      {
        out << _object.size() << GMseparator::Object;
        for(int i=0; i<_object.size(); i++)
          if(st>1 || (_object[i]->typeId() != 2))
            out << *(_object[i]);
      }*/
      return out;
    }

    template <typename T_Stream>
    friend T_Stream& operator >> ( T_Stream& in, SceneObject& s ) {

      static Separator os(GMseparator::Object);

      in >> s._type_id  >> os;
      in >> s._matrix   >> os >> s._scale >> os;
  /*		if(st)
      {
        int nr;
        in >> nr >> os;
        for(int i=0; i<nr; i++)
            _object += newDisplayObject(in);
      }*/
      return in;
    }

    template <typename T_Stream>
    SceneObject( T_Stream& in, int st ) {

      in >> *this;

      _name	      = _free_name++;
      _active	    = false;
      _local_cs   = true;
      _visible    = true;
      _collapsed  = false;
    }

    #endif

  }; // END class SceneObject











  /*! void SceneObject::_display()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::display( Camera* cam ) {

    if(!_active) {

      const HqMatrix<float,3> &mvmat = getModelViewMatrix(cam);
      const HqMatrix<float,3> &pmat = getProjectionMatrix(cam);

      if(_collapsed) {

        const GLProgram &prog = _std_rep_visu->getRenderProgram();
        prog.bind();
        prog.setUniform( "u_mvmat", mvmat, 1, true );
        prog.setUniform( "u_mvpmat", pmat * mvmat, 1, true );
        _std_rep_visu->display();
        prog.unbind();
      }
      else {

        for( int i = 0; i < _visualizers.getSize(); ++i ) {

          const GLProgram &prog = _visualizers[i]->getRenderProgram();
          prog.bind();
          prog.setUniform( "u_mvmat", mvmat, 1, true );
          prog.setUniform( "u_mvpmat", pmat * mvmat, 1, true );
          _visualizers[i]->display();
          prog.unbind();
        }

        localDisplay();
      }
    }
  }

  /*! void SceneObject::displaySelection( Camera* cam )
   *  \brief Pending
   *
   *  Pending
   */
  inline
  void SceneObject::displaySelection( Camera* cam ) {

    if(!_active && _selected ) {

      const GLProgram render_select_prog("render_select");
      render_select_prog.setUniform( "u_mvpmat", getModelViewProjectionMatrix(cam), 1, true );
      render_select_prog.bind();

      if( _collapsed )
        _std_rep_visu->select();
      else {

        for( int i = 0; i < _visualizers.getSize(); ++i )
          _visualizers[i]->select();
      }
//        localSelect();
      render_select_prog.unbind();
    }
  }

  /*! void SceneObject::_select( int what, Camera* cam )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::select( int what, Camera* cam ) {

    if( !_active && ( what == 0 || what == _type_id || ( what < 0 && what + _type_id != 0 ) ) ) {

      const GLProgram &select_prog = getSelectProgram();
      select_prog.setUniform( "u_mvpmat", getModelViewProjectionMatrix(cam), 1, true );
      select_prog.setUniform( "u_color", Color(getVirtualName()) );

      if( _collapsed )
        _std_rep_visu->select();
      else
        localSelect();
    }
  }


  /*! void SceneObject::edit(int selector_id)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::edit( int /* selector_id */ ) {}


  /*! void SceneObject::edit(SceneObject* lp)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::edit( SceneObject* /* obj */ ) {}


  /*! void SceneObject::edit()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::edit() {}


  /*! void SceneObject::editPos(Vector<float,3> delta)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::editPos( Vector<float,3> /* delta*/  ) {}


  /*! void SceneObject::enableChildren( bool enable = true )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::enableChildren( bool enable ) {

    for(int i=0;i<_children.getSize();i++) _children[i]->setVisible(enable);
  }


  /*! bool SceneObject::flipSelected()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::flipSelected() {

    _selected = !_selected;

    if(_selected)
      edit();
    return _selected;
  }


  /*! Point<float,3> SceneObject::getCenterPos() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Point<float,3> SceneObject::getCenterPos() const	{

    return  getSurroundingSphere().getPos();
  }


  /*! Array<SceneObject*>& SceneObject::getChildren()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Array<SceneObject*>& SceneObject::getChildren(){

    return _children;
  }


  /*! const GL_Matrix& SceneObject::getMatrixGlobal() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  const HqMatrix<float,3>& SceneObject::getMatrixGlobal() const {

    return _present;
  }


  /*! unsigned int SceneObject::getName() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  unsigned int SceneObject::getName() const {

    return _name;
  }

  inline
  SceneObject* SceneObject::getParent() const {

    return _parent;
  }

  inline
  Scene* SceneObject::getScene() const {

    return _scene;
  }

  inline
  const GLProgram &SceneObject::getSelectProgram() const {

    return _select_prog;
  }


  /*! bool SceneObject::getSelected()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::getSelected() const {

    return _selected;
  }


  /*! Sphere<float,3>	SceneObject::getSurroundingSphere() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Sphere<float,3> SceneObject::getSurroundingSphere() const	{

    return  _global_total_sphere;
  }


  /*! int SceneObject::getTypeId()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  int SceneObject::getTypeId() const {

    return _type_id;
  }

  inline
  unsigned int SceneObject::getVirtualName() const {

    if( _parent && _is_part ) return _parent->getVirtualName();
    else                      return getName();
  }

  /*! bool SceneObject::isCollapsed() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::isCollapsed() const {

    return _collapsed;
  }


  inline
  bool SceneObject::isOpaque() const {

    return _opaque;
  }


  /*! bool SceneObject::isSelected() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::isSelected() const {

    return _selected;
  }


  /*! bool SceneObject::isVisible() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::isVisible() const {

    return _visible;
  }


  /*! void SceneObject::selectEvent(int selector_id)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::selectEvent( int /* selector_id */ ) {}



  /*! void SceneObject::setCollapsed(bool c)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::setCollapsed(bool c) {

    _collapsed = c;
  }


  inline
  void SceneObject::setOpaque( bool o ) {

    _opaque = o;
  }



  /*! void SceneObject::setParent( SceneObject* obj )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::setParent( SceneObject* obj ) {

    _parent = obj;
  }



  /*! void SceneObject::setSelected( bool s )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::setSelected( bool s ) {

    _selected = s;
  }



  /*! void SceneObject::setVisible(bool v)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void SceneObject::setVisible( bool v, int prop ) {

    _visible = v;

    // Propagate Children
    if( prop != 0 ) {

      if( prop > 0)
        prop -= 1;

      for( int i = 0; i < _children.getSize(); i++ )
        _children[i]->setVisible( v, prop );
    }
  }



  /*! void SceneObject::toggleCollapsed()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::toggleCollapsed() {

    return _collapsed = !_collapsed;
  }

  /*! void SceneObject::toggleVisible()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool SceneObject::toggleVisible() {

    return _visible =! _visible;
  }


} // END namespace GMlib



#endif  // __gmSCENEOBJECT_H__
