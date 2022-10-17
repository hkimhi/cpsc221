#include "block.h"
#include <cmath>
#include <iostream>

using namespace std;

int Block::width() const
{
    return data.size();
}
int Block::height() const
{
    return data[0].size();
}

void Block::render(PNG &im, int column, int row) const
{
    for(int x = column; x < column + width(); x++) {
        for(int y = row; y < row + height(); y++) {
            RGBAPixel *pixel = im.getPixel(x,y);
            // cout << "curr: " << *pixel << endl;
            *pixel = data[x-column][y-row];
            // cout << "new: " << *pixel << endl;
        }
    }
}

void Block::build(PNG &im, int column, int row, int width, int height)
{
    data.clear();
    data.resize(width);

    for(int x = column; x < column + width; x++) {
        vector<RGBAPixel> col;
        col.resize(height);

        for(int y = row; y < row + height; y++) {
            RGBAPixel *pixel = im.getPixel(x,y);
            col[y-row] = *pixel;
        }

        data[x-column] = col;
    }
}

void Block::flipVert()
{
    int _height = height();

    for(int x = 0; x < width() - 1; x++) {
        for(int y = 0; y < _height / 2; y++) {
            RGBAPixel temp = data[x][y];
            data[x][y] = data[x][_height - y - 1];
            data[x][_height - y - 1] = temp;
        }
    }
}

void Block::flipHoriz()
{
    int _width = width();

    for(int x = 0; x < _width/2; x++) {
        for(int y = 0; y < height() - 1; y++) {
            if(x % 10 == 0) cout << "("<<x<<", "<<y<<") --> (" <<_width-x-1<<", "<<y<<")"<<endl;
            RGBAPixel temp = data[x][y];
            data[x][y] = data[_width - x - 1][y];
            data[_width - x - 1][y] = temp;
        }
    }
}

void Block::rotateRight()
{
    // vector<vector<RGBAPixel>> newData;

    // for(int x = 0; x < _width; x++) {
    //     for(int y = 0; y < _height; y++) {
    //         data.at(x).at(y)

    //         data[x][y] = newData[_width-1-y][x];
    //     }
    // }
}
