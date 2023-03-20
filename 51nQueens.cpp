#include <iostream>
#include <stack>

using namespace std;

//The function that checks if the queen is in a safe spot 
bool queenSafe(int row, int column, stack<int>& rowSpot) {
    
    //Creating a temp stack with the same values because we will be deleting the values in the stack
    //to move to previous members of the stack to check safety
    stack<int> temp = rowSpot;
    int testRow = row - 1;
    //Checking each queen position
    while (!temp.empty()) {
        int current = temp.top();
        //Checking if each queen is in the same column, upper or lower diagonal positions
        if (current == column || current - column == testRow - row || current - column == row - testRow || row == testRow) {
            return false;
        }
        temp.pop();
        testRow--;
    }
    return true;
}

//Function to place queens in a safe location on the board
bool nQueens(int n, int row, stack<int>& rowSpot) {
    //stopping the recussion if the last row is reached 
    if (row == n) {
        return true;
    }
    //Parsing through each column to place a queen
    for (int column = 0; column < n; column++) {
        if (queenSafe(row, column, rowSpot)) {
            rowSpot.push(column);
            //Placing a queen again
            if (nQueens(n, row+1, rowSpot)) {
                return true;
            }
            //If the position on the board doenst lead to a safe spot
            //delete the position and move to the next position
            rowSpot.pop();
        }
    }
    return false;
}

//Function to print the solution board 
void printBoard(int n, stack<int>& rowSpot) {

    //Creating an empty chess board that is n by n in size
    int chessBoard[n][n]={};
    //Assigning a value to all safe positions so they are not the null character zero
    while (!rowSpot.empty()) {
            chessBoard[rowSpot.top()][rowSpot.size()-1] = 1; 
            rowSpot.pop();
        }
        //Printing out Q if there is a value or printing out a . if there is a null character
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (chessBoard[i][j]) {
                    cout << "Q ";
                }
                else {
                    cout << ". ";
                }
            }
        cout << endl;
    }
}

int main() {
    //Asking the user for the board size
    int n;
    cout << "Enter the size of the board: ";
    cin >> n;
    //Creating a stack for the column positions 
    stack<int> rowSpot;
    if (nQueens(n, 0, rowSpot)) {
        printBoard(n, rowSpot);
    }
    //Base case if there arent any solutions
    else {
        cout << "No solution exists for n = " << n << endl;
    }
    return 0;
}
