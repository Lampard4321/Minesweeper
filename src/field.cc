#include <iostream>
#include <cstdlib>
#include <ctime>
#include "field.h"
 
using namespace std;

field::field(int n_row, int n_col, int n_mine) {
  this->n_row = n_row;
  this->n_col = n_col;
  this->n_mine = n_mine;
  done_th = n_row * n_col - n_mine;
  done_cur = 0;

  init_mine(n_row, n_col, n_mine);
  init_click(n_row, n_col);
  init_flag(n_row, n_col);
  init_neighbor(n_row, n_col);
}

field::~field() { 
  for (int i = 0; i < n_row; i++) {
    free(mine_field[i]);
    free(click_field[i]);
    free(flag_field[i]);
    free(neighbor_field[i]);
  }
  free(mine_field);
  free(click_field);
  free(flag_field);
  free(neighbor_field);
}

void field::flag(int row, int col) {
  flag_field[row][col] = !flag_field[row][col];
}

int field::check_neighbor(int row, int col) {
  if (!click_field[row][col] && !flag_field[row][col]) return 0;
  else {
    for (int i = -1; i <= 1; i++) {
      for (int j = -1; j <= 1; j++) {
        if (i == 0 && j == 0) continue;
        else {
          int r = row + i;
          int c = col + j;
          if (valid_area(r,c)) {
            if (flag_field[r][c]) continue;
            else if (mine_field[r][c]) return -1; 
            else {
              chain_open(r,c);
            }
          }
        }
      }
    }
  }
  return (done_th == done_cur);
}

int field::click(int row, int col) {
  if (mine_field[row][col]) return -1;
  else if (click_field[row][col] || flag_field[row][col]) return 0;
  chain_open(row,col);

  return (done_th == done_cur);

}

void field::chain_open(int row, int col) {
  if (flag_field[row][col]) return;

  else if (neighbor_field[row][col] > 0) { 
    if (!click_field[row][col]) {
      click_field[row][col] = true; 
      done_cur++; 
    }
    return; 
  } 

  else if (neighbor_field[row][col] == 0) { 
    if (!click_field[row][col]) {
      click_field[row][col] = true; 
      done_cur++;
      for (int i = -1; i <= 1; i++) { 
        for (int j = -1; j <= 1; j++) { 
          if (i == 0 && j == 0) continue; 
          int recur_row = row + i; 
          int recur_col = col + j; 
          if (valid_area(recur_row,recur_col)) { 
            chain_open(recur_row,recur_col); 
          } 
        }
      }
    }
  } 

 return; 
}

bool field::valid_area(int row, int col) {
  if (row >= 0 && row < n_row) {
    if (col >= 0 && col < n_col) {
      return true;
    }  
  }
  return false;
}

void field::init_mine(int n_row, int n_col, int n_mine) {
  mine_field = (bool**) malloc(n_row * sizeof(bool*));
  for (int i = 0; i < n_row; i++){
    mine_field[i] = (bool*) malloc(n_col * sizeof(bool));
  }
// field area malloc
  
  int mine_count = 0;
  srand((unsigned int)time(NULL));

  while (mine_count != n_mine) {
    int num = rand();
    int mine_row = num % n_row;
    int mine_col = (num / n_row) % n_col;
    if (!mine_field[mine_row][mine_col]) {
      mine_count++;
      mine_field[mine_row][mine_col] = true;  
    }
  }
}

void field::init_click(int n_row, int n_col) {
  click_field = (bool**) malloc(n_row * sizeof(bool*));
  for (int i = 0; i < n_row; i++) { 
    click_field[i] = (bool*) malloc(n_col * sizeof(bool));
  }

  for (int i = 0; i < n_row; i++) { 
    for (int j = 0; j < n_col; j++) {
      click_field[i][j] = false;
    }
  }
}

void field::init_flag(int n_row, int n_col) {
  flag_field = (bool**) malloc(n_row * sizeof(bool*));
  for (int i = 0; i < n_row; i++) {
    flag_field[i] = (bool*) malloc(n_col * sizeof(bool));
  }

  for (int i = 0; i < n_row; i++) {
    for (int j = 0; j < n_col; j++) {
      flag_field[i][j] = false;
    }
  }
}

void field::init_neighbor(int n_row, int n_col){
  neighbor_field = (int**) malloc(n_row * sizeof(int*));
  for (int i = 0; i < n_row; i++) {
    neighbor_field[i] = (int*) malloc(n_col * sizeof(int));
  }

  for (int i = 0; i < n_row; i++) {
    for (int j = 0; j < n_col; j++) {
      neighbor_field[i][j] = neighbor_num_mine(i,j);
    }
  }

}

int field::neighbor_num_mine(int center_row, int center_col) {
  if (mine_field[center_row][center_col]) return -1;

  int mine_count = 0;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (i == 0 && j == 0) continue;
      int row = center_row + i;
      int col = center_col + j; 
      if(valid_area(row, col) && mine_field[row][col]){
        mine_count++;
      }
    }
  }
  return mine_count;
}

void field::disp_field(int row, int col) {
  system("clear");

  for (int i = 0; i < n_col + 2; i++) cout << "-";
  cout << endl;
  for (int i = 0; i < n_row; i++) {
    cout << "|";
    for (int j = 0; j < n_col; j++) {
      if (i == row && j == col) cout << "$";
      else if (click_field[i][j]) {
        if (neighbor_field[i][j] > 0) cout << neighbor_field[i][j];
        else cout << "\'";
      }
      else if (flag_field[i][j]) cout << "?";
      else cout << " ";
    } 
    cout << "|" << endl;
  }
  for (int i = 0; i < n_col + 2; i++) cout << "-";
  cout << endl;

  cout << "----------------" << endl;
  cout << "|h:left        |" << endl;
  cout << "|j:down        |" << endl;
  cout << "|k:up          |" << endl;
  cout << "|l:right       |" << endl;
  cout << "|q:click       |" << endl;
  cout << "|w:check flag  |" << endl;
  cout << "|e:open around |" << endl;
  cout << "----------------" << endl;

  return;
}

void field::disp_mine(int row, int col) {
  system("clear");

  for (int i = 0; i < n_col + 2; i++) cout << "-";
  cout << endl;
  for (int i = 0; i < n_row; i++) {
    cout << "|";
    for (int j = 0; j < n_col; j++) {
      if (mine_field[i][j]) cout << "*";
      else if (i == row && j == col) cout << "$";
      else if (click_field[i][j]) {
        if (neighbor_field[i][j] > 0) cout << neighbor_field[i][j];
        else cout << "\'";
      }
      else if (flag_field[i][j]) cout << "?";
      else cout << " ";
    }
    cout << "|" << endl;
  }
  for (int i = 0; i < n_col + 2; i++) cout << "-";
  cout << endl;
  cout << "---------------BOMB!---------------";

  return;
}

void field::disp_done() {
  system("clear");

  for (int i = 0; i < n_col + 2; i++) cout << "-";
  cout << endl;
  for (int i = 0; i < n_row; i++) {
    cout << "|";
    for (int j = 0; j < n_col; j++){
      if (mine_field[i][j]) cout << "*";
      else if (click_field[i][j]) {
        if (neighbor_field[i][j] > 0) cout << neighbor_field[i][j];
        else cout << "\'";
      }
      else if (flag_field[i][j]) cout << "?";
      else cout << " ";
    }
    cout << "|" << endl;
  }
  for (int i = 0; i < n_col + 2; i++) cout << "-";
  cout << endl;
  cout << "---------------DONE!---------------";

  return;
}





