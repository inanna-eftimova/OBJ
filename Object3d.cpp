#include "Object3d.h"

#include <iostream>
#include <fstream>
#include <sstream>

Object3d::Object3d(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        loadModel(file);
    } else {
        std::cerr << "Error opening file: " << filename << std::endl;
    }
}

Object3d::Object3d(std::istream& inputStream) {
    loadModel(inputStream);
}

void Object3d::loadModel(std::istream& inputStream) {
    std::string line;
    while (std::getline(inputStream, line)) {
        if (line.empty() || line[0] == '#')
            continue;
        std::istringstream iss(line);
        char type;
        iss >> type;
        if (type == 'v') {
            std::vector<float> vertex(3);
            iss >> vertex[0] >> vertex[1] >> vertex[2];
            vertices.push_back(vertex);
        } else if (type == 'f') {
            std::vector<int> face;
            int vertexIndex;
            while (iss >> vertexIndex) {
                face.push_back(vertexIndex);
            }
            faces.push_back(face);
        }
    }
    std::cout << "The model has been successfully loaded from the input stream!" << std::endl;
}

void Object3d::printModelData() const {
    std::cout << "V:" << std::endl;
    for (const auto& vertex : vertices) {
        std::cout << "v ";
        for (float coord : vertex) {
            std::cout << coord << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "F:" << std::endl;
    for (const auto& face : faces) {
        std::cout << "f ";
        for (int vertexIndex : face) {
            std::cout << vertexIndex << " ";
        }
        std::cout << std::endl;
    }
}

int Object3d::getVertexCount() const {
    return vertices.size();
}

int Object3d::getFaceCount() const {
    return faces.size();
}