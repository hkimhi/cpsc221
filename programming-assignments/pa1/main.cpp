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

int main()
{
   /**
    * Write your own functions to print out variants of different images!
    * You'll find the outputs in the "images" folder.
    * A sample function has been written for you.
    */
   TestFlip();
   return 0;
}
