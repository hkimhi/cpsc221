#include "stats.h"

stats::stats(PNG &im)
{
    /* Your code here!! */
    sumRed.resize(im.width(), vector<long>(im.height()));
    sumGreen.resize(im.width(), vector<long>(im.height()));
    sumBlue.resize(im.width(), vector<long>(im.height()));
    sumsqRed.resize(im.width(), vector<long>(im.height()));
    sumsqGreen.resize(im.width(), vector<long>(im.height()));
    sumsqBlue.resize(im.width(), vector<long>(im.height()));

    for (int x = 0; x < im.width(); x++)
    {
        for (int y = 0; y < im.height(); y++)
        {
            if (x == 0 && y == 0)
            {
                RGBAPixel *px = im.getPixel(x, y);
                sumRed[x][y] = px->r;
                sumsqRed[x][y] = pow(px->r, 2);
                sumGreen[x][y] = px->g;
                sumsqGreen[x][y] = pow(px->g, 2);
                sumBlue[x][y] = px->b;
                sumsqBlue[x][y] = pow(px->b, 2);
            }

            else if (x == 0)
            {
                RGBAPixel *px = im.getPixel(x, y);
                sumRed[x][y] = px->r + sumRed[x][y - 1];
                sumsqRed[x][y] = pow(px->r, 2) + sumsqRed[x][y - 1];
                sumGreen[x][y] = px->g + sumGreen[x][y - 1];
                sumsqGreen[x][y] = pow(px->g, 2) + sumsqGreen[x][y - 1];
                sumBlue[x][y] = px->b + sumBlue[x][y - 1];
                sumsqBlue[x][y] = pow(px->b, 2) + sumsqBlue[x][y - 1];
            }

            else
            {
                sumRed[x][y] = sumRed[x - 1][y];
                sumsqRed[x][y] = sumsqRed[x - 1][y];
                sumGreen[x][y] = sumGreen[x - 1][y];
                sumsqGreen[x][y] = sumsqGreen[x - 1][y];
                sumBlue[x][y] = sumBlue[x - 1][y];
                sumsqBlue[x][y] = sumsqBlue[x - 1][y];

                for (int h = 0; h <= y; h++)
                {
                    RGBAPixel *px = im.getPixel(x, h);
                    sumRed[x][y] += px->r;
                    sumsqRed[x][y] += pow(px->r, 2);
                    sumGreen[x][y] += px->g;
                    sumsqGreen[x][y] += pow(px->g, 2);
                    sumBlue[x][y] += px->b;
                    sumsqBlue[x][y] += pow(px->b, 2);
                }
            }
        }
    }
}

