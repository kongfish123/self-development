#include <iostream>
#include <fstream>
#include <iomanip> //for setw()
#include <cstdlib>
#include "pf/helper.cpp"
using namespace std;

const int MAX_ROWS = 100;
const int MAX_COLS = 100;
char board[MAX_ROWS][MAX_COLS];

// Alien and Zombie variables
int alienX, alienY;
int zombieX, zombieY;
int zombies[MAX_ROWS * MAX_COLS];
int numZombies;

// Game Board settings
int numRows, numCols;
int defRows, defCols, defZombies;

// Attributes
const int MAX_LIFE = 500;
const int MAX_ATTACK = 50;
int alienLifeAttr, alienAttackAttr;
int zombieLifeAttr[MAX_ROWS * MAX_COLS], zombieAttackAttr[MAX_ROWS * MAX_COLS];

//Game Objeact
int noOfObjects;
char objects[];

void difficulties()
{
    char diff;
    int Rows,Cols,Zombies;

    cout << "Welcome to Alien vs Zombies! " << endl;
    cout << "\nFirst let choose difficultiy : Easy (E) || Normal (N) || Hard (H)" << endl;
    cout << "\nChoose Your difficulity to start the game => ";
    cin >> diff;

    switch (diff)
    {
        case 'E':
        case 'e':
        Rows = 5;
        Cols = 9;
        Zombies = 1;
        break;

        case 'N':
        case 'n':
        Rows = 9;
        Cols = 11;
        Zombies = 2;

        case 'H':
        case 'h':
        Rows = 13;
        Cols = 15;
        Zombies = 3;
    }

    defRows=Rows;
    defCols=Cols;
    defZombies=Zombies;

}
void defaultGameSettings()
{

    cout << "\nDefault Game Settings" << endl;
    cout << "-----------------------" << endl;
    cout << "Board Rows    : " << defRows << endl;
    cout << "Board Colums  : " << defCols << endl;
    cout << "Zombie Count  : " << defZombies << endl;

    char gameSetChange;
    cout << "\nDo you wish to change the game settings (y/n)? => ";
    cin >> gameSetChange;

    if (gameSetChange == 'N' || gameSetChange == 'n')
    {
        numRows = defRows;
        numCols = defCols;
        numZombies = defZombies;
    }
    else
    {
        cout << "Enter the number of rows for the game board (odd number): ";
        cin >> numRows;
        while (numRows % 2 == 0)
        {
            cout << "Number of rows must be an odd number. Please enter again: ";
            cin >> numRows;
        }

        cout << "Enter the number of columns for the game board (odd number): ";
        cin >> numCols;
        while (numCols % 2 == 0)
        {
            cout << "Number of columns must be an odd number. Please enter again: ";
            cin >> numCols;
        }

        cout << "Enter the number of Zombies on the board: ";
        cin >> numZombies;
        while (numZombies > (numRows * numCols) - 1)
        {
            cout << "Too many Zombies for the board size. Please re-enter again: ";
            cin >> numZombies;
        }
        cout << "Settings Updated" << endl;
        cout << "Press any key to continue";
    }
}

void Gameobj()
{
    char objects[] = {' ', ' ', ' ',' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'v', '^', '<', '>', 'h', 'p', 'r'};
    int noOfObjects = 20; // number of game objects and empty spaces in the array

    // put game objects randomly in empty spaces on the board
    for (int i = 0; i < numRows; ++i)
    {
        for (int j = 0; j < numCols; ++j)
        {
        if ( board[i][j] == ' ')
            {
            int objNo = rand() % noOfObjects;
            board[i][j] = objects[objNo];
            }
        }
    }
    
}

void GameobjAttr()
{
    int x, y;
    if (board[x][y] == 'v' || board[x][y] == '^' || board[x][y] == '<' || board[x][y] == '>')
    {
        alienAttackAttr += 20;
    }
    else if (board[x][y] == 'h')
    {
        alienLifeAttr += 20;
    }
}

void initializeBoard()
{
    // Clear board
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            board[i][j] = ' ';
        }
    }
    // Place Alien at center of board
    alienX = numRows / 2;
    alienY = numCols / 2;
    board[alienX][alienY] = 'A';
    // Initialize Alien attributes
    alienLifeAttr = (rand() % (MAX_LIFE / 5) + 1) * 5;
    alienAttackAttr = 0;
    // Place Zombies randomly on board
    for (int i = 0; i < numZombies; i++)
    {
        int x, y;
        do
        {
            zombieX = rand() % numRows;
            zombieY = rand() % numCols;
        } while (board[zombieX][zombieY] != ' ');
        board[zombieX][zombieY] = 'Z';
    //Initialize Zombie attributes
        zombieLifeAttr[i] = (rand() % (MAX_LIFE / 5) + 1) * 5;
        zombieAttackAttr[i] = (rand() % (MAX_ATTACK / 5) + 1) * 5;
    }
    //Place game objects randomly on the board
    Gameobj();
}

