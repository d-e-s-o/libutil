// OutStream.hpp

/***************************************************************************
 *   Copyright (C) 2009,2014 Daniel Mueller (deso@posteo.net)              *
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

#ifndef UTLOUTSTREAM_HPP
#define UTLOUTSTREAM_HPP

#include <type/Types.hpp>
#include <type/Traits.hpp>

#include "util/Config.hpp"


namespace utl
{
  /**
   * This class can be used for printing out various values.
   * @todo think about adding support for floating point values
   * @todo add support for printing bools
   * @todo think about removing flush functionality or at least creating a derived class that
   *       provides it
   */
  template<typename BufferT>
  class OutStream
  {
  public:
    OutStream(BufferT& buffer);

    void print(char const* value);
    void print(void const* value);

    void print(char value);
    void print(uchar_t value);
    void print(schar_t value);

    void print(ushort_t value);
    void print(sshort_t value);

    void print(uint_t value);
    void print(sint_t value);

    void print(ulong_t value);
    void print(slong_t value);

    void print(nullptr_t value);

    void setBase(uint8_t base);
    void setFixed(bool fixed);

    void flush();

  private:
    BufferT* buffer_;

    uint8_t base_;
    bool fixed_;

    template<typename T>
    void printSignedValue(T value);

    template<typename T>
    void printUnsignedValue(T value);

    template<typename T>
    void printUnsignedValueImpl(T value);

    void printChar(char c);
  };


  template<typename BufferT>
  OutStream<BufferT>& bin(OutStream<BufferT>& stream);

  template<typename BufferT>
  OutStream<BufferT>& oct(OutStream<BufferT>& stream);

  template<typename BufferT>
  OutStream<BufferT>& dec(OutStream<BufferT>& stream);

  template<typename BufferT>
  OutStream<BufferT>& hex(OutStream<BufferT>& stream);

  template<typename BufferT>
  OutStream<BufferT>& fix(OutStream<BufferT>& stream);

  template<typename BufferT>
  OutStream<BufferT>& var(OutStream<BufferT>& stream);

  template<typename BufferT>
  OutStream<BufferT>& flush(OutStream<BufferT>& stream);

  template<typename BufferT, typename T>
  OutStream<BufferT>& operator << (OutStream<BufferT>& stream, T value);
}


namespace utl
{
  /**
   * This template calculates the greatest power to Base that can be stored within the given
   * datatype T.
   * E.g.
   *   - Base = 10, T is 16 bit unsigned value -> GreatestPower::X = 10000 = 10^4 because
   *     100000 = 10^5 would cause the datatype to overflow
   *   - Base = 2,  T is 32 bit signed value   -> GreatestPower::X = 1073741824 = 2^30 because
   *     2147483648 = 2^31 would be one above the maximum value the type may store
   * @param T datatype to store value in
   * @param Base
   */
  template<typename T, unsigned long Base>
  struct GreatestPower
  {
    /**
     * @note though Value should also be of type T we cannot change this, because g++ cannot find
     *       the template specialication in that case and recurses like 500 times and cancels
     * @todo it would be nice, however, to find a way to make Value of type T anyway
     */
    template<unsigned long Value = Base,
             unsigned long Max   = sizeof(T) * 8,
             unsigned long I     = Max - 1>
    struct IncreasePower
    {
      static T const X1   = static_cast<T>(Value);
      static T const X2   = static_cast<T>(X1 * Base);
      static T const Stop = X2 / Base != X1 ? 0 : I - 1;

      static T const X = Stop != 0 ? IncreasePower<X2, Max, Stop>::X : X1;
    };

    /**
     * This specialication cancels the recursion that will occur in the IncreasePower template.
     */
    template<unsigned long Value,
             unsigned long Max>
    struct IncreasePower<Value, Max, 0>
    {
      static T const X = 0;
    };

    static T const X = IncreasePower<>::X;
  };

