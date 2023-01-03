#include <iostream>
#include "API.cpp"
#include <bits/stdc++.h>
using namespace std;

int currentX = 0;
int currentY = 0;

void log(const std::string& text) {
    std::cerr << text << std::endl  ;
}
typedef struct cell
{
  bool FrontWall;
  bool LeftWall;
  bool RightWall;
  int VisitedCount;
}Cell;
char currentDir = 'F';
char latestDir = 'N';
Cell Maze[16][16] {{0}};

 class Cellx {
 public:
    int row;
    int col;

    Cellx(int _row, int _col) {
        row = _row;
        col = _col;
    }
    string toString() {
        return "{" + to_string(col) + ", " + to_string(row) + "}";
    }
};

bool AllCellsVisited()
{
  for(int i = 0; i < 16; i++)
  {
    for(int j = 0; j < 16; j++)
    {
      if(Maze[i][j].VisitedCount == 0)
      {
        return false;
      }
    }
  }
  return true;
}

//This function is responsible for controlling how the current robot direction changes after a rotation. Ex: When the robot is moving right and rotates to the right, 
//his current movment direction is the front direction. After moving, it updates the x and y coordinates of the robot. Ex: Moving in the left direction decreases the 
// x coordinate by 1 for each cell, and vice verse
void MoveInDirection(char dir)
{

  if(dir == 'F')
  {
    if(currentDir == 'F')
    {
      currentY += 1;
      API::moveForward();
    }

    else if(currentDir == 'R')
    {
      currentX += 1;
      API::moveForward();
    }

    else if(currentDir == 'L')
    {
      currentX -= 1;
      API::moveForward();
    }

    else if(currentDir == 'B')
    {
      currentY -= 1;
      API::moveForward();
    }
  }

  else if(dir == 'R')
  {
    API::turnRight();
    if(currentDir == 'F')
    {
      currentX += 1;
      currentDir = 'R';
      API::moveForward();
    }

    else if(currentDir == 'R')
    {
      currentY -= 1;
      currentDir = 'B';
      API::moveForward();
    }

    else if(currentDir == 'L')
    {
      currentY += 1;
      currentDir = 'F';
      API::moveForward();
    }

    else if(currentDir == 'B')
    {
      currentX -= 1;
      currentDir = 'L';
      API::moveForward();
    }
  }

  else if(dir == 'L')
  {
    API::turnLeft();
    if(currentDir == 'F')
    {
      currentX -= 1;
      currentDir = 'L';
      API::moveForward();
    }

    else if(currentDir == 'R')
    {
      currentY += 1;
      currentDir = 'F';
      API::moveForward();
    }

    else if(currentDir == 'L')
    {
      currentY -= 1;
      currentDir = 'B';
      API::moveForward();
    }

    else if(currentDir == 'B')
    {
      currentX += 1;
      currentDir = 'R';
      API::moveForward();
    }
  }

  else if(dir == 'B')
  {
    API::turnRight();
    API::turnRight();
    if(currentDir == 'F')
    {
      currentY -= 1;
      currentDir = 'B';
      API::moveForward();
    }

    else if(currentDir == 'R')
    {
      currentX -= 1;
      currentDir = 'L';
      API::moveForward();
    }

    else if(currentDir == 'L')
    {
      currentX += 1;
      currentDir = 'R';
      API::moveForward();
    }

    else if(currentDir == 'B')
    {
      currentY += 1;
      currentDir = 'F';
      API::moveForward();
    }
  }

  if(Maze[currentX][currentY].VisitedCount == 0)
  {
    if(currentDir == 'F')
    {
      Maze[currentX][currentY].FrontWall = API::wallFront();
      Maze[currentX][currentY].LeftWall = API::wallLeft();
      Maze[currentX][currentY].RightWall = API::wallRight();
    }
    else if(currentDir == 'R')
    {
      Maze[currentX][currentY].FrontWall = API::wallLeft();
      Maze[currentX][currentY].LeftWall = 0;
      Maze[currentX][currentY].RightWall = API::wallFront();
    }
    else if(currentDir == 'L')
    {
      Maze[currentX][currentY].FrontWall = API::wallRight();
      Maze[currentX][currentY].RightWall = 0;
      Maze[currentX][currentY].LeftWall = API::wallFront();
    }
    else if(currentDir == 'B')
    {
      Maze[currentX][currentY].FrontWall = 0;
      Maze[currentX][currentY].RightWall = API::wallLeft();
      Maze[currentX][currentY].LeftWall = API::wallRight();
    }

  }

  if(Maze[currentX][currentY].VisitedCount != 123)
  {
    Maze[currentX][currentY].VisitedCount += 1;
  }
}

