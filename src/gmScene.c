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



/*! \file gmScene.c
 *  \brief Inline Scene class implementations
 *
 *  Implementation of the Scene class.
 *
 *  \date   2008-08-03
 */


namespace GMlib {



  /*! double Scene::getElapsedTime()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  double Scene::getElapsedTime() {

    return _timer_time_elapsed;
  }


  /*! double Scene::getTimeScale()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  double Scene::getTimeScale() {

    return _timer_time_scale;
  }


  /*! bool Scene::isRunning()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  bool Scene::isRunning() {

    return _timer_active;
  }


  /*! void Scene::resetTime()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Scene::resetTime() {

    _timer_time_elapsed = 0;
  }


  /*! void Scene::setTimeScale( double s )
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Scene::setTimeScale( double s ) {

    _timer_time_scale = s;
  }


  /*! void Scene::start()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void Scene::start() {

    _timer_active = true;
    _timer.update();
  }


  /*! void   Scene::stop()
   *  \brief Pending Documentation
   *
   *  Pending Documentation
   */
  inline
  void   Scene::stop() {

    _timer_active = false;
  }

}
