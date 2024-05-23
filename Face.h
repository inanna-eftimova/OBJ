#ifndef FACE_H
#define FACE_H

#include <vector>

class Face {
public:
    Face();
    Face(const std::vector<int>& vertices);
    std::vector<int> vertices;
};

#endif
