# Minesweeper

How to use this game
1. mkdir build
2. cd build
3. cmake ..
4. make -j4
5. make install
6. cd ../bin
7. ./minesweeper easy # or medium or hard

There are three modes, easy, medium, hard.

Easy: 9x9, number of mines = 10

Medium: 16x16, number of mines = 40

Hard: 30x16, number of mines = 99

Keys
h / j / k / l : left / down / up / right (same as Vim)
q: left click
w: right click (check as possible mine)
e: double click (open neighbors except for possible mines)

after playing games
1. rm -rf build
2. rm -rf bin