//Finds which path around the robot was visited the least and returns whether it's to the front, right, left, or back of the robot. 
char GetLeastVisitedPath(char currDir)
{
  if(API::wallFront() && API::wallRight() && API::wallLeft())
  {
    Maze[currentX][currentY].VisitedCount = 125;
    return 'B';
  }
  if(currDir == 'F')
  {
    if((API::wallLeft() || Maze[currentX - 1][currentY].VisitedCount == 123) && (API::wallRight() || Maze[currentX + 1][currentY].VisitedCount == 123) && !API::wallFront())
    {
      if(Maze[currentX][currentY + 1].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }
      else
      {
        if(Maze[currentX][currentY + 1].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'F';
        }

        else
        {
          return 'B';
        }

      }
    }

    else if((API::wallFront() || Maze[currentX][currentY + 1].VisitedCount == 123) && (API::wallLeft() || Maze[currentX - 1][currentY].VisitedCount == 123) && !API::wallRight())
    {
      if(Maze[currentX + 1][currentY].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }

      else
      {
        if(Maze[currentX + 1][currentY].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'R';
        }

        else
        {
          return 'B';
        }
      }
    }

    else if((API::wallRight() || Maze[currentX + 1][currentY].VisitedCount == 123) && !API::wallLeft() && (API::wallFront() || Maze[currentX][currentY + 1].VisitedCount == 123))
    {
      if(Maze[currentX - 1][currentY].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }

      else
      {
        if(Maze[currentX - 1][currentY].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'L';
        }

        else
        {
          return 'B';
        }
      }
    }

    else
    {
      if((!API::wallLeft() && Maze[currentX - 1][currentY].VisitedCount != 123) && (!API::wallRight() && Maze[currentX + 1][currentY].VisitedCount != 123) && (!API::wallFront() && Maze[currentX][currentY + 1].VisitedCount != 123))
      {
        if(Maze[currentX][currentY + 1].VisitedCount <= Maze[currentX + 1][currentY].VisitedCount && Maze[currentX][currentY + 1].VisitedCount <= Maze[currentX - 1][currentY].VisitedCount)
        {
          return 'F';
        }

        else if(Maze[currentX + 1][currentY].VisitedCount <= Maze[currentX - 1][currentY].VisitedCount)
        {
          return 'R';
        }


        else
        {
          return 'L';
        }
      }

      else if (API::wallLeft() || Maze[currentX - 1][currentY].VisitedCount == 123)
      {
        if(Maze[currentX][currentY + 1].VisitedCount <= Maze[currentX + 1][currentY].VisitedCount)
        {
          return 'F';
        }
        else
        {
          return 'R';
        }
      }

      else if(API::wallRight() || Maze[currentX + 1][currentY].VisitedCount == 123)
      {
        if(Maze[currentX][currentY + 1].VisitedCount <= Maze[currentX - 1][currentY].VisitedCount)
        {
          return 'F';
        }
        else
        {
          return 'L';
        }
      }

      else if(API::wallFront() || Maze[currentX][currentY + 1].VisitedCount == 123)
      {
        if(Maze[currentX + 1][currentY].VisitedCount <= Maze[currentX - 1][currentY].VisitedCount)
        {
          return 'R';
        }
        else
        {
          return 'L';
        }
      }

      else
      {
        return 'F';
      }
    }

  }

  else if(currDir == 'R')
  {
    if((API::wallLeft() || Maze[currentX][currentY + 1].VisitedCount == 123) && (API::wallRight() || Maze[currentX][currentY - 1].VisitedCount == 123) && !API::wallFront())
    {
      if(Maze[currentX + 1][currentY].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }
      else
      {
        if(Maze[currentX + 1][currentY].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'F';
        }

        else
        {
          return 'B';
        }

      }
    }

    else if((API::wallFront() || Maze[currentX + 1][currentY].VisitedCount == 123) && (API::wallLeft() || Maze[currentX][currentY + 1].VisitedCount == 123) && !API::wallRight())
    {
      if(Maze[currentX][currentY - 1].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }

      else
      {
        if(Maze[currentX][currentY - 1].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'R';
        }

        else
        {
          return 'B';
        }
      }
    }

    else if((API::wallRight() || Maze[currentX][currentY - 1].VisitedCount == 123) && !API::wallLeft() && (API::wallFront() || Maze[currentX + 1][currentY].VisitedCount == 123))
    {
      if(Maze[currentX][currentY + 1].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }

      else
      {
        if(Maze[currentX][currentY + 1].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'L';
        }

        else
        {
          return 'B';
        }
      }
    }

    else
    {
      if((!API::wallLeft() && Maze[currentX][currentY + 1].VisitedCount != 123) && (!API::wallRight() && Maze[currentX][currentY - 1].VisitedCount != 123) && (!API::wallFront() && Maze[currentX + 1][currentY].VisitedCount != 123))
      {
        if(Maze[currentX + 1][currentY].VisitedCount <= Maze[currentX][currentY - 1].VisitedCount && Maze[currentX + 1][currentY].VisitedCount <= Maze[currentX][currentY + 1].VisitedCount)
        {
          return 'F';
        }
        else if(Maze[currentX][currentY - 1].VisitedCount <= Maze[currentX][currentY + 1].VisitedCount)
        {
          return 'R';
        }
        else
        {
          return 'L';
        }
      }

      else if(API::wallLeft() || Maze[currentX][currentY + 1].VisitedCount == 123)
      {
        if(Maze[currentX + 1][currentY].VisitedCount <= Maze[currentX][currentY - 1].VisitedCount)
        {
          return 'F';
        }
        else
        {
          return 'R';
        }
      }

      else if(API::wallRight() || Maze[currentX + 1][currentY].VisitedCount == 123)
      {
        if(Maze[currentX + 1][currentY].VisitedCount <= Maze[currentX][currentY + 1].VisitedCount)
        {
          return 'F';
        }
        else
        {
          return 'L';
        }
      }

      else if(API::wallFront() || Maze[currentX + 1][currentY].VisitedCount == 123)
      {
        if(Maze[currentX][currentY - 1].VisitedCount <= Maze[currentX][currentY + 1].VisitedCount)
        {
          return 'R';
        }
        else
        {
          return 'L';
        }
      }

      else
      {
        return 'F';
      }
    }

  }

  else if(currDir == 'L')
  {
    if((API::wallLeft() || Maze[currentX][currentY - 1].VisitedCount == 123) && (API::wallRight() || Maze[currentX][currentY + 1].VisitedCount == 123) && !API::wallFront())
    {
      if(Maze[currentX - 1][currentY].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }
      else
      {
        if(Maze[currentX - 1][currentY].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'F';
        }

        else
        {
          return 'B';
        }

      }
    }

    else if((API::wallFront() || Maze[currentX - 1][currentY].VisitedCount == 123) && (API::wallLeft() || Maze[currentX][currentY - 1].VisitedCount == 123) && !API::wallRight())
    {
      if(Maze[currentX][currentY - 1].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }

      else
      {
        if(Maze[currentX][currentY + 1].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'R';
        }

        else
        {
          return 'B';
        }
      }
    }

    else if((API::wallRight() || Maze[currentX][currentY + 1].VisitedCount == 123) && !API::wallLeft() && (API::wallFront() || Maze[currentX - 1][currentY].VisitedCount == 123))
    {
      if(Maze[currentX][currentY - 1].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }

      else
      {
        if(Maze[currentX][currentY - 1].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'L';
        }

        else
        {
          return 'B';
        }
      }
    }

    else
    {
      if((!API::wallLeft() && Maze[currentX][currentY - 1].VisitedCount != 123) && (!API::wallRight() && Maze[currentX][currentY + 1].VisitedCount != 123) && (!API::wallFront() && Maze[currentX - 1][currentY].VisitedCount != 123))
      {
        if(Maze[currentX - 1][currentY].VisitedCount <= Maze[currentX][currentY + 1].VisitedCount && Maze[currentX - 1][currentY].VisitedCount <= Maze[currentX][currentY - 1].VisitedCount)
        {
          return 'F';
        }
        else if(Maze[currentX][currentY + 1].VisitedCount <= Maze[currentX][currentY - 1].VisitedCount)
        {
          return 'R';
        }
        else
        {
          return 'L';
        }
      }

      else if(API::wallLeft() || Maze[currentX][currentY - 1].VisitedCount == 123)
      {
        if(Maze[currentX - 1][currentY].VisitedCount <= Maze[currentX][currentY + 1].VisitedCount)
        {
          return 'F';
        }
        else
        {
          return 'R';
        }
      }

      else if(API::wallRight() || Maze[currentX - 1][currentY].VisitedCount == 123)
      {
        if(Maze[currentX - 1][currentY].VisitedCount <= Maze[currentX][currentY - 1].VisitedCount)
        {
          return 'F';
        }
        else
        {
          return 'L';
        }
      }

      else if(API::wallFront() || Maze[currentX - 1][currentY].VisitedCount == 123)
      {
        if(Maze[currentX][currentY + 1].VisitedCount <= Maze[currentX][currentY - 1].VisitedCount)
        {
          return 'R';
        }
        else
        {
          return 'L';
        }
      }

      else
      {
        return 'F';
      }
    }
  }

  else //currDir == 'B'
  {
    if((API::wallLeft() || Maze[currentX + 1][currentY].VisitedCount == 123) && (API::wallRight() || Maze[currentX - 1][currentY].VisitedCount == 123) && !API::wallFront())
    {
      if(Maze[currentX][currentY - 1].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }
      else
      {
        if(Maze[currentX][currentY - 1].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'F';
        }

        else
        {
          return 'B';
        }

      }
    }

    else if((API::wallFront() || Maze[currentX][currentY - 1].VisitedCount == 123) && (API::wallLeft() || Maze[currentX + 1][currentY].VisitedCount == 123) && !API::wallRight())
    {
      if(Maze[currentX - 1][currentY].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }

      else
      {
        if(Maze[currentX - 1][currentY].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'R';
        }

        else
        {
          return 'B';
        }
      }
    }

    else if((API::wallRight() || Maze[currentX - 1][currentY].VisitedCount == 123) && !API::wallLeft() && (API::wallFront() || Maze[currentX][currentY - 1].VisitedCount == 123))
    {
      if(Maze[currentX + 1][currentY].VisitedCount == 123)
      {
        //Maze[currentX][currentY].VisitedCount = 123;
        return 'B';
      }

      else
      {
        if(Maze[currentX + 1][currentY].VisitedCount <= Maze[currentX][currentY].VisitedCount)
        {
          return 'L';
        }

        else
        {
          return 'B';
        }
      }
    }

    else
    {
      if((!API::wallLeft() && Maze[currentX + 1][currentY].VisitedCount != 123) && (!API::wallRight() && Maze[currentX - 1][currentY].VisitedCount != 123) && (!API::wallFront() && Maze[currentX][currentY - 1].VisitedCount != 123))
      {
        if(Maze[currentX][currentY - 1].VisitedCount <= Maze[currentX - 1][currentY].VisitedCount && Maze[currentX][currentY - 1].VisitedCount <= Maze[currentX + 1][currentY].VisitedCount)
        {
          return 'F';
        }
        else if(Maze[currentX - 1][currentY].VisitedCount <= Maze[currentX + 1][currentY].VisitedCount)
        {
          return 'R';
        }
        else
        {
          return 'L';
        }
      }

      else if (API::wallLeft() || Maze[currentX + 1][currentY].VisitedCount == 123)
      {
        if(Maze[currentX][currentY - 1].VisitedCount <= Maze[currentX - 1][currentY].VisitedCount)
        {
          return 'F';
        }
        else
        {
          return 'R';
        }
      }

      else if(API::wallRight() || Maze[currentX - 1][currentY].VisitedCount == 123)
      {
        if(Maze[currentX][currentY - 1].VisitedCount <= Maze[currentX + 1][currentY].VisitedCount)
        {
          return 'F';
        }
        else
        {
          return 'L';
        }
      }

      else if(API::wallFront() || Maze[currentX][currentY - 1].VisitedCount == 123)
      {
        if(Maze[currentX - 1][currentY].VisitedCount <= Maze[currentX + 1][currentY].VisitedCount)
        {
          return 'R';
        }
        else
        {
          return 'L';
        }
      }

      else
      {
        return 'F';
      }
    }

  }
}

