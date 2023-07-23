/*
Name: Benjamin Zhang
Class and Instructor: CSCI 23500 Tiziana Ligorio
Assignment: Project 6 SudokuSolver.cpp
Description: This is the implementation of the cpp file of SudokuSolver
*/

#include "SudokuSolver.hpp"

//Constructor
/*
the default constructor initializes an emtpy board, that is, a board 
filled with zeros (an array of 9 arrays, each filled with 9 zeros). 
This board will be marked unsolvable. 
*/
SudokuSolver::SudokuSolver() {
  //Creating the 2D pointer array
  puzzle_ = new int*[9];
  for (int a = 0; a < 9; a++){
    puzzle_[a] = new int[9];
  }

  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      puzzle_[i][j] = 0;
    }
  }
  is_solvable_ = false;

}

/*
 the parameterized constructor reads the input file to initialize 
 the board. The input files consist of 9 digits on each row separated 
 by commas, and 9 rows separated by new line characters \n, 
 corresponding to a sudoku board. Empty squares contain the digit 0. 
 After reading the puzzle, the constructor tries to solve it and records 
 whether the puzzle has a solution or not.

TIP! We strongly suggest that you break down this task with the use of 
helper functions (reading the file, solving the puzzle etc.) and thoroughly 
test and debug each functionality separately.
*/
SudokuSolver::SudokuSolver(std::string input_file) {
  
  //Creating the 2D pointer array
  puzzle_ = new int*[9];
  for (int a = 0; a < 9; a++){
    puzzle_[a] = new int[9];
  }

  std::string file, number;
  std::ifstream sudokufile(input_file);
  int row = 0;
  
  for(int j = 0; j < 9; j++){
    while(std::getline(sudokufile, file)) {
      int col = 0;
      std::istringstream s(file);
      while(std::getline(s, number, ',')){
        puzzle_[row][col] = stoi(number);
        col++;
      } 
      row++;
    }
  }
  sudokufile.close();

  is_solvable_ = solvePuzzle(puzzle_, 0, 0);
  
 
}

//Solving puzzle
bool SudokuSolver::solvePuzzle(int** puzzle, int row, int col){
  Sudoku::Location emptysquare;
  emptysquare.row = row;
  emptysquare.col = col;
  emptysquare = returnNextEmpty();
  
  if (emptysquare.row == -1 && emptysquare.col == -1){
    return true;
  }

  for(int i = 1; i <= 9; i++){
    if (checkLegalValue(i, emptysquare)){
      puzzle[emptysquare.row][emptysquare.col] = i;
      
      if(solvePuzzle(puzzle, emptysquare.row, emptysquare.col)){
        return true;
      } 
    }
    puzzle_[emptysquare.row][emptysquare.col] = 0; 
  }
  return false;
}
//Accessors and mutators
/*
returns true if the puzzle is solvable, false otherwise. We suggest 
you keep track of this when solving the problem at construction, rather
than solving the puzzle again each time this function is called.
*/
bool SudokuSolver::isPuzzleSolvable() {
  return is_solvable_;
}

/*
records the puzzle as being solvable
*/
void SudokuSolver::setSolvable() {
  is_solvable_ = true;
}

/*
 returns the  2D pointer array representing the puzzle
*/
int** SudokuSolver::getPuzzleNumbers() {
  return puzzle_;
}

/*
 sets the  2D pointer array representing the puzzle to the value of 
 the parameter 
*/
void SudokuSolver::setPuzzleNumbers(int** puzzle) {
  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      puzzle_[i][j] = puzzle[i][j];
    }
  }
}


//Utility Functions
/*
returns a Location object with the coordinates of the first 0 found 
in the 2D pointer array, meaning that it is an empty square in the 
sudoku board. To find the first empty square you must read the 2D 
array from top-left (0,0) to bottom right (8,8), one row at a time. 
Set the row and col of the Location to the indices at which the first
 0 is found in the 2D array. If there are no empty squares the Location
  object should have row and col values of -1.
*/
Sudoku::Location SudokuSolver::returnNextEmpty() {
  Sudoku::Location located;
  for(int row = 0; row < 9; row++){
    for(int col = 0; col < 9; col++){
      if(puzzle_[row][col] == 0) {
        located.row = row;
        located.col = col;
        return located;
      }
      else{
        located.col = -1; 
        located.row = -1;
      }
    }
  }
  
  return located;
}

/*
returns true if the value parameter (which can take on values 1-9) 
can legally be placed at the given location in the 2D array without 
breaking the rules of sudoku. It returns false if placing value at 
location is not a legal move. Remember, in order to be a valid move, 
the value must be unique with a row, column, and sub-grid.

    Hint: to define the top-left corner of the sub-grid in which the
    location falls, integer division of the coordinates (row and col)
    by 3 will come in handy since all sub-grids are 3x3.
*/
bool SudokuSolver::checkLegalValue(int value, Sudoku::Location location) {
  for(int i = 0; i < 9; i++) {
    if (puzzle_[location.row][i] == value || puzzle_[i][location.col] == value){
      return false;
    }
  }

  int division_row = (location.row / 3) * 3;
  int division_col = (location.col / 3) * 3;
  for(int i = division_row; i < division_row + 3; i++){
    for(int j = division_col; j < division_col + 3; j++){
      if(puzzle_[i][j] == value){
        return false;
      }
    }
  }
  return true;

}

/*
will display the board as illustrated below:

Example:

NXX|NXN|XXN
NXN|XNN|XXX
NXN|NXX|XXX
------------ 
XNX|NXN|NXX
XXX|XNX|XXX
XXN|NXN|XNX
------------ 
XXX|XXN|NXN
XXX|NNX|NXN
NXX|NXN|XXN
(No spaces needed at all, except 2 spaces preceding | and one space back)
*/
void SudokuSolver::display() {
 for (int row = 0; row < 9; row++) {
  for (int col = 0; col < 9; col++) {
    int number = puzzle_[row][col];
    if (number == 0) {
      std::cout<<"X";
    } 
    else {
      std::cout<<number;
    }

    //Adding '-' and '|'
    if (col % 3 == 2 && col != 8) {
      std::cout << "  | ";
    }
    }
    std::cout<<std::endl;
    if (row % 3 == 2 && row != 8) {
        std::cout<<"------------"<<std::endl;
    }
  }
}

