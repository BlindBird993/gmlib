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




#ifndef GM_CORE_UTILS_COLOR_H
#define GM_CORE_UTILS_COLOR_H


#include "gmstream.h"
#include "gmutils.h"

// stl
#include <cmath>
#include <algorithm>


namespace GMlib {




  /*! \brief A color class
   *  A color-type class defining a color object and "color" operations
   */
  class Color {
  public:
    Color( unsigned int n = 0 );
    Color( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 255 );
    Color( int r, int g, int b, int a = 255 );
    Color( double r, double g, double b, double a = 1.0 );
    Color(const Color &copy) = default;




    unsigned int    get() const;
    unsigned char   get( int i ) const;
    unsigned char   getAlpha() const;
    double          getAlphaC() const;
    unsigned char   getBlue() const;
    double          getBlueC() const;
    double          getClampd( int i ) const;
    unsigned char   getGreen() const;
    double          getGreenC() const;
    Color           getInterpolatedHSV( double d, Color mx ) const;
    Color           getInverse() const;
    unsigned char   getRed() const;
    double          getRedC() const;
    const unsigned char*  getRgba() const;

    void            set( unsigned int n );
    void            set( unsigned char  rgba, int i );
    void            set( double rgba, int i );
    void            set( unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0 );
    void            set( double r, double g, double b, double a = 0.0 );
    void            setAlpha( unsigned char a );
    void            setAlpha( double a );
    void            setBlue( unsigned char b );
    void            setBlue( double b );
    void            setGreen( unsigned char g );
    void            setGreen( double g );
    void            setRed( unsigned char r );
    void            setRed( double r );
    void            toHSV();
    void            toRGB();


    Color&          operator =  ( const Color& other );
    Color&          operator *= ( double d );
    Color           operator *  ( double d ) const;
    Color&          operator /= ( double d );
    Color           operator /  ( double d ) const;
    Color&          operator += ( const Color& o );
    Color           operator +  ( const Color& o ) const;
    Color&          operator -= ( const Color& o );
    Color           operator -  ( const Color& o ) const;
    Color&          operator += ( int o );
    Color           operator +  ( int o ) const;
    Color&          operator -= ( int o );
    Color           operator -  ( int o ) const;
    Color&          operator += ( double o );
    Color           operator +  ( double o );
    Color&          operator -= ( double o );
    Color           operator -  ( double o ) const;
    bool            operator == ( const Color& co ) const;


  protected:

    union{
      unsigned int name;
      unsigned char rgba[4];
    } _color;


  private:
    unsigned char clampMult( const unsigned char& one, const double& d ) {
      return static_cast<unsigned char>( double(one) * d > 255.0 ? 255 : double(one) * d );
    }

    unsigned char clampAdd( const unsigned char& one, const int& other ) {
      return static_cast<unsigned char>( int(one) + other > 255 ? 255 : int(one) + other );
    }

    unsigned char clampSub( const unsigned char& one, const int& other ) {
      return static_cast<unsigned char>( int(one) - other < 0 ? 0 : int(one) - other );
    }

  public:

    friend
    Color operator * ( double d, Color o ) {

        return o *= d;
      }


    // *****************************
    // IOSTREAM overloaded operators

    #ifdef GM_STREAM

    template<typename T_Stream>
    friend T_Stream& operator >> ( T_Stream& in, Color& v ) {

      static Separator es(GMseparator::Element);

      //unsigned char r,g,b,a;
      double r, g, b, a;

      in >> r >> es >> g >> es >> b >> es >> a;
      v.set(r, g, b, a);

      return in;
    }


    template<typename T_Stream>
    friend T_Stream& operator << ( T_Stream& out, const Color& v ) {

      out << v.getRedC()    << GMseparator::Element
          << v.getGreenC()  << GMseparator::Element
          << v.getBlueC()   << GMseparator::Element
          << v.getAlphaC();
      return out;
    }


  private:
    std::istream& _printIn( std::istream& in ) {

      double r,g,b,a;
      in >> r >> g >> b >> a;
      set(r,g,b,a);
      return in;
    }

    std::ostream& _printOut( std::ostream& out ) const {

      out << getRedC() << "  "
          << getGreenC() << "  "
          <<  getBlueC() << "  "
          << getAlphaC();
      return out;
    }

    friend
    std::ostream& operator << ( std::ostream& out, const Color& v ) {

      return v._printOut( out );
    }

    friend
    std::istream& operator >> ( std::istream& in, Color& v ) {

      return v._printIn(in);
    }

    #endif


  };  // END class Color










  inline
  Color::Color(unsigned int n) {

    _color.name = n;
  }


