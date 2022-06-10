/*
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  @authors: Arthur Artene, Joshua Richard Kalapati, Michael Tecce
  Class: Intro to Computer Science CS 174 Spring 2020
  Assignment: Final Group Project: Maze Generator and Solver 
  Due 5/13/2020
  
  Header and Comments made by @ArthurArtene
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef FINALPROJ_H
#define FINALPROJ_H
using namespace std;

/*
      Class holding all public and private methods, constructors, destructor, and elements
      <p>
      Class essentially has every part needed for the program to work.
      First are the global vectors of coordinate_list, maze_vector, and direction.
      Next all global int values needed. 
      Next are global boolean conditionals.
      Finally are methods used throughout the file.
      
      @param nothing
      @return nothing
      @see class Maze
*/
class Maze{
public:
  int numOfCells;
   Maze(int size);
  ~Maze();
private:
  vector<vector<char>> maze_vector;
  vector<vector<bool>> coordinate_list;
  vector<string> directions;
  int sizeOfMaze;
  int row_size;
  int col_size;
  int lastk;
  int startxcoordwall;
  int endxcoordwall;
  bool deadend = false;
  bool atend = false; 
  bool canGoNorth(int xcoor, int ycoor);
  bool canGoSouth(int xcoor, int ycoor);
  bool canGoEast(int xcoor, int ycoor);
  bool canGoWest(int xcoor, int ycoor);
  bool isWall(int x, int y);
  bool endChecker(int x, int y);
  int randomOddNumberGeneratorForMazeBlock();
  void makeMaze(int xcoor, int ycoor);
  void constructVector();
  void constructCoordinateList();
  void printMaze();
  void solver(int x, int y, bool fromL, bool fromT, bool fromR, bool fromB, int k);
  void printDirections();
};

#endif