  template<typename T>
  T getGreatestPower(uint8_t base)
  {
    switch(base)
    {
    case 2:
      return GreatestPower<T, 2>::X;

    case 3:
      return GreatestPower<T, 3>::X;

    case 4:
      return GreatestPower<T, 4>::X;

    case 5:
      return GreatestPower<T, 5>::X;

    case 6:
      return GreatestPower<T, 6>::X;

    case 7:
      return GreatestPower<T, 7>::X;

    case 8:
      return GreatestPower<T, 8>::X;

    case 9:
      return GreatestPower<T, 9>::X;

    case 10:
      return GreatestPower<T, 10>::X;

    case 11:
      return GreatestPower<T, 11>::X;

    case 12:
      return GreatestPower<T, 12>::X;

    case 13:
      return GreatestPower<T, 13>::X;

    case 14:
      return GreatestPower<T, 14>::X;

    case 15:
      return GreatestPower<T, 15>::X;

    case 16:
      return GreatestPower<T, 16>::X;
    }
    return 0;
  }

  inline char makeDigit(char c)
  {
    if (c <= 9)
      return c + '0';
    else
      return c - 10 + 'A';
  }

  enum
  {
    BASE_MIN         = 1,
    BASE_BINARY      = 2,
    BASE_OCTAL       = 8,
    BASE_DECIMAL     = 10,
    BASE_HEXADECIMAL = 16,
    BASE_MAX         = 17
  };


  /**
   * @param buffer buffer to be used
   */
  template<typename BufferT>
  inline OutStream<BufferT>::OutStream(BufferT& buffer)
    : buffer_(&buffer),
      base_(BASE_DECIMAL),
      fixed_(false)
  {
  }

  template<typename BufferT>
  void OutStream<BufferT>::print(char const* value)
  {
    for ( ; *value != '\0'; ++value)
      print(*value);
  }

  template<typename BufferT>
  void OutStream<BufferT>::print(void const* value)
  {
    printUnsignedValue(reinterpret_cast<byte_t const*>(value) -
                       reinterpret_cast<byte_t const*>(0));
  }

  template<typename BufferT>
  inline void OutStream<BufferT>::print(char value)
  {
    printChar(value);
  }

  template<typename BufferT>
  inline void OutStream<BufferT>::print(uchar_t value)
  {
    printUnsignedValue(value);
  }

  template<typename BufferT>
  inline void OutStream<BufferT>::print(schar_t value)
  {
    printSignedValue(value);
  }

  template<typename BufferT>
  inline void OutStream<BufferT>::print(ushort_t value)
  {
    printUnsignedValue(value);
  }

  template<typename BufferT>
  inline void OutStream<BufferT>::print(sshort_t value)
  {
    printSignedValue(value);
  }

  template<typename BufferT>
  inline void OutStream<BufferT>::print(uint_t value)
  {
    printUnsignedValue(value);
  }

  template<typename BufferT>
  inline void OutStream<BufferT>::print(sint_t value)
  {
    printSignedValue(value);
  }

  template<typename BufferT>
  inline void OutStream<BufferT>::print(ulong_t value)
  {
    printUnsignedValue(value);
  }

  template<typename BufferT>
  inline void OutStream<BufferT>::print(slong_t value)
  {
    printSignedValue(value);
  }

  template<typename BufferT>
  inline void OutStream<BufferT>::print(nullptr_t value)
  {
    // @todo introduce printString or something similar
    printChar('n');
    printChar('u');
    printChar('l');
    printChar('l');
  }

  template<typename BufferT>
  template<typename T>
  void OutStream<BufferT>::printSignedValue(T value)
  {
    if (value < 0)
    {
      printChar('-');
      value *= -1;
    }
    printUnsignedValue(value);
  }

  /**
   * @param value value to print
   */
  template<typename BufferT>
  template<typename T>
  inline void OutStream<BufferT>::printUnsignedValue(T value)
  {
    printUnsignedValueImpl<typename typ::MakeUnsigned<T>::Type>(value);
  }