void displayBoard();

void Help()
{
    char input;
    cout << "\nCommands";
    cout << "\n w        - Move up.";
    cout << "\n s        - Move down.";
    cout << "\n a        - Move left.";
    cout << "\n s        - Move right.";
    cout << "\n help     - Display user commands explainations.";
    cout << "\n v        - Save the game.";
    cout << "\n l        - Load previous game.";
    cout << "\nq         - Quit game.\n";
    cout << "\n Press any key to continue your game.";
    cin >> input;
    pf::ClearScreen();
    displayBoard();
}

void displayBoard()
{

    cout << " . : Alien vs Zombie : ." << endl;
    // for each row
    for (int i = 0; i < numRows; ++i)
    {
        // display upper border of the row
        cout << "   ";
        for (int j = 0; j < numCols; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        // display row number
        cout << setw(2) << (i + 1) << " ";

        // display cell content and border of each column
        for (int j = 0; j < numCols; ++j)
        {
            cout << "|" << board[i][j];
        }
        cout << "|" << endl;
    }
    // display lower border of the last row
    cout << "   ";
    for (int j = 0; j < numCols; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;
    // display column number
    cout << "    ";
    for (int j = 0; j < numCols; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "   ";
    for (int j = 0; j < numCols; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl;
}

void displayAttr()
{
    cout << "Alien    : Life  " << alienLifeAttr << ", Attack  "  << alienAttackAttr << endl;
    for (int i = 0; i < numZombies; i++)
    {
        cout << "Zombie " << i << ": Life  " << zombieLifeAttr[i] << ", Attack  " << zombieAttackAttr[i] << endl;
    }
}

void moveAlien(int x, int y)
{
    // make sure Alien always stay in game board
    if (x < 0 || x >= numRows || y < 0 || y >= numCols)
    {
        cout << "Invalid move." << endl;
        return;
    }

    board[alienX][alienY] = '.';
    alienX = x;
    alienY = y;
    board[alienX][alienY] = 'A';
}

void zombieMovement()
{
    int x = 0;
    int y = 0;
    int direction = rand() % 4;
    // zombie move up
    if (direction == 0)
    {
        x = zombieX - 1;
        y = zombieY;
    }
    //zombie move down
    else if ( direction == 1 )
    {
        x = zombieX + 1;
        y = zombieY;
    }
    //zombie move left
    else if ( direction == 2 )
    {
        x = zombieX;
        y = zombieY - 1;
    }
    //zombie move right
    else if ( direction == 3 )
    {
        x = zombieX;
        y = zombieY + 1;
    }
   //make sure zombie stays inside the board and the new zombie postion is not occupied by Alien 
    if( (x>0) && (x<numRows) && (y>0) && (y<numCols) && (board[x][y] != 'A'))
    { 
        board[zombieX][zombieY] = ' ';
        zombieX = x;
        zombieY = y;
        board[zombieX][zombieY] = 'Z';
    }
   //generate a random movement again if new zombie position is outside the board or Alien is in the new position
    else
    {
        zombieMovement();
    }
    
}

void zombieAttack()
{
    int rangeX, rangeY;
    rangeX = rand() % (numRows/3) + 1; //vertical range of attack is a randNum between 0 and 1/3 of the board rows
    rangeY = rand() % (numCols/3) + 1; //horizontal range of attack is a randNum between 0 and 1/3 of the board columns

    for (int i = zombieX; i <= (zombieX + rangeX); i++) //check the space below the zombie
    {   if (board[i][zombieY] == ' ')
        {
            continue;
        }
        else if (board[i][zombieY] == 'A')
        {
            board[i][zombieY] = ' '; //kill Alien
            break;
        }
    }
    for (int x = zombieX - rangeX; x < zombieX; x++) //check the space above the zombie
    {   if (board[x][zombieY] == ' ')
        {
            continue;
        }
        else if (board[x][zombieY] == 'A')
        {
            board[x][zombieY] = ' '; //kill Alien
            break;
        }
    }
        
    for (int j = zombieY; j <= (zombieY + rangeY); j++) //check the space to the right of the zombie
    {

        if (board[zombieX][j] == ' ')
        { continue; }

        else if (board[zombieX][j] == 'A')
        {
            board[zombieX][j] = ' '; //kill Alien
            break;
        }
    }

    for (int y = zombieY - rangeY; y < zombieY; y++) //check the space to the left of the zombie
    {

        if (board[zombieX][y] == ' ')
        { continue; }

        else if (board[zombieX][y] == 'A')
        {
            board[zombieX][y] = ' '; //kill Alien
            break;
        }
    }
}

//void objFunction()
//{
//    if(alienX==objects['p'] && alienY==objects['p']) 
//    {
//        cout<<"Alien gain a pod."<<endl;
//        zombieLifeAttr[MAX_ROWS * MAX_COLS]=-20;
//    }
//    else(alienX==objects['r'] && alienY==objects['r'])
//    {
//        cout<<"Alien flip the rock and found a pod."<<endl;
//        int objNo = rand() % noOfObjects;
//        objects['r']=objects[objNo];
//    }
//    else(alienX==objects['h'] && alienY==objects['h'])
//    {
//        cout<<"Alien found a health Pod."<<endl;
//       alienLifeAttr=+20;
//    }
//    else(alienX==objects['^'] && alienY==objects['^'])
//    {
//        cout<<"Alien gain a arrow."
//        alienAttackAttr=+20;
//        alienX=+1;
//        alienY=alienY;
//    }
//    else(alienX==objects['<'] && alienY==objects['<'])
//    {
//        cout<<"Alien gain a arrow."
//        alienAttackAttr=+20;
//        alienX=alienX;
//       alienY=alienY-1;   
//    }
//    else(alienX==objects['>'] && alienY==objects['>'])
//    {
//        cout<<"Alien gain a arrow."
//        alienAttackAttr=+20;
//        alienX=alienX;
//        alienY=alienY+1;
//    }
//    else(alienX==objects['v'] && alienY==objects['v'])
//    {
//        cout<<"Alien gain a arrow."
//        alienAttackAttr=+20;
//        alienX=alienX-1;
//        alienY=alienY;
//    }
//    else if(alienX==objects[' '] && alienY==objects[''])
//    {
//        cout<<"Alien move to a blankc space."
//    }
//}

void saveGame(string fileName)
{
    ofstream outFile(fileName);
    outFile << numRows << " " << numCols << endl;
    outFile << alienX << " " << alienY << endl;
    outFile << numZombies << " ";
    for (int i = 0; i < numZombies; i++)
    {
        outFile << zombies[i] << " ";
    }
    outFile << endl;
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            outFile << board[i][j];
        }
        outFile << endl;
    }
    outFile.close();
    cout << "Game saved successfully." << endl;
}

void loadGame(string fileName)
{
    ifstream inFile(fileName);
    inFile >> numRows >> numCols;
    inFile >> alienX >> alienY;
    inFile >> numZombies;
    for (int i = 0; i < numZombies; i++)
    {
        inFile >> zombies[i];
    }
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            inFile >> board[i][j];
        }
    }
    inFile.close();
    cout << "Game loaded successfully." << endl;
    pf::Pause();
    pf::ClearScreen();
}

