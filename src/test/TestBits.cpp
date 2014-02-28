// TestBits.cpp

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

#include <util/Bits.hpp>

#include "TestBits.hpp"


namespace test
{
  TestBits::TestBits()
    : tst::TestCase<TestBits>(*this, "TestBits")
  {
    add(&TestBits::testRotateLeft1);
    add(&TestBits::testRotateRight1);
  }

  void TestBits::testRotateLeft1(tst::TestResult& result)
  {
    ASSERT((utl::rotateLeft<uint32_t, 32>(1, 32) == 1));
    ASSERT((utl::rotateLeft<uint32_t, 32>(2, 32) == 2));
    ASSERT((utl::rotateLeft<uint32_t, 20>(1, 20) == 1));
    ASSERT((utl::rotateLeft<uint32_t, 20>(2, 20) == 2));

    ASSERT((utl::rotateLeft<uint32_t, 20>(0, 1)  == 0));
    ASSERT((utl::rotateLeft<uint32_t, 20>(0, 2)  == 0));

    ASSERT((utl::rotateLeft<uint32_t, 20>(7, 2)  == 28));
    ASSERT((utl::rotateLeft<uint32_t, 20>(7, 2)  == 28));
    ASSERT((utl::rotateLeft<uint32_t, 20>(1 << 19, 1) == 1));
  }

  void TestBits::testRotateRight1(tst::TestResult& result)
  {
    ASSERT((utl::rotateRight<uint32_t, 32>(1, 32) == 1));
    ASSERT((utl::rotateRight<uint32_t, 32>(2, 32) == 2));

    ASSERT((utl::rotateRight<uint32_t, 19>(1, 1) == 1 << 18));
    ASSERT((utl::rotateRight<uint32_t, 19>(1, 2) == 1 << 17));
  }
}
