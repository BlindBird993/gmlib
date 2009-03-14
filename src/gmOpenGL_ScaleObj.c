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



/*! \file gmOpenGL_ScaleObj.c
 *  \brief Inline ScaleObj class implementations
 *
 *  Inline implementation of the gmOpengGL components ScaleObj class.
 *
 *  \date   2008-08-03
 */



namespace GMlib {



  /*! ScaleObj::ScaleObj()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  ScaleObj::ScaleObj() {
    reset();
  }


  /*! ScaleObj::ScaleObj(float	s)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  ScaleObj::ScaleObj(float	s) {
    reset(Point<float,3>(s));
  }


  /*! ScaleObj::ScaleObj(Point<float,3>	sc)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  ScaleObj::ScaleObj(Point<float,3>	sc) {
    reset(sc);
  }


  /*! void ScaleObj::scale(const Point<float,3>& sc)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void ScaleObj::scale(const Point<float,3>& sc) {
    _scaled=true; _s %= sc; _updateMax();
  }


  /*! void ScaleObj::reset()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void ScaleObj::reset() {
    _scaled=false; _s=Point<float,3>(1);
  }


  /*! void ScaleObj::reset(const Point<float,3>& sc)
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void ScaleObj::reset(const Point<float,3>& sc) {
    if(sc(0)!= 1 || sc(1)!= 1 || sc(2)!= 1) { _s=sc; _updateMax(); _scaled=true; }
    else { _scaled=false; _s=sc; }
  }


  /*! void ScaleObj::glScaling()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void ScaleObj::glScaling() {
    if(_scaled) glScale(_s);
  }


  /*! bool  ScaleObj::isActive()  const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool  ScaleObj::isActive()  const {
    return _scaled;
  }


  /*! float ScaleObj::getMax() const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  float ScaleObj::getMax() const {
    return _max;
  }


  /*! Point<float,3>const& ScaleObj::getScale()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Point<float,3>const& ScaleObj::getScale() {
    return _s;
  }


  /*! Sphere<float,3> ScaleObj::scaleSphere(const Sphere<float,3>& sp) const
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  Sphere<float,3> ScaleObj::scaleSphere(const Sphere<float,3>& sp) const {

    if(_scaled)
    {
      if(sp.isValid()) return Sphere<float,3>(_max*sp.getPos(),_max*sp.getRadius());
      else return sp;
    }
    else return sp;
  }


  /*! void ScaleObj::_updateMax()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void ScaleObj::_updateMax() {
    _max = (_s[0] > _s[1] ? ( _s[0]>_s[2] ? _s[0]:_s[2] ):(_s[1]>_s[2] ? _s[1]:_s[2]));
  }

}
