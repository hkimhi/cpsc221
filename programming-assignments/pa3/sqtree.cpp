/**
 *
 * shifty quadtree (pa3)
 * sqtree.cpp
 * This file will be used for grading.
 *
 */

#include "sqtree.h"

// First Node constructor, given.
SQtree::Node::Node(pair<int,int> ul, int w, int h, RGBAPixel a, double v)
  :upLeft(ul),width(w),height(h),avg(a),var(v),NW(NULL),NE(NULL),SE(NULL),SW(NULL)
{}

// Second Node constructor, given
SQtree::Node::Node(stats & s, pair<int,int> ul, int w, int h)
  :upLeft(ul),width(w),height(h),NW(NULL),NE(NULL),SE(NULL),SW(NULL) {
  avg = s.getAvg(ul,w,h);
  var = s.getVar(ul,w,h);
}

// SQtree destructor, given.
SQtree::~SQtree() {
  clear();
}

// SQtree copy constructor, given.
SQtree::SQtree(const SQtree & other) {
  copy(other);
}

// SQtree assignment operator, given.
SQtree & SQtree::operator=(const SQtree & rhs) {
  if (this != &rhs) {
    clear();
    copy(rhs);
  }
  return *this;
}

/**
 * SQtree constructor given tolerance for variance.
 */
SQtree::SQtree(PNG & imIn, double tol) {
  //recursively create nodes in the tree until variance <= tol
  stats s = stats(imIn);
  pair<int,int> ul{0,0};

  root = buildTree(s, ul, imIn.width(), imIn.height(), tol);
}

/**
 * Helper for the SQtree constructor.
 */
SQtree::Node * SQtree::buildTree(stats & s, pair<int,int> & ul,
				 int w, int h, double tol) {
  //FROM ERRATA
  //In SQtree's buildTree , if there are multiple partitions with the same maximum variability, 
  //choose the bottom-right-most partition.

  //create the current node
  Node *curr = new Node(ul, w, h, s.getAvg(ul, w, h), s.getVar(ul, w, h));
  if((w == 1) && (h == 1)) {
    // 1x1 pixel, cannot get smaller
    return curr;
  }

  if(curr->var <= tol) {
    // don't partition the current rectangle because the variance is small enough
    return curr;
  }

  //partition the current node

  // border partitions
  double maxVar = -1; //dummy start variable
  int bestWidth, bestHeight = -5;

  /*
   * width == 0 and width == w are the same partitions, but we want
   * the lowest and right-most partitions, so we assume width == 0
   */
  for(int height = 1; height <= h; height++) {
    double varN = s.getVar(ul, w, height);
    double varS = s.getVar({ul.first,ul.second+height}, w, h-height);

    double currMaxVar = max(varN, varS);
    if(maxVar == -1 || currMaxVar <= maxVar) {
      maxVar = currMaxVar;
      bestWidth = 0;
      bestHeight = height;
    }
  }

  /*
   * height == 0 and height == h are the same partitions, but we want
   * the lowest and right-most partitions so we assume height == 0
   */
  for(int width = 1; width <= w; width++) {
    double varW = s.getVar(ul, width, h);
    double varE = s.getVar({ul.first+width,ul.second}, w-width, h);

    double currMaxVar = max(varW, varE);
    if(currMaxVar <= maxVar) {
      maxVar = currMaxVar;
      bestWidth = width;
      bestHeight = 0;
    }
  }

  // internal partitions
  //check literally every possible partition
  for(int width = 1; width <= w-1; width++) {
    for(int height = 1; height <= h-1; height++) {
      double varNW = s.getVar(ul, width, height);
      double varNE = s.getVar({ul.first+width,ul.second}, w-width, height);
      double varSE = s.getVar({ul.first+width,ul.second+height}, w-width, h-height);
      double varSW = s.getVar({ul.first,ul.second+height}, width, h-height);

      double currMaxVar = max(varNW, max(varNE, max(varSE, varSW)));
      if(currMaxVar <= maxVar) {
        // if we can minimize the maximum variance, update the records
        maxVar = currMaxVar;
        bestWidth = width;
        bestHeight = height;
      }
    }
  }

  //at this point, should have minimized maximum variability
  //now we need to make a node for each sub rectangle
  std::pair<int,int> ulNW {ul};
  std::pair<int,int> ulNE {ul.first+bestWidth,ul.second};
  std::pair<int,int> ulSE {ul.first+bestWidth,ul.second+bestHeight};
  std::pair<int,int> ulSW {ul.first,ul.second+bestHeight};

  if(bestHeight == 0) {
    //only have SE, SW nodes
    curr->SE = buildTree(s, ulSE, w-bestWidth, h, tol);
    curr->SW = buildTree(s, ulSW, bestWidth, h, tol);
  }
  else if (bestWidth == 0) {
    //only have NE, SE nodes
    curr->NE = buildTree(s, ulNE, w, bestHeight, tol);
    curr->SE = buildTree(s, ulSE, w, h-bestHeight, tol);
  }
  else {
    //have all 4 child nodes
    curr->NW = buildTree(s, ulNW, bestWidth, bestHeight, tol);
    curr->NE = buildTree(s, ulNE, w-bestWidth, bestHeight, tol);
    curr->SE = buildTree(s, ulSE, w-bestWidth, h-bestHeight, tol);
    curr->SW = buildTree(s, ulSW, w, h-bestHeight, tol);
  }

  return curr;
}

