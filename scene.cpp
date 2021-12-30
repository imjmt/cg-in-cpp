#include "scene.h"

using namespace scene;

void Scene::canvasToViewport(const int& cx, const int& cy, Eigen::Vector3d& vp) const
{
    double vx = cx * this->viewWidth / static_cast<double>(this->canvas.getWidth());
    double vy = cy * this->viewHeight / static_cast<double>(this->canvas.getHeight());

    vp = Eigen::Vector3d(vx, vy, this->viewDistanceFromCamera);
}

void Scene::placeCamera(const Eigen::Vector3d& location, const Eigen::Vector3d& direction,
        const double& viewportWidth, const double& viewportHeight, const double& viewportDist)
{
    this->cameraLocation = location;
    this->cameraDirection = direction;
    this->viewWidth = viewportWidth;
    this->viewHeight = viewportHeight;
    this->viewDistanceFromCamera = viewportDist;
}

double Scene::computeLighting(const Eigen::Vector3d& pointToLight, const Eigen::Vector3d& normal,
                                const Eigen::Vector3d& viewVector, const int& specularity) const
{
    double intensity = 0;
    double nDotL, rDotV;
    Eigen::Vector3d lightVector;
    Eigen::Vector3d reflection;

    for(Light light : this->lights)
    {
        if(light.type == ambient) { intensity += light.intensity; }
        else
        {
            if(light.type == point) { lightVector = light.vector - pointToLight; }
            else { lightVector = light.vector; }

            // Diffuse lighting
            nDotL = normal.dot(lightVector);
            if(nDotL > 0)
            {
                intensity += light.intensity * (nDotL)/(normal.norm() * lightVector.norm());
            }

            // Specularity
            if(specularity != -1)
            {
                reflection = 2 * normal * normal.dot(lightVector) - lightVector;
                rDotV = reflection.dot(viewVector);
                if(rDotV > 0)
                {
                    intensity += light.intensity * pow(rDotV/(reflection.norm() * viewVector.norm()), specularity);
                }
            }

        }
    }

    return intensity;
}

colour::RGB Scene::pixelColour(const int& x, const int&y, const double& tMin, const double& tMax) const
{
    Eigen::Vector3d viewportCoordinates;
    canvasToViewport(x, y, viewportCoordinates);
    Eigen::Vector3d rayDirection = viewportCoordinates - this->cameraLocation;

    double tClosest = T_VERY_LARGE;
    objects::Sphere sClosest;
    
    double t1, t2;
    bool intersect;
    for(objects::Sphere sphere : this->objects)
    {
        intersect = sphere.rayIntersect(this->cameraLocation, rayDirection, t1, t2);
        if(intersect)
        {
            if(tMin < t1 && t1 < tMax && t1 < tClosest)
            {
                tClosest = t1;
                sClosest = sphere;
            }

            if(tMin < t2 && t2 < tMax && t2 < tClosest)
            {
                tClosest = t2;
                sClosest = sphere;
            }
        }
    }

    Eigen::Vector3d P = this->cameraLocation + tClosest * rayDirection;
    Eigen::Vector3d N = P - sClosest.getLocation();
    N.normalize();


    return (this->computeLighting(P, N, -rayDirection, sClosest.getSpecularity())) * sClosest.getColour();
}