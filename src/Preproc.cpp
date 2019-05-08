#include "DataStructures.hpp"
#include "Preproc.hpp"

void PrintPoly(Polygon Poly){ // Prints the given polygon
    cout << "Label = " << Poly.label << endl;
    for(int i=0; i<4; i++)
    {
        cout << i << " " << Poly.points[i].x << " " << Poly.points[i].y << endl;
    }
}

void gridding(Box *grid, Polygon BoundingBox){ //Initializes grids in the boundingbox
    int num_Yparts = (1/StrideY);
    cout << "num_Yparts = " << num_Yparts << endl;

    float Len_X = abs(BoundingBox.points[0].x - BoundingBox.points[3].x);
    cout << "hello" << endl;
    float Len_Y = abs(BoundingBox.points[0].y - BoundingBox.points[1].y);

    float AddLenX = StrideX*Len_X; //How much length adds to each box X
    float AddLenY = StrideY*Len_Y; //How much length adds to each box Y

    int id;
    for(int i=0; i<num_Yparts; i++){
        for(int j=0; j<(1/StrideX); j++){
            id = (i*num_Yparts)+j; 
            grid[id].lower.x = min(BoundingBox.points[0].x, BoundingBox.points[3].x) + j*AddLenX;
            grid[id].lower.y = min(BoundingBox.points[1].y, BoundingBox.points[0].y) + i*AddLenY;
        }
    }
}

void InsidePoly(Box *grid, Polygon *ListPolygons, int numberofBox) 
{
    for(int i=0; i<numberofBox; i++)
    {
        cout << "Grid " << i << " " << grid[i].lower.x << " " << grid[i].lower.y << endl;
    }
}
