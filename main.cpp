#include "SudokuSolver.hpp"

int main() {

    //Parameterized constructor of SudokuSolver
    SudokuSolver solver("puzzle1.csv");
    
    
    // Check if the puzzle is solvable and print the puzzle
    if (solver.isPuzzleSolvable()) {
        // Solve the puzzle and print the solution
        std::cout<<"Solution of first puzzle:"<<std::endl;
        solver.display();
        std::cout<<std::endl;
    } 

    else {
        std::cout<<"The puzzle is unsolvable."<<std::endl;
        solver.display();
    }





    //Parameterized constructor of SudokuSolver
    SudokuSolver solver2("puzzle2.csv");
    
    
    // Check if the puzzle is solvable and print the puzzle
    if (solver2.isPuzzleSolvable()) {
        // Solve the puzzle and print the solution
        std::cout<<"Solution of second puzzle:"<<std::endl;
        solver2.display();
        std::cout<<std::endl;
    } 

    else {
        std::cout<<"The puzzle is unsolvable."<<std::endl;
        solver2.display();
    }






    //Parameterized constructor of SudokuSolver
    SudokuSolver solver3("difficultpuzzle.csv");
    
    
    // Check if the puzzle is solvable and print the puzzle
    if (solver3.isPuzzleSolvable()) {
        // Solve the puzzle and print the solution
        std::cout<<"Solution of difficult puzzle:"<<std::endl;
        solver3.display();
        std::cout<<std::endl;
    } 

    else {
        std::cout<<"The puzzle is unsolvable."<<std::endl;
        solver3.display();
    }






    //Parameterized constructor of SudokuSolver
    SudokuSolver impsolver("impossiblepuzzle.csv");
    
    
    // Check if the puzzle is solvable and print the puzzle
    if (impsolver.isPuzzleSolvable()) {
        // Solve the puzzle and print the solution
        std::cout<<"Solution of impossible puzzle:"<<std::endl;
        impsolver.display();
        std::cout<<std::endl;
    } 

    else {
        std::cout<<"The puzzle is unsolvable."<<std::endl;
        impsolver.display();
    }
}
