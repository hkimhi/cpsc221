#include "decoder.h"
#include "queue.h"
#include "stack.h"
using namespace std;

decoder::decoder(const PNG &tm, pair<int, int> s)
    : start(s), mapImg(tm)
{
   pathPts.push_back(start);
   maze = vector<vector<bool>>(mapImg.width(), vector<bool>(mapImg.height()));
   vector<vector<int>> distance(mapImg.width(), vector<int>(mapImg.height()));
   vector<vector<pair<int, int>>> parent(mapImg.width(), vector<pair<int, int>>(mapImg.height()));
   pair<int, int> curr;
   Stack<pair<int, int>> reverseSolution;
   Queue<pair<int, int>> bfs;

   maze[start.first][start.second] = true;
   distance[start.first][start.second] = 0;
   parent[start.first][start.second] = start;
   bfs.enqueue(start);


   while (!bfs.isEmpty())
   {
      curr = bfs.dequeue();

      for (pair<int, int> neighbor : neighbors(curr))
      {
         if (good(maze, distance, curr, neighbor))
         {
            maze[neighbor.first][neighbor.second] = true;
            distance[neighbor.first][neighbor.second] = distance[curr.first][curr.second] + 1;
            parent[neighbor.first][neighbor.second] = curr;
            bfs.enqueue(neighbor);
         }
      }
   }



   while (curr != start)
   {
      reverseSolution.push(curr);
      curr = parent[curr.first][curr.second];
   }

   while (!reverseSolution.isEmpty())
   {
      pathPts.push_back(reverseSolution.pop());
   }
}

PNG decoder::renderSolution()
{
   PNG solution = PNG(mapImg);

   for (pair<int, int> point : pathPts)
   {
      RGBAPixel *pixel = solution.getPixel(point.first, point.second);
      pixel->r = 255;
      pixel->g = 0;
      pixel->b = 0;
   }

   return solution;
}

PNG decoder::renderMaze()
{
   PNG shadowMaze = PNG(mapImg);

   vector<vector<bool>> visited(shadowMaze.width(), vector<bool>(shadowMaze.height()));

   Queue<pair<int, int>> bfs;
   setGrey(shadowMaze, start);
   visited[start.first][start.second] = true;
   bfs.enqueue(start);

   while (!bfs.isEmpty())
   {
      pair<int, int> curr = bfs.dequeue();

      for (pair<int, int> neighbor : neighbors(curr))
      {
         if (neighbor.first >= 0 && neighbor.first < (int)mapImg.width() && neighbor.second >= 0 && neighbor.second < (int)mapImg.height())
         {
            if (maze[neighbor.first][neighbor.second] && !visited[neighbor.first][neighbor.second])
            {
               visited[neighbor.first][neighbor.second] = true;
               setGrey(shadowMaze, neighbor);
               bfs.enqueue(neighbor);
            }
         }
      }
   }

   for (int i = start.first - 3; i <= start.first + 3; i++)
   {
      for (int j = start.second - 3; j <= start.second + 3; j++)
      {
         if (i >= 0 && i < (int)shadowMaze.width() && j >= 0 && j < (int)shadowMaze.height())
         {
            RGBAPixel *currPixel = shadowMaze.getPixel(i, j);
            currPixel->r = 255;
            currPixel->g = 0;
            currPixel->b = 0;
         }
      }
   }
   return shadowMaze;
}

void decoder::setGrey(PNG &im, pair<int, int> loc)
{
   RGBAPixel *pixel = im.getPixel(loc.first, loc.second);

   pixel->r = 2 * (pixel->r / 4);
   pixel->g = 2 * (pixel->g / 4);
   pixel->b = 2 * (pixel->b / 4);
}

pair<int, int> decoder::findSpot()
{
   return pathPts.back();
}

int decoder::pathLength()
{
   return pathPts.size();
}

bool decoder::good(vector<vector<bool>> &v, vector<vector<int>> &d, pair<int, int> curr, pair<int, int> next)
{
   if (next.first < 0 || next.first >= (int)mapImg.width() || next.second < 0 || next.second >= (int)mapImg.height())
   {
      return false;
   }

   if (v[next.first][next.second])
   {
      return false;
   }

   RGBAPixel* currPixel = mapImg.getPixel(next.first, next.second);

   if (!compare(*currPixel, d[curr.first][curr.second]))
   {  
      return false;
   }

   return true;
}

vector<pair<int, int>> decoder::neighbors(pair<int, int> curr)
{
   vector<pair<int, int>> neighbors = vector<pair<int, int>>();
   neighbors.push_back(pair<int, int>(curr.first - 1, curr.second));
   neighbors.push_back(pair<int, int>(curr.first, curr.second + 1));
   neighbors.push_back(pair<int, int>(curr.first + 1, curr.second));
   neighbors.push_back(pair<int, int>(curr.first, curr.second - 1));

   return neighbors;
}

bool decoder::compare(RGBAPixel p, int d)
{
   // int rBits = (p.r & 0b11) << 4;
   // int gBits = (p.g & 0b11) << 2;
   // int bBits = p.b & 0b11;
   // int distance = rBits | gBits | bBits;
   return ((d + 1) % 64 == ((p.r % 4) * 16 + (p.g % 4) * 4 + (p.b % 4)));
}