/**
 * Render SQtree and return the resulting image.
 */
PNG SQtree::render() {
  PNG img = PNG(root->width, root->height);
  render(img, root);

  img.writeToFile("images/output.png");

  return img;
}

void SQtree::render(PNG &img, Node *subroot) {
  //only want to render a node if it is a leaf
  if(subroot == NULL) return;

  if(subroot->NW==NULL && subroot->NE == NULL && subroot->SE == NULL && subroot->SW == NULL) {
    //SUBROOT has no children --> it is a leaf --> draw it on img
    //iterate through all pixels and set them to avg
    for(int x = subroot->upLeft.first; x < subroot->upLeft.first + subroot->width; x++) {
      for(int y = subroot->upLeft.second; y < subroot->upLeft.second + subroot->height; y++) {
        RGBAPixel *pixel = img.getPixel(x, y);
        *pixel = subroot->avg;
      }
    }
  }

  render(img, subroot->NW);
  render(img, subroot->NE);
  render(img, subroot->SE);
  render(img, subroot->SW);
}


/**
 * Delete allocated memory.
 */
void SQtree::clear() {
  clear(root);
}

void SQtree::clear(Node *subroot) {
  while(subroot != NULL) {
    clear(subroot->NW);
    clear(subroot->NE);
    clear(subroot->SE);
    clear(subroot->SW);
  }

  free(subroot);
}

void SQtree::copy(const SQtree & other) {
  copy(root, other.root);
}

void SQtree::copy(Node *&subroot, Node *othersubroot) {
  if(othersubroot == NULL) {
    return;
  }

  subroot->upLeft = othersubroot->upLeft;
  subroot->width = othersubroot->width;
  subroot->height = othersubroot->height;
  subroot->avg = othersubroot->avg;
  subroot->var = othersubroot->var;
  subroot->NW = NULL;
  subroot->NE = NULL;
  subroot->SE = NULL;
  subroot->SW = NULL;

  
  copy(subroot->NW, othersubroot->NW);
  copy(subroot->NE, othersubroot->NE);
  copy(subroot->SE, othersubroot->SE);
  copy(subroot->SW, othersubroot->SW);
}

int SQtree::size() {
  return size(root);
}

int SQtree::size(Node *subroot) {
  if(subroot == NULL) {
    return 0;
  }
  else {
    return 1 + size(subroot->NW) + size(subroot->NE) + size(subroot->SE) + size(subroot->SW);
  }
}

