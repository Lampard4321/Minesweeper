#include <iostream>
#include <cstdlib>
#include <ctime>
#include "field.h"

field::field(int n_row, int n_col, int n_mine){
  this->n_row=n_row;
  this->n_col=n_col;
  this->n_mine=n_mine;
  done_th=n_row*n_col-n_mine;
  done_cur=0;

  init_mine(n_row, n_col, n_mine);
  init_click(n_row, n_col);
  init_flag(n_row, n_col);
  init_neighbor(n_row, n_col);
}

field::~field(){
  for(int i=0; i<n_row;i++){
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

int field::click(int row, int col){
  if(mine_field[row][col]==true) return -1; //bomb
  else if(flag_field[row][col]==true) return 0;
  chain_open(row,col);

  return (done_th==done_cur);

}

void field::chain_open(int row, int col){
  if(neighbor_field[row][col]>0) {
    flag_field[row][col]=false;
    click_field[row][col]=true;
    done_cur++;
    return;
  }

  else if(mine_field[row][col]==true){
    return;
  }
  
  else if(click_field[row][col]==false){
    flag_field[row][col]=false;
    click_field[row][col]=true;
    done_cur++; 
    for(int i=-1; i<=1; i++){
      for(int j=-1; j<=1; j++){
        int recur_row=row+i;
        int recur_col=col+j;
        if(valid_area(recur_row,recur_col)) {
          chain_open(recur_row,recur_col);
        }
      }
    }
  }

  return;
}

bool field::valid_area(int row, int col){
  if(row>=0 && row<n_row){
    if(col>=0 && col<n_col){
      return true;
    }  
  }
  return false;
}

void field::init_mine(int n_row, int n_col, int n_mine){
  mine_field = (bool**) malloc(n_row * sizeof(bool*));
  for (int i=0; i<n_row; i++){
    mine_field[i]=(bool*) malloc(n_col * sizeof(bool));
  }
// field area malloc
  
  int mine_count=0;
  srand((unsigned int)time(NULL));

  while(mine_count!=n_mine){
    int num=rand();
    int mine_row=num%n_row;
    int mine_col=(num/n_row)%n_col;
    if(mine_field[mine_row][mine_col]==false){
      mine_count++;
      mine_field[mine_row][mine_col]=true;  
    }
  }
}

void field::init_click(int n_row, int n_col){
  click_field = (bool**) malloc(n_row * sizeof(bool*));
  for (int i=0; i<n_row; i++){
    click_field[i]=(bool*) malloc(n_col * sizeof(bool));
  }

  for(int i=0; i<n_row; i++){
    for(int j=0; j<n_col; j++){
      click_field[i][j]=false;
    }
  }
}

void field::init_flag(int n_row, int n_col){
  flag_field = (bool**) malloc(n_row * sizeof(bool*));
  for (int i=0; i<n_row; i++){
    flag_field[i]=(bool*) malloc(n_col * sizeof(bool));
  }

  for(int i=0; i<n_row; i++){
    for(int j=0; j<n_col; j++){
      flag_field[i][j]=false;
    }
  }
}

void field::init_neighbor(int n_row, int n_col){
  neighbor_field = (int**) malloc(n_row * sizeof(int*));
  for (int i=0; i<n_row; i++){
    neighbor_field[i]=(int*) malloc(n_col * sizeof(int));
  }

  for(int i=0; i<n_row; i++){
    for(int j=0; j<n_col; j++){
      neighbor_field[i][j] = neighbor_num_mine(i,j);
    }
  }

}

int field::neighbor_num_mine(int center_row, int center_col){
  int mine_count=0;
  if(mine_field[center_row][center_col]==true) return -1;
  for(int i=-1; i<=1; i++){
    for(int j=-1; j<=1; j++){
      if(i==0 && j==0) continue;
      int row = center_row+i;
      int col = center_col+j; 
      if(valid_area(row, col) && mine_field[row][col]==true){
        mine_count++;
      }
    }
  }
  return mine_count;
}

void field::disp_field(int row, int col){
  for(int i=0; i<n_col+2; i++) std::cout<<"-";
  for(int i=0; i<n_row; i++){
    std::cout<<"|";
    for(int j=0; j<n_col; j++){
      if(mine_field[i][j]==true) std::cout<<"*";
      else if(i==row && j==col) std::cout<<"$";
      else if(click_field[i][j]==true) std::cout<<"'";
      else if(neighbor_field[i][j]>0) std::cout<<neighbor_field[i][j];
      else if(flag_field[i][j]==true) std::cout<<"?";
      else std::cout<<" ";
    } 
    std::cout<<"|";
  }
  for(int i=0; i<n_col+2; i++) std::cout<<"-";

  std::cout<<"----------------";
  std::cout<<"|h:left        |";
  std::cout<<"|j:down        |";
  std::cout<<"|k:up          |";
  std::cout<<"|l:right       |";
  std::cout<<"|q:click       |";
  std::cout<<"|w:check flag  |";
  std::cout<<"|e:open around |";
  std::cout<<"----------------";

  return;
}

void field::disp_mine(int row, int col){
  for(int i=0; i<n_col+2; i++) std::cout<<"-";
  for(int i=0; i<n_row; i++){
    std::cout<<"|";
    for(int j=0; j<n_col; j++){
      if(mine_field[i][j]==true) std::cout<<"*";
      else if(i==row && j==col) std::cout<<"$";
      else if(click_field[i][j]==true) std::cout<<"'";
      else if(neighbor_field[i][j]>0) std::cout<<neighbor_field[i][j];
      else if(flag_field[i][j]==true) std::cout<<"?";
      else std::cout<<" ";
    }
    std::cout<<"|";
  }
  for(int i=0; i<n_col+2; i++) std::cout<<"-";
  std::cout<<"---------------BOMB!---------------";

  return;
}

void field::disp_done(int row, int col){
  for(int i=0; i<n_col+2; i++) std::cout<<"-";
  for(int i=0; i<n_row; i++){
    std::cout<<"|";
    for(int j=0; j<n_col; j++){
      if(mine_field[i][j]==true) std::cout<<"*";
      else if(i==row && j==col) std::cout<<"$";
      else if(click_field[i][j]==true) std::cout<<"'";
      else if(neighbor_field[i][j]>0) std::cout<<neighbor_field[i][j];
      else if(flag_field[i][j]==true) std::cout<<"?";
      else std::cout<<" ";
    }
    std::cout<<"|";
  }
  for(int i=0; i<n_col+2; i++) std::cout<<"-";
  std::cout<<"---------------DONE!---------------";

  return;
}





