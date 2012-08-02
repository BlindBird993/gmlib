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



/*! \file gmmaterial.h
 *
 *  Material Class
 */


#ifndef __gmMATERIAL_H__
#define __gmMATERIAL_H__

#include "gmtexture.h"

// gmlib::core
#include <core/utils/gmstring.h>
#include <core/containers/gmarray.h>
#include <opengl/gmopengl.h>


namespace GMlib {



  class Material;
  class MaterialObject;
  class MaterialObjectList;



  /*! \class Material gmmaterial.h <gmMaterial>
   *  \brief The Material class
   *
   *  containing:
   *    ambient, diffuce and specular colors,
   *		shininess (0-100) and
   *    texture ID and
   *		source and destination blending factors
   */
  class Material {
  public:
    Material(
      const Color& amb 	= Color( 0.7f, 0.0f, 0.0f, 1.0f ),
      const Color& dif 	= Color( 0.7f, 0.0f, 0.0f, 1.0f ),
      const Color& spc 	= Color( 0.7f, 0.0f, 0.0f, 1.0f ),
      float shininess 		= 0.0f,
      const Texture& texture = Texture()
    );
    Material( const Texture& tex, const Material& mat = Material() );
    Material( const Material& copy );
    virtual ~Material();

    const Color&    getAmb() const;
    const Color&    getDif() const;
    const Color&    getSpc() const;
    float           getShininess() const;
    int             getTextureID() const;
    virtual void    glSet() const;
    void            glSetInverse() const;
    virtual void    glUnSet() const;
    bool            isTransparent() const;
    void            set( const Color& amb, const Color& dif, const Color& spc, float shininess, const Texture& texture );
    void            set( const Color& amb, const Color& dif, const Color& spc );
    void            set( const GLenum sfactor, const GLenum dfactor );
    void            set( float shininess );
    void            set( const Texture& texture );
    void            setAmb( const Color& amb );
    void            setDif( const Color& dif );
    void            setDoubleSided( bool s );
    void            setSided( GLenum s );
    void            setSpc( const Color& spc );
    void            setTransparancy( double t );

    Material&       operator =  ( const Material& m );
    bool            operator == ( const Material& m ) const;


  protected:
    Texture         _texture;
    Color           _amb;
    Color           _dif;
    Color           _spc;
    float           _shininess;


  private:

    GLenum          _source_blend_factor;
    GLenum          _destination_blend_factor;
    GLenum          _sided;


  // *****************************
    // IOSTREAM overloaded operators

  #ifdef GM_STREAM

  public:
    template <class T_Stream>
    friend T_Stream& operator << ( T_Stream& out, const Material& m ) {

      out << m._amb       << GMseparator::Element
          << m._dif       << GMseparator::Element
          << m._spc       << GMseparator::Element
          << m._shininess << GMseparator::Element;

//      if(m._texture.isValid()) {
//
//        char *tx=Texture::findFileName(m._texname);
//        out << tx << GMseparator::Group;
//      }
//      else
//      {
//        char* no = "no-texture";
//        out << no << GMseparator::Group;
//      }

      return out;
    }

    template <class T_Stream>
    friend T_Stream& operator >> ( T_Stream& in, Material& m ) {

      static Separator es(GMseparator::Element);
      static Separator gs(GMseparator::Group);
      char fn[255];  // think about this

      in  >> m._amb       >> es
          >> m._dif       >> es
          >> m._spc       >> es
          >> m._shininess >> es
          >> fn           >> gs;

//      if( !( fn[0] == 'n' && fn[1] == 'o' && fn[2] == '-' ) )
//      {
//        Texture tx(true);
//        m.set(tx.LoadGL(fn));
//      }
      m.set( GL_ONE, GL_ONE );
  //		delete fn;
      return in;
    }

    #endif

  }; // END class Material


  // ********************
  // Predefined Materials

  namespace GMmaterial {

