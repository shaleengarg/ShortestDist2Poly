#include "Point2Polygon.hpp"
#include "Preproc.hpp"
#include "ReorientPoly.hpp"
#include <cfloat>
#include <fstream>

using namespace std;

//Gets the biggest Rectangle which encloses all the polygons
void UpdateboundingBox(Polygon &bBox, Point P)
{
    //0 -> Sx, Sy
    //1 -> Sx, Ly
    //2 -> Lx, Ly
    //3 -> Lx, Sy
    //
    if(P.x < bBox.points[0].x){ //Sx
        bBox.points[0].x = bBox.points[1].x = P.x;
    }
    if(P.x > bBox.points[2].x){//Lx
        bBox.points[2].x = bBox.points[3].x = P.x;
    }

    if(P.y < bBox.points[0].y){ //Sy
        bBox.points[0].y = bBox.points[3].y = P.y;
    }
    if(P.y > bBox.points[1].y){ //Ly
        bBox.points[1].y = bBox.points[2].y = P.y;
    }
}

int main(int argc, char *argv[]){
    if(argc < 3){
        cout << "try ./main quadlist pointslist" << endl;
        return -1;
    }

    Point P; //Point from which we have to find the nearest polygon
    int N_Polygons; //Number of Polygons

    ifstream infile(argv[1]);
    infile >> N_Polygons;
    cout << N_Polygons << " polygons in this file" << endl;

    Polygon *ListPolygons; //This is the list of all the polygons given
    ListPolygons = (Polygon*)malloc(sizeof(Polygon)*N_Polygons);

    Polygon BoundingBox; //This is the largest rectangle enclosing all of these polygons
    //Initialize the Bounding box
    BoundingBox.points[0].x = BoundingBox.points[1].x = FLT_MAX;
    BoundingBox.points[0].y = BoundingBox.points[3].y = FLT_MAX;
    BoundingBox.points[2].x = BoundingBox.points[3].x = FLT_MIN;
    BoundingBox.points[1].y = BoundingBox.points[2].y = FLT_MIN;
    BoundingBox.label = -1;

    //Reading the file and adding all the polygons
    char eater; //Just eats the commas
    for(int i=0; i<N_Polygons; i++){ //Reads the file and populates the list of polygons
        infile >> ListPolygons[i].points[0].x >> eater >> ListPolygons[i].points[0].y >> eater;
        infile >> ListPolygons[i].points[1].x >> eater >> ListPolygons[i].points[1].y >> eater;
        infile >> ListPolygons[i].points[2].x >> eater >> ListPolygons[i].points[2].y >> eater;
        infile >> ListPolygons[i].points[3].x >> eater >> ListPolygons[i].points[3].y;
        ListPolygons[i].label = i;
        Reorient(ListPolygons[i]); //Makes the polygon vertices in one order
        //PrintPoly(ListPolygons[i]);

        UpdateboundingBox(BoundingBox, ListPolygons[i].points[0]);
        UpdateboundingBox(BoundingBox, ListPolygons[i].points[1]);
        UpdateboundingBox(BoundingBox, ListPolygons[i].points[2]);
        UpdateboundingBox(BoundingBox, ListPolygons[i].points[3]);
    }
    infile.close();
    
    Box *grid;
    int num_Yparts = (1/StrideY);
    int numberofBox = (1/StrideX)*(num_Yparts);
    grid = (Box*)malloc(sizeof(Box)*numberofBox); //allcate that many grid elements
    gridding(grid, BoundingBox); //Initializing Grids
    InsidePoly(BoundingBox, grid, ListPolygons, N_Polygons, numberofBox);

    cout << "outside InsidePoly" << endl;

    //Completed PreProc

    //Now Read the Points input file
    ifstream Pointfile(argv[2]);
    /*
       while((Pointfile >> P.x >> eater >> P.y))
       {
    //cout << P.x << " " << P.y << endl;

    //Here is where you try to get the smallest distance for this point

    }
    */
    Pointfile.close();

    /*
       int index = 0;
       float dist = 1000000000;
       float distn;
       for(int i=0; i< N_Polygons; i++)
       {
       distn = Point2Polygon(P, ListPolygons[i]);
       if(distn < dist)
       {
       dist = distn;
       index = ListPolygons[i].label;
       }
       }
       cout << "Shortest Dist is " << dist << " from Polygon number "  << index << endl;
       */
    return 0;
}
