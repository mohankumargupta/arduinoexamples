#include "TimerNB.h"

/************************************************************
    Call with:
      IntervalMicros  The IntervalMicros elapsed time in uS
       NextMicro  Pointer to an unsigned long, which is the caller's private time marker,

    Return true if IntervalMicros uS have passed, alter NextMicro to the new point in time.
*/

int TestElapsedMicros_NB(unsigned long IntervalMicros, unsigned long *NextMicro)
{
  if (micros() - *NextMicro >= IntervalMicros) {
    *NextMicro = *NextMicro + IntervalMicros;
    return true ;
  }
  else {
    return false;
  }
}
