// Copyright (C) 2005 Free Software Foundation, Inc.
//
// This file is part of the GNU ISO C++ Library.  This library is free
// software; you can redistribute it and/or modify it under the
// terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option)
// any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License along
// with this library; see the file COPYING.  If not, write to the Free
// Software Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307,
// USA.

// 27.6.2.6 Unformatted output functions
//
// _GLIBCXX_RESOLVE_LIB_DEFECTS
// DR 60. What is a formatted input function?
// basic_ostream::write(const char_type*, streamsize) is an unformatted
// output function.
// DR 63. Exception-handling policy for unformatted output.
// Unformatted output functions should catch exceptions thrown
// from streambuf members.

#include <ostream>
#include <streambuf>
#include <testsuite_hooks.h>

class Buf : public std::wstreambuf
{
protected:
  virtual int_type
  overflow(int_type = traits_type::eof())
  { throw 0; }
};

void test01()
{
  bool test = true;

  Buf buf;
  std::wostream os(&buf);

  VERIFY( os.good() );

  os.write(L"a", 1);

  VERIFY( os.rdstate() == std::ios_base::badbit );

  os.clear();
  os.exceptions(std::ios_base::badbit);

  try
    {
      os.write(L"b", 1);
      VERIFY( false );
    }
  catch (int)
    {
      VERIFY( os.rdstate() == std::ios_base::badbit );
    }
}

int main()
{
  test01();
  return 0;
}
