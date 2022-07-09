#include "minesweeper.h"
#include "field.h"
#include "utils.h"

#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
  minesweeper* m_minesweeper;
  field* m_field;

  if (argc == 1) {
    m_field = new field(config[1][0], config[1][1], config[1][2]);
  }
  else if (!strcmp(argv[1],"easy")) { 
    m_field = new field(config[0][0], config[0][1], config[0][2]);
  }
  else if (!strcmp(argv[1],"medium")) {
    m_field = new field(config[1][0], config[1][1], config[1][2]);
  }
  else if (!strcmp(argv[1],"hard")) { 
    m_field = new field(config[2][0], config[2][1], config[2][2]);
  }
  else {
    std::cout << "error in main";
    return 0;
  }
  m_minesweeper = new minesweeper(m_field);

  int ret = 0;
  m_field->disp_field(0,0);
  while (ret == 0) {
    ret = m_minesweeper->action();
  }

  delete m_minesweeper;
  delete m_field;


  return 0;
}
