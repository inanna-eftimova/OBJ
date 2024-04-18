#ifndef FIRST_HOMEWORK_OBJECT3D_H
#define FIRST_HOMEWORK_OBJECT3D_H

#include <string>
#include <vector>


class Object3d {
private:
    std::vector<std::vector<float>> vertices;
    std::vector<std::vector<int>> faces;
public:
    Object3d(const std::string& filename);
    Object3d(std::istream& inputStream);
    void loadModel(const std::string& filename);
    void loadModelByStream(std::istream& inputStream);
    void printModelData() const;
};

#endif
