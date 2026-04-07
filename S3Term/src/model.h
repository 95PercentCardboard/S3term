#pragma once
#include "objtypes.h"

// Auto-generated from input.obj
// 8 vertices, 12 edges

//parameters to be changed by you

float rX = 0.02; //how much you rotate in radians per frame
float rY = 0.02; //you get the jist
float rZ = 0.02;

float fov = 2.0; //how strong perspective warping is

float zoom = 0.4; //size of model

int fps = 60; //how fast the animation runs, lower fps and heighten rotation if you experience performance impacts

int boxW = 124; //bounding box model will draw inside of
int boxH = 124;

//do not touch these

const int memUsage = 7168;
const int vertexCount = 8;
const int edgeCount = 12;

static points3d verts[] = {
  {0.5000, 0.5000, -0.5000},
  {0.5000, -0.5000, -0.5000},
  {0.5000, 0.5000, 0.5000},
  {0.5000, -0.5000, 0.5000},
  {-0.5000, 0.5000, -0.5000},
  {-0.5000, -0.5000, -0.5000},
  {-0.5000, 0.5000, 0.5000},
  {-0.5000, -0.5000, 0.5000}
};

static edge edges[] = {
  {0, 1},
  {0, 2},
  {0, 4},
  {1, 3},
  {1, 5},
  {2, 3},
  {2, 6},
  {3, 7},
  {4, 5},
  {4, 6},
  {5, 7},
  {6, 7}
};
