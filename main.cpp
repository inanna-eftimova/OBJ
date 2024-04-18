#include "Object3d.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main() {
    // Work only with full path ???
    Object3d myObj("/Users/inana/CLionProjects/first-homework/files/cube.obj");
    std::cout << myObj.getVertexCount() << "\n";
    std::cout << myObj.getFaceCount();
//     myObj.printModelData();
//    std::ifstream file("/Users/inana/CLionProjects/first-homework/files/cube.obj");
//    if (file.is_open()) {
//        Object3d myObj(file);
//        myObj.printModelData();
//    } else {
//        std::cerr << "Error opening file!!!" << std::endl;
//    }
    return 0;
}
