#include <stdlib.h>
#include <iostream>

using namespace std;

void gridding(Box*, Polygon); //Initializes grids in the boundingbox
void PrintPoly(Polygon); // Prints the given polygon
void InsidePoly(Polygon, Box *, Polygon *, int, int);//adds polygons that are inside this box ;
int PointInside(Point, Box *, Polygon); //Returns the ID of the Gridblock where this point lies
