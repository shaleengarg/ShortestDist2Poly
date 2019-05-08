#include "DataStructures.hpp"
#include "ReorientPoly.hpp"
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

// Given three colinear points p, q, r, the function checks if 
// point q lies on line segment 'pr' 
bool onSegment(Point p, Point q, Point r) { 
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && 
            q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) 
        return true; 
    return false; 
} 
// The main function that returns true if line segment 'p1q1' 
// and 'p2q2' intersect. 
bool Intersect(Point p1, Point p2, Point q1, Point q2) //True if p and q intersect else false
{ 
    cout << "Intersect" << endl;
    // Find the four orientations needed for general and 
    // special cases 
    int o1 = orientation(p1, q1, p2); 
    int o2 = orientation(p1, q1, q2); 
    int o3 = orientation(p2, q2, p1); 
    int o4 = orientation(p2, q2, q1); 

    // General case 
    if (o1 != o2 && o3 != o4) 
        return true; 

    // Special Cases 
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
    if (o1 == 0 && onSegment(p1, p2, q1)) return true; 

    // p1, q1 and q2 are colinear and q2 lies on segment p1q1 
    if (o2 == 0 && onSegment(p1, q2, q1)) return true; 

    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
    if (o3 == 0 && onSegment(p2, p1, q2)) return true; 

    // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
    if (o4 == 0 && onSegment(p2, q1, q2)) return true; 

    return false; // Doesn't fall in any of the above cases 
}

bool AtIntersect(Box &grid, Polygon Poly, Polygon BoundingBox){ //Returns true if atleast one edge intersects rectangle edge
    Polygon GridBox;
    float AddLenX = StrideX*abs(BoundingBox.points[0].x - BoundingBox.points[3].x);
    float AddLenY = StrideY*abs(BoundingBox.points[0].y - BoundingBox.points[1].y); 
    GridBox.points[0].x = GridBox.points[1].x = grid.lower.x;
    GridBox.points[2].x = GridBox.points[3].x = grid.lower.x + AddLenX;
    GridBox.points[0].y = GridBox.points[3].y = grid.lower.y;
    GridBox.points[1].y = GridBox.points[2].y = grid.lower.y + AddLenY;

    for(int i=0; i<4; i++) //for sides of grid 01, 12, 23, 30
        for(int j=0; j<4; j++) //for sides of Poly
        {
            if(Intersect(GridBox.points[i%4], GridBox.points[(i+1)%4], Poly.points[j%4], Poly.points[(j+1)%4]));
            {
                PrintPoly(Poly);
                return true;
            }
        }
    return false;
}

bool Inside(Box &grid, Polygon Poly, Polygon BoundingBox){ //Returns true if atleast one vertex inside the rectange
    cout << "Polygon inside grid " << grid.lower.x << " " << grid.lower.y << endl;
    ////////////////////////////////////////////////////////////////
    //Gets the box edges from grid
    float AddLenX = StrideX*abs(BoundingBox.points[0].x - BoundingBox.points[3].x);
    float AddLenY = StrideY*abs(BoundingBox.points[0].y - BoundingBox.points[1].y); 
    //////////////////////////////////////////////////////////////////

    //Check if atleast one edge inside
    for(int j=0; j<4; j++) //for each point in polygon
    {
        if(Poly.points[j].x > grid.lower.x && Poly.points[j].x < (grid.lower.x+AddLenX)
            && Poly.points[j].y > grid.lower.y && Poly.points[j].y < (grid.lower.y+AddLenY))
        {
            PrintPoly(Poly);
            return true;
        }
    }
    return false;
}

void InsidePoly(Polygon BoundingBox, Box *grid, Polygon *ListPolygons, int N_Polygons, int numberofBox){
    for(int i=0; i<numberofBox; i++)
    {
        //cout << "Grid " << i << " " << grid[i].lower.x << " " << grid[i].lower.y << endl;
        cout << "Polygon inside grid " << grid[i].lower.x << " " << grid[i].lower.y << endl;
        for(int j=0; j<N_Polygons; j++)
        {
            //Check if the Polygon is inside the rectangle
            //check if the polygon intersects the rectangle
            if(Inside(grid[i], ListPolygons[j], BoundingBox) || AtIntersect(grid[i], ListPolygons[j], BoundingBox))
            {
                //Add Index of this polygon in this grid vector
                //grid[i].Poly.push_back(ListPolygons[j].label);
            }
        }
        /*for(int j=0; i<grid[i].Poly.size(); j++)
        {
            cout << "Poly number " << grid[i].Poly[j] << endl;
        }
        */
    }
}
