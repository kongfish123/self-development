#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip> //for setw()
#include "pf/helper.cpp"
#include <vector>

class Board
{
public:
    std::vector<std::vector<char>> board;
    int MAX_ROWS = 100;
    int MAX_COLS = 100;
    int numRows, numCols;
    int defRows, defCols, defZombies;
    int itemsNo;
    char choice;
};

class Alien
{
public:
    int alienX, alienY;
};

class Zombie
{
public:
    int zombieX, zombieY;
    int numZombies;
};

// Attributes
class Attr
{
public:
    int MAX_LIFE = 500;
    int MAX_ATTACK = 50;
    int alienLifeAttr, alienAttackAttr;
    std::vector<int> zombieLifeAttr;
    std::vector<int> zombieAttackAttr;
};

void difficulties(Board &Board)
{
    char diff;
    int Rows, Cols, Zombies;

    std::cout << "Welcome to Alien vs Zombies! " << std::endl;
    std::cout << "\nFirst let choose difficultiy : Easy (E) || Normal (N) || Hard (H)" << std::endl;
    std::cout << "\nChoose Your difficulity to start the game => ";
    std::cin >> diff;

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

    Board.defRows = Rows;
    Board.defCols = Cols;
    Board.defZombies = Zombies;
}

void defaultGameSettings(Board &Board, Zombie &Zombie)
{

    std::cout << "\nDefault Game Settings" << std::endl;
    std::cout << "-----------------------" << std::endl;
    std::cout << "Board Rows    : " << Board.defRows << std::endl;
    std::cout << "Board Colums  : " << Board.defCols << std::endl;
    std::cout << "Zombie Count  : " << Board.defZombies << std::endl;

    char gameSetChange;
    std::cout << "\nDo you wish to change the game settings (y/n)? => ";
    std::cin >> gameSetChange;

    if (gameSetChange == 'N' || gameSetChange == 'n')
    {
        Board.numRows = Board.defRows;
        Board.numCols = Board.defCols;
        Zombie.numZombies = Board.defZombies;
    }
    else
    {
        std::cout << "Enter the number of rows for the game board (odd number): ";
        std::cin >> Board.numRows;
        while (Board.numRows % 2 == 0)
        {
            std::cout << "Number of rows must be an odd number. Please enter again: ";
            std::cin >> Board.numRows;
        }

        std::cout << "Enter the number of columns for the game board (odd number): ";
        std::cin >> Board.numCols;
        while (Board.numCols % 2 == 0)
        {
            std::cout << "Number of columns must be an odd number. Please enter again: ";
            std::cin >> Board.numCols;
        }

        std::cout << "Enter the number of Zombies on the board: ";
        std::cin >> Zombie.numZombies;
        while (Zombie.numZombies > (Board.numRows * Board.numCols) - 1)
        {
            std::cout << "Too many Zombies for the board size. Please re-enter again: ";
            std::cin >> Zombie.numZombies;
        }
        std::cout << "Settings Updated" << std::endl;
        std::cout << "Press any key to continue";
    }
}

void displayAttr(Attr &Attr, Zombie &Zombie)
{
    std::cout << "Alien    : Life  " << Attr.alienLifeAttr << ", Attack  " << Attr.alienAttackAttr << std::endl;
    for (int i = 0; i < Zombie.numZombies; i++)
    {
        std::cout << "Zombie " << i << ": Life  " << Attr.zombieLifeAttr[i] << ", Attack  " << Attr.zombieAttackAttr[i] << std::endl;
    }
}

void GameObj(Board &Board)
{
    char objects[] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'v', '^', '<', '>', 'h', 'p', 'r'};
    int noOfObjects = 20; // number of game objects and empty spaces in the array

    // put game objects randomly in empty spaces on the board
    for (int i = 0; i < Board.numRows; ++i)
    {
        for (int j = 0; j < Board.numCols; ++j)
        {
            int objNo = rand() % noOfObjects;
            Board.board[i][j] = objects[objNo];
        }
    }
}

void initializeBoard(Alien &Alien, Zombie &Zombie, Board &Board, Attr &Attr)
{
    Board.board.resize(Board.numCols); // create empty rows
    for (int i = 0; i < Board.numCols; ++i)
    {
        Board.board[i].resize(Board.numRows); // resize each row
    }
    // Clear board
    for (int i = 0; i < Board.numRows; i++)
    {
        for (int j = 0; j < Board.numCols; j++)
        {
            Board.board[i][j] = ' ';
        }
    }
    // Place Alien at center of board
    Alien.alienX = Board.numRows / 2;
    Alien.alienY = Board.numCols / 2;
    Board.board[Alien.alienX][Alien.alienY] = 'A';
    // Initialize Alien attributes
    Attr.alienLifeAttr = (rand() % (Attr.MAX_LIFE / 5) + 1) * 5;
    Attr.alienAttackAttr = 0;
    // Place Zombies randomly on board
    for (int i = 0; i < Zombie.numZombies; i++)
    {
        int x, y;
        do
        {
            Zombie.zombieX = rand() % Board.numRows;
            Zombie.zombieY = rand() % Board.numCols;
        } while (Board.board[Zombie.zombieX][Zombie.zombieY] != ' ');
        Board.board[Zombie.zombieX][Zombie.zombieY] = 'Z';
        // Initialize Zombie attributes
        Attr.zombieLifeAttr.push_back((rand() % (Attr.MAX_LIFE / 5) + 1) * 5);
        Attr.zombieAttackAttr.push_back((rand() % (Attr.MAX_ATTACK / 5) + 1) * 5);
    }
    // Place game objects randomly on the board
    GameObj(Board);
}