    extern Material BlackPlastic;
    extern Material BlackRubber;
    extern Material Brass;
    extern Material Bronze;
    extern Material Chrome;
    extern Material Copper;
    extern Material Emerald;
    extern Material Gold;
    extern Material Jade;
    extern Material Obsidian;
    extern Material Pearl;
    extern Material Pewter;
    extern Material Plastic;
    extern Material PolishedBronze;
    extern Material PolishedCopper;
    extern Material PolishedGold;
    extern Material PolishedGreen;
    extern Material PolishedRed;
    extern Material PolishedSilver;
    extern Material Ruby;
    extern Material Sapphire;
    extern Material Silver;
    extern Material Snow;
    extern Material Turquoise;

  } // END namespace GMlib::Material







  /*! \class MaterialObject gmmaterial.h <gmMaterial>
   *  \brief The MaterialObject class
   *
   *  containing:
   *    A name and
   *	  is a Materia
   */
  class MaterialObject: public Material {
  public:
    MaterialObject(
			const Material& mat = GMmaterial::Snow,
      const char* name = "Snow"
		);

    MaterialObject(
			const Material& mat,
      std::string name
		);

    MaterialObject(	const MaterialObject& m);

    void 							deleteTexture();
    const Material&		getMaterial() const;
    const String&			getName() const;
    const char*				getNameC() const;
    bool 							is(const char* name) const;
    bool 							is(const std::string& name) const;
    bool 							is(const Material& m) const;
    void 							setMaterial(const Material& m);
    void 							setName(const std::string& name);
    void 							setName(const char* name);

    MaterialObject&		operator=(const MaterialObject& m);


	private:
    String		_name;			// Size of name is max 16 letters

  }; // END MaterialObject class








  /*! \class MaterialObjectList gmmaterial.h <gmMaterial>
   *  \brief List of materialObjects class
   *
   *  containing:
   *    List of materialObjects
   */
  class MaterialObjectList : Array<MaterialObject> {
  public:
    MaterialObjectList(bool init=true);
    MaterialObjectList(char* file_name);

    void	initPreDef();
    bool	readFromFile(char* file_name);
    bool	storeToFile(char* file_name);

  }; // END class MaterialObjectList












  /*! Material::Material(	const Color& amb, const Color& dif, const Color& spc, float shininess, const Texture& texture )
   *	\brief Pending Documentation
   *
   *	Default/Standar constructor
   */
  inline
  Material::Material(	const Color& amb, const Color& dif, const Color& spc, float shininess, const Texture& texture )	{

    set( amb, dif, spc, shininess, texture );
    set(GL_ONE,GL_ONE);
    _sided = GL_FRONT_AND_BACK;
  }


  inline
  Material::Material( const Texture& tex, const Material& mat ) {

    *this = mat;

    set( tex );
  }


  /*! Material::Material( const Material&  m )
   *	\brief Pending Documentation
   *
   *	Copy constructor
   */
  inline
  Material::Material( const Material&  copy ) {

    _texture = copy._texture;
    _amb = copy._amb;
    _dif = copy._dif;
    _spc = copy._spc;
    _shininess = copy._shininess;

    _source_blend_factor = copy._source_blend_factor;
    _destination_blend_factor = copy._destination_blend_factor;
    _sided = copy._sided;
  }


  /*! Material::~Material()
   *  \brief Pending Documentations
   *
   *  Pending Documentation
   */
  inline
  Material::~Material() {}


  inline
  const Color& Material::getAmb() const {

    return _amb;
  }


  inline
  const Color& Material::getDif() const {

    return _dif;
  }


  inline
  const Color& Material::getSpc() const {

    return _spc;
  }

  inline
  float Material::getShininess() const {

    return _shininess;
  }


