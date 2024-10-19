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

#ifndef BOOST_BASED_TIMER_H
#define BOOST_BASED_TIMER_H

#include <boost/timer/timer.hpp>
#include <string>

namespace AE {

class Timer 
{
 public:

  Timer() : sofar(0.0), it_runs(false) { uhr.stop(); }
  
  void start() { uhr.start();
                 it_runs = true;
               } 

  void stop()  { if (it_runs) 
                 {  sofar += std::stod( uhr.format( 5, std::string("%t"))); }
                 it_runs = false;
               } 

  void reset() { sofar = 0.0; } 
  
  double time(){ return sofar; }

 protected:

  boost::timer::cpu_timer   uhr;
  double sofar;
  bool   it_runs;
};

} // namespace AE

#endif // BOOST_BASED_TIMER_H
