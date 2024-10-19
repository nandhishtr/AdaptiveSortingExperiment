// ======================================================================
//
// Copyright (c) OVGU Magdeburg
//
// This software and related files are part of an Algorithm Engineering
// implementation project on adaptive sorting of polygon vertices,
// conducted at computer science department (FIN) at OVGU Magdeburg, 
// Germany. All rights reserved.
//
// ======================================================================

#ifndef POINT_2_H
#define POINT_2_H

#include <iostream>

namespace AE {

template <typename NumberType> class Point_2;


template <typename NumberType>
std::istream&
operator>>(std::istream&, Point_2<NumberType>& );


template <typename NumberType>
std::ostream&
operator<<(std::ostream&, const Point_2<NumberType>& );



template <typename NumberType>
class Point_2
{
 public:
  Point_2( const NumberType& x, const NumberType& y) : xcoord(x), ycoord(y) {}

  Point_2() : xcoord(NumberType(0)), ycoord(NumberType(0)) {};

/*
  Point_2() : xcoord(NumberType(0)), ycoord(NumberType(0)) 
              { std::cout << "WARNING: default constructor might not exist!\n"; 
              }
*/

//  Point_2() = delete;

  NumberType  x() const { return xcoord; }

  NumberType  y() const { return ycoord; }

         friend
         std::istream& 
         operator>> <>(std::istream& is, Point_2<NumberType>& p);

 private:

  NumberType xcoord;
  NumberType ycoord;
};
 

template <typename NumberType>
bool
operator==( const Point_2<NumberType>& p, const Point_2<NumberType>& q)
{ return (p.x() == q.x()) && (p.y() == q.y()); } 

template <typename NumberType>
bool
operator!=( const Point_2<NumberType>& p, const Point_2<NumberType>& q)
{ return (p.x() != q.x()) || (p.y() != q.y()); }

template <typename NumberType>
std::istream&
operator>>(std::istream& is, Point_2<NumberType>& p)
{ is >> p.xcoord ;
  is >> p.ycoord ;
  return is;
}

template <typename NumberType>
std::ostream&
operator<<(std::ostream& os, const Point_2<NumberType>& p)
{ os << p.x() ;
  os << " ";
  os << p.y() ;
  return os;
}

template <typename NumberType>
class Less_2
{
 public:
  typedef const Point_2<NumberType>  first_argument_type;
  typedef const Point_2<NumberType>  second_argument_type;
  typedef bool  result_type;

  bool 
  operator()( const Point_2<NumberType>& p, const Point_2<NumberType>& q ) const
  { if (p.x() < q.x()) return true;
    if (q.x() < p.x()) return false;
    if (p.y() < q.y()) return true;
                       return false;
  }

  void
  reset_counter() {};
};


template <typename NumberType>
class Call_counting_less
{
 public:
  typedef const Point_2<NumberType>  first_argument_type;
  typedef const Point_2<NumberType>  second_argument_type;
  typedef bool  result_type;

  Call_counting_less( int* ptr) : c_ptr(ptr) {};

  bool 
  operator()( const Point_2<NumberType>& p, const Point_2<NumberType>& q ) const
  { *c_ptr = *c_ptr + 1;
    if (p.x() < q.x()) return true;
    if (q.x() < p.x()) return false;
    if (p.y() < q.y()) return true;
                       return false;
  }

  int counter() 
  { return *c_ptr; }

  void
  reset_counter() { *c_ptr = 0;}

 private:
  int* c_ptr;
};



} // namespace AE

#endif // POINT_2_H