  inline
  Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a ) {

    _color.rgba[0] = r;
    _color.rgba[1] = g;
    _color.rgba[2] = b;
    _color.rgba[3] = a;
  }


  inline
  Color::Color(int r, int g, int b, int a ) {

    _color.rgba[0] = static_cast<unsigned char>(r);
    _color.rgba[1] = static_cast<unsigned char>(g);
    _color.rgba[2] = static_cast<unsigned char>(b);
    _color.rgba[3] = static_cast<unsigned char>(a);
  }


  inline
  Color::Color( double r, double g, double b, double a ) {

    _color.rgba[0] = static_cast<unsigned char>(r*255);
    _color.rgba[1] = static_cast<unsigned char>(g*255);
    _color.rgba[2] = static_cast<unsigned char>(b*255);
    _color.rgba[3] = static_cast<unsigned char>(a*255);
  }


  inline
  unsigned int Color::get() const {
    return _color.name;
  }


  inline
  unsigned char Color::get(int i)const	{
    return _color.rgba[i];
  }


  inline
  unsigned char Color::getAlpha()const {
    return _color.rgba[3];
  }


  inline
  double Color::getAlphaC()const {
    return _color.rgba[3]/255.0;
  }


  inline
  unsigned char Color::getBlue()const {
    return _color.rgba[2];
  }


  inline
  double Color::getBlueC()const {
    return _color.rgba[2]/255.0;
  }


  inline
  double Color::getClampd(int i)const	{
    return _color.rgba[i]/255.0;
  }


  inline
  unsigned char Color::getGreen()const {
    return _color.rgba[1];
  }


  inline
  double Color::getGreenC()const {
    return _color.rgba[1]/255.0;
  }


  inline
  Color Color::getInterpolatedHSV(double d, Color mx) const {

    Color mn = *this;
    mx.toHSV();
    mn.toHSV();
    mx = (1-d)*mn+d*mx;
    mx.toRGB();
    return mx;
  }


  inline
  Color Color::getInverse() const {

    return Color(255-_color.rgba[0],255-_color.rgba[1],255-_color.rgba[3]);
  }


  inline
  unsigned char Color::getRed()const {
    return _color.rgba[0];
  }


  inline
  double Color::getRedC()const {
    return _color.rgba[0]/255.0;
  }


  inline
  const unsigned char*  Color::getRgba() const {

    return _color.rgba;
  }


  inline
  void Color::set(unsigned int n) {
    _color.name = n;
  }


  inline
  void Color::set(unsigned char  rgba, int i)	{
    _color.rgba[i] = rgba;
  }


  inline
  void Color::set(double rgba, int i)	{
    _color.rgba[i] = static_cast<unsigned char>(rgba*255);
  }


  inline
  void Color::set(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
    _color.rgba[0] = r; _color.rgba[1] = g; _color.rgba[2] = b; _color.rgba[3] = a;
  }


  inline
  void Color::set(double r, double g, double b, double a) {
    _color.rgba[0] = static_cast<unsigned char>(r*255); _color.rgba[1] = static_cast<unsigned char>(g*255);
    _color.rgba[2] = static_cast<unsigned char>(b*255); _color.rgba[3] = static_cast<unsigned char>(a*255);
  }


  inline
  void Color::setAlpha(unsigned char a) {
    _color.rgba[3] = a;
  }


  inline
  void Color::setAlpha(double a) {
    _color.rgba[3] = static_cast<unsigned char>(a*255);
  }


  inline
  void Color::setBlue(unsigned char b) {
    _color.rgba[2] = b;
  }


  inline
  void Color::setBlue(double b) {
    _color.rgba[2] = static_cast<unsigned char>(b*255);
  }


  inline
  void Color::setGreen(unsigned char g) {
    _color.rgba[1] = g;
  }


  inline
  void Color::setGreen(double g) {
    _color.rgba[1] = static_cast<unsigned char>(g*255);
  }


  inline
  void Color::setRed( unsigned char r ) {

    _color.rgba[0] = r;
  }


  inline
  void Color::setRed(double r) {
    _color.rgba[0] = static_cast<unsigned char>(r*255);
  }


  inline
  void Color::toHSV() {

    double r=getRedC(),g=getGreenC(),b=getBlueC();
    double h,s,v,mx,mn;
    mx = std::max<double>( std::max<double>(r,g), b );
    mn = std::min<double>( std::min<double>(r,g), b );
    v=mx;
    if(mx > 1e-6) s = (mx-mn)/mx;
    else		  s = 0.0;
    if(s == 0.0)  h = 0.0;
    else
    {
      double rc = (mx-r)/(mx-mn);
      double gc = (mx-g)/(mx-mn);
      double bc = (mx-b)/(mx-mn);
      if(std::fabs(r-mx) < 1e-7)         h = bc-gc;
      else if(std::fabs(g - mx) < 1e-7)  h = rc-bc + 2.0;
      else                               h = gc-rc + 4.0;                                // else if(std::abs(b -mx) < 1e-7)
      h *= 60.0;
      if(h<0.0) h += 360.0;
      h /= 360.0;			// 360 degree is skaled to 1.
    }
    setRed(h); setGreen(s); setBlue(v);
  }


  inline
  void Color::toRGB() {

    double h=getRedC(),s=getGreenC(),v=getBlueC();
    double r,g,b;
    h *= 360.0;
    if(s < 0.000001)
      r = g = b = v;
    else
    {
      if(h > 359.999999) h = 0.0;
      h /= 60.0;
      int    i = static_cast<int>(h);
      double f = h - double(i);
      double p = v*(1-s);
      double q = v*(1-s*f);
      double t = v*(1-s*(1-f));
      switch(i)
      {
      case 0:  r=v; g=t; b=p; break;
      case 1:  r=q; g=v; b=p; break;
      case 2:  r=p; g=v; b=t; break;
      case 3:  r=p; g=q; b=v; break;
      case 4:  r=t; g=p; b=v; break;
      default: r=v; g=p; b=q; break; // i == 5
      }
    }
    setRed( r ); setGreen( g ); setBlue( b );
  }

  inline
  Color&
  Color::operator = (const Color& other) {
    _color = other._color;
    return *this;
  }


  inline
  Color& Color::operator*=(double d) {

    _color.rgba[0] = clampMult(_color.rgba[0],d);
    _color.rgba[1] = clampMult(_color.rgba[1],d);
    _color.rgba[2] = clampMult(_color.rgba[2],d);
    _color.rgba[3] = clampMult(_color.rgba[3],d);
    return * this;
  }


  inline
  Color Color::operator*(double d)const {

    return d * (*this);
  }


  inline
  Color& Color::operator/=(double d) {

    d=1/d;
    return (*this) *= d;
  }


  inline
  Color Color::operator/(double d) const {

    d=1/d;
    return d * (*this);
  }


  inline
  Color& Color::operator+=(const Color& o) {

    _color.rgba[0] = clampAdd(_color.rgba[0],o._color.rgba[0]);
    _color.rgba[1] = clampAdd(_color.rgba[1],o._color.rgba[1]);
    _color.rgba[2] = clampAdd(_color.rgba[2],o._color.rgba[2]);
    _color.rgba[3] = clampAdd(_color.rgba[3],o._color.rgba[3]);
    return * this;
  }


  inline
  Color Color::operator+(const Color& o) const {

    Color k= (*this);
    return k += o;
  }


  inline
  Color& Color::operator-=(const Color& o) {

    _color.rgba[0] = clampSub(_color.rgba[0],o._color.rgba[0]);
    _color.rgba[1] = clampSub(_color.rgba[1],o._color.rgba[1]);
    _color.rgba[2] = clampSub(_color.rgba[2],o._color.rgba[2]);
    _color.rgba[3] = clampSub(_color.rgba[3],o._color.rgba[3]);
    return * this;
  }


  inline
  Color Color::operator-(const Color& o) const {

    Color k= (*this);
    return k -= o;
  }


  inline
  Color& Color::operator+=(int o) {

    _color.rgba[0] = clampAdd(_color.rgba[0],o);
    _color.rgba[1] = clampAdd(_color.rgba[1],o);
    _color.rgba[2] = clampAdd(_color.rgba[2],o);
    _color.rgba[3] = clampAdd(_color.rgba[3],o);
    return *this;
  }


  inline
  Color Color::operator+(int o) const {

    Color k= (*this);
    return k += o;
  }


  inline
  Color& Color::operator-=(int o) {

    _color.rgba[0] = clampSub(_color.rgba[0],o);
    _color.rgba[1] = clampSub(_color.rgba[1],o);
    _color.rgba[2] = clampSub(_color.rgba[2],o);
    _color.rgba[3] = clampSub(_color.rgba[3],o);
    return * this;
  }


  inline
  Color Color::operator-(int o) const {

    Color k= (*this); return k -= o;
  }


  inline
  Color& Color::operator+=(double o) {

    int k = int(o*255);
    return (*this) += k;
  }


  inline
  Color Color::operator+(double o) {

    Color k= (*this); return k += o;
  }


  inline
  Color& Color::operator-=(double o) {

    int k = int(o*255);
    return (*this) -= k;
  }


  inline
  Color Color::operator-(double o) const {

    Color k= (*this); return k -= o;
  }


  inline
  bool Color::operator==(const Color& co) const {

    return _color.name == co._color.name;
  }




  // *****************
  // Predefined Colors

  namespace GMcolor {

    extern Color AliceBlue;
    extern Color AntiqueWhite;
    extern Color Aqua;
    extern Color AquaMarine;
    extern Color Azure;
    extern Color Beige;
    extern Color Bisque;
    extern Color Black;
    extern Color BlanchedAlamond;
    extern Color Blue;
    extern Color BlueViolet;
    extern Color Brown;
    extern Color BurlyWood;
    extern Color CadetBlue;
    extern Color Chartreuse;
    extern Color Chocolate;
    extern Color Coral;
    extern Color CornflowerBlue;
    extern Color Cornsilk;
    extern Color Crimson;
    extern Color Cyan;
    extern Color DarkBlue;
    extern Color DarkCyan;
    extern Color DarkGoldenRod;
    extern Color DarkGrey;
    extern Color DarkGreen;
    extern Color DarkKhaki;
    extern Color DarkMagenta;
    extern Color DarkOliveGreen;
    extern Color DarkOrange;
    extern Color DarkOrchid;
    extern Color DarkRed;
    extern Color DarkSalmon;
    extern Color DarkSeaGreen;
    extern Color DarkSlateBlue;
    extern Color DarkSlateGrey;
    extern Color DarkTurquoise;
    extern Color DarkViolet;
    extern Color DeepPink;
    extern Color DeepSkyBlue;
    extern Color DimGrey;
    extern Color DodgerBlue;
    extern Color FireBrick;
    extern Color FloralWhite;
    extern Color ForestGreen;
    extern Color Fuchsia;
    extern Color Gainsboro;
    extern Color GhostWhite;
    extern Color Gold;
    extern Color GoldenRod;
    extern Color Grey;
    extern Color Green;
    extern Color GreenYellow;
    extern Color HoneyDew;
    extern Color HotPink;
    extern Color IndianRed;
    extern Color Indigo;
    extern Color Ivory;
    extern Color Khaki;
    extern Color Lavender;
    extern Color LavenderBlush;
    extern Color LawnGreen;
    extern Color LemonChiffon;
    extern Color LightBlue;
    extern Color LightCoral;
    extern Color LightCyan;
    extern Color LightGoldenRodYellow;
    extern Color LightGrey;
    extern Color LightGreen;
    extern Color LightPink;
    extern Color LightSalmon;
    extern Color LightSeaGreen;
    extern Color LightSkyBlue;
    extern Color LightSlateGrey;
    extern Color LightSteelBlue;
    extern Color LightYellow;
    extern Color Lime;
    extern Color LimeGreen;
    extern Color Linen;
    extern Color Magenta;
    extern Color Maroon;
    extern Color MediumAquaMarine;
    extern Color MediumBlue;
    extern Color MediumOrchid;
    extern Color MediumPurple;
    extern Color MediumSeaGreen;
    extern Color MediumSlateBlue;
    extern Color MediumSpringGreen;
    extern Color MediumTurquoise;
    extern Color MediumVioletRed;
    extern Color MidnightBlue;
    extern Color MintCream;
    extern Color MistyRose;
    extern Color Moccasin;
    extern Color NavajoWhite;
    extern Color Navy;
    extern Color OldLace;
    extern Color Olive;
    extern Color OliveDrab;
    extern Color Orange;
    extern Color OrangeRed;
    extern Color Orchid;
    extern Color PaleGoldenRod;
    extern Color PaleGreen;
    extern Color PaleTurquoise;
    extern Color PaleVioletRed;
    extern Color PapayaWhip;
    extern Color PeachPuff;
    extern Color Peru;
    extern Color Pink;
    extern Color Plum;
    extern Color PowderBlue;
    extern Color Purple;
    extern Color Red;
    extern Color RosyBrown;
    extern Color RoyalBlue;
    extern Color SaddleBrown;
    extern Color Salmon;
    extern Color SandyBrown;
    extern Color SeaGreen;
    extern Color SeaShell;
    extern Color Sienna;
    extern Color Silver;
    extern Color SkyBlue;
    extern Color SlateBlue;
    extern Color SlateGrey;
    extern Color Snow;
    extern Color SpringGreen;
    extern Color SteelBlue;
    extern Color Tan;
    extern Color Teal;
    extern Color Thistle;
    extern Color Tomato;
    extern Color Turquoise;
    extern Color Violet;
    extern Color Wheat;
    extern Color White;
    extern Color WhiteSmoke;
    extern Color Yellow;
    extern Color YellowGreen;

  } // END namespace GMcolor


} // END namespace GMlib


#endif // GM_CORE_UTILS_COLOR_H


