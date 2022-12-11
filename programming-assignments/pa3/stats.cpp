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
            if (x == 0)
            {
                RGBAPixel *px = im.getPixel(x, y);

                if (y == 0)
                {
                    sumRed[x][y] = px->r;
                    sumsqRed[x][y] = pow(px->r, 2);
                    sumGreen[x][y] = px->g;
                    sumsqGreen[x][y] = pow(px->g, 2);
                    sumBlue[x][y] = px->b;
                    sumsqBlue[x][y] = pow(px->b, 2);
                }
                else
                {
                    sumRed[x][y] = px->r + sumRed[x][y - 1];
                    sumsqRed[x][y] = pow(px->r, 2) + sumsqRed[x][y - 1];
                    sumGreen[x][y] = px->g + sumGreen[x][y - 1];
                    sumsqGreen[x][y] = pow(px->g, 2) + sumsqGreen[x][y - 1];
                    sumBlue[x][y] = px->b + sumBlue[x][y - 1];
                    sumsqBlue[x][y] = pow(px->b, 2) + sumsqBlue[x][y - 1];
                }
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
        return sumRed[ul.first + w - 1][ul.second + h - 1];
        break;
    case 'g':
        return sumGreen[ul.first + w - 1][ul.second + h - 1];
        break;
    case 'b':
        return sumBlue[ul.first + w - 1][ul.second + h - 1];
        break;
    }
}

long stats::getSumSq(char channel, pair<int, int> ul, int w, int h)
{
    switch (channel)
    {
    case 'r':
        return sumsqRed[ul.first + w - 1][ul.second + h - 1];
        break;
    case 'g':
        return sumsqGreen[ul.first + w - 1][ul.second + h - 1];
        break;
    case 'b':
        return sumsqBlue[ul.first + w - 1][ul.second + h - 1];
        break;
    }
}

// given a rectangle, compute its sum of squared deviations from mean, over all color channels.
// see written specification for a description of this function.
double stats::getVar(pair<int, int> ul, int w, int h)
{
    
    double rVar = sumsqRed[ul.first + w - 1][ul.second + h - 1] -
                  (pow(sumRed[ul.first + w - 1][ul.second + h - 1], 2) / (w * h));
    double gVar = sumsqGreen[ul.first + w - 1][ul.second + h - 1] -
                  (pow(sumGreen[ul.first + w - 1][ul.second + h - 1], 2) / (w * h));
    double bVar = sumsqBlue[ul.first + w - 1][ul.second + h - 1] -
                  (pow(sumBlue[ul.first + w - 1][ul.second + h - 1], 2) / (w * h));

    return rVar + gVar + bVar;
}

RGBAPixel stats::getAvg(pair<int, int> ul, int w, int h)
{
    return RGBAPixel(sumRed[ul.first + w - 1][ul.second + h - 1] / (w * h),
                     sumGreen[ul.first + w - 1][ul.second + h - 1] / (w * h),
                     sumBlue[ul.first + w - 1][ul.second + h - 1] / (w * h));
}
