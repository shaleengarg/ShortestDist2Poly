//This Finds the shortest distance to a given polygon
#include"Point2Polygon.hpp"

using namespace std;

float Dotp(Point A, Point B, Point C){ //Dot product of AB and BC
    return ((A.x-B.x)*(C.x-B.x)) + ((A.y-B.y)*(C.y-B.y));
}

float Magnitude(Point A, Point B){
    return sqrt(pow((A.y-B.y), 2) + pow((A.x-B.x), 2));
}

float Point2Side(Point P, Point A, Point B){ //Point A is shared
    float Z = Dotp(B, A, P);
    float I = Magnitude(A, B);
    //float R = Dotp(Poly.points[0], Poly.points[1], P)/pow(Magnitude(Poly.points[0], Poly.points[1]),2);
    float R = Z/pow(I, 2);
    if(R < 0)
        return Magnitude(P, A);
    else if(R > 1)
        return Magnitude(P, B);
    else
        return sqrt(pow(Magnitude(P, A), 2) - Z);
}

float Point2Polygon(Point P, Polygon Poly){
    return min({Point2Side(P, Poly.points[0], Poly.points[1]), \
                Point2Side(P, Poly.points[1], Poly.points[2]), \
                Point2Side(P, Poly.points[2], Poly.points[3]), \
                Point2Side(P, Poly.points[3], Poly.points[0])});
}
