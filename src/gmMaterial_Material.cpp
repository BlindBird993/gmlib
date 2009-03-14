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



/*! \file gmMaterial_Material.cpp
 *
 *  Implementation of the Material class.
 *
 *  \date   2008-07-24
 */


#include "gmMaterial.h"


namespace GMlib {

  namespace GMmaterial {

    //	Predefined Materials
    /*
    Material name				  									GL_AMBIENT																			GL_DIFFUSE																			GL_SPECULAR																				GL_SHININESS
    */
    Material BlackPlastic	    = Material ( 	GLColor( 0.0,      0.0,      0.0,      1.0),		GLColor( 0.01,      0.01, 		0.01, 		1.0),		GLColor( 0.50, 			0.50, 		 0.50, 			1.0),		32.0		);
    Material BlackRubber	    = Material ( 	GLColor( 0.02,     0.02,     0.02,     1.0),		GLColor( 0.01,      0.01, 		0.01, 		1.0),		GLColor( 0.4, 			0.4, 			 0.4, 			1.0),		10.0		);
    Material Brass			      = Material ( 	GLColor( 0.329412, 0.223529, 0.027451, 1.0),   	GLColor( 0.780392,  0.568627, 0.113725,	1.0),		GLColor( 0.992157,	0.941176,	 0.807843, 	1.0), 	27.8974	);
    Material Bronze			      = Material ( 	GLColor( 0.2125,   0.1275,   0.054,    1.0),		GLColor( 0.714,     0.4284, 	0.18144, 	1.0),		GLColor( 0.393548,  0.271906,  0.166721, 	1.0),		25.6		);
    Material Chrome			      = Material ( 	GLColor( 0.25,     0.25,     0.25,     1.0),		GLColor( 0.4,       0.4, 			0.4, 			1.0),		GLColor( 0.774597, 	0.774597,  0.774597, 	1.0),		76.8		);
    Material Copper			      = Material ( 	GLColor( 0.19125,  0.0735,   0.0225,   1.0),		GLColor( 0.7038,    0.27048, 	0.0828, 	1.0),		GLColor( 0.256777, 	0.137622,  0.086014, 	1.0),		12.8		);
    Material Emerald		      = Material ( 	GLColor( 0.0215,   0.1745,   0.0215,   0.55),		GLColor( 0.07568,   0.61424, 	0.07568, 	0.55),	GLColor( 0.633, 		0.727811,  0.633, 		0.55),	76.8		);
    Material Gold			        = Material ( 	GLColor( 0.24725,  0.1995,   0.0745,   1.0),		GLColor( 0.75164,   0.60648, 	0.22648, 	1.0),		GLColor( 0.628281, 	0.555802,  0.366065, 	1.0),		51.2		);
    Material Jade			        = Material ( 	GLColor( 0.135,    0.2225,   0.1575,   0.95),		GLColor( 0.54,      0.89, 		0.63, 		0.95),	GLColor( 0.316228, 	0.316228,  0.316228, 	0.95),	12.8		);
    Material Obsidian		      = Material ( 	GLColor( 0.05375,  0.05,     0.06625,  0.82),		GLColor( 0.18275,   0.17, 		0.22525, 	0.82),	GLColor( 0.332741, 	0.328634,  0.346435, 	0.82),	38.4		);
    Material Pearl			      = Material ( 	GLColor( 0.25,     0.20725,  0.20725,  0.922),	GLColor( 1.0,       0.829, 		0.829, 		0.922),	GLColor( 0.296648, 	0.296648,  0.296648, 	0.922), 11.264	);
    Material Pewter			      = Material ( 	GLColor( 0.105882, 0.058824, 0.113725, 1.0),	  GLColor( 0.427451,  0.470588, 0.541176,	1.0),		GLColor( 0.333333, 	0.333333,  0.521569, 	1.0),		9.84615 );
    Material Plastic		      = Material ( 	GLColor( 1.0,      1.0,      1.0,      0.5),		GLColor( 0.5,       0.5, 			0.5, 			0.5),		GLColor( 0.4, 			0.4, 			 0.4, 			1.0),		10.0		);
    Material PolishedBronze	  = Material ( 	GLColor( 0.25,     0.148,    0.06475,  1.0),		GLColor( 0.4,       0.2368, 	0.1036, 	1.0),		GLColor( 0.774597, 	0.458561,  0.200621, 	1.0),		66.8		);
    Material PolishedCopper	  = Material ( 	GLColor( 0.2295,   0.08825,  0.0275,   1.0),		GLColor( 0.5508,    0.2118, 	0.066, 		1.0),		GLColor( 0.580594, 	0.223257,  0.0695701,	1.0),		51.2		);
    Material PolishedGold	    = Material ( 	GLColor( 0.24725,  0.2245,   0.0645,   1.0),		GLColor( 0.34615,   0.3143, 	0.0903, 	1.0),		GLColor( 0.797357, 	0.723991,  0.208006, 	1.0),		83.2		);
    Material PolishedGreen	  = Material ( 	GLColor( 0.0,      0.0,      0.0,      1.0),		GLColor( 0.1,       0.35, 		0.1, 			1.0),		GLColor( 0.45, 			0.55, 		 0.45, 			1.0),		50.0		);
    Material PolishedRed	    = Material ( 	GLColor( 0.0,      0.0,      0.0,      1.0),		GLColor( 0.5,       0.0, 			0.0, 			1.0),		GLColor( 0.7, 			0.6, 		   0.6, 			1.0),		50.0		);
    Material PolishedSilver   = Material ( 	GLColor( 0.23125,  0.23125,  0.23125,  1.0),		GLColor( 0.2775,    0.2775, 	0.2775, 	1.0),		GLColor( 0.773911, 	0.773911,  0.773911, 	1.0),		89.6		);
    Material Ruby			        = Material ( 	GLColor( 0.1745,   0.01175,  0.01175,  0.55),		GLColor( 0.61424,   0.04136, 	0.04136, 	0.55),	GLColor( 0.727811, 	0.626959,  0.626959, 	0.55),  56.8		);
    Material Sapphire		      = Material ( 	GLColor( 0.01175,  0.01175,  0.1745,   0.55),	  GLColor( 0.04136,   0.04136, 	0.61424, 	0.55),	GLColor( 0.626959, 	0.626959,  0.727811,	0.55),	76.8		);
    Material Silver			      = Material ( 	GLColor( 0.19225,  0.19225,  0.19225,  1.0),		GLColor( 0.50754,   0.50754,  0.50754, 	1.0), 	GLColor( 0.508273, 	0.508273,  0.508273, 	1.0), 	51.2		);
    Material Snow			        = Material ( 	GLColor( 1.0,      1.0,      1.0,      1.0),		GLColor( 0.5,       0.5, 			0.5, 			1.0),		GLColor( 0.4, 			0.4, 			 0.4, 			1.0),		10.0		);
    Material Turquoise		    = Material ( 	GLColor( 0.1,      0.18725,  0.1745,   0.8),		GLColor( 0.396,     0.74151, 	0.69102, 	0.8),		GLColor( 0.297254, 	0.30829, 	 0.306678, 	0.8),		12.8		);
  }




