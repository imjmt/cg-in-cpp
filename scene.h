#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <limits>

#include <Eigen/Dense>

#include "canvas.h"
#include "objects.h"
#include "colour.h"

namespace scene
{

constexpr double T_VERY_LARGE {std::numeric_limits<double>::infinity()};

enum light_type
{
    ambient,
    point,
    directional
};

class Light
{
public:
    light_type type;
    double intensity;
    Eigen::Vector3d vector;

    Light(const light_type& type, const double& intensity, const Eigen::Vector3d& vector=Eigen::Vector3d(0,0,0))
        : type { type }
        , intensity { intensity }
        , vector { vector } {}
};

class Scene
{
private:
    std::vector<objects::Sphere> objects;

    std::vector<Light> lights;

    Eigen::Vector3d cameraLocation;
    Eigen::Vector3d cameraDirection;

    double viewWidth;
    double viewHeight;
    double viewDistanceFromCamera;

    // Converts the given canvas coordinates to viewport coordinates. Stores the result
    // in the parameter vp
    void canvasToViewport(const int& cx, const int& cy, Eigen::Vector3d& vp) const;

public:
    canvas::Canvas canvas;

    Scene(const int& canvWidth, const int& canvHeight)
        : canvas {canvWidth, canvHeight} {};

    // Sets up the scene with a camera at the given location, pointed at a viewport
    // in the given direction with given dimensions
    void placeCamera(const Eigen::Vector3d& location, const Eigen::Vector3d& direction,
        const double& viewportWidth, const double& viewportHeight, const double& viewportDist);

    // Adds a sphere to the scene
    void addSphere(const objects::Sphere& sphere) { this->objects.push_back(sphere); }

    void addLight(const Light& light) { this->lights.push_back(light); }

    double computeLighting(const Eigen::Vector3d& point, const Eigen::Vector3d& normal,
                            const Eigen::Vector3d& viewVector, const int& specularity) const;

    // Trace the ray from its origin, and find any scene objects it intersects with.
    // Returns the colour of the nearest object the ray intersects
    colour::RGB pixelColour(const int& x, const int&y, const double& tMin
                            , const double& tMax = T_VERY_LARGE) const;

};

}

#endif