//The movement algorithm, which works by going in a loop where always the least visited path by the robot is visited untill all the cells are marked as visited
//When a new cell is visited, the robot maps its walls into its corrosponding x, y coordinates in the Maze array
void Tremax()
{
  //(currentX != 8 && currentY != 8) || (currentX != 7 && currentY != 8) || (currentX != 7 && currentY != 7) || (currentX != 8 && currentY != 7)
  Maze[currentX][currentY].FrontWall = API::wallFront();
  Maze[currentX][currentY].LeftWall = API::wallLeft();
  Maze[currentX][currentY].RightWall = API::wallRight();
  while(AllCellsVisited() == false)
  {
    if(AllCellsVisited() == true)
    {
      break;
    }

    MoveInDirection(GetLeastVisitedPath(currentDir));
    //API::setText(15, 14, s3);
    //API::setText(14, 15, s4);
    //API::setText(14, 14, s5);
  }
}

void log2(const std::string& text) {
    std::cerr << text;
}
struct Node
{
    // (x, y) represents matrix cell coordinates, and
    // `dist` represents their minimum distance from the source
    int x, y, dist;
};

// Below arrays detail all four possible movements from a cell
int row[] = { -1, 0, 0, 1 };
int col[] = { 0, -1, 1, 0 };

// Function to check if it is possible to go to position (row, col)
// from the current position. The function returns false if (row, col)
// is not a valid position or has a value 0 or already visited.
bool isValid(vector<vector<int>> const &mat, vector<vector<bool>> &visited,
        int row, int col) {
    return (row >= 0 && row < mat.size()) && (col >= 0 && col < mat[0].size())
        && mat[row][col] != 1 && !visited[row][col];
}