void gamePause()
{
    cout << "Pausing Now" << endl;
    pf::Pause();
    cout << endl;
}

void gameClearScreen()
{
    cout << "Pausing and Clearing Screen Now" << endl;
    pf::Pause();
    pf::ClearScreen();
    cout << endl;
}

int main()
{
    srand(time(0));
    difficulties();
    defaultGameSettings();
    gameClearScreen();
    initializeBoard();
    displayBoard();
    displayAttr();

    char choice;
    int x, y;
    
    while (true)
    {
        cout << "\nEnter move (W - up, A - left, S - down, D - right, Q - quit, V - save, L - load, H - help): ";
        cin >> choice;

        if (choice == 'W' || choice == 'w')
        {
            x = alienX - 1;
            y = alienY;
        }
        else if (choice == 'A' || choice == 'a')
        {
            x = alienX;
            y = alienY - 1;
        }
        else if (choice == 'S' || choice == 's')
        {
            x = alienX + 1;
            y = alienY;
            
        }
        else if (choice == 'D' || choice == 'd')
        {
            x = alienX;
            y = alienY + 1;
        }
        else if (choice == 'Q' || choice == 'q')
        {
            break;
        }
        else if (choice == 'V' || choice == 'v')
        {
            string fileName;
            cout << "Enter the file name to save the game: ";
            cin >> fileName;
            saveGame(fileName);
            continue;
        }
        else if (choice == 'L' || choice == 'l')
        {
            string fileName;
            cout << "Enter the file name to load the game: ";
            cin >> fileName;
            loadGame(fileName);
            continue;
        }
        else if (choice=='H'||choice=='h')
        {
            Help();
            continue;
        }
        else
        {
            cout << "Invalid choice." << endl;
            continue;
        }
        zombieMovement();
        zombieAttack();
        moveAlien(x, y);
        gameClearScreen();
        displayBoard();
    }

    cout << "Thank you for playing Alien vs Zombie!" << endl;

    return 0;
}
