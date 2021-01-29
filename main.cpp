// Author: Mohammed Hisham Moizuddin - CS-141 SUMMER 2020

// Prog6maze.cpp
// Play a simple maze game.
// Program: #6, Navigating a maze using classes

#include <bits/stdc++.h>
#include <iostream> 
#include <cctype>   
#include <fstream>      //to implement file i/o operations
#include <string>       //to implement strings
#include <vector>       //to implement vectors   
#include <sstream>  
using namespace std;

//#############################################################################################

class Inventory         //Class Inventory definition
{
public:
    void setHerbs(int value) { this->numHerbs = value; }    //mutators
    void setHealth(int value) { this->totalHealth = value; }
    void setGold() { numGold++; }
    
    int getHerbs() { return numHerbs; }      //getter functions
    int getHealth() { return totalHealth; }
    int getGold() { return numGold; }

private:       //Data Members
    int numHerbs = 0;
    int totalHealth = 3;
    int numGold = 0;
};

//#############################################################################################

class Player         //Class Player definition
{
public:
    void setRow(int row) { this->row = row; }      //mutators
    void setCol(int col) { this->col = col; }

    Inventory &getInventory() { return inventory; }
    
    int getRow() { return row; }    //getter functions
    int getCol() { return col; }

private:       //Data Members
    Inventory inventory;
    int row;
    int col;
};

//#############################################################################################

class Board       //Class Board definition
{
public:
    void readCoordinates();      //mutators
    void initialiseMazeBoard();
    void displayMazeBoard();
    void movePlayer(int row, int col);
    void doMove();
    
    Player &getPlayer() { return player; }
    
    int getTotalRows() { return totalRows; }    //getter functions
    int getTotalCols() { return totalCols; }

private:       //Data members
    Player player; 
    int totalRows;
    int totalCols;
    char **mazeBoard; 
};

//#############################################################################################

void Board::initialiseMazeBoard(){     //Member function to initialize maze board
    mazeBoard = new char *[totalRows];
    for(int i=0; i<totalRows; i++){
        mazeBoard[i] = new char[totalCols];
    }
    for(int i=0; i<totalRows; i++){
        for(int j=0; j<totalCols; j++){
            mazeBoard[i][j] = '.';
        }
    }
    for (int i=0; i<totalRows; i++)
    {
        for (int j=0; j<totalCols; j++)
        {
            if (i==0 || j==0 || i==totalRows-1 || j==totalCols-1 )
            {
                mazeBoard[i][j] = '*';
            }
        }
    }
}

//#############################################################################################

void Board::displayMazeBoard(){     //Member function to display maze board
    for(int i=0; i<totalRows; i++){
        for(int j=0; j<totalCols; j++){
            cout << " " << mazeBoard[i][j];
        }
        if (i!=9){
            cout << endl;
        }
    }
}

//#############################################################################################

void Board::readCoordinates(){      //Member function to read coordinates
    char item;
    int rows;
    int cols;

    ifstream inputStream("maze.txt");
    inputStream >> rows >> cols;
    totalRows = rows;
    totalCols = cols;
    initialiseMazeBoard();
    inputStream >> rows >> cols;
    player.setRow(rows);
    player.setCol(cols);
    mazeBoard[rows][cols] = 'P';
    while(inputStream >> item >> rows >> cols){
        if(item == 'W'){
            mazeBoard[rows][cols] = '*';
        }
        else{
            mazeBoard[rows][cols] = item;
        }
    }
    inputStream.close();
}

//#############################################################################################

