// TestAlgorithm.cpp

/***************************************************************************
 *   Copyright (C) 2010-2014 Daniel Mueller (deso@posteo.net)              *
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

#include <util/Algorithm.hpp>

#include "TestAlgorithm.hpp"


namespace test
{
  TestAlgorithm::TestAlgorithm()
    : tst::TestCase<TestAlgorithm>(*this, "TestAlgorithm"),
      source_begin_(source_),
      source_end_(source_ + SIZE),
      destination_begin_(destination_),
      destination_end_(destination_ + SIZE)
  {
    add(&TestAlgorithm::testRotateLeft1);
    add(&TestAlgorithm::testRotateRight1);
    add(&TestAlgorithm::testFill);
    add(&TestAlgorithm::testFind);
    add(&TestAlgorithm::testFindNot);
    add(&TestAlgorithm::testFindBinary1);
    add(&TestAlgorithm::testFindBinary2);
    add(&TestAlgorithm::testCopy1);
    add(&TestAlgorithm::testCopy2);
    add(&TestAlgorithm::testCopy3);
  }

  void TestAlgorithm::setUp()
  {
    for (int* it = source_begin_; it != source_end_; ++it)
      *it = 0;

    for (int* it = destination_begin_; it != destination_end_; ++it)
      *it = 0;
  }

  void TestAlgorithm::testRotateLeft1(tst::TestResult& result)
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

  void TestAlgorithm::testRotateRight1(tst::TestResult& result)
  {
    ASSERT((utl::rotateRight<uint32_t, 32>(1, 32) == 1));
    ASSERT((utl::rotateRight<uint32_t, 32>(2, 32) == 2));

    ASSERT((utl::rotateRight<uint32_t, 19>(1, 1) == 1 << 18));
    ASSERT((utl::rotateRight<uint32_t, 19>(1, 2) == 1 << 17));
  }

  void TestAlgorithm::testFill(tst::TestResult& result)
  {
    ASSERT(utl::find(source_begin_, source_end_, 0) == source_begin_);

    utl::fill(source_begin_, source_end_, 1);
    ASSERT(utl::find(source_begin_, source_end_, 0) == source_end_);

    utl::fill(source_begin_ + 20, source_end_ - 70, 0);
    ASSERT(utl::find(source_begin_,      source_end_, 0) == source_begin_ + 20);
    ASSERT(utl::find(source_begin_ + 21, source_end_, 1) == source_end_ - 70);
  }

  void TestAlgorithm::testFind(tst::TestResult& result)
  {
    ASSERT(utl::find(source_begin_, source_end_, 1) == source_end_);

    *(source_end_ - 1) = 1;
    ASSERT(utl::find(source_begin_, source_end_, 1) == source_end_ - 1);

    *(source_end_ - 16) = 1;
    ASSERT(utl::find(source_begin_, source_end_, 1) == source_end_ - 16);

    *(source_begin_ + 2) = 1;
    ASSERT(utl::find(source_begin_, source_end_, 1) == source_begin_ + 2);

    *(source_begin_) = 1;
    ASSERT(utl::find(source_begin_, source_end_, 1) == source_begin_);

    ASSERT(utl::find(source_begin_ + 3, source_end_, 1) == source_end_ - 16);
  }

  void TestAlgorithm::testFindNot(tst::TestResult& result)
  {
    ASSERT(utl::findNot(source_begin_, source_end_, 0) == source_end_);

    *(source_end_ - 1) = 1;
    ASSERT(utl::findNot(source_begin_, source_end_, 0) == source_end_ - 1);

    *(source_end_ - 16) = 1;
    ASSERT(utl::findNot(source_begin_, source_end_, 0) == source_end_ - 16);

    *(source_begin_ + 2) = 1;
    ASSERT(utl::findNot(source_begin_, source_end_, 0) == source_begin_ + 2);

    *(source_begin_) = 1;
    ASSERT(utl::findNot(source_begin_, source_end_, 0) == source_begin_);

    ASSERT(utl::findNot(source_begin_ + 3, source_end_, 0) == source_end_ - 16);
  }

  void TestAlgorithm::testFindBinary1(tst::TestResult& result)
  {
    int* p = destination_begin_;

    ASSERT(utl::findBinary(p, p, 0) == p);

    *p = 1;
    ASSERT(utl::findBinary(p, p + 1, 0) == p);
    ASSERT(utl::findBinary(p, p + 1, 1) == p);
    ASSERT(utl::findBinary(p, p + 1, 2) == p + 1);
  }

  void TestAlgorithm::testFindBinary2(tst::TestResult& result)
  {
    int* end = destination_begin_;
    *end++ = 0;
    *end++ = 7;
    *end++ = 12;
    *end++ = 15;
    *end++ = 16;
    *end++ = 2000;
    *end++ = 14444;

    ASSERT(utl::findBinary(destination_begin_, end,     0) == destination_begin_);
    ASSERT(utl::findBinary(destination_begin_, end,     1) == destination_begin_ + 1);
    ASSERT(utl::findBinary(destination_begin_, end,     4) == destination_begin_ + 1);
    ASSERT(utl::findBinary(destination_begin_, end,     7) == destination_begin_ + 1);
    ASSERT(utl::findBinary(destination_begin_, end,     8) == destination_begin_ + 2);
    ASSERT(utl::findBinary(destination_begin_, end,    12) == destination_begin_ + 2);
    ASSERT(utl::findBinary(destination_begin_, end,    13) == destination_begin_ + 3);
    ASSERT(utl::findBinary(destination_begin_, end,    15) == destination_begin_ + 3);
    ASSERT(utl::findBinary(destination_begin_, end,    16) == destination_begin_ + 4);
    ASSERT(utl::findBinary(destination_begin_, end,  1000) == destination_begin_ + 5);
    ASSERT(utl::findBinary(destination_begin_, end,  2000) == destination_begin_ + 5);
    ASSERT(utl::findBinary(destination_begin_, end,  2001) == destination_begin_ + 6);
    ASSERT(utl::findBinary(destination_begin_, end, 14444) == destination_begin_ + 6);
    ASSERT(utl::findBinary(destination_begin_, end, 30000) == destination_begin_ + 7);
  }

  void TestAlgorithm::testCopy1(tst::TestResult& result)
  {
    // simply copy from src to dst
    ASSERT(utl::find(destination_begin_, destination_end_, 0) == destination_begin_);

    utl::fill(source_begin_ + 1, source_end_ - 1, 1);
    utl::copy(source_begin_, source_end_, destination_begin_);

    ASSERT(utl::find(destination_begin_,     destination_end_, 0) == destination_begin_);
    ASSERT(utl::find(destination_begin_ + 1, destination_end_, 0) == destination_end_ - 1);

    // a small copy
    utl::fill(source_begin_, source_begin_ + 6, 0);
    utl::copy(source_begin_, source_begin_ + 6, destination_begin_);

    ASSERT(utl::find(destination_begin_, destination_end_, 1) == destination_begin_ + 6);
  }

  void TestAlgorithm::testCopy2(tst::TestResult& result)
  {
    int const OVERLAP_MAX         = 20;
    int const OVERLAP_VALUE_START = 10;
    int const RANGE_DIFF_SIZE     = 10;
    int const RANGE_SIZE          = 100;

    // copy with overlapping data
    for (int overlap = 0; overlap < OVERLAP_MAX; ++overlap)
    {
      // fill in some test data (each value different from the others)
      for (int i = 0; i < RANGE_DIFF_SIZE; ++i)
        destination_begin_[i] = OVERLAP_VALUE_START + i;

      utl::copy(destination_begin_, destination_begin_ + RANGE_SIZE, destination_begin_ + overlap);

      for (int i = 0; i < RANGE_DIFF_SIZE; ++i)
        ASSERT(destination_begin_[overlap + i] == OVERLAP_VALUE_START + i);

      ASSERT(destination_begin_[overlap + RANGE_DIFF_SIZE] == 0);

      // clean up
      utl::fill(destination_begin_, destination_end_, 0);
    }
  }

  void TestAlgorithm::testCopy3(tst::TestResult& result)
  {
    // test optimized version of copy
    // @todo implement me!
    //ASSERTM(false, "implement me!");
  }
}