void displayBoard(Board &Board)
{

    std::cout << " . : Alien vs Zombie : ." << std::endl;
    // for each row
    for (int i = 0; i < Board.numRows; ++i)
    {
        // display upper border of the row
        std::cout << "   ";
        for (int j = 0; j < Board.numCols; ++j)
        {
            std::cout << "+-";
        }
        std::cout << "+" << std::endl;

        // display row number
        std::cout << std::setw(2) << (i + 1) << " ";

        // display cell content and border of each column
        for (int j = 0; j < Board.numCols; ++j)
        {
            std::cout << "|" << Board.board[i][j];
        }
        std::cout << "|" << std::endl;
    }
    // display lower border of the last row
    std::cout << "   ";
    for (int j = 0; j < Board.numCols; ++j)
    {
        std::cout << "+-";
    }
    std::cout << "+" << std::endl;
    // display column number
    std::cout << "    ";
    for (int j = 0; j < Board.numCols; ++j)
    {
        int digit = (j + 1) / 10;
        std::cout << " ";
        if (digit == 0)
            std::cout << " ";
        else
            std::cout << digit;
    }
    std::cout << std::endl;
    std::cout << "   ";
    for (int j = 0; j < Board.numCols; ++j)
    {
        std::cout << " " << (j + 1) % 10;
    }
    std::cout << std::endl;

    std::cout << "\nEnter move (W - up, A - left, S - down, D - right, Q - quit, V - save, L - load): ";
}

void Help(Board &Board)
{
    std::cout << "\nCommands";
    std::cout << "\n w        - Move up.";
    std::cout << "\n s        - Move down.";
    std::cout << "\n a        - Move left.";
    std::cout << "\n s        - Move right.";
    std::cout << "\n help     - Display user commands explainations.";
    std::cout << "\n v        - Save the game.";
    std::cout << "\n l        - Load previous game.";
    std::cout << "\nq         - Quit game.\n";
    std::cout << "\n Press any key to continue your game.";
    std::cin >> Board.choice;
    pf::ClearScreen();
    displayBoard(Board);
}

void saveGame(Board &Board, Zombie &Zombie, Alien &Alien, std::string fileName)
{
    std::ofstream outFile(fileName);
    std::vector<int> zombies;
    outFile << Board.numRows << " " << Board.numCols << std::endl;
    outFile << Alien.alienX << " " << Alien.alienY << std::endl;
    outFile << Zombie.numZombies << " ";
    for (int i = 0; i < Zombie.numZombies; i++)
    {
        outFile << zombies[i] << " ";
    }
    outFile << std::endl;
    for (int i = 0; i < Board.numRows; i++)
    {
        for (int j = 0; j < Board.numCols; j++)
        {
            outFile << Board.board[i][j];
        }
        outFile << std::endl;
    }
    outFile.close();
    std::cout << "Game saved successfully." << std::endl;
}

void loadGame(Board &Board, Zombie &Zombie, Alien &Alien, std::string fileName)
{
    std::ifstream inFile(fileName);
    std::vector<int> zombies;
    inFile >> Board.numRows >> Board.numCols;
    inFile >> Alien.alienX >> Alien.alienY;
    inFile >> Zombie.numZombies;
    for (int i = 0; i < Zombie.numZombies; i++)
    {
        inFile >> zombies[i];
    }
    for (int i = 0; i < Board.numRows; i++)
    {
        for (int j = 0; j < Board.numCols; j++)
        {
            inFile >> Board.board[i][j];
        }
    }
    inFile.close();
    std::cout << "Game loaded successfully." << std::endl;
}

void gamePause()
{
    std::cout << "Pausing Now" << std::endl;
    pf::Pause();
    std::cout << std::endl;
}

void gameClearScreen()
{
    std::cout << "Pausing and Clearing Screen Now" << std::endl;
    pf::Pause();
    pf::ClearScreen();
    std::cout << std::endl;
}

void userinput(Board &Board, Alien &Alien, Zombie &Zombie, int x, int y, std::string fileName)
{
    while (true)
    {

        if (Board.choice == 'W' || Board.choice == 'w')
        {
            x = Alien.alienX - 1;
            y = Alien.alienY;
        }
        else if (Board.choice == 'A' || Board.choice == 'a')
        {
            x = Alien.alienX;
            y = Alien.alienY - 1;
        }
        else if (Board.choice == 'S' || Board.choice == 's')
        {
            x = Alien.alienX + 1;
            y = Alien.alienY;
        }
        else if (Board.choice == 'D' || Board.choice == 'd')
        {
            x = Alien.alienX;
            y = Alien.alienY + 1;
        }
        else if (Board.choice == 'Q' || Board.choice == 'q')
        {
            break;
        }
        else if (Board.choice == 'V' || Board.choice == 'v')
        {
            std::cout << "Enter the file name to save the game: ";
            std::cin >> fileName;
            saveGame(Board, Zombie, Alien, fileName);
            continue;
        }
        else if (Board.choice == 'L' || Board.choice == 'l')
        {
            loadGame(Board, Zombie, Alien, fileName);
        }
        else
        {
            std::cout << "Invalid choice." << std::endl;
            continue;
        }
    }
}

