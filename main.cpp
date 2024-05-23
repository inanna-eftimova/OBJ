#include "Object3d.h"
#include <iostream>
#include <unistd.h>

int main() {

// Program starts from: /Users/inana/CLionProjects/obj/cmake-build-debug
//    char cwd[1024];
//    getcwd(cwd, sizeof(cwd));
//    std::cout << "Current working directory: " << cwd << std::endl;

//Cut Bunny
    Object3d b("../files/bunny.obj");
    Object3d b_cut = b.cut([](float x, float y, float z) -> bool {
        return y - x < 2.5; });
    b_cut.save("../files/generated/bunny_cut.obj");

//Create sphere
    Object3d sphere = Object3d::createSphere(2);
    sphere.save("../files/generated/new_sphere.obj");

//Create cube
    Object3d cube = Object3d::createCube(2);
    std::cout << "Vertex Count: " <<cube.getVertexCount() << '\n'
              << "Face Count: " << cube.getFaceCount();
    cube.save("../files/generated/new_cube.obj");

// Flip cube
    cube.flip();
    cube.save("../files/generated/cube_flip.obj");

    return 0;
}
