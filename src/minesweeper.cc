#include <iostream>
#include <stdlib.h>
#include "minesweeper.h"

minesweeper::minesweeper(field* m_field) {
  this->m_field = m_field;
  cur_row = 0;
  cur_col = 0;  
}

minesweeper::~minesweeper() {
}

int minesweeper::action() {
  int ret = 0;
  char input;
  input = getch_(0);
  
  switch(input) { 
    case 'h':
      cursor_update(WEST);
      break;
    
    case 'l':
      cursor_update(EAST);
      break;
    
    case 'j':
      cursor_update(SOUTH);
      break;
    
    case 'k':
      cursor_update(NORTH);
      break;
    
    case 'q':
      ret = m_field->click(cur_row,cur_col);
      break;

    case 'w':
      m_field->flag(cur_row, cur_col);
      break;

    case 'e':
      ret = m_field->check_neighbor(cur_row, cur_col);
      break;
      
    default:
      break;
  }
  if (ret == 0) m_field->disp_field(cur_row, cur_col);
  else if (ret == -1) m_field->disp_mine(cur_row, cur_col);
  else if (ret == 1) m_field->disp_done();
  else std::cout << "error";

  return ret;
}


void minesweeper::cursor_update(int dir) {
  if (dir == WEST) {
    if (cur_col >= 1) cur_col--;
  }
  else if (dir==EAST) {
    if (cur_col < m_field->n_col - 1) cur_col++;
  }
  else if (dir == NORTH) {
    if (cur_row >= 1) cur_row--;
  }
  else if (dir == SOUTH) {
    if (cur_row < m_field->n_row - 1) cur_row++;
  }

  return;
}