// Find the shortest possible route in a matrix `mat` from source
// cell (i, j) to destination cell (x, y)
vector<int> x;

int findShortestPathLength(vector<vector<int>> const &mat, pair<int, int> &src, pair<int, int> &dest)
{
    // base case: invalid input
    if (mat.size() == 0 || mat[src.first][src.second] == 1) {
        return -1;
    }
    // `M � N` matrix
    int M = mat.size();
    int N = mat[0].size();

    // construct a `M � N` matrix to keep track of visited cells
    vector<vector<bool>> visited;
    visited.resize(M, vector<bool>(N));

    // create an empty queue
    queue<Node> q;

    // get source cell (i, j)
    int i = src.first;
    int j = src.second;

    // mark the source cell as visited and enqueue the source node
    visited[i][j] = true;
    q.push({i, j, 0});

    // stores length of the longest path from source to destination
    int min_dist = INT_MAX;

    // loop till queue is empty
    while (!q.empty())
    {
        // dequeue front node and process it
        Node node = q.front();
        q.pop();

        // (i, j) represents a current cell, and `dist` stores its
        // minimum distance from the source
        int i = node.x, j = node.y, dist = node.dist;


        // if the destination is found, update `min_dist` and stop
        if (i == dest.first && j == dest.second)
        {
            min_dist = dist;
            break;
        }

        // check for all four possible movements from the current cell
        // and enqueue each valid movement
        for (int k = 0; k < 4; k++)
        {
            // check if it is possible to go to position
            // (i + row[k], j + col[k]) from current position
            if (isValid(mat, visited, i + row[k], j + col[k]))
            {
                // mark next cell as visited and enqueue it
                visited[i + row[k]][j + col[k]] = true;
                q.push({ i + row[k], j + col[k], dist + 1 });
            }
        }
    }

    if (min_dist != INT_MAX) {
        return min_dist;
    }

    return -1;
}

