#include <iostream>
using namespace std; 
  
#include "DataStructures.hpp"
  
// A global point needed for  sorting points with reference 
// to the first point. Used in compare function of qsort() 
Point p0; 
  
// A utility function to swap two points 
int swap(Point &p1, Point &p2) 
{ 
    Point temp = p1; 
    p1 = p2; 
    p2 = temp; 
} 
  
// A utility function to return square of distance between 
// p1 and p2 
int dist(Point p1, Point p2) 
{ 
    return (p1.x - p2.x)*(p1.x - p2.x) + 
           (p1.y - p2.y)*(p1.y - p2.y); 
} 
  
// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(Point p, Point q, Point r) 
{ 
    int val = (q.y - p.y) * (r.x - q.x) - 
              (q.x - p.x) * (r.y - q.y); 
  
    if (val == 0) return 0;  // colinear 
    return (val > 0)? 1: 2; // clockwise or counterclock wise 
} 
  
// A function used by library function qsort() to sort 
//  an array of points with respect to the first point 
int compare(const void *vp1, const void *vp2) 
{ 
   Point *p1 = (Point *)vp1; 
   Point *p2 = (Point *)vp2; 
  
   // Find orientation 
   int o = orientation(p0, *p1, *p2); 
   if (o == 0) 
     return (dist(p0, *p2) >= dist(p0, *p1))? -1 : 1; 
  
   return (o == 2)? -1: 1; 
} 
  
// Prints simple closed path for a set of n points. 
//void printClosedPath(Point points[], int n) 
void Reorient(Polygon &Poly)
{ 
   // Find the bottommost point 
   int ymin = Poly.points[0].y, min = 0; 
   for (int i = 1; i < 4; i++) 
   { 
     int y = Poly.points[i].y; 
  
     // Pick the bottom-most. In case of tie, chose the 
     // left most point 
     if ((y < ymin) || (ymin == y && 
         Poly.points[i].x < Poly.points[min].x)) 
        ymin = Poly.points[i].y, min = i; 
   } 
  
   // Place the bottom-most point at first position 
   swap(Poly.points[0], Poly.points[min]); 
  
   // Sort n-1 points with respect to the first point. 
   // A point p1 comes before p2 in sorted ouput if p2 
   // has larger polar angle (in counterclockwise 
   // direction) than p1 
   p0 = Poly.points[0]; 
   qsort(&Poly.points[1], 3, sizeof(Point), compare); 
} 
  
/*
// Driver program to test above functions 
int main() 
{ 
    Polygon Poly;
    Poly.points[0].x = 0;
    Poly.points[1].x = 2;
    Poly.points[2].x = 0;
    Poly.points[3].x = 2;
    Poly.points[0].y = 2;
    Poly.points[1].y = 0;
    Poly.points[2].y = 0;
    Poly.points[3].y = 2;

    //int n = sizeof(points)/sizeof(points[0]); 
    //printClosedPath(points, 4); 
    ClosedPath(Poly); 
   for (int i=0; i<4; i++) 
       cout << "(" << Poly.points[i].x << ", "
            << Poly.points[i].y <<"), "; 
   cout << endl;
    return 0; 
} 
*/