  /*! int Material::getTextureID()
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  int  Material::getTextureID() const {

    return _texture.getTextureId();
  }


  /*! bool Material::isTransparent()
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool Material::isTransparent() const {

    if( _texture.isValid() )
      return ( !((_source_blend_factor==GL_ONE) && (_destination_blend_factor==GL_ONE)) );
    else
      return ( (_amb.getAlpha() < 1.0) && (_dif.getAlpha() < 1.0) && (_spc.getAlpha() < 1.0) );
  };


  /*! void Material::set( const Color& amb, const Color& dif, const Color& spc, float shininess, const Texture& texture )
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::set( const Color& amb, const Color& dif, const Color& spc, float shininess, const Texture& texture ) {

    _amb = amb;
    _dif = dif;
    _spc = spc;
    _shininess = shininess;
    _texture = texture;
  }


  /*! void Material::set(const Color& amb, const Color& dif, const Color& spc )
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::set(const Color& amb, const Color& dif, const Color& spc ) {

    _amb = amb;
    _dif = dif;
    _spc = spc;
  }


  /*! void Material::setAmb(const Color& amb)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::setAmb(const Color& amb)	{

    _amb = amb;
  }


  /*!void Material::setDif(const Color& dif)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::setDif(const Color& dif)	{

    _dif = dif;
  }


  /*! void Material::setDoubleSided(bool s)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::setDoubleSided(bool s)	{

    if(s) _sided = GL_FRONT_AND_BACK;
    else _sided = GL_FRONT;
  }


  /*! void Material::setSided(GLenum s)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::setSided(GLenum s) {

    _sided = s;
  }


  /*! void Material::setSpc(const Color& spc)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::setSpc(const Color& spc)	{

    _spc=spc;
  }


  /*! void Material::setTransparancy(double t)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::setTransparancy(double t) {

    _amb.setAlpha( t );
    _dif.setAlpha( t );
    _spc.setAlpha( t );
  }


  /*! Material& Material::operator=(const Material& m)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   *	Makes a copy
   */
  inline
  Material& Material::operator=(const Material& m) {

    memcpy(this,&m,sizeof(Material));
    return *this;
  }


  /*! bool Material::operator==(const Material& m) const
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool Material::operator==(const Material& m) const {

    return _amb == m._amb && _dif == m._dif && _spc == m._spc &&
      _shininess == m._shininess && _texture == m._texture;
  }

  /*! MaterialObject::MaterialObject(	const Material& mat, const char* name )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObject::MaterialObject(	const Material& mat, const char* name ) : Material(mat)	{

    _name = name;
  }


  /*! MaterialObject::MaterialObject(	const Material& mat, string name )
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObject::MaterialObject(	const Material& mat, std::string name ) : Material(mat)	{

    _name = name;
  }


  /*! MaterialObject::MaterialObject(	const MaterialObject& m)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObject::MaterialObject(	const MaterialObject& m) : Material(m) {

    _name = m._name;
  }


  /*! void MaterialObject::deleteTexture()
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void MaterialObject::deleteTexture() {

    this->_texture = Texture();
  }


  /*! const Material&		MaterialObject::getMaterial() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  const Material&		MaterialObject::getMaterial() const {

    return *this;
  }


  /*! const GM_String&	MaterialObject::getName() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  const String&	MaterialObject::getName() const {

    return _name;
  }


  /*! const char* MaterialObject::getNameC() const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  const char* MaterialObject::getNameC() const {

    return _name.c_str();
  }


  /*! bool MaterialObject::is(const char* name) const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool MaterialObject::is(const char* name) const {

    return _name == name;
  }


  /*! bool MaterialObject::is(const string& name) const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool MaterialObject::is(const std::string& name) const {

    return _name == name;
  }


  /*! bool MaterialObject::is(const Material& m) const
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  bool MaterialObject::is(const Material& m) const {

    return m == (Material)(*this);
  }


  /*! void MaterialObject::setMaterial(const Material& m)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void MaterialObject::setMaterial(const Material& m)	{

    Material::operator = ( m );
  }

  /*! void MaterialObject::setName(const string& name)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void MaterialObject::setName(const std::string& name) {

    _name = name;
  }

  /*! void MaterialObject::setName(const char* name)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  void MaterialObject::setName(const char* name) {

    _name = name;
  }


  /*! MaterialObject& MaterialObject::operator=(const MaterialObject& m)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObject& MaterialObject::operator=(const MaterialObject& m) {

    Material::operator = ( m );

    _name         = m._name;

    return *this;
  }

  /*! MaterialObjectList::MaterialObjectList(bool init)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObjectList::MaterialObjectList(bool init) {

    if(init)
      initPreDef();
  }


  /*! MaterialObjectList::MaterialObjectList(char* file_name)
   *	\brief Pending Documentation
   *
   *	Pending Documentation
   */
  inline
  MaterialObjectList::MaterialObjectList( char* file_name ) {

    if(file_name) readFromFile(file_name);
  }

} // END namespace GMlib


#endif // __gmMATERIAL_H__
