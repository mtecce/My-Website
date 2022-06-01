/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  @authors: Arthur Artene, Joshua Richard Kalapati, Michael Tecce
  Class: Intro to Computer Science CS 174 Spring 2020
  Assignment: Final Group Project: Maze Generator and Solver
  Due 5/13/2020
  
  Comments were made by @JoshuaRichardKalapati
  Formatting and Cleaning was done by @ArthurArtene
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <stdlib.h>
#include "FinalProj.h"
using namespace std;

/*
    @MichaelTecce created this method
    
    Main Maze method holding all other methods.
    <p>
    Takes in the given size and creates the values needed to construct the vector. 
    Once created, the maze will be created through the vector and print the maze.
    Will also create another vector to store directions. 
    Once done, the solver will begin and then print the new maze with solution.
    FInally printing out the solution. 
    
    @param int size
    @return nothing
    @see Class Maze
*/
Maze::Maze(int size){
  numOfCells = size;
  sizeOfMaze = (size*2) + 1;
  constructVector();
  constructCoordinateList();
  makeMaze(startxcoordwall,1);
  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
  cout << "       Here is your maze, safe travels :)\n" << endl;
  printMaze();
  directions.resize(sizeOfMaze * sizeOfMaze);
  solver(startxcoordwall,0,true,false,false,false,0);
  cout << "      Here is the maze with the solution :)\n" << endl;
  printMaze();
  printDirections();
}
/*
    @MichaelTecce created this method
    
    Maze Constructor that creates the vector base for maze
    <p>
    Uses values gathered from beginning of program to allocate for maze vector
    Allocates for path as well to use later during solver method. 
    Both mazes have walls with # and spaces that are ' '. 
    Then determines where the start x coordinate is on left wall and end x coodinate on right wall. 
    These are the beginning and end for the maze. 
    Makes sure start point is created and cisually seen through a open space on walls.
    
    @param nothing
    @return nothing
    @see maze_vector
*/
void Maze::constructVector(){
  maze_vector.resize(sizeOfMaze);
  for(int i = 0; i < sizeOfMaze; i++){
    maze_vector[i].resize(sizeOfMaze);
  }
  for(int i = 0; i< sizeOfMaze; i++){
    for(int j = 0; j < sizeOfMaze; j++){
      if(i % 2 == 0 || i == 0){
	    maze_vector[i][j] = '#';
      }
      else if(j % 2 == 0 || j == 0){
	    maze_vector[i][j] = '#';
      }
      else{
	    maze_vector[i][j] = ' ';
      }
    }
  }
  startxcoordwall = randomOddNumberGeneratorForMazeBlock();
  endxcoordwall = randomOddNumberGeneratorForMazeBlock();
  maze_vector[startxcoordwall][0] = ' ';
  maze_vector[endxcoordwall][sizeOfMaze-1] = ' ';
}
/*
    @MichaelTecce created this method
    
    A multi-dimensional array of booleans that holds cells that have been assigned an element
    <p>
    Takes in every coordinate value generated during maze allocation. 
    Then will add each coordinate and its element into the list.
    Odd numbers are the spaces and even numbers are possible walls
    At the end, it ndicates starting point for maze creation, 
    true for made tile, false for undesignated area.

    @param nothing
    @return nothing
    @see maze_vector
*/
void Maze::constructCoordinateList(){
  coordinate_list.resize(sizeOfMaze);
  for(int i = 0; i < sizeOfMaze; i++){
    coordinate_list[i].resize(sizeOfMaze);
    for(int j = 0; j < sizeOfMaze; j++){
      coordinate_list[i][j] = false;
    }
  }
  coordinate_list[startxcoordwall][1] = true;
}
/*
    @MichaelTecce created this method
    
    Uses allocated maze to build the actual maze with paths
    <p>
    First it checks if no cells adjacent to be filled, end program. 
    Else, pick random direction (north,south,east,west) that is 2 spaces from current location.
    Then will take wall down between the two spots. 
    Will set new point to next point, and rerun method
    Also checks that lines only be made on odd numbers
    
    @param int xcoor, ycoor
    @return nothing
    @see maze_vector

*/
void Maze::makeMaze(int xcoor, int ycoor){

  bool nor = canGoNorth(xcoor,ycoor);
  bool sou = canGoSouth(xcoor,ycoor);
  bool eas = canGoEast(xcoor,ycoor);
  bool wes = canGoWest(xcoor,ycoor);
  if(!nor && !sou && !eas && !wes){
        //do nothing
  }else{
    bool hasMoved = false;
    while(!hasMoved){
      
      random_device newnum;
      mt19937 mt(newnum());
      uniform_int_distribution<int> dist(0,3);
      
      switch(dist(mt)){
      case 0:
	if(nor){
	  coordinate_list[xcoor-2][ycoor] = true;
	  maze_vector[xcoor-1][ycoor] = ' ';
	  hasMoved = true;
	  makeMaze(xcoor-2,ycoor);
	}
	break;
      case 1:
	if(sou){
	  coordinate_list[xcoor+2][ycoor] = true;
	  maze_vector[xcoor+1][ycoor] = ' ';
	  hasMoved = true;
	  makeMaze(xcoor+2,ycoor);
	}
	break;
      case 2:
	if(eas){
	  coordinate_list[xcoor][ycoor+2] = true;
	  maze_vector[xcoor][ycoor+1] = ' ';
	  hasMoved = true;
	  makeMaze(xcoor,ycoor+2);
	}
	break;
      case 3:
	if(wes){
	  coordinate_list[xcoor][ycoor-2] = true;
	  maze_vector[xcoor][ycoor-1] = ' ';
	  hasMoved = true;
	  makeMaze(xcoor,ycoor-2);
	}
	break;
      }
    }
    makeMaze(xcoor,ycoor);
  }

}
/*
    @MichaelTecce created this method
    
    Goes North for Wall takedown
    <p>
    Sets return_bool to true. 
    Then checks if the xcoor is a wall. 
    if yes, return_bool is false. 
    Else if coordinate_list is true, return_bool is false.
    Then return return_bool to return to makeMaze 
    and move in North direction. 
    
    @param int xcoor, ycoor
    @return return_bool
    @see coordinate_list[][]
*/
bool Maze::canGoNorth(int xcoor, int ycoor){
  bool return_bool = true;
  if(xcoor == 1){
    return_bool = false;
  }else if(coordinate_list[xcoor-2][ycoor] == true){
    return_bool = false;
  }
  return return_bool;
}
/*
    @MichaelTecce created this method
    
    Goes South for Wall takedown
    <p>
    Sets return_bool to true. 
    Then checks if the xcoor is a wall. 
    if yes, return_bool is false. 
    Else if coordinate_list is true, return_bool is false.
    Then return return_bool to return to makeMaze 
    and move in South direction. 
    
    @param int xcoor, ycoor
    @return return_bool
    @see coordinate_list[][]
*/
bool Maze::canGoSouth(int xcoor, int ycoor){
  bool return_bool = true;
  if(xcoor == (sizeOfMaze - 2)){
    return_bool = false;
  }else if(coordinate_list[xcoor+2][ycoor] == true){
    return_bool = false;
  }
  return return_bool;
}
/*
    @MichaelTecce created this method
    
    Goes East for Wall takedown
    <p>
    Sets return_bool to true. 
    Then checks if the xcoor is a wall. 
    if yes, return_bool is false. 
    Else if coordinate_list is true, return_bool is false.
    Then return return_bool to return to makeMaze 
    and move in East direction. 
    
    @param int xcoor, ycoor
    @return return_bool
    @see coordinate_list[][]
*/
bool Maze::canGoEast(int xcoor, int ycoor){
  bool return_bool = true;
  if(ycoor == (sizeOfMaze - 2)){
    return_bool = false;
  }else if(coordinate_list[xcoor][ycoor+2] == true){
    return_bool = false;
  }
  return return_bool;
}
/*  
    @MichaelTecce created this method
    
    Goes West for Wall takedown
    <p>
    Sets return_bool to true. 
    Then checks if the xcoor is a wall. 
    if yes, return_bool is false. 
    Else if coordinate_list is true, return_bool is false.
    Then return return_bool to return to makeMaze 
    and move in West direction. 
    
    @param int xcoor, ycoor
    @return return_bool
    @see coordinate_list[][]
*/
bool Maze::canGoWest(int xcoor, int ycoor){
  bool return_bool = true;
  if(ycoor == 1){
    return_bool = false;
  }else if(coordinate_list[xcoor][ycoor-2] == true){
    return_bool = false;
  }
  return return_bool;
}
/*
    @ArthurArtene created this method
    
    Creates random value to go pick direction for Maze Creation
    <p>
    declares a new returnInt to use per move.
    Makes a boolean to check for odd value.
    Random number generator used to create number needed. 
    Checks if calue is odd before returning.
    
    @param nothing
    @return returnInt
    @see nothing
*/
int Maze::randomOddNumberGeneratorForMazeBlock(){
  int returnInt = 0;
  bool isOdd = false;

  while(!isOdd){
      random_device oddnum;
      mt19937 mt(oddnum());
      uniform_int_distribution<int> udist(1,sizeOfMaze-2);
      returnInt = udist(mt);

      if(returnInt != 1){
	    isOdd = (returnInt % 2 != 0);
      }else{
	    isOdd = true;
      }
  }
  return returnInt;
}
/*
    @JoshuaRichardKalapati created this method
    
    Maze printer
    <p>
    Creates a visual prepresentation of Maze for viewer to see. 
    Done by using a for loop to print x and y values.
    When solver is done, will call again with solution path.
    
    @param nothing
    @return nothing
    @see maze_vector
*/
void Maze::printMaze(){
  for(int i = 0; i < sizeOfMaze; i++){
    cout << "             ";
    for(int j = 0; j < sizeOfMaze; j++){
      cout <<  maze_vector[i][j] << " ";
    }
    cout << endl;
  }
  cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
}
/*
    @JoshuaRichardKalapati created this method
    
    Checks for wall to use in movement
    <p>
    Takes in given x and y int values.  
    If the point is a '#' then returns true
    Else returns false
    
    @param int x,y
    @return boolean
    @see nothing
*/
bool Maze:: isWall(int x, int y){
  if(maze_vector[x][y]=='#'){
    return true;
  }else{ 
    return false;
  }
}
/*
    @ArthurArtene created this method
    
    Checks for end to use in movement
    <p>
    Takes in given x and y int values.  
    If the point is the same as end then returns true
    Else returns false
    
    @param int x,y
    @return boolean
    @see nothing
*/
bool Maze:: endChecker(int x, int y){
  if(x == endxcoordwall && y == sizeOfMaze-1){
    return true;
  }else{
    return false;
  }
}
/*
    @JoshuaRichardKalapati & @ArthurArtene created this method 
    
    Main solving method for Maze
    <p>
    Takes in an int x and y as well as boolean values. 
    Taken in Boolean values are used to check where the value is coming from.
    
    Checks if the point has a wall above, below, to the right, or the left. 
    Checks where solver came from. 
    Checks for first avaiable direction, will step in the found direction. 
    Slowly moving through the maze till it reaches the end value. 
    Each direction made is put into directions vector
    
    @param int x, y, k & bool fromL, fromT, fromR, fromB
    @return nothing
    @see maze_vector
*/
void Maze:: solver(int x, int y, bool fromL, bool fromT, bool fromR, bool fromB, int k){

  bool leftW = isWall(x,y-1);
  bool topW = isWall(x-1,y);
  bool rightW = isWall(x,y+1);
  bool bottomW = isWall(x+1,y);
  int d = k+1;
  
  if(endChecker(x,y)){
    maze_vector[x][y] = '~';
    directions[k] = "Right.";
    atend = true;
    lastk = k;
  }else if(fromL){
    if(!topW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Up";
      solver(x-1,y,false,false,false,true,d);
    }
    if(!rightW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Right";
      solver(x,y+1,true,false,false,false,d);
    }
    if(!bottomW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Down";
      solver(x+1,y,false,true,false,false,d);
    }
    if(!atend){
      maze_vector[x][y] = ' ';
      directions[k] = "";
    }
  }else if(fromT){
    if(!leftW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Left";
      solver(x,y-1,false,false,true,false,d);
    }
    if(!bottomW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Down";
      solver(x+1,y,false,true,false,false,d);
    }
    if(!rightW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Right";
      solver(x,y+1,true,false,false,false,d);
    }
    if(!atend){
      maze_vector[x][y] = ' ';
      directions[k] = "";
    }
  }else if(fromR){
    if(!bottomW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Down";
      solver(x+1,y,false,true,false,false,d);
    }
    if(!leftW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Left";
      solver(x,y-1,false,false,true,false,d);
    }
    if(!topW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Up";
      solver(x-1,y,false,false,false,true,d);
    }
    if(!atend){
      maze_vector[x][y] = ' ';
      directions[k] = "";
    }
  }else if(fromB){
    if(!leftW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Left";
      solver(x,y-1,false,false,true,false,d);
    }
    if(!topW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Up";
      solver(x-1,y,false,false,false,true,d);
    }
    if(!rightW && !atend){
      maze_vector[x][y] = '~';
      directions[k] = "Right";
      solver(x,y+1,true,false,false,false,d);
    }
    if(!atend){
      maze_vector[x][y] = ' ';
      directions[k] = "";
    }
  }
}
/*
    @JoshuaRichardKalapati created this method
    
    Print directions for the solution.
    <p>
    Creates a string that will hold all directions. 
    Runs a loop till it reaches the end. If the value isnt 
    the end element, will print whatever is in directions at i
    and then put a comma. At the end, will print final direction.
    Afterwords, will print out directions string for final step.
    
    @param nothing
    @return nothing
    @see direction_string & directions[]
*/
void Maze:: printDirections(){
  string directions_string = "Solution directions:\n";
  for(int i = 0; i < lastk; i++){
    if(i == lastk - 1){
      directions_string.append("");
      directions_string.append(directions[i]);
    }else{
      directions_string.append(directions[i]);
      directions_string.append(", ");
    }
  }
  cout << directions_string << endl;
}
/*
    @ArthurArtene formated this method
    
    Main
    <p>
    Asks for size and put it into Maze class to use.
    
    @param nothing
    @return nothing
    @see Class Maze, method Maze::Maze
*/
int main(){
  int size;
  cout << "Please give size of maze wanted: ";
  cin >> size;
  cout << endl;
  Maze* mazemade = new Maze(size);
}