long stats::getSum(char channel, pair<int, int> ul, int w, int h)
{
    switch (channel)
    {
    case 'r':
        if (ul.first == 0 && ul.second == 0)
        {
            return sumRed[w - 1][h - 1];
        }
        else if (ul.first == 0)
        {
            return sumRed[w - 1][ul.second + h - 1] -
                   sumRed[w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return sumRed[ul.first + w - 1][h - 1] -
                   sumRed[ul.first - 1][h - 1];
        }
        else
        {
            return sumRed[ul.first + w - 1][ul.second + h - 1] -
                   sumRed[0][ul.second + h - 1] -
                   sumRed[ul.first + w - 1][0] +
                   sumRed[ul.first - 1][ul.second - 1];
        }
        break;
    case 'g':
        if (ul.first == 0 && ul.second == 0)
        {
            return sumGreen[w - 1][h - 1];
        }
        else if (ul.first == 0)
        {
            return sumGreen[w - 1][ul.second + h - 1] -
                   sumGreen[w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return sumGreen[ul.first + w - 1][h - 1] -
                   sumGreen[ul.first - 1][h - 1];
        }
        else
        {
            return sumGreen[ul.first + w - 1][ul.second + h - 1] -
                   sumGreen[0][ul.second + h - 1] -
                   sumGreen[ul.first + w - 1][0] +
                   sumGreen[ul.first - 1][ul.second - 1];
        }
        break;
    case 'b':
        if (ul.first == 0 && ul.second == 0)
        {
            return sumBlue[w - 1][h - 1];
        }
        else if (ul.first == 0)
        {
            return sumBlue[w - 1][ul.second + h - 1] -
                   sumBlue[w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return sumBlue[ul.first + w - 1][h - 1] -
                   sumBlue[ul.first - 1][h - 1];
        }
        else
        {
            return sumBlue[ul.first + w - 1][ul.second + h - 1] -
                   sumBlue[0][ul.second + h - 1] -
                   sumBlue[ul.first + w - 1][0] +
                   sumBlue[ul.first - 1][ul.second - 1];
        }
        break;
    }
}

long stats::getSumSq(char channel, pair<int, int> ul, int w, int h)
{
    switch (channel)
    {
    case 'r':
        if (ul.first == 0 && ul.second == 0)
        {
            return sumsqRed[w - 1][h - 1];
        }
        else if (ul.first == 0)
        {
            return sumsqRed[w - 1][ul.second + h - 1] -
                   sumsqRed[w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return sumsqRed[ul.first + w - 1][h - 1] -
                   sumsqRed[ul.first - 1][h - 1];
        }
        else
        {
            return sumsqRed[ul.first + w - 1][ul.second + h - 1] -
                   sumsqRed[0][ul.second + h - 1] -
                   sumsqRed[ul.first + w - 1][0] +
                   sumsqRed[ul.first - 1][ul.second - 1];
        }
        break;
    case 'g':
        if (ul.first == 0 && ul.second == 0)
        {
            return sumsqGreen[w - 1][h - 1];
        }
        else if (ul.first == 0)
        {
            return sumsqGreen[w - 1][ul.second + h - 1] -
                   sumsqGreen[w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return sumsqGreen[ul.first + w - 1][h - 1] -
                   sumsqGreen[ul.first - 1][h - 1];
        }
        else
        {
            return sumsqGreen[ul.first + w - 1][ul.second + h - 1] -
                   sumsqGreen[0][ul.second + h - 1] -
                   sumsqGreen[ul.first + w - 1][0] +
                   sumsqGreen[ul.first - 1][ul.second - 1];
        }
        break;
    case 'b':
        if (ul.first == 0 && ul.second == 0)
        {
            return sumsqBlue[w - 1][h - 1];
        }
        else if (ul.first == 0)
        {
            return sumsqBlue[w - 1][ul.second + h - 1] -
                   sumsqBlue[w - 1][ul.second - 1];
        }
        else if (ul.second == 0)
        {
            return sumsqBlue[ul.first + w - 1][h - 1] -
                   sumsqBlue[ul.first - 1][h - 1];
        }
        else
        {
            return sumsqBlue[ul.first + w - 1][ul.second + h - 1] -
                   sumsqBlue[0][ul.second + h - 1] -
                   sumsqBlue[ul.first + w - 1][0] +
                   sumsqBlue[ul.first - 1][ul.second - 1];
        }
        break;
    }
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int w, int h)
{
    long red, sqred, blue, sqblue, green, sqgreen;
    if (ul.first == 0 && ul.second == 0)
    {
        red = sumRed[w - 1][h - 1];
        blue = sumBlue[w - 1][h - 1];
        green = sumGreen[w - 1][h - 1];
        sqred = sumsqRed[w - 1][h - 1];
        sqblue = sumsqBlue[w - 1][h - 1];
        sqgreen = sumsqGreen[w - 1][h - 1];
    }
    else if (ul.first == 0)
    {
        red = sumRed[w - 1][ul.second + h - 1] -
              sumRed[w - 1][ul.second - 1];
        green = sumGreen[w - 1][ul.second + h - 1] -
                sumGreen[w - 1][ul.second - 1];
        blue = sumBlue[w - 1][ul.second + h - 1] -
               sumBlue[w - 1][ul.second - 1];
        sqred = sumsqRed[w - 1][ul.second + h - 1] -
                sumsqRed[w - 1][ul.second - 1];
        sqgreen = sumsqGreen[w - 1][ul.second + h - 1] -
                  sumsqGreen[w - 1][ul.second - 1];
        sqblue = sumsqBlue[w - 1][ul.second + h - 1] -
                 sumsqBlue[w - 1][ul.second - 1];
    }
    else if (ul.second == 0)
    {
        red = sumRed[ul.first + w - 1][h - 1] -
              sumRed[ul.first - 1][h - 1];
        green = sumGreen[ul.first + w - 1][h - 1] -
                sumGreen[ul.first - 1][h - 1];
        blue = sumBlue[ul.first + w - 1][h - 1] -
               sumBlue[ul.first - 1][h - 1];
        sqred = sumsqRed[ul.first + w - 1][h - 1] -
                sumsqRed[ul.first - 1][h - 1];
        sqgreen = sumsqGreen[ul.first + w - 1][h - 1] -
                  sumsqGreen[ul.first - 1][h - 1];
        sqblue = sumsqBlue[ul.first + w - 1][h - 1] -
                 sumsqBlue[ul.first - 1][h - 1];
    }
    else
    {
        red = sumRed[ul.first + w - 1][ul.second + h - 1] -
              sumRed[0][ul.second + h - 1] -
              sumRed[ul.first + w - 1][0] +
              sumRed[ul.first - 1][ul.second - 1];
        green = sumGreen[ul.first + w - 1][ul.second + h - 1] -
                sumGreen[0][ul.second + h - 1] -
                sumGreen[ul.first + w - 1][0] +
                sumGreen[ul.first - 1][ul.second - 1];
        blue = sumBlue[ul.first + w - 1][ul.second + h - 1] -
               sumBlue[0][ul.second + h - 1] -
               sumBlue[ul.first + w - 1][0] +
               sumBlue[ul.first - 1][ul.second - 1];
        sqred = sumsqRed[ul.first + w - 1][ul.second + h - 1] -
                sumsqRed[0][ul.second + h - 1] -
                sumsqRed[ul.first + w - 1][0] +
                sumsqRed[ul.first - 1][ul.second - 1];
        sqgreen = sumsqGreen[ul.first + w - 1][ul.second + h - 1] -
                  sumsqGreen[0][ul.second + h - 1] -
                  sumsqGreen[ul.first + w - 1][0] +
                  sumsqGreen[ul.first - 1][ul.second - 1];
        sqblue = sumsqBlue[ul.first + w - 1][ul.second + h - 1] -
                 sumsqBlue[0][ul.second + h - 1] -
                 sumsqBlue[ul.first + w - 1][0] +
                 sumsqBlue[ul.first - 1][ul.second - 1];
    }

    double rVar = sqred - (pow(red, 2) / (w * h));
    double gVar = sqgreen - (pow(green, 2) / (w * h));
    double bVar = sqblue - (pow(blue, 2) / (w * h));

    return rVar + gVar + bVar;
}

RGBAPixel stats::getAvg(pair<int, int> ul, int w, int h)
{
    long red, green, blue;

    if (ul.first == 0 && ul.second == 0)
    {
        red = sumRed[w - 1][h - 1];
        blue = sumBlue[w - 1][h - 1];
        green = sumGreen[w - 1][h - 1];
    }
    else if (ul.first == 0)
    {
        red = sumRed[w - 1][ul.second + h - 1] -
              sumRed[w - 1][ul.second - 1];
        green = sumGreen[w - 1][ul.second + h - 1] -
                sumGreen[w - 1][ul.second - 1];
        blue = sumBlue[w - 1][ul.second + h - 1] -
               sumBlue[w - 1][ul.second - 1];
    }
    else if (ul.second == 0)
    {
        red = sumRed[ul.first + w - 1][h - 1] -
              sumRed[ul.first - 1][h - 1];
        green = sumGreen[ul.first + w - 1][h - 1] -
                sumGreen[ul.first - 1][h - 1];
        blue = sumBlue[ul.first + w - 1][h - 1] -
               sumBlue[ul.first - 1][h - 1];
    }
    else
    {
        red = sumRed[ul.first + w - 1][ul.second + h - 1] -
              sumRed[0][ul.second + h - 1] -
              sumRed[ul.first + w - 1][0] +
              sumRed[ul.first - 1][ul.second - 1];
        green = sumGreen[ul.first + w - 1][ul.second + h - 1] -
                sumGreen[0][ul.second + h - 1] -
                sumGreen[ul.first + w - 1][0] +
                sumGreen[ul.first - 1][ul.second - 1];
        blue = sumBlue[ul.first + w - 1][ul.second + h - 1] -
               sumBlue[0][ul.second + h - 1] -
               sumBlue[ul.first + w - 1][0] +
               sumBlue[ul.first - 1][ul.second - 1];
    }

    return RGBAPixel(red / (w * h), green / (w * h), blue / (w * h));
}