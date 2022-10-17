/**
 * @file main.cpp
 * A simple C++ program that manipulates an image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "chain.h"
#include "block.h"
#include <iostream>
#include "cs221util/PNG.h"
using namespace cs221util;
using namespace std;

void TestFlip()
{
   PNG ht;
   ht.readFromFile("img-input/JDP_MV_Road.png");
   Block b;
   b.build(ht, 0,0, 430, 680);
    cout << "got here (build success)" << endl;
   b.flipHoriz();
    cout << "got here (flipHoriz success)" << endl;

   PNG ht_p = ht;
   b.render(ht_p, 0,0);
    cout << "got here (render success)" << endl;
   ht_p.writeToFile("img-out/jdlargeflipcorner.png");
    cout << "got here (writeToFile succes)" << endl;
}

void testChainSwap() {
   PNG pngin;
   pngin.readFromFile("img-input/jingle-dresssmall.png");

   int cols = 3;
   int rows = 6;

   Chain c(pngin, cols, rows);
   Chain d(c);

   PNG orig = c.render(cols,rows);
   cout << d.size() << endl;
   d.swap(12, 14);
   PNG result = d.render(cols,rows);
   
   orig.writeToFile("img-out/orig.png");
   result.writeToFile("img-out/result.png");
}

void testChainRotate() {
   PNG pngin;
   pngin.readFromFile("img-input/jingle-dresssmall.png");

   int cols = 3;
   int rows = 6;

   Chain c(pngin, cols, rows);
   Chain d(c);

   PNG orig = c.render(cols,rows);
   d.rotate(3);
   PNG result = d.render(cols,rows);
   
   orig.writeToFile("img-out/orig.png");
   result.writeToFile("img-out/result.png");
}

int main()
{
   /**
    * Write your own functions to print out variants of different images!
    * You'll find the outputs in the "images" folder.
    * A sample function has been written for you.
    */
   // TestFlip();
   testChainRotate();
   return 0;
}
