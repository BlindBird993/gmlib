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



/*! \file gmMaterial_Material.c
 *  \brief Inline Material class implementations
 *
 *  Implementation of the Material class.
 *
 *  \date   2008-08-03
 */


namespace GMlib {


  /*! Material::Material(	const GL_Color& amb, const GL_Color& dif, const GL_Color& spc, float shininess, const Texture& texture )
   *	\brief Pending Documentation
   *
   *	Default/Standar constructor
   */
  inline
  Material::Material(	const GLColor& amb, const GLColor& dif, const GLColor& spc, float shininess, const Texture& texture )	{

    set( amb, dif, spc, shininess, texture );
    set(GL_ONE,GL_ONE);
    _sided = GL_FRONT_AND_BACK;
    _transparancy = 1;
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
    _transparancy = copy._transparancy;

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
  const GLColor& Material::getAmb() const {

    return _amb;
  }


  inline
  const GLColor& Material::getDif() const {

    return _dif;
  }


  inline
  const GLColor& Material::getSpc() const {

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

    return ( !((_source_blend_factor==GL_ONE) && (_destination_blend_factor==GL_ONE)) );
  };


  /*! void Material::set( const GLColor& amb, const GLColor& dif, const GLColor& spc, float shininess, const Texture& texture )
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::set( const GLColor& amb, const GLColor& dif, const GLColor& spc, float shininess, const Texture& texture ) {

    _amb = amb;
    _dif = dif;
    _spc = spc;
    _shininess = shininess;
    _texture = texture;
  }


  /*! void Material::set(const GLColor& amb, const GLColor& dif, const GLColor& spc )
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::set(const GLColor& amb, const GLColor& dif, const GLColor& spc ) {

    _amb = amb;
    _dif = dif;
    _spc = spc;
  }


  /*! void Material::setAmb(const GLColor& amb)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::setAmb(const GLColor& amb)	{

    _amb = amb;
  }


  /*!void Material::setDif(const GLColor& dif)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::setDif(const GLColor& dif)	{

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


  /*! void Material::setSpc(const GLColor& spc)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::setSpc(const GLColor& spc)	{

    _spc=spc;
  }


  /*! void Material::setTransparancy(double t)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Material::setTransparancy(double t) {

    _transparancy = t;
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

}
