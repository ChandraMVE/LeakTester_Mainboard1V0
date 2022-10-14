// |  Filename : NOPdelays.h
// |     Desc' : Delay functions using Nop() method
//  ----------------------------------------------------------------------------

#ifndef NOPDELAYS_H
#define    NOPDELAYS_H

void __attribute__((optimize("-O2"))) usDelay( unsigned int us );                     //delay using Nop() blocking

#endif  //DELAYS