#ifndef OBJECT3D_H
#define OBJECT3D_H
#include "Vertex.h"
#include "Face.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

class Vertex;
class Face;

class Object3d {
public:
    std::vector<Vertex> vertices;
    std::vector<Face> faces;
    Object3d(const std::string& filename);
    Object3d(std::istream& input);
    Object3d();
    void smooth();
    int getVertexCount();
    int getFaceCount();
    void save(const std::string& filename);
    void print(std::ostream& output);
    Object3d cut(std::function<bool(float, float, float)> predicate);
    void flip();
    static Object3d createCube(float size);
    static Object3d createSphere(float radius);
    void loadFromFile(const std::string& filename);
    void loadFromStream(std::istream& input);
};

#endif // OBJECT3D_H