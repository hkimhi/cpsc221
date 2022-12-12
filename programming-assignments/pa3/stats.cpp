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

    RGBAPixel *px = im.getPixel(0, 0);
    sumRed[0][0] = px->r;
    sumsqRed[0][0] = pow(px->r, 2);
    sumGreen[0][0] = px->g;
    sumsqGreen[0][0] = pow(px->g, 2);
    sumBlue[0][0] = px->b;
    sumsqBlue[0][0] = pow(px->b, 2);

    for (int y = 1; y < im.height(); y++)
    {
        RGBAPixel *px = im.getPixel(0, y);
        sumRed[0][y] = px->r + sumRed[0][y - 1];
        sumsqRed[0][y] = pow(px->r, 2) + sumsqRed[0][y - 1];
        sumGreen[0][y] = px->g + sumGreen[0][y - 1];
        sumsqGreen[0][y] = pow(px->g, 2) + sumsqGreen[0][y - 1];
        sumBlue[0][y] = px->b + sumBlue[0][y - 1];
        sumsqBlue[0][y] = pow(px->b, 2) + sumsqBlue[0][y - 1];
    }

    for (int x = 1; x < im.width(); x++)
    {
        for (int y = 0; y < im.height(); y++)
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

    double varRed = getSumSq('r', ul, w, h) - pow(getSum('r', ul, w, h), 2) / (w * h);
    double varGreen = getSumSq('g', ul, w, h) - pow(getSum('g', ul, w, h), 2) / (w * h);
    double varBlue = getSumSq('b', ul, w, h) - pow(getSum('b', ul, w, h), 2) / (w * h);

    return varRed + varGreen + varBlue;
}

RGBAPixel stats::getAvg(pair<int, int> ul, int w, int h)
{
    return RGBAPixel(getSum('r', ul, w, h) / (w * h),
                     getSum('g', ul, w, h) / (w * h),
                     getSum('b', ul, w, h) / (w * h));
}
