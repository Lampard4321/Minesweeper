#ifndef FIELD_H
#define FIELD_H
 
#include "utils.h"

class field{
  public:
    field(int n_row, int n_col, int n_mine);
    ~field();
    int click(int row, int col);
    void flag(int row, int col);
    int check_neighbor(int row, int col);
    void disp_field(int row, int col);
    void disp_mine(int row, int col);
    void disp_done();

  private:
    bool valid_area(int row, int col);
    void init_mine(int n_row, int n_col, int n_mine);
    void init_click(int n_row, int n_col);
    void init_flag(int n_row, int n_col);
    void init_neighbor(int n_row, int n_col);
    int neighbor_num_mine(int center_row, int center_col);
    void chain_open(int row, int col);

  public:
    int n_row;
    int n_col;

  private:
    bool** mine_field;
    bool** click_field;
    bool** flag_field;
    int** neighbor_field;
    int n_mine;
    int done_th;
    int done_cur;
};


 


#endif
