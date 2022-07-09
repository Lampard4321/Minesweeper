#ifndef __UTILS_H__
#define __UTILS_H__

#include <termios.h>
#include <cstdio>

enum DIR {
  WEST=0, 
  NORTH,
  SOUTH,
  EAST
};


const int config[3][3] = {
  {9, 9, 10}, {16, 16, 40}, {16, 30, 99}
};

static struct termios old, current;

/* Initialize new terminal i/o settings */
void initTermios(int echo);
void resetTermios();
char getch_(int echo);

#endif
