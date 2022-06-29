#include <iostream>
#include "minesweeper.h"

minesweeper::minesweeper(field* field){
  this->field = field;
  cur_row=0;
  cur_col=0;  
}

minesweeper::~minesweeper(){
}

int minesweeper::action(){
  int ret=0;
  char input;
  input=getch_(0);
  
  switch(input){
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
      ret=field->click(cur_row,cur_col);
      break;

    case 'w':
      field->flag();
      break;

    case 'e':
      ret=field->check_neighbor();
      break;
      
    default:
      break;
  }
  if(ret==0) field->disp_field(cur_row, cur_col);
  else if(ret==-1) field->disp_mine(cur_row, cur_col);
  else if(ret==1) field->disp_done(cur_row, cur_col);
  else std::cout<<"error";

  return ret;
}


void minesweeper::cursor_update(int dir){
  if(dir==WEST){
    if(cur_col>=1) cur_col--;
  }
  else if(dir==EAST){
    if(cur_col<field->n_col) cur_col++;
  }
  else if(dir==NORTH){
    if(cur_row>=1) cur_row--;
  }
  else if(dir==SOUTH){
    if(cur_row<field->n_row) cur_row++;
  }

  return;
}