  template<typename BufferT>
  template<typename T>
  void OutStream<BufferT>::printUnsignedValueImpl(T value)
  {
    if (!fixed_ && value == 0)
    {
      printChar('0');
      return;
    }

    bool print = fixed_;

    for (T power = getGreatestPower<T>(base_); power >= 1; power /= base_)
    {
      T div = value / power;
      T mod = value % power;

      print = print || div > 0;

      if (print)
      {
        printChar(makeDigit(static_cast<char>(div)));

        value = mod;
      }
    }
  }

  /**
   * This helper method prints out a single character.
   * @param c character to print
   */
  template<typename BufferT>
  inline void OutStream<BufferT>::printChar(char c)
  {
    buffer_->put(c);
  }

  /**
   * @param base new base to set
   */
  template<typename BufferT>
  inline void OutStream<BufferT>::setBase(uint8_t base)
  {
    if (BASE_MIN < base && base < BASE_MAX)
      base_ = base;
  }

  /**
   * @param fixed true to make all output have fixed width according to data type, false to make it
   *        variable according to value
   */
  template<typename BufferT>
  inline void OutStream<BufferT>::setFixed(bool fixed)
  {
    fixed_ = fixed;
  }

  /**
   *
   */
  template<typename BufferT>
  inline void OutStream<BufferT>::flush()
  {
    buffer_->flush();
  }

  /**
   * This manipulator can be used for setting binary output.
   */
  template<typename BufferT>
  OutStream<BufferT>& bin(OutStream<BufferT>& stream)
  {
    stream.setBase(BASE_BINARY);
    return stream;
  }

  /**
   * This manipulator can be used for setting octal output.
   */
  template<typename BufferT>
  OutStream<BufferT>& oct(OutStream<BufferT>& stream)
  {
    stream.setBase(BASE_OCTAL);
    return stream;
  }

  /**
   * This manipulator can be used for setting decimal output.
   */
  template<typename BufferT>
  OutStream<BufferT>& dec(OutStream<BufferT>& stream)
  {
    stream.setBase(BASE_DECIMAL);
    return stream;
  }

  /**
   * This manipulator can be used for setting hexadecimal output.
   */
  template<typename BufferT>
  OutStream<BufferT>& hex(OutStream<BufferT>& stream)
  {
    stream.setBase(BASE_HEXADECIMAL);
    return stream;
  }

  /**
   * This manipulator can be used for setting fixed output width.
   * @see OutStream::setFixed
   */
  template<typename BufferT>
  OutStream<BufferT>& fix(OutStream<BufferT>& stream)
  {
    stream.setFixed(true);
    return stream;
  }

  /**
   * This manipulator can be used for setting variable output width.
   * @see OutStream::setFixed
   */
  template<typename BufferT>
  OutStream<BufferT>& var(OutStream<BufferT>& stream)
  {
    stream.setFixed(false);
    return stream;
  }

  /**
   *
   */
  template<typename BufferT>
  OutStream<BufferT>& flushl(OutStream<BufferT>& stream)
  {
    stream.print('\n');
    stream.flush();
    return stream;
  }

  /**
   *
   */
  template<typename BufferT>
  OutStream<BufferT>& flush(OutStream<BufferT>& stream)
  {
    stream.flush();
    return stream;
  }

  /**
   * This is the overloaded version of operator << for printing value into a buffer.
   * @param stream stream to print value to
   * @param value value to print
   * @return stream that was supplied
   */
  template<typename BufferT, typename T>
  inline OutStream<BufferT>& operator << (OutStream<BufferT>& stream, T value)
  {
    stream.print(value);
    return stream;
  }

  /**
   * This is the specialization of operator << for invoking a manipulator function on the given
   * stream.
   * @param stream stream to invoke manipulator on
   * @param manipulator manipulator to invoke
   * @return stream that was supplied
   */
  template<typename BufferT>
  inline OutStream<BufferT>&
  operator << (OutStream<BufferT>& stream,
               OutStream<BufferT>& (*manipulator)(OutStream<BufferT>&))
  {
    return (*manipulator)(stream);
  }
}


#endif