vector<vector<int>> vc;
//Call the maze exploration and mapping algorithm. Then start compiling a matrix of 0s and 1s that contain the maze information, where 0s represent empty spaces
// and 1s represent walls. By alternatingly making two strings, one that carries the empty cells and walls within the x-xis, and one that does the same with the y-axis 
void mapping(){
    Tremax();
    for(int i = 0; i < 16; i++)
    {
      vector<int> compiledStringLeft;
      vector<int> compiledStringUp;
      for(int j = 0; j < 16; j++)
      {
        compiledStringLeft.push_back(0);
        compiledStringLeft.push_back(Maze[j][i].RightWall);

        compiledStringUp.push_back(Maze[j][i].FrontWall);

        compiledStringUp.push_back(1);

      }

      vc.push_back(compiledStringLeft);
      vc.push_back(compiledStringUp);

}
vector<string> fin;
    for(int i = 0; i < 32; i++){
            string temp = "";
        for(int j = 0; j < 32; j++){
            temp += to_string(vc[i][j]);
            temp += " ";
        }
        fin.push_back(temp);
    }

    for(int i = fin.size() - 1; i >= 0; i--)
        {
            log(fin[i]);
        }
}

void shortpathlength(){
    pair<int, int> src = make_pair(0, 0);
    pair<int, int> dest = make_pair(16, 16);

    int min_dist = findShortestPathLength(vc, src, dest);
    log(to_string(min_dist));
}

