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
            *pixel = data[x-column][y-row];
        }
    }
}

void Block::build(PNG &im, int column, int row, int width, int height)
{
    data.resize(width);

    for(int x = column; x < column + width; x++) {
        data[x-column].resize(height);

        for(int y = row; y < row + height; y++) {
            RGBAPixel *pixel = im.getPixel(x,y);
            data[x-column][y-row] = *pixel;
        }
    }
}

void Block::flipVert()
{
    int _height = height();

    for(int x = 0; x < width(); x++) {
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

    for(int x = 0; x < _width / 2; x++) {
        for(int y = 0; y < height(); y++) {
            RGBAPixel temp = data[x][y];
            data[x][y] = data[_width - x - 1][y];
            data[_width - x - 1][y] = temp;
        }
    }
}

void Block::rotateRight()
{
    vector<vector<RGBAPixel>> copy(data);

    for(int x = 0; x < width(); x++) {
        for(int y = 0; y < height(); y++) {
            data[x][y] = copy[y][height() - x - 1];
        }
    }
}
