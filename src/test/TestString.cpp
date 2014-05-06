// TestString.cpp

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

#include <util/String.hpp>

#include "TestString.hpp"


namespace test
{
  namespace
  {
    char const string1[] = {'a', 'b', '\0', 'a', 'b'};
    char const string2[] = {'a', 'b', 'c', '\0', 'a', 'b', 'c'};
  }


  TestString::TestString()
    : tst::TestCase<TestString>(*this, "TestString")
  {
    add(&TestString::testLength);
    add(&TestString::testCompareLess);
    add(&TestString::testCompareEqual);
    add(&TestString::testCopy);
  }

  void TestString::testLength(tst::TestResult& result)
  {
    ASSERT(utl::length("")   == 0);
    ASSERT(utl::length("a")  == 1);
    ASSERT(utl::length("b")  == 1);
    ASSERT(utl::length("ab") == 2);

    ASSERT(utl::length(string1) == 2);
    ASSERT(utl::length(string2) == 3);
  }

  void TestString::testCompareLess(tst::TestResult& result)
  {
    ASSERT(utl::compare("",   "a") < 0);
    ASSERT(utl::compare("a",  "b") < 0);
    ASSERT(utl::compare("a",  "z") < 0);
    ASSERT(utl::compare("ab", "z") < 0);

    ASSERT(utl::compare("aabb",  "aabbc") < 0);
    ASSERT(utl::compare("aabbb", "aabbc") < 0);

    ASSERT(utl::compare(string1, string2) < 0);
  }

  void TestString::testCompareEqual(tst::TestResult& result)
  {
    ASSERT(utl::compare("",  "")  == 0);
    ASSERT(utl::compare("a", "a") == 0);

    ASSERT(utl::compare("azaz", "azaz") == 0);

    ASSERT(utl::compare(string1, string1) == 0);
    ASSERT(utl::compare(string2, string2) == 0);
  }

  /**
   * @todo need more test cases!
   */
  void TestString::testCopy(tst::TestResult& result)
  {
    char buffer[12] = {};
    size_t size = sizeof(buffer);

    ASSERT(utl::copy("", buffer, size) == buffer + 1);
    ASSERT(utl::compare(buffer, "") == 0);

    ASSERT(utl::copy("abc", buffer, size) == buffer + 4);
    ASSERT(utl::compare(buffer, "abc") == 0);

    ASSERT(utl::copy("abcdefghijk", buffer, size) == buffer + size);
    ASSERT(utl::compare(buffer, "abcdefghijk") == 0);

    ASSERT(utl::copy("abcdefghijkl", buffer, size) == buffer + size);
    ASSERT(utl::compare(buffer, "abcdefghijk") == 0);

    ASSERT(utl::copy("abcdefghijklmnopqrst", buffer, size) == buffer + size);
    ASSERT(utl::compare(buffer, "abcdefghijk") == 0);
  }
}
