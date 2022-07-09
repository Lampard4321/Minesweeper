# Minesweeper

How to use this game
1. mkdir build
2. cd build
3. cmake ..
4. make -j4
5. make install
6. cd ../bin
7. ./minesweeper easy # or medium or hard

-------------------------------------------------------------------------------

There are three modes, easy, medium, hard.
1. Easy: 9x9, number of mines = 10
2. Medium: 16x16, number of mines = 40
3. Hard: 30x16, number of mines = 99

-------------------------------------------------------------------------------

Keys
1. moving cursor -  h / j / k / l : left / down / up / right (same as Vim)
2. left click - q
3. check flag - w
4. open around - e

-------------------------------------------------------------------------------

After playing games
1. rm -rf build
2. rm -rf bin

