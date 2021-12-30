#ifndef OBJECTS_H
#define OBJECTS_H

#include <Eigen/Dense>

#include "colour.h"

namespace objects
{

class Sphere
{
private:
    Eigen::Vector3d location;
    double radius;
    colour::RGB colour;
    int specularity;

public:
    // Default constructor:
    // 0 radius, centered at origin, colour white
    Sphere(const Eigen::Vector3d& location = Eigen::Vector3d(0, 0, 0)
        , const double& radius = 0.0, const int& specularity=-1, const colour::RGB& colour = colour::RGB(0xFFFFFF))
            : location {location}
            , radius {radius}
            , specularity {specularity}
            , colour {colour} {}

    // Get coordinates of sphere's center
    Eigen::Vector3d getLocation() const { return this->location; }
    // Get radius of sphere
    double getRadius() const { return this->radius; }
    // Get sphere's colour
    colour::RGB getColour() const { return this->colour; }
    // Get the specularity
    int getSpecularity() const { return this->specularity; }
    

    // Check if the ray in direction <rayDirection> from origin <rayOrigin> intersects
    // this sphere. Returns the number of intersections.
    //
    // If there is no intersection, function returns false and parameters <t1> and <t2> are
    // unaltered. If there are one or more intersections, the function returns true
    // and <t1> and <t2> will hold the solutions
    bool rayIntersect(const Eigen::Vector3d& rayOrigin, const Eigen::Vector3d& rayDirection
                    , double& t1, double& t2) const;
};

}

#endif