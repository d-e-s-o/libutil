// Util.hpp

/***************************************************************************
 *   Copyright (C) 2014 Daniel Mueller (deso@posteo.net)                   *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation, either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>. *
 ***************************************************************************/

#ifndef UTLUTIL_HPP
#define UTLUTIL_HPP


namespace utl
{
  template<typename T>
  constexpr T min(T first, T second);

  template<typename T>
  constexpr T max(T first, T second);

  template<typename T>
  void swap(T& first, T& second);
}


namespace utl
{
  /**
   * @param first
   * @param second
   */
  template<typename T>
  constexpr T min(T first, T second)
  {
    return first < second ? first : second;
  }

  /**
   * @param first
   * @param second
   */
  template<typename T>
  constexpr T max(T first, T second)
  {
    return first > second ? first : second;
  }

  /**
   * This function swaps the contents of 'first' with that of 'second'.
   * @param first
   * @param second
   */
  template<typename T>
  void swap(T& first, T& second)
  {
    T temp = first;
    first  = second;
    second = temp;
  }
}


#endif
