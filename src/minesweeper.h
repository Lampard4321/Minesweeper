#ifndef MINESWEEPER_H
#define MINESWEEPER_H
 
#include "field.h"
#include "utils.h"

class minesweeper{
  public:
    minesweeper(field* field);
    ~minesweeper();
    int action();

  private:
    void cursor_update(int dir);

  public:
    field* m_field;

  private:
    int cur_row;
    int cur_col;
};

#endif