void AlienMove(Board &Board, Alien &Alien, char x, char y)
{
    if (Board.choice == 'W' || Board.choice == 'w')
    {
        x = Alien.alienX - 1;
        y = Alien.alienY;
    }
    else if (Board.choice == 'A' || Board.choice == 'a')
    {
        x = Alien.alienX;
        y = Alien.alienY - 1;
    }
    else if (Board.choice == 'S' || Board.choice == 's')
    {
        x = Alien.alienX + 1;
        y = Alien.alienY;
    }
    else if (Board.choice == 'D' || Board.choice == 'd')
    {
        x = Alien.alienX;
        y = Alien.alienY + 1;
    }
    else if (Board.choice == 'Q' || Board.choice == 'q')
    {
        std::cout << "Thank you for playing Alien and Zombie!" << std::endl;
    }
}

void zombieMovement(Zombie &Zombie, Board &Board)
{
    int x, y;
    int direction;
    int direction = rand() % 4;
    // zombie move up
    if (direction == 0)
    {
        x = Zombie.zombieX - 1;
        y = Zombie.zombieY;
    }
    // zombie move down
    else if (direction == 1)
    {
        x = Zombie.zombieX + 1;
        y = Zombie.zombieY;
    }
    // zombie move left
    else if (direction == 2)
    {
        x = Zombie.zombieX;
        y = Zombie.zombieY - 1;
    }
    // zombie move right
    else if (direction == 3)
    {
        x = Zombie.zombieX;
        y = Zombie.zombieY + 1;
    }
    // make sure zombie stays inside the board and the new zombie postion is not occupied by Alien
    if (x < 0 && x > Board.numRows && y < 0 && y > Board.numCols && Board.board[x][y] != 'A')
    {
        Zombie.zombieX = x;
        Zombie.zombieY = y;
        Board.board[Zombie.zombieX][Zombie.zombieY] = 'Z';
    }
    // generate a random movement again if new zombie position is outside the board or Alien is in the new position
    else
    {
        zombieMovement(Zombie, Board);
    }
}

void zombieAttack(Zombie &Zombie, Board &Board)
{
    int rangeX, rangeY;
    rangeX = rand() % (Board.numRows / 3) + 1; // vertical range of attack is a randNum between 0 and 1/3 of the board rows
    rangeY = rand() % (Board.numCols / 3) + 1; // horizontal range of attack is a randNum between 0 and 1/3 of the board columns

    for (int i = Zombie.zombieX; i <= (Zombie.zombieX + rangeX); i++) // check the space below the zombie
    {
        if (Board.board[i][Zombie.zombieY] == ' ')
        {
            continue;
        }
        else if (Board.board[i][Zombie.zombieY] == 'A')
        {
            Board.board[i][Zombie.zombieY] = ' '; // kill Alien
            break;
        }
    }
    for (int x = Zombie.zombieX - rangeX; x < Zombie.zombieX; x++) // check the space above the zombie
    {
        if (Board.board[x][Zombie.zombieY] == ' ')
        {
            continue;
        }
        else if (Board.board[x][Zombie.zombieY] == 'A')
        {
            Board.board[x][Zombie.zombieY] = ' '; // kill Alien
            break;
        }
    }

    for (int j = Zombie.zombieY; j <= (Zombie.zombieY + rangeY); j++) // check the space to the right of the zombie
    {

        if (Board.board[Zombie.zombieX][j] == ' ')
        {
            continue;
        }

        else if (Board.board[Zombie.zombieX][j] == 'A')
        {
            Board.board[Zombie.zombieX][j] = ' '; // kill Alien
            break;
        }
    }

    for (int y = Zombie.zombieY - rangeY; y < Zombie.zombieY; y++) // check the space to the left of the zombie
    {

        if (Board.board[Zombie.zombieX][y] == ' ')
        {
            continue;
        }

        else if (Board.board[Zombie.zombieX][y] == 'A')
        {
            Board.board[Zombie.zombieX][y] = ' '; // kill Alien
            break;
        }
    }
}

int main()
{
    Board board;
    Alien alien;
    Zombie zombie;
    Attr atr;

    char x, y;
    srand(time(0));
    difficulties(board);
    defaultGameSettings(board, zombie);
    gameClearScreen();
    initializeBoard(alien, zombie, board, atr);
    displayBoard(board);
    displayAttr(atr, zombie);

    zombieMovement(zombie, board);
    zombieAttack(zombie, board);
    gameClearScreen();
    displayBoard(board);

    std::cout << "Thank you for playing Alien vs Zombie!" << std::endl;

    return 0;
}