bool isValid(int row, int col, int maxRow, int maxCol) {
    return row >= 0 && row < maxRow && col >= 0 && col < maxCol;
}

void addNeighbors(Cellx cell, vector<Cellx> &cells, int maxRow, int maxCol) {
    int ds[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < 4; i++) {
        int row = cell.row + ds[i][0];
        int col = cell.col + ds[i][1];
        if (isValid(row, col, maxRow, maxCol))
            cells.push_back(Cellx(row, col));
    }
}

Cellx getNeighbor(Cellx cell, int distance, vector<vector<int>> distances) {
    int ds[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (int i = 0; i < 4; i++) {
        int row = cell.row + ds[i][0];
        int col = cell.col + ds[i][1];
        if (isValid(row, col, distances.size(), distances[0].size())&& distances[row][col] == distance)
            return Cellx(row, col);
    }
    return Cellx(0, 0);
}

//Fill in the stack of cells with the shortest path route towards the center 
int GetShortestPath(vector<vector<int>> mat, Cellx start, Cellx dist, stack<Cellx> &path)
{
    vector<vector<int>> distances(mat.size(), vector<int>(mat.size(), INT_MAX));
    int distance = 0;
    vector<Cellx> currentCells;
    currentCells.push_back(start);
    while(distances[dist.row][dist.col] == INT_MAX && currentCells.size() != 0)
        {
            if(distances[dist.row][dist.col] != INT_MAX)
                {
                    break;
                }
            vector<Cellx> nextCells;
            for(int i = 0; i < currentCells.size(); i++)
                {
                    int currRow = currentCells[i].row;
                    int currCol = currentCells[i].col;
                    if(distances[currRow][currCol] == INT_MAX && mat[currRow][currCol] != 1)
                        {
                            distances[currRow][currCol] = distance;
                            addNeighbors(currentCells[i], nextCells, mat.size(), mat[0].size());
                        }
                }
            currentCells = nextCells;
            distance++;
        }

        if(distances[dist.row][dist.col] < INT_MAX)
            {
                log("I won");
                Cellx cell = dist;
                path.push(dist);
                for(int d = distances[dist.row][dist.col] - 1; d >= 0; d--)
                    {
                        cell = getNeighbor(cell, d, distances);
                        path.push(cell);
                    }
            }

        return distances[dist.row][dist.col];

}

//Find the center in a given matrix of cells. The center is defined as a point that has all space around it as empty (all cells around it have a value of 0)
Cellx findend(vector<vector<int>> mat){
  Cellx cell(0, 0);
  for(int i = 0; i < mat.size(); i++){
    for(int j = 0; j < mat.size(); j++){
      if((mat[i][j] ==1) && (mat[i][j+1] == 0) && (mat[i+1][j+1] == 0) && (mat[i+1][j] == 0) && (mat[i+1][j-1] == 0) && (mat[i][j - 1] == 0) && (mat[i-1][j-1] == 0) && (mat[i-1][j] == 0) && (mat[i-1][j+1] == 0))
      {
        log(to_string(i) + " " + to_string(j));
        return Cellx(i - 1, j-1);
      }
    }
  }
  return cell;
}

int main(int argc, char* argv[])
{
mapping();
API::ackReset();
//shortpathlength();
stack<Cellx> path;
Cellx start(0, 0);
Cellx endc = findend(vc);
GetShortestPath(vc, start, endc, path);
    int lastX = 0;
    int lastY = 0;
    vector<char> dirs;
    if(!API::wallFront())
        {
            currentDir = 'F';
        }
    else if(!API::wallRight())
        {
            currentDir = 'R';
            API::turnRight();
        }
        path.pop();
    while (!path.empty())
    {
        lastX = (path.top()).col;
        lastY = (path.top()).row;
        log((path.top()).toString());
        path.pop();
        log(to_string(currentDir));
        if(lastX == (path.top()).col)
            {
                if((path.top()).row > lastY)
                    {
                        if(currentDir == 'F')
                            {
                                MoveInDirection('F');
                            }
                        else if(currentDir == 'L')
                            {
                                MoveInDirection('R');
                            }
                        else if(currentDir == 'R')
                            {
                                MoveInDirection('L');
                            }
                    }
                    else
                        {
                        if(currentDir == 'B')
                            {
                                MoveInDirection('F');
                            }
                        else if(currentDir == 'L')
                            {
                                MoveInDirection('L');
                            }
                        else if(currentDir == 'R')
                            {
                                MoveInDirection('R');
                            }
                        }

            }
        else
            {
                if((path.top()).col > lastX)
                {
                        if(currentDir == 'R')
                            {
                                MoveInDirection('F');
                            }
                        else if(currentDir == 'F')
                            {
                                MoveInDirection('R');
                            }
                        else if(currentDir == 'B')
                            {
                                MoveInDirection('L');
                            }
                }
                else
                {
                        if(currentDir == 'L')
                            {
                                MoveInDirection('F');
                            }
                        else if(currentDir == 'F')
                            {
                                MoveInDirection('L');
                            }
                        else if(currentDir == 'B')
                            {
                                MoveInDirection('R');
                            }
                }

            }
            log((path.top()).toString());
            path.pop();
    }
}