void Board::movePlayer(int row, int col){    //Member function to move player
    int numHerbs = player.getInventory().getHerbs();
    int totalHealth = player.getInventory().getHealth();
    int numGold = player.getInventory().getGold();

    if (mazeBoard[row][col] == 'H'){
        cout << "You found a healing item!" << endl;
        mazeBoard[row][col] = 'P'; 
        player.setRow(row);
        player.setCol(col);
        player.getInventory().setHerbs(numHerbs + 1);
    }
    else if (mazeBoard[row][col] == 'C'){
        cout << "You found a chest!" << endl;
        mazeBoard[row][col] = 'P';
        player.setRow(row);
        player.setCol(col);
        player.getInventory().setGold();
    }
    else if (mazeBoard[row][col] == 'T'){
        cout << "You stepped on a trap!" << endl;
        mazeBoard[row][col] = 'P';
        player.setRow(row);
        player.setCol(col);
        if (totalHealth-1 == 0)
        {
            if (numHerbs != 0)
            {
                player.getInventory().setHealth(numHerbs);
                player.getInventory().setHerbs(0);
            }
            else
            {
                cout << "You died!" << endl;
                exit(-1);
            }
        }
        else
        {
            player.getInventory().setHealth(totalHealth - 1);
        }
    }
    else if (mazeBoard[row][col] == 'D'){
        mazeBoard[row][col] = 'P'; 
        cout << endl;
        displayMazeBoard();
        cout << endl;
        cout << "You have reached the door!" << endl;
        cout << "Thank you for playing, here is a summary of your game: " << endl;
        cout << "Player health: " << player.getInventory().getHealth() << endl;
        cout << "Player has " << player.getInventory().getHerbs() << " healing items." << endl;
        cout << "Player has " << player.getInventory().getGold() << " gold coins." << endl;
        exit(-1);
    }
    else{
        mazeBoard[row][col] = 'P';
        player.setRow(row);
        player.setCol(col);
    }
}

//#############################################################################################

void Board::doMove(){
    char moveCommand;
    int row = player.getRow();
    int col = player.getCol();
    int numGold = player.getInventory().getGold();
    int totalHealth = player.getInventory().getHealth();
    int numHerbs = player.getInventory().getHerbs();

    cin >> moveCommand;

    switch(toupper(moveCommand)){
    case 'W':
        if(mazeBoard[row-1][col] == '*'){
            cout << "The location is blocked. You can't move there!" << endl;
            cout << "Try again!" << endl;
        }
        else{
            mazeBoard[row][col] = '.';
            movePlayer(row-1, col);
        }
    break;
    case 'A':
        if(mazeBoard[row][col-1] == '*'){
            cout << "The location is blocked. You can't move there!" << endl;
            cout << "Try again!" << endl;
        }
        else{
            mazeBoard[row][col] = '.';
            movePlayer(row, col-1);
        }
    break;
    case 'S':
        if(mazeBoard[row+1][col] == '*'){
            cout << "The location is blocked. You can't move there!" << endl;
            cout << "Try again!" << endl;
        }
        else{
            mazeBoard[row][col] = '.';
            movePlayer(row+1, col);
        }
    break;
    case 'D':
        if(mazeBoard[row][col+1] == '*'){
            cout << "The location is blocked. You can't move there!" << endl;
            cout << "Try again!" << endl;
        }
        else{
            mazeBoard[row][col] = '.';
            movePlayer(row, col+1);
        }
    break;
    case 'I':
        cout << "Player health: " << totalHealth << endl;
        cout << "Player has " << numHerbs << " healing items." << endl;
        cout << "Player has " << numGold << " gold coins." << endl;
    break;
    case 'X':
        cout << "Exiting..." << endl;
        exit(-1);
    }
    
}

//#############################################################################################

void displayInstructions(){      //Function to display instructions
    cout << "\n"
         << "Let's Play!\n"
         << "Move the player icon up, down, right, or left\n"
         << "with w, s, d ,a keys\n"
         << "press i to display player inventory\n"
         << "At any point press x to exit the game.\n"
         << endl;
} // end displayInstructions()

//#############################################################################################

int main(){
    Board board;
    
    board.readCoordinates();
    
    cout << "Reading the maze file..." << endl << endl;
    board.displayMazeBoard();
    displayInstructions();

    while(true){
        board.doMove();
        cout << endl;
        board.displayMazeBoard();
        cout << endl;
    }
}
