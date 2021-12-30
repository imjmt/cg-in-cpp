#include "scene.h"
#include "canvas.h"

#include <string>
#include <Eigen/Dense>

using namespace scene;

int main()
{
    Scene scene {1600, 900};

    const Eigen::Vector3d cameraLocation(0, 0, 0);
    const Eigen::Vector3d cameraDirection(0, 0, 1);
    
    scene.placeCamera(cameraLocation, cameraDirection, 1.6, 0.9, 1.0);

    scene.addSphere(objects::Sphere(Eigen::Vector3d(0, -1, 3), 1.0, 500, colour::RGB(0xFFB17A)));
    scene.addSphere(objects::Sphere(Eigen::Vector3d(2, 0, 4), 1.0, 10, colour::RGB(0x4F4789)));
    scene.addSphere(objects::Sphere(Eigen::Vector3d(-2, 0, 4), 1.0, 500, colour::RGB(0xFFFDED)));
    scene.addSphere(objects::Sphere(Eigen::Vector3d(0, -5001, 0), 5000.0, 1000, colour::RGB(0xFCE762)));

    scene.addLight(Light(ambient, 0.2));
    scene.addLight(Light(point, 0.6, Eigen::Vector3d(2,1,0)));
    scene.addLight(Light(directional, 0.2, Eigen::Vector3d(1,4,4)));

    int x, y;
    double vx, vy;
    for(x = -800; x < 800; x++)
    {
        for(y = -450; y < 450; y++)
        {
            scene.canvas.putPixel(x, y, scene.pixelColour(x, y, 1));
        }
    }

    std::string filepath = "output.bmp";
    scene.canvas.toBitmap(filepath);

    return 0;
}