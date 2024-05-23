#include "Object3d.h"

Object3d::Object3d(const std::string& filename) {
    loadFromFile(filename);
}

Object3d::Object3d(std::istream& input) {
    loadFromStream(input);
}

Object3d::Object3d() {}

int Object3d::getVertexCount() {
    return vertices.size();
}

int Object3d::getFaceCount() {
    return faces.size();
}

void Object3d::save(const std::string& filename) {
    std::ofstream output(filename);
    if (output) {
        output << std::fixed << std::setprecision(8);
        for (const auto& vertex : vertices) {
            output << "v " << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
        }
        for (const auto& face : faces) {
            output << "f";
            for (const auto& vertexIndex : face.vertices) {
                output << " " << vertexIndex + 1;
            }
            output << std::endl;
        }
    } else {
        std::cerr << "Error: unable to save to file " << filename << std::endl;
    }
}

void Object3d::print(std::ostream& output) {
    output << std::fixed << std::setprecision(8);
    for (const auto& vertex : vertices) {
        output << "v " << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
    }
    for (const auto& face : faces) {
        output << "f";
        for (const auto& vertexIndex : face.vertices) {
            output << " " << vertexIndex + 1;
        }
        output << std::endl;
    }
}

Object3d Object3d::cut(std::function<bool(float, float, float)> predicate) {
    Object3d result;
    std::vector<Vertex> newVertices;
    std::vector<int> vertexMap(vertices.size(), -1);
    int newIndex = 0;

    for (int i = 0; i < vertices.size(); i++) {
        const Vertex& vertex = vertices[i];
        if (predicate(vertex.x, vertex.y, vertex.z)) {
            newVertices.push_back(vertex);
            vertexMap[i] = newIndex;
            newIndex++;
        }
    }

    for (const auto& face : faces) {
        std::vector<int> newFace;
        for (int vertexIndex : face.vertices) {
            if (vertexMap[vertexIndex] != -1) {
                newFace.push_back(vertexMap[vertexIndex]);
            }
        }
        if (newFace.size() >= 3) {
            result.faces.push_back(Face(newFace));
        }
    }

    result.vertices = newVertices;
    return result;
}


void Object3d::flip() {
    for (auto& face : faces) {
        std::reverse(face.vertices.begin(), face.vertices.end());
    }
}

Object3d Object3d::createCube(float size) {
    Object3d cube;
    cube.vertices = {
            {-size, -size, -size},
            {size, -size, -size},
            {size, size, -size},
            {-size, size, -size},
            {-size, -size, size},
            {size, -size, size},
            {size, size, size},
            {-size, size, size}
    };
    cube.faces = {
            {Face(std::vector<int>{0, 1, 2, 3})},
            {Face(std::vector<int>{4, 5, 6, 7})},
            {Face(std::vector<int>{0, 4, 5, 1})},
            {Face(std::vector<int>{1, 5, 6, 2})},
            {Face(std::vector<int>{2, 6, 7, 3})},
            {Face(std::vector<int>{3, 7, 4, 0})}
    };
    return cube;
}
Object3d Object3d::createSphere(float radius) {
    Object3d sphere;
    int segments = 32;
    float pi = 3.14159265358979323846;
    for (int i = 0; i <= segments; i++) {
        for (int j = 0; j <= segments; j++) {
            float u = (float)i / segments;
            float v = (float)j / segments;
            float x = radius * sin(2 * pi * u) * cos(pi * v);
            float y = radius * cos(2 * pi * u) * cos(pi * v);
            float z = radius * sin(pi * v);
            sphere.vertices.push_back(Vertex(x, y, z));
        }
    }
    for (int i = 0; i < segments; i++) {
        for (int j = 0; j < segments; j++) {
            int a = i * (segments + 1) + j;
            int b = (i + 1) * (segments + 1) + j;
            int c = (i + 1) * (segments + 1) + (j + 1);
            int d = i * (segments + 1) + (j + 1);
            sphere.faces.push_back(Face(std::vector<int>{a, b, c}));
            sphere.faces.push_back(Face(std::vector<int>{a, c, d}));
        }
    }

    for (int i = 0; i <= segments; i++) {
        for (int j = 0; j <= segments; j++) {
            float u = (float)i / segments;
            float v = (float)j / segments;
            float x = radius * sin(2 * pi * u) * cos(-pi * v);
            float y = radius * cos(2 * pi * u) * cos(-pi * v);
            float z = radius * sin(-pi * v);
            sphere.vertices.push_back(Vertex(x, y, z));
        }
    }
    for (int i = 0; i < segments; i++) {
        for (int j = 0; j < segments; j++) {
            int a = (i * (segments + 1) + j) + (segments + 1) * (segments + 1);
            int b = ((i + 1) * (segments + 1) + j) + (segments + 1) * (segments + 1);
            int c = ((i + 1) * (segments + 1) + (j + 1)) + (segments + 1) * (segments + 1);
            int d = (i * (segments + 1) + (j + 1)) + (segments + 1) * (segments + 1);
            sphere.faces.push_back(Face(std::vector<int>{a, b, c}));
            sphere.faces.push_back(Face(std::vector<int>{a, c, d}));
        }
    }
    return sphere;
}

void Object3d::loadFromFile(const std::string& filename) {
    std::ifstream input(filename);
    if (input) {
        loadFromStream(input);
    } else {
        std::cerr << "Error: unable to load from file " << filename << std::endl;
    }
}

void Object3d::loadFromStream(std::istream& input) {
    std::string line;
    while (std::getline(input, line)) {
        char type = line[0];
        std::istringstream iss(line.substr(1));
        if (type == 'v') {
            float x, y, z;
            if (iss >> x >> y >> z) {
                vertices.push_back(Vertex(x, y, z));
            } else {
                std::cerr << "Error: invalid vertex format" << std::endl;
            }
        } else if (type == 'f') {
            std::vector<int> faceVertices;
            int vertexIndex;
            while (iss >> vertexIndex) {
                faceVertices.push_back(vertexIndex - 1);
            }
            if (faceVertices.size() >= 3) {
                faces.push_back(Face(faceVertices));
            } else {
                std::cerr << "Error: invalid face format" << std::endl;
            }
        }
    }
}