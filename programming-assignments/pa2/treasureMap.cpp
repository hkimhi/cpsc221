#include "treasureMap.h"
#include "queue.h"
using namespace std;

treasureMap::treasureMap(const PNG &baseim, const PNG &mazeim, pair<int, int> s)
{
    base = baseim;
    maze = mazeim;
    start = s;
}

void treasureMap::setGrey(PNG &im, pair<int, int> loc)
{
    RGBAPixel *pixel = im.getPixel(loc.first, loc.second);
    pixel->r = 2 * (pixel->r / 4);
    pixel->g = 2 * (pixel->g / 4);
    pixel->b = 2 * (pixel->b / 4);
}

void treasureMap::setLOB(PNG &im, pair<int, int> loc, int d)
{
    RGBAPixel *pixel = im.getPixel(loc.first, loc.second);

    int rMask = (d & 0b110000) >> 4;
    int gMask = (d & 0b001100) >> 2;
    int bMask = d & 0b000011;

    pixel->r = pixel->r & rMask;
    pixel->g = pixel->g & gMask;
    pixel->b = pixel->b & bMask;
}

PNG treasureMap::renderMap()
{
    PNG tMap = PNG(base);

    vector<vector<bool>> visited(tMap.height(), vector<bool>(tMap.width()));
    vector<vector<int>> distance(tMap.height(), vector<int>(tMap.width()));

    Queue<pair<int, int>> bfs;

    visited[start.first][start.second] = true;
    distance[start.first][start.second] = 0;
    setLOB(tMap, start, 0);
    bfs.enqueue(start);

    while (!bfs.isEmpty())
    {
        pair<int, int> curr = bfs.dequeue();

        for (pair<int, int> neighbor : neighbors(curr))
        {
            if (good(visited, curr, neighbor))
            {
                visited[neighbor.first][neighbor.second] = true;
                distance[neighbor.first][neighbor.second] = distance[curr.first][curr.second] + 1;
                setLOB(tMap, neighbor, distance[neighbor.first][neighbor.second]);
                bfs.enqueue(neighbor);
            }
        }
    }

    return tMap;
}

PNG treasureMap::renderMaze()
{
    PNG shadowMaze = PNG(base);

    vector<vector<bool>> visited(shadowMaze.height(), vector<bool>(shadowMaze.width()));

    // BFS to paint shadow
    Queue<pair<int, int>> bfs;
    setGrey(shadowMaze, start);
    visited[start.first][start.second] = true;
    bfs.enqueue(start);

    while (!bfs.isEmpty())
    {
        pair<int, int> curr = bfs.dequeue();

        for (pair<int, int> neighbor : neighbors(curr))
        {
            if (good(visited, curr, neighbor))
            {
                visited[neighbor.first][neighbor.second] = true;
                setGrey(shadowMaze, neighbor);
                bfs.enqueue(neighbor);
            }
        }
    }

    // Make Red Square
    for (int i = start.first - 3; i <= start.first + 3; i++)
    {
        for (int j = start.second - 3; j <= start.second + 3; j++)
        {
            if (i < 0 || i >= (int) shadowMaze.width() || j < 0 || j >= (int) shadowMaze.height())
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

bool treasureMap::good(vector<vector<bool>> &v, pair<int, int> curr, pair<int, int> next)
{
    if (next.first < 0 || next.first >= (int) base.width() || next.second < 0 || next.second >= (int) base.height())
    {
        return false;
    }

    if (v[next.first][next.second])
    {
        return false;
    }

    if (*maze.getPixel(curr.first, curr.second) != *maze.getPixel(next.first, next.second))
    {
        return false;
    }

    return true;
}

vector<pair<int, int>> treasureMap::neighbors(pair<int, int> curr)
{

    vector<pair<int, int>> neighbors = vector<pair<int, int>>();
    neighbors.push_back(pair<int, int>(curr.first - 1, curr.second));
    neighbors.push_back(pair<int, int>(curr.first, curr.second - 1));
    neighbors.push_back(pair<int, int>(curr.first + 1, curr.second));
    neighbors.push_back(pair<int, int>(curr.first, curr.second + 1));

    return neighbors;
}
