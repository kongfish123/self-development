# Alien vs. Zombie

On a planet far far away from earth, a young alien is fighthing unknown zombies that invade his home planet. Help this young alien to protect his home.

You as a player will help this alien to navigate his way to defeat the zombies and keep his home save.

Alien vs. Zombie is a text-based game where player are able to input simple command to control the character which is the alien. The alien will be able to defeat the zombies by attacking the zombie.

The player will use simple command such as up(^), down(v), left(<) and right(>) to move around the game board and attack the zombies.

There will be multiple game object where player will be able to interact with to make the game even more fun. XD
![Display Help](https://github.com/Kong-fish/Assignment/blob/main/Screenshot/Help.png)


Please provide the YouTube link to your [Video Demo](https://youtu.be/h6MXmUfKmPs).

## Compilation Instructions

1. Download the file into your local machine. Player is advised to download the whole program instead of just the .exe file to maintain stability.
2. Unzip the zip file into your selected location.
3. Right click on the folder **containing** the main.cpp application file.
4. Choose "Copy as Path".
5. If there is an option to "Open in Terminal" or "Open in Command Prompt", select that and skip Step 6-8.
6. Open Command Prompt / Windows Terminal.
7. Write "cd", space, and then paste the path that you copied by right clicking.
8. Click Enter.
9. Write "g++ main.cpp pf/*.cpp -o main" into the terminal and press enter.
10. Open back your folder and there should be a main.exe file. Double click it and start your game.

```
g++ main.cpp pf/*.cpp -o main
```

## User Manual

1. Generation of game board
User will be choose between three set of default difficulity with different rows and and coloums for game board size. There is also different numbers of zombies that user need to defeat for each difficulity. 
User can choose between three default which is 
:Easy (Rows = 5, Colums = 9, Zombies = 1)
![Easy](https://github.com/Kong-fish/Assignment/blob/main/Screenshot/Easy.png)

:Normal (Rows = 9, Colums = 11, Zombies = 2) 
![Medium](https://github.com/Kong-fish/Assignment/blob/main/Screenshot/Medium.png)

:Hard (Rows = 13, Colums = 15, Zombies = 3). 
![Hard](https://github.com/Kong-fish/Assignment/blob/main/Screenshot/Hard.png)

User is able to change the default settings of the game board too. 
Player are able to move around the generated game board. Invalid input will shown if the player move the Alien out of bounds. Zombie will also move randomly in the game board.

2. Game Character and Game Objects
Alien (A) is the character that player able to control.
Zombie (Z) will be the non-player character that player need to defeat by passing around the zombies.
Rock (r) is an obstacle object that will block the Alien path. It will turn into another game object after Alien bumping into the rock.
Arrow (^,v,<,>) is game objects that that allow Alien to change its path.

3. Player Input
Player able to input lower or uppercase of the alphabet symbolize each input.
W key will be moving Alien up.
A key will be moving Alien to the left
D key will be moving Alien to the right.
S key will be moving Alien to the bottom
Q key will let player to end the game.
V key will let the player to save it game.
L key will let player load previous game file.
H key will display the Player Input explaination.

For save game, player are able to input file name and save it into local machine.
For load game, player reinput previous save game and the programme load from the safe file.

## Progress Log

- [Part 1](PART1.md)
- [Part 2](PART2.md)

## Contributors

- Kong Xin Yu
- Chan Yeng Hui
- Wong Wai Yee