  /*! void Material::glSet()
   *	\brief Pending Documentation
   *
   *  push this material to current GL-state.
   */
  void Material::glSet() const {

    glMaterial(_sided,GL_AMBIENT,_amb);
    glMaterial(_sided,GL_DIFFUSE,_dif);
    glMaterial(_sided,GL_SPECULAR,_spc);
    glMaterial(_sided,GL_SHININESS,_shininess);

    if( _texture.isValid() ) {
      glEnable( _texture.getDimension() );
      glBindTexture( _texture.getDimension(), _texture.getTextureId() );
    }
  }


  /*! void Material::glSetInverse()
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Material::glSetInverse() const {

    glMaterial(GL_FRONT,GL_AMBIENT,_amb.getInverse());
    glMaterial(GL_FRONT,GL_DIFFUSE,_dif.getInverse());
    glMaterial(GL_FRONT,GL_SPECULAR,_spc.getInverse());
    glMaterial(GL_FRONT,GL_SHININESS,128 - _shininess);
  }


  /*! void Material::glUnSet()
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Material::glUnSet() const {

    if( _texture.isValid() )
    {
      glDisable( _texture.getDimension() );
      glBindTexture( _texture.getDimension(), 0 );
    }
  }


  /*! void Material::set( const GLenum sfactor, const GLenum dfactor )
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Material::set( const GLenum sfactor, const GLenum dfactor ) {

    _source_blend_factor		= sfactor;
    _destination_blend_factor	= dfactor;
  }


  /*! void Material::set(float shininess)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Material::set(float shininess) {

    _shininess = shininess;
  }


  /*! void Material::set(unsigned int texname)
   *	\brief Pending Documentation
   *
   *  Pending Documentation
   */
  void Material::set( Texture texture ) {

    _texture = texture;
  }

}
