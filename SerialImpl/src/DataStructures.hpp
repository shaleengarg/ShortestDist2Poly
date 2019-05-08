#include <vector>
//Defines all the DataStructures
struct Point{
    float x, y;
};

typedef struct p{
    int label;//Gives a number to the polygon
    struct Point points[4];
}Polygon;

typedef struct g{
    struct Point lower; //The lower point of the box
    std::vector<int> Poly; //Indices of all polygons inside this box
}Box;

#define StrideX 0.1 //parts of the length
#define StrideY 0.1 //parts of the width
