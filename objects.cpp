#include "objects.h"

#include <Eigen/Dense>
#include <cmath>

using namespace objects;

bool Sphere::rayIntersect(const Eigen::Vector3d& rayOrigin, const Eigen::Vector3d& rayDirection
                        , double& t1, double& t2) const
{
    // CO = O - C, where C is the center of this sphere and 
    // O is the origin of the ray
    Eigen::Vector3d centerToRayOrigin = rayOrigin - this->location;

    // Solve quadratic equation at^2 + bt + c = 0, where
    //  a := <rayDirection, rayDirection>
    //  b := 2 * <centerToRayOrigin, rayDirection>
    //  c := <centerToRayOrigin, centerToRayOrigin> - r^2
    double rSquared = pow(this->radius, 2.0);
    double a = rayDirection.dot(rayDirection);
    double b = 2.0 * centerToRayOrigin.dot(rayDirection);
    double c = centerToRayOrigin.dot(centerToRayOrigin) - rSquared;

    double determinant = pow(b, 2.0) - 4.0 * a * c;

    if(determinant < 0) { return false; } // No solutions

    // Leave it up to the user to figure out if t1 == t2
    t1 = (-b + sqrt(determinant))/(2.0 * a);
    t2 = (-b - sqrt(determinant))/(2.0 * a);

    return true;
}