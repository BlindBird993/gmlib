
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





namespace GMlib {


  template <typename T>
  inline
  PBoysSurface<T>::PBoysSurface() {

    init();
  }


  template <typename T>
  inline
  PBoysSurface<T>::PBoysSurface( const PBoysSurface<T>& copy ) : PSurf<T,3>( copy ) {

    init();
  }



  template <typename T>
  PBoysSurface<T>::~PBoysSurface() {}


  template <typename T>
  void PBoysSurface<T>::eval(T u, T v, int d1, int d2, bool /*lu*/, bool /*lv*/ ) {

    this->_p.setDim( d1+1, d2+1 );

    this->_p[0][0][0] =	cos(u)*(T(M_SQRT2)/T(3)*cos(u)*cos(T(2)*v)+T(2)/T(3)*sin(u)*cos(v))
            /(T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v));
    this->_p[0][0][1] =	cos(u)*(T(M_SQRT2)/T(3)*cos(u)*sin(T(2)*v)-T(2)/T(3)*sin(u)*sin(v))
            /(T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v));
    this->_p[0][0][2] =	cos(u)/(T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v))*cos(u)-T(1);


    if( this->_dm == GM_DERIVATION_EXPLICIT ) {

      if(d1) //u
      {
        this->_p[1][0][0] =	-sin(u)*(T(1)/T(3)*T(M_SQRT2)*cos(u)*cos(T(2)*v)+T(2)/T(3)*sin(u)*cos(v))
                / (T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v))+cos(u)*(-T(1)/T(3)*T(M_SQRT2)*sin(u)*cos(T(2)*v)
                +T(2)/T(3)*cos(u)*cos(v))/(T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v))
                -cos(u)*(T(1)/T(3)*T(M_SQRT2)*cos(u)*cos(T(2)*v) + T(2)/T(3)*sin(u)*cos(v))
                * (-T(M_SQRT2)*cos(u)*cos(u)*sin(T(3)*v)+T(M_SQRT2)*sin(u)*sin(u)*sin(T(3)*v))
                / pow((T)(T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v)),T(2));
        this->_p[1][0][1] =	-sin(u)*((T(1)/T(3)*cos(u)*sin(T(2)*v)*T(M_SQRT2) - T(2)/T(3)*sin(u)*sin(v)))
                / (T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v))
                + cos(u)*(-(T(1)/T(3)*sin(u)*sin(T(2)*v)*T(M_SQRT2) - T(2)/T(3)*cos(u)*sin(v)))
                /(T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v))
                - cos(u)*(T(1)/T(3)*cos(u)*sin(T(2)*v)*T(M_SQRT2) - T(2)/T(3)*sin(u)*sin(v))
                * (-T(M_SQRT2)*cos(u)*cos(u)*sin(T(3)*v) + T(M_SQRT2)*sin(u)*sin(u)*sin(T(3)*v))
                / pow((T)(T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v)),T(2));
        this->_p[1][0][2] =	-T(2)*cos(u)*sin(u)/(T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v))
                - (cos(u)*cos(u)*(-T(M_SQRT2)*cos(u)*cos(u)*sin(T(3)*v)	+ T(M_SQRT2)*sin(u)*sin(u)*sin(T(3)*v)))
                / pow((T)(T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v)),T(2));
      }

      if(d1>1)//uu
      {
        this->_p[2][0][0] =	-cos(u)*(T(M_SQRT2)*cos(u)*cos(T(2.0)*v)/T(3.0)+T(2.0)/T(3.0)*sin(u)*cos(v))
                /(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))-T(2.0)*sin(u)*(-T(M_SQRT2)*sin(u)*cos(T(2.0)*v)
                /T(3.0)+T(2.0)/T(3.0)*cos(u)*cos(v))/(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))
                +T(2.0)*sin(u)*(T(M_SQRT2)*cos(u)*cos(T(2.0)*v)/T(3.0)+T(2.0)/T(3.0)*sin(u)*cos(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*(-T(M_SQRT2)*pow(cos(u),T(2.0))
                *sin(T(3.0)*v)+T(M_SQRT2)*pow(sin(u),T(2.0))*sin(T(3.0)*v))+cos(u)*(-T(M_SQRT2)*cos(u)
                *cos(T(2.0)*v)/T(3.0)-T(2.0)/T(3.0)*sin(u)*cos(v))/(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))
                -T(2.0)*cos(u)*(-T(M_SQRT2)*sin(u)*cos(T(2.0)*v)/T(3.0)+T(2.0)/T(3.0)*cos(u)*cos(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*(-T(M_SQRT2)*pow(cos(u),T(2.0))
                *sin(T(3.0)*v)+T(M_SQRT2)*pow(sin(u),T(2.0))*sin(T(3.0)*v))+T(2.0)*cos(u)*(T(M_SQRT2)*cos(u)
                *cos(T(2.0)*v)/T(3.0)+T(2.0)/T(3.0)*sin(u)*cos(v))/pow(T(1.0)-sqrt(T(2.0))*sin(u)*cos(u)
                *sin(T(3.0)*v),T(3.0))*pow(-T(M_SQRT2)*pow(cos(u),T(2.0))*sin(T(3.0)*v)+sqrt(T(2.0))
                *pow(sin(u),T(2.0))*sin(T(3.0)*v),T(2.0))-T(4.0)*pow(cos(u),T(2.0))*(T(M_SQRT2)*cos(u)
                *cos(T(2.0)*v)/T(3.0)+T(2.0)/T(3.0)*sin(u)*cos(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),	T(2.0))*T(M_SQRT2)*sin(u)*sin(T(3.0)*v);

        this->_p[2][0][1] =	-cos(u)*(T(M_SQRT2)*cos(u)*sin(T(2.0)*v)/T(3.0)-T(2.0)/T(3.0)*sin(u)*sin(v))
                /(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))-T(2.0)*sin(u)*(-T(M_SQRT2)*sin(u)*sin(T(2.0)*v)
                /T(3.0)-T(2.0)/T(3.0)*cos(u)*sin(v))/(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))
                +T(2.0)*sin(u)*(T(M_SQRT2)*cos(u)*sin(T(2.0)*v)/T(3.0)-T(2.0)/T(3.0)*sin(u)*sin(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*(-T(M_SQRT2)*pow(cos(u),T(2.0))
                *sin(T(3.0)*v)+T(M_SQRT2)*pow(sin(u),T(2.0))*sin(T(3.0)*v))+cos(u)*(-T(M_SQRT2)*cos(u)
                *sin(T(2.0)*v)/T(3.0)+T(2.0)/T(3.0)*sin(u)*sin(v))/(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)
                *sin(T(3.0)*v))-T(2.0)*cos(u)*(-T(M_SQRT2)*sin(u)*sin(T(2.0)*v)/T(3.0)-T(2.0)
                /T(3.0)*cos(u)*sin(v))/pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*(-T(M_SQRT2)
                *pow(cos(u),T(2.0))*sin(T(3.0)*v)+T(M_SQRT2)*pow(sin(u),T(2.0))*sin(T(3.0)*v))+T(2.0)
                *cos(u)*(T(M_SQRT2)*cos(u)*sin(T(2.0)*v)/T(3.0)-T(2.0)/T(3.0)*sin(u)*sin(v))/pow(T(1.0)
                -sqrt(T(2.0))*sin(u)*cos(u)*sin(T(3.0)*v),T(3.0))*pow(-T(M_SQRT2)*pow(cos(u),T(2.0))
                *sin(T(3.0)*v)+sqrt(T(2.0))*pow(sin(u),T(2.0))*sin(T(3.0)*v),T(2.0))-T(4.0)*pow(cos(u),T(2.0))
                *(T(M_SQRT2)*cos(u)*sin(T(2.0)*v)/T(3.0)-T(2.0)/T(3.0)*sin(u)*sin(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*T(M_SQRT2)*sin(u)*sin(T(3.0)*v);

        this->_p[2][0][2] =	T(2.0)*pow(sin(u),T(2.0))/(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))+T(4.0)*cos(u)
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*sin(u)*(-T(M_SQRT2)*pow(cos(u),T(2.0))
                *sin(T(3.0)*v)+T(M_SQRT2)*pow(sin(u),T(2.0))*sin(T(3.0)*v))-T(2.0)*pow(cos(u),T(2.0))
                /(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))+T(2.0)*pow(cos(u),T(2.0))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(3.0))*pow(-T(M_SQRT2)*pow(cos(u),T(2.0))
                *sin(T(3.0)*v)+sqrt(T(2.0))*pow(sin(u),T(2.0))*sin(T(3.0)*v),T(2.0))-T(4.0)*pow(cos(u),T(3.0))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*T(M_SQRT2)*sin(u)*sin(T(3.0)*v);
      }

      if(d2) //v
      {
        this->_p[0][1][0] =	cos(u)*(-T(2)/T(3)*cos(u)*sin(T(2)*v)*T(M_SQRT2)-T(2)/T(3)*sin(u)*sin(v))
                / (T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v))
                + T(3)*cos(u)*cos(u)*(T(1)/T(3)*T(M_SQRT2)*cos(u)*cos(T(2)*v)
                + T(2)/T(3)*sin(u)*cos(v))*T(M_SQRT2)*sin(u)*cos(T(3)*v)
                / pow((T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v)),T(2));

        this->_p[0][1][1] =	cos(u)*(T(2)/T(3)*T(M_SQRT2)*cos(u)*cos(T(2)*v)-T(2)/T(3)*sin(u)*cos(v))
                / (T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(3*v))
                + T(3)*cos(u)*cos(u)*(T(1)/T(3)*cos(u)*sin(T(2)*v)*T(M_SQRT2)
                - T(2)/T(3)*sin(u)*sin(v))*T(M_SQRT2)*sin(u)*cos(T(3)*v)
                / pow((T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v)),T(2));

        this->_p[0][1][2] =	T(3)*cos(u)*cos(u)*cos(u)*T(M_SQRT2)*sin(u)*cos(T(3)*v)
                / pow((T(1)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3)*v)),T(2));
      }

      if(d2>1) //vv
      {
        this->_p[0][2][0] =	cos(u)*(-T(4.0)/T(3.0)*T(M_SQRT2)*cos(u)*cos(T(2.0)*v)-T(2.0)/T(3.0)*sin(u)*cos(v))
                /(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))+T(6.0)*pow(cos(u),T(2.0))
                *(-T(2.0)/T(3.0)*sqrt(T(2.0))*cos(u)*sin(T(2.0)*v)-T(2.0)/T(3.0)*sin(u)*sin(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*T(M_SQRT2)*sin(u)*cos(T(3.0)*v)
                +T(36.0)*pow(cos(u),T(3.0))*(T(M_SQRT2)*cos(u)*cos(T(2.0)*v)/T(3.0)+T(2.0)/T(3.0)*sin(u)*cos(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(3.0))*pow(sin(u),T(2.0))
                *pow(cos(T(3.0)*v),T(2.0))-T(9.0)*pow(cos(u),T(2.0))*(T(M_SQRT2)*cos(u)*cos(T(2.0)*v)/T(3.0)
                +T(2.0)/T(3.0)*sin(u)*cos(v))/pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))
                *T(M_SQRT2)*sin(u)*sin(T(3.0)*v);

        this->_p[0][2][1] =	cos(u)*(-T(4.0)/T(3.0)*T(M_SQRT2)*cos(u)*sin(T(2.0)*v)+T(2.0)/T(3.0)*sin(u)*sin(v))
                /(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))+T(6.0)*pow(cos(u),T(2.0))
                *(T(2.0)/T(3.0)*T(M_SQRT2)*cos(u)*cos(T(2.0)*v)-T(2.0)/T(3.0)*sin(u)*cos(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*T(M_SQRT2)*sin(u)*cos(T(3.0)*v)
                +T(36.0)*pow(cos(u),T(3.0))*(T(M_SQRT2)*cos(u)*sin(T(2.0)*v)/T(3.0)-T(2.0)/T(3.0)*sin(u)*sin(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(3.0))*pow(sin(u),T(2.0))
                *pow(cos(T(3.0)*v),T(2.0))-T(9.0)*pow(cos(u),T(2.0))*(T(M_SQRT2)*cos(u)*sin(T(2.0)*v)
                /T(3.0)-T(2.0)/T(3.0)*sin(u)*sin(v))/pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))
                *T(M_SQRT2)*sin(u)*sin(T(3.0)*v);

        this->_p[0][2][2] =	T(36.0)*pow(cos(u),T(4.0))/pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(3.0))
                *pow(sin(u),T(2.0))*pow(cos(T(3.0)*v),T(2.0))-T(9.0)*pow(cos(u),T(3.0))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*T(M_SQRT2)*sin(u)*sin(T(3.0)*v);
      }
      if(d1 && d2) //uv
      {
        this->_p[1][1][0] =	-sin(u)*(-T(2.0)/T(3.0)*T(M_SQRT2)*cos(u)*sin(T(2.0)*v)-T(2.0)/T(3.0)*sin(u)*sin(v))
                /(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))-T(3.0)*pow(sin(u),T(2.0))*(T(M_SQRT2)*cos(u)
                *cos(T(2.0)*v)/T(3.0)+T(2.0)/T(3.0)*sin(u)*cos(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*T(M_SQRT2)*cos(u)*cos(T(3.0)*v)
                +cos(u)*(T(2.0)/T(3.0)*T(M_SQRT2)*sin(u)*sin(T(2.0)*v)-T(2.0)/T(3.0)*cos(u)*sin(v))
                /(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))+T(3.0)*pow(cos(u),T(2.0))*(-T(M_SQRT2)*sin(u)
                *cos(T(2.0)*v)/T(3.0)+T(2.0)/T(3.0)*cos(u)*cos(v))/pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))
                *T(M_SQRT2)*sin(u)*cos(T(3.0)*v)-cos(u)*(-T(2.0)/T(3.0)*T(M_SQRT2)*cos(u)*sin(T(2.0)*v)
                -T(2.0)/T(3.0)*sin(u)*sin(v))/pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))
                *(-T(M_SQRT2)*pow(cos(u),T(2.0))*sin(T(3.0)*v)+T(M_SQRT2)*pow(sin(u),T(2.0))*sin(T(3.0)*v))
                -T(6.0)*pow(cos(u),T(2.0))*(T(M_SQRT2)*cos(u)*cos(T(2.0)*v)/T(3.0)+T(2.0)/T(3.0)*sin(u)*cos(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(3.0))*(-T(M_SQRT2)*pow(cos(u),T(2.0))
                *sin(T(3.0)*v)+T(M_SQRT2)*pow(sin(u),T(2.0))*sin(T(3.0)*v))*T(M_SQRT2)*sin(u)*cos(T(3.0)*v)
                -cos(u)*(T(M_SQRT2)*cos(u)*cos(T(2.0)*v)/T(3.0)+T(2.0)/T(3.0)*sin(u)*cos(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*(-T(3.0)*T(M_SQRT2)
                *pow(cos(u),T(2.0))*cos(T(3.0)*v)+T(3.0)*T(M_SQRT2)*pow(sin(u),T(2.0))*cos(T(3.0)*v));

        this->_p[1][1][1] =	-sin(u)*(T(2.0)/T(3.0)*T(M_SQRT2)*cos(u)*cos(T(2.0)*v)-T(2.0)/T(3.0)*sin(u)*cos(v))
                /(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))-T(3.0)*pow(sin(u),T(2.0))*(T(M_SQRT2)*cos(u)
                *sin(T(2.0)*v)/T(3.0)-T(2.0)/T(3.0)*sin(u)*sin(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*T(M_SQRT2)*cos(u)*cos(T(3.0)*v)
                +cos(u)*(-T(2.0)/T(3.0)*T(M_SQRT2)*sin(u)*cos(T(2.0)*v)-T(2.0)/T(3.0)*cos(u)*cos(v))
                /(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v))+T(3.0)*pow(cos(u),T(2.0))
                *(-T(M_SQRT2)*sin(u)*sin(T(2.0)*v)/T(3.0)-T(2.0)/T(3.0)*cos(u)*sin(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*T(M_SQRT2)*sin(u)*cos(T(3.0)*v)
                -cos(u)*(T(2.0)/T(3.0)*T(M_SQRT2)*cos(u)*cos(T(2.0)*v)-T(2.0)/T(3.0)*sin(u)*cos(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*(-T(M_SQRT2)*pow(cos(u),T(2.0))
                *sin(T(3.0)*v)+T(M_SQRT2)*pow(sin(u),T(2.0))*sin(T(3.0)*v))-T(6.0)*pow(cos(u),T(2.0))
                *(T(M_SQRT2)*cos(u)*sin(T(2.0)*v)/T(3.0)-T(2.0)/T(3.0)*sin(u)*sin(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(3.0))*(-T(M_SQRT2)*pow(cos(u),T(2.0))
                *sin(T(3.0)*v)+T(M_SQRT2)*pow(sin(u),T(2.0))*sin(T(3.0)*v))*T(M_SQRT2)*sin(u)*cos(T(3.0)*v)
                -cos(u)*(T(M_SQRT2)*cos(u)*sin(T(2.0)*v)/T(3.0)-T(2.0)/T(3.0)*sin(u)*sin(v))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))*(-T(3.0)*T(M_SQRT2)
                *pow(cos(u),T(2.0))*cos(T(3.0)*v)+T(3.0)*T(M_SQRT2)*pow(sin(u),T(2.0))*cos(T(3.0)*v));

        this->_p[1][1][2] =	-T(6.0)*pow(cos(u),T(2.0))/pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))
                *pow(sin(u),T(2.0))*T(M_SQRT2)*cos(T(3.0)*v)-T(6.0)*pow(cos(u),T(3.0))
                /pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(3.0))*(-T(M_SQRT2)*pow(cos(u),T(2.0))
                *sin(T(3.0)*v)+T(M_SQRT2)*pow(sin(u),T(2.0))*sin(T(3.0)*v))*T(M_SQRT2)*sin(u)*cos(T(3.0)*v)
                -pow(cos(u),T(2.0))/pow(T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(2.0))
                *(-T(3.0)*T(M_SQRT2)*pow(cos(u),T(2.0))*cos(T(3.0)*v)+T(3.0)*T(M_SQRT2)
                *pow(sin(u),T(2.0))*cos(T(3.0)*v));
      }
      if(d1>1 && d2)//uuv
      {
        T s3 =	16.0*pow((T)cos(u),T(4))*T(M_SQRT2)*cos(T(3.0)*v)*T(3.0)*T(2.0)*cos(v)+8.0*pow((T)cos(u),T(5))
            *T(2)*sin(T(3.0)*v)*sin(u)*cos(T(3.0)*v)*T(3.0)*T(2.0)*cos(v)+4.0*cos(u)*cos(u)
            *T(2.0)*T(M_SQRT2)*sin(T(2.0)*v)+4.0*cos(u)*T(2.0)*sin(u)*sin(v)
            -16.0*pow((T)cos(u),T(3))*T(2)*sin(u)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)
            +8.0*pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)
            -T(4)*T(M_SQRT2)*sin(T(2.0)*v);

        T s2 =	s3+2.0*T(M_SQRT2)*cos(T(3.0)*v)*T(3.0)*T(2.0)*cos(v)-16.0*cos(u)*cos(u)*T(M_SQRT2)
            *cos(T(3.0)*v)*T(3.0)*T(2.0)*cos(v)-4.0*pow((T)cos(u),T(4))*pow(T(M_SQRT2),T(3))
            *cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)*sin(T(3.0)*v)-2.0*T(2.0)*T(M_SQRT2)*sin(T(3.0)*v)*sin(v)
            -6.0*pow((T)cos(u),T(4))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(2.0)*v)+6.0
            *pow((T)cos(u),T(4))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(2.0)*v)*T(9)
            +4.0*pow((T)cos(u),T(6))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(2.0)*v);

          s3 =	s2-4.0*pow((T)cos(u),T(6))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(2.0)*v)*T(9)+2.0
            *pow((T)cos(u),T(5))*T(2.0)*T(4)*sin(T(2.0)*v)*sin(u)*sin(T(3.0)*v)-2.0*pow((T)cos(u),T(5))
            *T(2.0)*T(4)*sin(T(2.0)*v)*sin(u)*sin(T(3.0)*v)*T(9)
            +4.0*pow((T)cos(u),T(5))*T(2.0)*T(2)*sin(v)*sin(u)-4.0*pow((T)cos(u),T(5))*T(4)
            *sin(v)*sin(u)*T(9)+4.0*sin(u)*T(2)*sin(T(3.0)*v)*cos(u)
            *cos(T(3.0)*v)*T(3.0)*T(2.0)*cos(v)-8.0*sin(u)*T(2)*sin(T(3.0)*v)
            *pow((T)cos(u),T(3))*cos(T(3.0)*v)*T(3.0)*T(2.0)*cos(v);

            T s1 =	s3+2.0*sin(u)*T(2.0)*T(2)*sin(T(2.0)*v)*cos(u)*sin(T(3.0)*v)+2.0*pow((T)cos(u),T(5))
            *T(4)*sin(u)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)-2.0*pow((T)cos(u),T(5))
            *T(4)*sin(u)*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*cos(T(2.0)*v)+6.0*sin(u)
            *T(2)*cos(u)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)+2.0*sin(u)*T(2.0)
            *T(2)*sin(v)*cos(u)-2.0*sin(u)*T(2.0)*T(2)*sin(v)*cos(u)
            *T(9)-4.0*sin(u)*T(2.0)*T(2)*sin(v)*pow((T)cos(u),T(3))
            +4.0*sin(u)*T(2.0)*T(2)*sin(v)*pow((T)cos(u),T(3))*T(9);

              s2 =	1/T(3.0)/pow((T)-T(1.0)+T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(4));

        this->_p[2][1][0] =	s1*s2;

          s3 =	2.0*T(2.0)*T(M_SQRT2)*cos(T(2.0)*v)+4.0*cos(u)*T(2.0)*sin(u)*cos(v)
            -16.0*pow((T)cos(u),T(4))*T(M_SQRT2)*cos(T(3.0)*v)*T(3.0)*T(2.0)*sin(v)
            +8.0*pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)
            -8.0*pow((T)cos(u),T(5))*T(2)*sin(T(3.0)*v)*sin(u)*cos(T(3.0)*v)*T(3.0)*T(2.0)
            *sin(v)-16.0*pow((T)cos(u),T(3))*T(2)*sin(u)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)
            +4.0*sin(u)*T(2.0)*T(2)*cos(v)*pow((T)cos(u),T(3))
            *T(9);

          s2 =	s3+2.0*sin(u)*T(2.0)*T(2)*cos(v)*cos(u)-2.0*sin(u)*T(2.0)*T(2)*cos(T(2.0)*v)
            *cos(u)*sin(T(3.0)*v)-4.0*sin(u)*T(2.0)*T(2)*cos(v)*pow((T)cos(u),T(3))
            +6.0*sin(u)*T(2)*cos(u)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)+4.0*pow((T)cos(u),T(5))
            *T(2.0)*T(2)*cos(v)*sin(u)-4.0*pow((T)cos(u),T(5))*T(2.0)*T(2)
            *cos(v)*sin(u)*T(9)+8.0*sin(u)*T(2)*sin(T(3.0)*v)
            *pow((T)cos(u),T(3))*cos(T(3.0)*v)*T(3.0)*T(2.0)*sin(v);

          s3 =	s2-4.0*sin(u)*T(2)*sin(T(3.0)*v)*cos(u)*cos(T(3.0)*v)*T(3.0)*T(2.0)*sin(v)
            -4.0*pow((T)cos(u),T(6))*T(2.0)*pow(T(M_SQRT2),T(3))*cos(T(2.0)*v)+4.0*pow((T)cos(u),T(6))*T(2.0)
            *pow(T(M_SQRT2),T(3))*cos(T(2.0)*v)*T(9)-4.0*cos(u)*cos(u)*T(2.0)*T(M_SQRT2)
            *cos(T(2.0)*v)+16.0*cos(u)*cos(u)*T(M_SQRT2)*cos(T(3.0)*v)*T(3.0)*T(2.0)*sin(v)
            +6.0*pow((T)cos(u),T(4))*T(2.0)*pow(T(M_SQRT2),T(3))*cos(T(2.0)*v)
            -6.0*pow((T)cos(u),T(4))*T(2.0)*pow(T(M_SQRT2),T(3))*cos(T(2.0)*v)*T(9);

          s1 =	s3-2.0*pow((T)cos(u),T(5))*T(4)*sin(u)*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*sin(T(2.0)*v)
            +2.0*pow((T)cos(u),T(5))*T(4)*sin(u)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)
            -2.0*pow((T)cos(u),T(5))*T(2.0)*T(4)*cos(T(2.0)*v)*sin(u)*sin(T(3.0)*v)
            +2.0*pow((T)cos(u),T(5))*T(2.0)*T(4)*cos(T(2.0)*v)*sin(u)*sin(T(3.0)*v)
            *T(9)-2.0*sin(u)*T(2.0)*T(2)*cos(v)*cos(u)
            *T(9)-2.0*T(2.0)*T(M_SQRT2)*sin(T(3.0)*v)*cos(v)-2.0*T(M_SQRT2)
            *cos(T(3.0)*v)*T(3.0)*T(2.0)*sin(v)-4.0*pow((T)cos(u),T(4))*pow(T(M_SQRT2),T(3))
            *cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)*sin(T(3.0)*v);

          s2 =	1/T(3.0)/pow((T)-T(1.0)+T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(4));

        this->_p[2][1][1] =	s1*s2;
        this->_p[2][1][2] =	-2.0*T(M_SQRT2)*cos(u)*cos(T(3.0)*v)*T(3.0)*(-4.0*pow((T)cos(u),T(5))*T(M_SQRT2)*sin(T(3.0)*v)
                +8.0*sin(u)*cos(u)*cos(u)-pow((T)cos(u),T(4))*sin(u)*T(2)+pow((T)cos(u),T(4))
                *sin(u)*T(2)*T(9)+2.0*pow((T)cos(u),T(3))*T(M_SQRT2)*sin(T(3.0)*v)
                -3.0*sin(u))/pow((T)-T(1.0)+T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(4));
      }
      if(d1 && d2>1) //uvv
      {
        T s4 =	T(2.0)*cos(v)*T(2)*cos(u)*cos(u)-T(2.0)*cos(v)*T(2)
            *cos(u)*cos(u)*T(9)-3.0*T(2.0)*cos(v)*T(2)*pow((T)cos(u),T(4))
            +3.0*T(2.0)*cos(v)*T(2)*pow((T)cos(u),T(4))*T(9)+2.0*T(2.0)*cos(v)
            *T(2)*pow((T)cos(u),T(6))-2.0*T(2.0)*cos(v)*T(2)
            *pow((T)cos(u),T(6))*T(9);
        T s3 =	s4+T(4)*pow((T)cos(u),T(4))*sin(T(3.0)*v)*T(9)*cos(T(2.0)*v)+T(4)
            *pow((T)cos(u),T(4))*sin(T(3.0)*v)*T(9)*cos(T(2.0)*v)*T(9)-T(4)
            *pow((T)cos(u),T(6))*sin(T(3.0)*v)*T(9)*cos(T(2.0)*v)-T(4)*pow((T)cos(u),T(6))
            *sin(T(3.0)*v)*T(9)*cos(T(2.0)*v)*T(9)+pow((T)cos(u),T(6))*T(4)
            *T(4)*sin(T(3.0)*v)*cos(T(2.0)*v)-pow((T)cos(u),T(6))*T(4)*T(4)
            *sin(T(3.0)*v)*cos(T(2.0)*v)*T(9)+2.0*T(2.0)*T(4)*pow((T)cos(u),T(4))
            *cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v);

          s4 =	s3-2.0*T(2.0)*T(4)*pow((T)cos(u),T(4))*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*sin(T(2.0)*v)
            -2.0*T(2.0)*T(4)*pow((T)cos(u),T(6))*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)+2.0*T(2.0)
            *T(4)*pow((T)cos(u),T(6))*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*sin(T(2.0)*v)+4.0*sin(u)
            *T(2.0)*T(M_SQRT2)*cos(u)*cos(T(3.0)*v)*T(3.0)*sin(v)-4.0*sin(u)*pow(T(M_SQRT2),T(3))
            *pow((T)cos(u),T(3))*T(9)*cos(T(2.0)*v)+4.0*sin(u)*pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(5))
            *T(9)*cos(T(2.0)*v);
        T s2 =	s4-4.0*sin(u)*pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(3))*T(9)*cos(T(2.0)*v)*T(9)
            -2.0*sin(u)*T(2.0)*cos(v)*T(M_SQRT2)*cos(u)*sin(T(3.0)*v)-5.0*T(4)
            *T(2)*cos(u)*cos(u)*cos(T(2.0)*v)*sin(T(3.0)*v)+2.0*sin(u)*T(M_SQRT2)
            *cos(u)*sin(T(3.0)*v)*T(9)*T(2.0)*cos(v)-2.0*T(2)
            *cos(u)*cos(u)*T(9)*T(2.0)*cos(v)-4.0*T(2)*cos(u)*cos(u)
            *T(9)*T(2.0)*cos(v)*T(9)+6.0*T(2)*pow((T)cos(u),T(4))
            *T(9)*T(2.0)*cos(v);

          s4 =	12.0*T(2)*pow((T)cos(u),T(4))*T(9)*T(2.0)*cos(v)*T(9)
            -4.0*T(2)*pow((T)cos(u),T(6))*T(9)*T(2.0)*cos(v)-8.0*T(2)
            *pow((T)cos(u),T(6))*T(9)*T(2.0)*cos(v)*T(9)+6.0*T(2.0)
            *T(2)*cos(u)*cos(u)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)-4.0*T(2.0)
            *T(2)*cos(u)*cos(u)*cos(T(3.0)*v)*T(3.0)*sin(v)*sin(T(3.0)*v)+T(24)
            *T(2)*pow((T)cos(u),T(4))*cos(T(3.0)*v)*T(3.0)*sin(v)*sin(T(3.0)*v);

          s3 =	s4-8.0*T(2.0)*T(2)*pow((T)cos(u),T(6))*cos(T(3.0)*v)*T(3.0)*sin(v)*sin(T(3.0)*v)
            +3.0*T(2)*cos(u)*cos(u)*sin(T(3.0)*v)*T(9)*cos(T(2.0)*v)
            -8.0*sin(u)*T(2.0)*pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(3))*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)
            *sin(T(3.0)*v)+4.0*sin(u)*T(4)*pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(3))*cos(T(2.0)*v)
            -2.0*sin(u)*T(4)*pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(5))*cos(T(2.0)*v)
            -4.0*sin(u)*T(4)*pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(3))*cos(T(2.0)*v)
            *T(9)+2.0*sin(u)*T(4)*pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(5))
            *cos(T(2.0)*v)*T(9);

          s4 =	s3-T(4)*T(4)*pow((T)cos(u),T(4))*cos(T(2.0)*v)*sin(T(3.0)*v)+T(4)
            *T(4)*pow((T)cos(u),T(4))*cos(T(2.0)*v)*sin(T(3.0)*v)*T(9)+8.0
            *pow((T)cos(u),T(5))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*sin(u)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)
            +T(2.0)*cos(v)+s2+2.0*sin(u)*T(4)*T(M_SQRT2)*cos(u)*cos(T(2.0)*v)
            ;
        T s1 =	s4-2.0*cos(u)*cos(u)*T(2.0)*cos(v)-8.0*pow((T)cos(u),T(4))*T(2.0)*T(2)
            *cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)+8.0*pow((T)cos(u),T(5))*pow(T(M_SQRT2),T(3))
            *T(9)*T(9)*sin(u)*cos(T(2.0)*v)-4.0*pow((T)cos(u),T(4))
            *T(2)*sin(T(3.0)*v)*T(9)*cos(T(2.0)*v)+4.0*pow((T)cos(u),T(4))
            *T(4)*T(2)*sin(T(3.0)*v)*cos(T(2.0)*v)-8.0*pow((T)cos(u),T(3))
            *T(2.0)*T(M_SQRT2)*sin(u)*cos(T(3.0)*v)*T(3.0)*sin(v)+4.0*pow((T)cos(u),T(3))*T(2.0)
            *cos(v)*T(M_SQRT2)*sin(u)*sin(T(3.0)*v)-4.0*pow((T)cos(u),T(3))*T(M_SQRT2)*sin(u)
            *sin(T(3.0)*v)*T(9)*T(2.0)*cos(v);

        s2 =	1/T(3.0)/pow((T)T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(4));

        this->_p[1][2][0] =	s1*s2;

          s4 =	-T(2.0)*sin(v)-2.0*sin(u)*T(M_SQRT2)*cos(u)*sin(T(3.0)*v)*T(9)*T(2.0)
            *sin(v)-4.0*T(2.0)*T(2)*cos(u)*cos(u)*cos(T(3.0)*v)*T(3.0)*cos(v)
            *sin(T(3.0)*v)-5.0*T(4)*T(2)*cos(u)*cos(u)*sin(T(2.0)*v)
            *sin(T(3.0)*v)+4.0*pow((T)cos(u),T(5))*pow(T(M_SQRT2),T(3))*T(9)*sin(u)*sin(T(2.0)*v)
            -8.0*pow((T)cos(u),T(5))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*sin(u)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)
            ;
          s3 =	s4+4.0*sin(u)*T(4)*pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(3))*sin(T(2.0)*v)-4.0*sin(u)
            *T(4)*pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(3))*sin(T(2.0)*v)*T(9)
            -4.0*sin(u)*pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(3))*T(9)*sin(T(2.0)*v)-pow((T)cos(u),T(6))
            *T(4)*sin(T(3.0)*v)*T(9)*sin(T(2.0)*v)+T(4)*pow((T)cos(u),T(4))
            *sin(T(3.0)*v)*T(9)*sin(T(2.0)*v)+8.0*sin(u)*T(2.0)*pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(3))
            *cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)*sin(T(3.0)*v)-6.0*T(2.0)*T(2)*cos(u)*cos(u)
            *cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v);

          s4 =	s3+4.0*sin(u)*T(2.0)*T(M_SQRT2)*cos(u)*cos(T(3.0)*v)*T(3.0)*cos(v)-2.0*T(2.0)
            *T(4)*pow((T)cos(u),T(4))*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)+2.0*T(2.0)*T(4)
            *pow((T)cos(u),T(4))*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*cos(T(2.0)*v)+2.0*T(2.0)*T(4)
            *pow((T)cos(u),T(6))*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)-2.0*T(2.0)*T(4)*pow((T)cos(u),T(6))
            *pow((T)cos(T(3.0)*v),T(3))*T(3.0)*cos(T(2.0)*v)-T(4)*pow((T)cos(u),T(6))*T(9)
            *T(9)*sin(T(2.0)*v)*sin(T(3.0)*v);

          s2 =	s4+2.0*T(2)*cos(u)*cos(u)*T(9)*T(2.0)*sin(v)-6.0*T(2)
            *pow((T)cos(u),T(4))*T(9)*T(2.0)*sin(v)+4.0*T(2)*pow((T)cos(u),T(6))
            *T(9)*T(2.0)*sin(v)+3.0*T(2)*cos(u)*cos(u)*sin(T(3.0)*v)*T(9)
            *sin(T(2.0)*v)+12.0*pow((T)cos(u),T(4))*T(2.0)*T(2)*cos(T(3.0)*v)*T(3.0)*cos(v)
            *sin(T(3.0)*v)-8.0*pow((T)cos(u),T(6))*T(2.0)*T(2)*cos(T(3.0)*v)*T(3.0)*cos(v)
            *sin(T(3.0)*v)-2.0*pow((T)cos(u),T(5))*T(4)*pow(T(M_SQRT2),T(3))*sin(T(2.0)*v)*sin(u);

          s4 =	2.0*pow((T)cos(u),T(5))*T(4)*pow(T(M_SQRT2),T(3))*sin(T(2.0)*v)*sin(u)*T(9)
            -T(4)*T(4)*pow((T)cos(u),T(4))*sin(T(2.0)*v)*sin(T(3.0)*v)+T(4)
            *T(4)*pow((T)cos(u),T(4))*sin(T(2.0)*v)*sin(T(3.0)*v)*T(9)+T(4)
            *T(4)*pow((T)cos(u),T(6))*sin(T(2.0)*v)*sin(T(3.0)*v)-T(4)*T(4)
            *pow((T)cos(u),T(6))*sin(T(2.0)*v)*sin(T(3.0)*v)*T(9)+4.0*T(2)*cos(u)*cos(u)
            *T(9)*T(9)*T(2.0)*sin(v);

          s3 =	s4-12.0*T(2)*pow((T)cos(u),T(4))*T(9)*T(9)*T(2.0)*sin(v)+8.0
            *T(2)*pow((T)cos(u),T(6))*T(9)*T(9)*T(2.0)*sin(v)-4.0*sin(u)
            *pow(T(M_SQRT2),T(3))*pow((T)cos(u),T(3))*T(9)*T(9)*sin(T(2.0)*v)-3.0*T(2.0)
            *sin(v)*T(2)*pow((T)cos(u),T(4))*T(9)-2.0*T(2.0)*sin(v)*T(2)
            *pow((T)cos(u),T(6))+2.0*T(2.0)*sin(v)*T(2)*pow((T)cos(u),T(6))*T(9)+2.0*sin(u)
            *T(2.0)*sin(v)*T(M_SQRT2)*cos(u)*sin(T(3.0)*v);

          s4 =	s3-T(2.0)*sin(v)*T(2)*cos(u)*cos(u)+T(2.0)*sin(v)*T(2)
            *cos(u)*cos(u)*T(9)+3.0*T(2.0)*sin(v)*T(2)*pow((T)cos(u),T(4))
            +T(4)*pow((T)cos(u),T(4))*T(9)*T(9)*sin(T(2.0)*v)*sin(T(3.0)*v)+4.0
            *pow((T)cos(u),T(4))*T(4)*T(2)*sin(T(3.0)*v)*sin(T(2.0)*v)+8.0
            *pow((T)cos(u),T(5))*pow(T(M_SQRT2),T(3))*T(9)*T(9)*sin(u)*sin(T(2.0)*v);

          s1 =	s4+8.0*pow((T)cos(u),T(4))*T(2.0)*T(2)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)-4.0*pow((T)cos(u),T(4))
            *T(2)*sin(T(3.0)*v)*T(9)*sin(T(2.0)*v)-8.0*pow((T)cos(u),T(3))*T(2.0)
            *T(M_SQRT2)*sin(u)*cos(T(3.0)*v)*T(3.0)*cos(v)-4.0*pow((T)cos(u),T(3))*T(2.0)*sin(v)*T(M_SQRT2)
            *sin(u)*sin(T(3.0)*v)+4.0*pow((T)cos(u),T(3))*T(M_SQRT2)*sin(u)*sin(T(3.0)*v)*T(9)*T(2.0)*sin(v)
            +2.0*sin(u)*T(4)*T(M_SQRT2)*cos(u)*sin(T(2.0)*v)+2.0*cos(u)*cos(u)*T(2.0)*sin(v)+s2;

          s2 =	1/T(3.0)/pow((T)-T(1.0)+T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(4));

        this->_p[1][2][1] =	s1*s2;
        this->_p[1][2][2] =	-cos(u)*cos(u)*T(M_SQRT2)*T(9)*(4.0*sin(T(3.0)*v)*cos(u)*cos(u)
                +pow((T)cos(u),T(4))*T(2)*T(9)*sin(T(3.0)*v)-3.0*sin(T(3.0)*v)
                -sin(T(3.0)*v)*T(2)*cos(u)*cos(u)+sin(T(3.0)*v)*T(2)
                *pow((T)cos(u),T(4))-4.0*sin(u)*T(M_SQRT2)*pow((T)cos(u),T(3))+4.0*sin(u)*T(M_SQRT2)
                *cos(u)-cos(u)*cos(u)*T(2)*T(9)*sin(T(3.0)*v)+4.0*cos(u)
                *sin(u)*T(M_SQRT2)*T(9)-8.0*pow((T)cos(u),T(3))*T(M_SQRT2)
                *T(9)*sin(u))/pow((T)T(1.0)-T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(4));

      }
      if(d1>1 && d2>1) //uuvv
      {
        T s5 =	-32.0*sin(u)*T(2.0)*T(2)*cos(T(3.0)*v)*T(3.0)*pow((T)cos(u),T(3))*sin(T(2.0)*v)
            -16.0*pow((T)cos(u),T(5))*T(2.0)*T(2)*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*sin(u)*sin(v)
            -4.0*T(4)*cos(u)*cos(u)*T(M_SQRT2)*cos(T(2.0)*v)-4.0*T(2.0)*sin(u)*cos(u)*cos(v)
            -16.0*pow((T)cos(u),T(3))*T(2)*sin(u)*sin(T(3.0)*v)*T(9)*cos(T(2.0)*v)
            +32.0*pow((T)cos(u),T(4))*T(2.0)*T(M_SQRT2)*cos(T(3.0)*v)*T(3.0)*sin(v);

        T s4 =	s5+16.0*pow((T)cos(u),T(4))*T(M_SQRT2)*sin(T(3.0)*v)*T(9)*T(2.0)*cos(v)-4.0
            *pow((T)cos(u),T(4))*T(2.0)*T(M_SQRT2)*sin(T(3.0)*v)*cos(v)-64.0*pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(3))
            *T(9)*T(9)*cos(T(2.0)*v)+2.0*T(4)*T(M_SQRT2)*cos(T(2.0)*v)
            +2.0*pow((T)cos(u),T(8))*pow(T(M_SQRT2),T(5))*T(9)*cos(T(2.0)*v)-2.0*pow((T)cos(u),T(8))*T(4)
            *pow(T(M_SQRT2),T(5))*cos(T(2.0)*v);

        s5 =	s4-2.0*pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(5))*T(9)*cos(T(2.0)*v)+2.0*pow((T)cos(u),T(6))*T(4)
            *pow(T(M_SQRT2),T(5))*cos(T(2.0)*v)+4.0*pow((T)cos(u),T(5))*T(2)*T(9)*sin(u)*T(2.0)
            *cos(v)+4.0*pow((T)cos(u),T(3))*T(4)*T(2)*sin(u)*sin(T(3.0)*v)*cos(T(2.0)*v)
            +8.0*pow((T)cos(u),T(5))*T(4)*T(4)*sin(u)*sin(T(3.0)*v)*cos(T(2.0)*v)
            *T(9);

        T  s3 =	s5-4.0*pow((T)cos(u),T(7))*T(4)*T(4)*sin(u)*sin(T(3.0)*v)*cos(T(2.0)*v)*T(9)
            -6.0*cos(u)*cos(u)*pow(T(M_SQRT2),T(3))*T(9)*cos(T(2.0)*v)-18.0*cos(u)*cos(u)
            *pow(T(M_SQRT2),T(3))*T(9)*cos(T(2.0)*v)*T(9)+18.0*pow((T)cos(u),T(4))
            *pow(T(M_SQRT2),T(3))*T(9)*cos(T(2.0)*v)+74.0*pow((T)cos(u),T(4))*pow(T(M_SQRT2),T(3))*T(9)
            *cos(T(2.0)*v)*T(9)-8.0*pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(3))*T(9)
            *cos(T(2.0)*v)-2.0*T(4)*pow(T(M_SQRT2),T(3))*cos(T(2.0)*v)*cos(u)*cos(u)
            *T(9);

          s5 =	4.0*T(4)*pow(T(M_SQRT2),T(3))*cos(T(2.0)*v)*pow((T)cos(u),T(4))-4.0*T(4)*pow(T(M_SQRT2),T(3))*cos(T(2.0)*v)
            *pow((T)cos(u),T(4))*T(9)-4.0*T(4)*pow(T(M_SQRT2),T(3))*cos(T(2.0)*v)
            *pow((T)cos(u),T(6))+4.0*T(4)*pow(T(M_SQRT2),T(3))*cos(T(2.0)*v)*pow((T)cos(u),T(6))
            *T(9)-4.0*T(4)*sin(u)*T(2)*cos(T(2.0)*v)*cos(u)*sin(T(3.0)*v)
            +4.0*T(2.0)*cos(u)*cos(u)*cos(v)*T(M_SQRT2)*sin(T(3.0)*v);

          s4 =	s5-8.0*pow((T)cos(u),T(5))*T(4)*T(4)*sin(u)*sin(T(3.0)*v)*cos(T(2.0)*v)-12.0
            *pow((T)cos(u),T(5))*T(2.0)*T(4)*sin(u)*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*sin(T(2.0)*v)-8.0*cos(u)*cos(u)
            *T(2.0)*pow(T(M_SQRT2),T(3))*cos(T(3.0)*v)*T(3.0)*sin(v)+24.0*pow((T)cos(u),T(4))*T(2.0)*pow(T(M_SQRT2),T(3))
            *cos(T(3.0)*v)*T(3.0)*sin(v)+8.0*cos(u)*cos(u)*T(2.0)*pow(T(M_SQRT2),T(3))*pow((T)cos(T(3.0)*v),T(3))
            *T(3.0)*sin(v)-24.0*pow((T)cos(u),T(4))*T(2.0)*pow(T(M_SQRT2),T(3))*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*sin(v)
            +36.0*pow((T)cos(u),T(4))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v);

          s5 =	s4+4.0*T(2.0)*sin(u)*pow((T)cos(u),T(3))*cos(v)*T(2)-4.0*T(2.0)*sin(u)*pow((T)cos(u),T(5))*cos(v)
            *T(2)-4.0*T(2.0)*sin(u)*pow((T)cos(u),T(3))*cos(v)*T(2)
            *T(9)-12.0*cos(u)*cos(u)*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)
            *sin(T(2.0)*v)+4.0*cos(u)*T(2.0)*T(2)*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*sin(u)
            *sin(v)+16.0*pow((T)cos(u),T(3))*T(2.0)*T(2)*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)
            *sin(u)*sin(v);

        T s2 =	s5-8.0*cos(u)*cos(u)*pow(T(M_SQRT2),T(3))*T(9)*T(9)*T(2.0)*cos(v)
            *sin(T(3.0)*v)+24.0*pow((T)cos(u),T(4))*pow(T(M_SQRT2),T(3))*T(9)*T(9)*T(2.0)*cos(v)
            *sin(T(3.0)*v)-32.0*pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(3))*T(9)*T(9)*T(2.0)*cos(v)
            *sin(T(3.0)*v)+16.0*pow((T)cos(u),T(8))*pow(T(M_SQRT2),T(3))*T(9)*T(9)*T(2.0)
            *cos(v)*sin(T(3.0)*v)+64.0*pow((T)cos(u),T(3))*T(2)*sin(u)*T(9)*T(9)
            *T(2.0)*cos(v)+2.0*pow((T)cos(u),T(5))*T(4)*sin(u)*T(9)*T(9)
            *cos(T(2.0)*v)*sin(T(3.0)*v)+s3;

          s5 =	-16.0*pow((T)cos(u),T(7))*T(2.0)*T(4)*sin(u)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)+16.0
            *pow((T)cos(u),T(7))*T(2.0)*T(4)*sin(u)*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*sin(T(2.0)*v)-32.0
            *pow((T)cos(u),T(6))*T(2.0)*pow(T(M_SQRT2),T(3))*cos(T(3.0)*v)*T(3.0)*sin(v)+16.0*pow((T)cos(u),T(8))*T(2.0)
            *pow(T(M_SQRT2),T(3))*cos(T(3.0)*v)*T(3.0)*sin(v)+32.0*pow((T)cos(u),T(6))*T(2.0)*pow(T(M_SQRT2),T(3))
            *pow((T)cos(T(3.0)*v),T(3))*T(3.0)*sin(v)-16.0*pow((T)cos(u),T(8))*T(2.0)*pow(T(M_SQRT2),T(3))*pow((T)cos(T(3.0)*v),T(3))
            *T(3.0)*sin(v);

          s4 =	s5+12.0*pow((T)cos(u),T(5))*T(2.0)*T(4)*sin(u)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)+2.0*
            T(4)*pow(T(M_SQRT2),T(3))*cos(T(2.0)*v)*cos(u)*cos(u)+4.0*pow((T)cos(u),T(7))
            *T(4)*T(4)*sin(u)*sin(T(3.0)*v)*cos(T(2.0)*v)-2.0*pow((T)cos(u),T(8))
            *pow(T(M_SQRT2),T(5))*pow((T)cos(T(3.0)*v),T(4))*T(9)*cos(T(2.0)*v)+2.0*T(2.0)*T(M_SQRT2)*sin(T(3.0)*v)
            *cos(v)-32.0*T(2.0)*T(M_SQRT2)*cos(u)*cos(u)*cos(T(3.0)*v)*T(3.0)*sin(v);

          s5 =	s4+12.0*sin(u)*T(2.0)*T(2)*cos(u)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)-14.0*cos(u)
            *T(2)*T(9)*T(9)*T(2.0)*sin(u)*cos(v)-16.0
            *cos(u)*cos(u)*T(M_SQRT2)*sin(T(3.0)*v)*T(9)*T(2.0)*cos(v)+2.0*cos(u)
            *T(2)*T(9)*T(2.0)*sin(u)*cos(v)+8.0*pow((T)cos(u),T(3))*T(2)
            *T(9)*T(2.0)*sin(u)*cos(v)-8.0*pow((T)cos(u),T(5))*T(2)*T(9)
            *T(2.0)*sin(u)*cos(v);

          s3 =	s5-16.0*pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*T(9)*T(2.0)*cos(v)+8.0
            *pow((T)cos(u),T(8))*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*T(9)*T(2.0)*cos(v)-4.0*pow((T)cos(u),T(6))
            *T(2.0)*pow(T(M_SQRT2),T(5))*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)+4.0*pow((T)cos(u),T(6))*T(2.0)
            *pow(T(M_SQRT2),T(5))*sin(T(3.0)*v)*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*sin(T(2.0)*v)+4.0*pow((T)cos(u),T(8))*T(2.0)
            *pow(T(M_SQRT2),T(5))*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)-4.0*pow((T)cos(u),T(8))*T(2.0)
            *pow(T(M_SQRT2),T(5))*sin(T(3.0)*v)*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*sin(T(2.0)*v)-4.0*cos(u)*cos(u)
            *pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*T(9)*T(2.0)*cos(v);

          s5 =	12.0*pow((T)cos(u),T(4))*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*T(9)*T(2.0)*cos(v)+2.0*pow((T)cos(u),T(6))
            *pow(T(M_SQRT2),T(5))*T(9)*cos(T(2.0)*v)*pow((T)cos(T(3.0)*v),T(4))-4.0*pow((T)cos(u),T(6))*T(4)
            *pow(T(M_SQRT2),T(5))*cos(T(2.0)*v)*T(9)+4.0*pow((T)cos(u),T(8))*T(4)*pow(T(M_SQRT2),T(5))
            *cos(T(2.0)*v)*T(9)+2.0*pow((T)cos(u),T(6))*T(4)*pow(T(M_SQRT2),T(5))*cos(T(2.0)*v)
            *pow((T)cos(T(3.0)*v),T(4))-2.0*pow((T)cos(u),T(8))*T(4)*pow(T(M_SQRT2),T(5))*cos(T(2.0)*v)*pow((T)cos(T(3.0)*v),T(4));

          s4 =	s5-8.0*pow((T)cos(u),T(7))*T(4)*sin(T(3.0)*v)*sin(u)*T(9)*cos(T(2.0)*v)+6.0
            *pow((T)cos(u),T(5))*T(4)*sin(T(3.0)*v)*sin(u)*T(9)*cos(T(2.0)*v)+4.0*T(2.0)
            *T(M_SQRT2)*cos(T(3.0)*v)*T(3.0)*sin(v)+2.0*T(M_SQRT2)*sin(T(3.0)*v)*T(9)*T(2.0)
            *cos(v)+6.0*sin(u)*T(2)*cos(u)*sin(T(3.0)*v)*T(9)*cos(T(2.0)*v)
            +8.0*pow((T)cos(u),T(6))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(v)-4.0*pow((T)cos(u),T(8))
            *T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(v);

          s5 =	s4-8.0*pow((T)cos(u),T(6))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(v)*T(9)+4.0
            *pow((T)cos(u),T(8))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(v)*T(9)+2.0*cos(u)*cos(u)
            *T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(v)-6.0*pow((T)cos(u),T(4))*T(2.0)*pow(T(M_SQRT2),T(3))
            *sin(T(3.0)*v)*cos(v)-2.0*cos(u)*cos(u)*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(v)*T(9)
            +6.0*pow((T)cos(u),T(4))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(v)*T(9);

          T s1 = s5-4.0*cos(u)*T(2.0)*T(2)*sin(u)*cos(v)+4.0*cos(u)*T(2.0)*T(2)
            *sin(u)*cos(v)*T(9)+s2-16.0*pow((T)cos(u),T(7))*T(4)
            *T(9)*T(9)*cos(T(2.0)*v)*sin(u)*sin(T(3.0)*v)+s3-16.0*pow((T)cos(u),T(6))
            *T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*sin(T(2.0)*v)-64.0
            *pow((T)cos(u),T(5))*T(2)*T(9)*T(9)*sin(u)*T(2.0)*cos(v);

          s2 =	1/T(3.0)/pow((T)-T(1.0)+T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(5));

        this->_p[2][2][0] =	s1*s2;

          s5 =	16.0*pow((T)cos(u),T(6))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)
            +32.0*pow((T)cos(u),T(3))*T(2.0)*T(2)*cos(T(3.0)*v)*T(3.0)*sin(u)*cos(T(2.0)*v)
            +4.0*pow((T)cos(u),T(4))*T(2.0)*T(M_SQRT2)*sin(T(3.0)*v)*sin(v)+4.0*cos(u)*T(2.0)*sin(u)*sin(v)
            -64.0*pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(3))*T(9)*T(9)*sin(T(2.0)*v)
            -4.0*cos(u)*cos(u)*T(4)*T(M_SQRT2)*sin(T(2.0)*v);

          s4 =	s5-16.0*pow((T)cos(u),T(5))*T(2.0)*T(2)*sin(T(3.0)*v)*sin(u)*cos(T(3.0)*v)*T(3.0)*cos(v)
            -16.0*pow((T)cos(u),T(7))*T(4)*sin(T(3.0)*v)*sin(u)*T(9)*T(9)*sin(T(2.0)*v)
            +64.0*pow((T)cos(u),T(5))*T(2)*T(9)*T(9)*sin(u)*T(2.0)*sin(v)+32.0
            *pow((T)cos(u),T(4))*T(2.0)*T(M_SQRT2)*cos(T(3.0)*v)*T(3.0)*cos(v)-16.0*pow((T)cos(u),T(4))*T(M_SQRT2)
            *sin(T(3.0)*v)*T(9)*T(2.0)*sin(v)-16.0*sin(u)*T(2)*sin(T(3.0)*v)
            *T(9)*pow((T)cos(u),T(3))*sin(T(2.0)*v);

          s5 =	s4+6.0*sin(u)*T(2)*sin(T(3.0)*v)*T(9)*cos(u)*sin(T(2.0)*v)-6.0*cos(u)*cos(u)
            *pow(T(M_SQRT2),T(3))*T(9)*sin(T(2.0)*v)+18.0*pow((T)cos(u),T(4))*pow(T(M_SQRT2),T(3))*T(9)
            *sin(T(2.0)*v)+4.0*cos(u)*T(2.0)*T(2)*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*sin(u)*cos(v)+16.0
            *pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*T(9)*T(2.0)*sin(v);

          s3 =	s5+8.0*pow((T)cos(u),T(5))*T(2)*sin(u)*T(9)*T(2.0)*sin(v)-8.0*pow((T)cos(u),T(8))
            *pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*T(9)*T(2.0)*sin(v)+4.0*T(2.0)*T(M_SQRT2)*cos(T(3.0)*v)*T(3.0)*cos(v)
            +16.0*pow((T)cos(u),T(3))*T(2.0)*T(2)*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*sin(u)*cos(v)+8.0*cos(u)*cos(u)
            *pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*T(9)*T(9)*T(2.0)*sin(v)+32.0*pow((T)cos(u),T(6))
            *pow(T(M_SQRT2),T(3))*T(9)*T(9)*T(2.0)*sin(v)*sin(T(3.0)*v)-36.0*pow((T)cos(u),T(4))*T(2.0)
            *pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v);

          s5 =	s3+12.0*cos(u)*cos(u)*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)-32.0*cos(u)*cos(u)
            *T(2.0)*T(M_SQRT2)*cos(T(3.0)*v)*T(3.0)*cos(v)-4.0*pow((T)cos(u),T(5))*T(2)*T(9)
            *sin(u)*T(2.0)*sin(v)-2.0*T(2.0)*T(M_SQRT2)*sin(T(3.0)*v)*sin(v)+16.0*T(M_SQRT2)*sin(T(3.0)*v)
            *T(9)*T(2.0)*sin(v)*cos(u)*cos(u);

          s4 =	s5-8.0*cos(u)*cos(u)*T(2.0)*pow(T(M_SQRT2),T(3))*cos(T(3.0)*v)*T(3.0)*cos(v)-4.0*cos(u)*cos(u)*T(2.0)*T(M_SQRT2)
            *sin(T(3.0)*v)*sin(v)-2.0*T(M_SQRT2)*sin(T(3.0)*v)*T(9)*T(2.0)*sin(v)+4.0*pow((T)cos(u),T(3))
            *T(4)*T(2)*sin(T(3.0)*v)*sin(u)*sin(T(2.0)*v)+2.0*T(4)*T(M_SQRT2)*sin(T(2.0)*v)
            -2.0*pow((T)cos(u),T(8))*T(4)*pow(T(M_SQRT2),T(5))*sin(T(2.0)*v)+2.0*pow((T)cos(u),T(8))*pow(T(M_SQRT2),T(5))
            *T(9)*sin(T(2.0)*v);

          s5 =	s4+2.0*pow((T)cos(u),T(6))*T(4)*pow(T(M_SQRT2),T(5))*sin(T(2.0)*v)-2.0*pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(5))*T(9)
            *sin(T(2.0)*v)+74.0*pow((T)cos(u),T(4))*pow(T(M_SQRT2),T(3))*T(9)*T(9)*sin(T(2.0)*v)-18.0*cos(u)*cos(u)
            *pow(T(M_SQRT2),T(3))*T(9)*T(9)*sin(T(2.0)*v)-2.0*pow((T)cos(u),T(8))*pow(T(M_SQRT2),T(5))
            *pow((T)cos(T(3.0)*v),T(4))*T(9)*sin(T(2.0)*v)-8.0*pow((T)cos(u),T(5))*T(4)*T(4)*sin(T(3.0)*v)*sin(u)
            *sin(T(2.0)*v);

          s2 =	s5+4.0*pow((T)cos(u),T(7))*T(4)*T(4)*sin(T(3.0)*v)*sin(u)*sin(T(2.0)*v)+8.0*pow((T)cos(u),T(5))
            *T(4)*T(4)*sin(T(3.0)*v)*sin(u)*sin(T(2.0)*v)*T(9)-4.0*pow((T)cos(u),T(7))
            *T(4)*T(4)*sin(T(3.0)*v)*sin(u)*sin(T(2.0)*v)*T(9)+6.0*pow((T)cos(u),T(4))
            *T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*sin(v)-8.0*pow((T)cos(u),T(6))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*sin(v)
            +4.0*pow((T)cos(u),T(8))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*sin(v)+2.0*cos(u)*cos(u)*T(2.0)*pow(T(M_SQRT2),T(3))
            *sin(T(3.0)*v)*sin(v)*T(9);

          s5 =	s2-6.0*pow((T)cos(u),T(4))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*sin(v)*T(9)+8.0*pow((T)cos(u),T(6))*T(2.0)
            *pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*sin(v)*T(9)-4.0*pow((T)cos(u),T(8))*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)
            *sin(v)*T(9)-4.0*pow((T)cos(u),T(3))*T(2.0)*T(2)*sin(u)*sin(v)+4.0
            *pow((T)cos(u),T(5))*T(2.0)*T(2)*sin(u)*sin(v);

          s4 =	s5-4.0*cos(u)*T(2.0)*T(2)*sin(u)*sin(v)*T(9)+4.0*pow((T)cos(u),T(3))*T(4)*sin(u)
            *sin(v)*T(9)-2.0*cos(u)*cos(u)*T(2.0)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*sin(v)+4.0*cos(u)*T(2.0)
            *T(2)*sin(u)*sin(v)-64.0*pow((T)cos(u),T(3))*T(2)*T(9)*T(9)*sin(u)
            *T(2.0)*sin(v)-24.0*pow((T)cos(u),T(4))*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*T(9)*T(9)
            *T(2.0)*sin(v);

          s5 =	s4-16.0*pow((T)cos(u),T(8))*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*T(9)*T(9)*T(2.0)*sin(v)+4.0*pow((T)cos(u),T(6))
            *T(2.0)*pow(T(M_SQRT2),T(5))*sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)-4.0*pow((T)cos(u),T(8))*T(2.0)*pow(T(M_SQRT2),T(5))
            *sin(T(3.0)*v)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)-4.0*pow((T)cos(u),T(6))*T(2.0)*pow(T(M_SQRT2),T(5))*sin(T(3.0)*v)*pow((T)cos(T(3.0)*v),T(3))
            *T(3.0)*cos(T(2.0)*v)+4.0*pow((T)cos(u),T(8))*T(2.0)*pow(T(M_SQRT2),T(5))*sin(T(3.0)*v)*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*cos(T(2.0)*v)
            -4.0*pow((T)cos(u),T(6))*T(4)*pow(T(M_SQRT2),T(5))*sin(T(2.0)*v)*T(9);

          s3 =	s5+4.0*pow((T)cos(u),T(8))*T(4)*pow(T(M_SQRT2),T(5))*sin(T(2.0)*v)*T(9)+2.0*pow((T)cos(u),T(6))*T(4)
            *pow(T(M_SQRT2),T(5))*sin(T(2.0)*v)*pow((T)cos(T(3.0)*v),T(4))-2.0*pow((T)cos(u),T(8))*T(4)*pow(T(M_SQRT2),T(5))*sin(T(2.0)*v)
            *pow((T)cos(T(3.0)*v),T(4))+14.0*sin(u)*T(2)*T(9)*T(9)*cos(u)*T(2.0)*sin(v)
            +2.0*cos(u)*cos(u)*T(4)*pow(T(M_SQRT2),T(3))*sin(T(2.0)*v)+4.0*pow((T)cos(u),T(4))*T(4)
            *pow(T(M_SQRT2),T(3))*sin(T(2.0)*v)-4.0*pow((T)cos(u),T(6))*T(4)*pow(T(M_SQRT2),T(3))*sin(T(2.0)*v);

          s5 =	s3-2.0*cos(u)*cos(u)*T(4)*pow(T(M_SQRT2),T(3))*sin(T(2.0)*v)*T(9)
            -4.0*pow((T)cos(u),T(4))*T(4)*pow(T(M_SQRT2),T(3))*sin(T(2.0)*v)*T(9)
            +4.0*pow((T)cos(u),T(6))*T(4)*pow(T(M_SQRT2),T(3))*sin(T(2.0)*v)*T(9)
            +6.0*pow((T)cos(u),T(5))*T(4)*sin(T(3.0)*v)*sin(u)*T(9)*sin(T(2.0)*v)-8.0*pow((T)cos(u),T(7))
            *T(4)*sin(T(3.0)*v)*sin(u)*T(9)*sin(T(2.0)*v);

          s4 =	s5+2.0*pow((T)cos(u),T(5))*T(4)*sin(T(3.0)*v)*sin(u)*T(9)*sin(T(2.0)*v)*T(9)
            -4.0*cos(u)*T(4)*T(2)*sin(T(3.0)*v)*sin(u)*sin(T(2.0)*v)-32.0*pow((T)cos(u),T(6))
            *T(2.0)*pow(T(M_SQRT2),T(3))*cos(T(3.0)*v)*T(3.0)*cos(v)+16.0*pow((T)cos(u),T(8))*T(2.0)*pow(T(M_SQRT2),T(3))
            *cos(T(3.0)*v)*T(3.0)*cos(v)+8.0*cos(u)*cos(u)*T(2.0)*pow(T(M_SQRT2),T(3))*pow((T)cos(T(3.0)*v),T(3))*T(3.0)
            *cos(v)-24.0*pow((T)cos(u),T(4))*T(2.0)*pow(T(M_SQRT2),T(3))*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*cos(v)+32.0
            *pow((T)cos(u),T(6))*T(2.0)*pow(T(M_SQRT2),T(3))*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*cos(v);

          s5 =	s4-16.0*pow((T)cos(u),T(8))*T(2.0)*pow(T(M_SQRT2),T(3))*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*cos(v)+24.0*pow((T)cos(u),T(4))
            *T(2.0)*pow(T(M_SQRT2),T(3))*cos(T(3.0)*v)*T(3.0)*cos(v)+2.0*pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(5))*T(9)
            *sin(T(2.0)*v)*pow((T)cos(T(3.0)*v),T(4))-2.0*cos(u)*T(2)*T(9)*T(2.0)*sin(u)*sin(v)
            -12.0*cos(u)*T(2.0)*T(2)*cos(T(3.0)*v)*T(3.0)*sin(u)*cos(T(2.0)*v)-12.0*pow((T)cos(u),T(5))
            *T(2.0)*T(4)*sin(u)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v);

          s1 =	s5+16.0*pow((T)cos(u),T(7))*T(2.0)*T(4)*sin(u)*cos(T(3.0)*v)*T(3.0)*cos(T(2.0)*v)+12.0*pow((T)cos(u),T(5))
            *T(2.0)*T(4)*sin(u)*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*cos(T(2.0)*v)-16.0*pow((T)cos(u),T(7))*T(2.0)
            *T(4)*sin(u)*pow((T)cos(T(3.0)*v),T(3))*T(3.0)*cos(T(2.0)*v)-12.0*pow((T)cos(u),T(4))*pow(T(M_SQRT2),T(3))
            *sin(T(3.0)*v)*T(9)*T(2.0)*sin(v)-8.0*pow((T)cos(u),T(3))*T(2)*sin(u)*T(9)
            *T(2.0)*sin(v)+4.0*cos(u)*cos(u)*pow(T(M_SQRT2),T(3))*sin(T(3.0)*v)*T(9)*T(2.0)*sin(v)
            -8.0*pow((T)cos(u),T(6))*pow(T(M_SQRT2),T(3))*T(9)*sin(T(2.0)*v);

          s2 = 1/T(3.0)/pow((T)-T(1.0)+T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(5));

        this->_p[2][2][1] =	s1*s2;

        T s6 =	8.0*sin(u)*sin(T(3.0)*v)*cos(u)*cos(u)+32.0*pow((T)cos(u),T(5))*T(M_SQRT2)*T(9)
            +8.0*pow((T)cos(u),T(6))*T(2)*sin(T(3.0)*v)*sin(u)*T(9)
            -pow((T)cos(u),T(7))*pow(T(M_SQRT2),T(3))-3.0*sin(u)*sin(T(3.0)*v)+3.0*T(M_SQRT2)
            *cos(u)+4.0*pow((T)cos(u),T(6))*sin(u)*T(2)*sin(T(3.0)*v)-3.0*pow((T)cos(u),T(4))*sin(u)
            *T(2)*sin(T(3.0)*v);

          s5 =	s6-pow((T)cos(u),T(4))*sin(u)*T(2)*sin(T(3.0)*v)*T(9)+pow((T)cos(u),T(5))
            *pow(T(M_SQRT2),T(3))+9.0*T(M_SQRT2)*cos(u)*T(9)-9.0*pow((T)cos(u),T(3))*T(M_SQRT2)
            -37.0*pow((T)cos(u),T(3))*T(M_SQRT2)*T(9)+4.0*pow((T)cos(u),T(5))
            *T(M_SQRT2)+pow((T)cos(u),T(7))*pow(T(M_SQRT2),T(3))*pow((T)cos(T(3.0)*v),T(4))-pow((T)cos(u),T(5))
            *pow(T(M_SQRT2),T(3))*pow((T)cos(T(3.0)*v),T(4));

          s6 = 1/(pow((T)-T(1.0)+T(M_SQRT2)*sin(u)*cos(u)*sin(T(3.0)*v),T(5)));

          s4 = T(9)*s5*s6;

        this->_p[2][2][2] =	-2.0*T(M_SQRT2)*cos(u)*s4;
      }
    }
  }


  template <typename T>
  inline
  T PBoysSurface<T>::getEndPU() {

    return T(0.5 * M_PI);
  }


  template <typename T>
  inline
  T PBoysSurface<T>::getEndPV() {

    return T(M_PI);
  }


  template <typename T>
  inline
  T PBoysSurface<T>::getStartPU() {

    return T(0);
  }


  template <typename T>
  inline
  T PBoysSurface<T>::getStartPV() {

    return T(0);
  }


  template <typename T>
  void PBoysSurface<T>::init() {

    this->_dm = GM_DERIVATION_EXPLICIT;
  }


  template <typename T>
  inline
  bool PBoysSurface<T>::isClosedU() const {

    return false;
  }


  template <typename T>
  inline
  bool PBoysSurface<T>::isClosedV() const {

    return false;
  }

} // END namespace GMlib
