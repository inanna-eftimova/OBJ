# OBJ

This project implements a 3D model class in C++ for handling Wavefront `.obj` files. The `Object3d` class allows loading, saving, manipulating, and generating 3D models.

## Features

- Load a 3D model from a file or input stream.
- Save a 3D model to a file.
- Get the number of vertices and faces in the model.
- Print the model to an output stream.
- Cut the model based on a predicate function.
- Flip the faces of the model.
- Static methods to create a cube and a sphere.

## Class Methods

### Constructors

- **Object3d(const std::string& filename)**
  - Loads a 3D model from the specified file.
- **Object3d(std::istream& input)**
  - Loads a 3D model from the given input stream.

### Member Functions

- **int getVertexCount() const**
  - Returns the number of vertices in the model.
- **int getFaceCount() const**
  - Returns the number of faces in the model.
- **void save(const std::string& filename) const**
  - Saves the model to the specified file.
- **void print(std::ostream& output) const**
  - Prints the model to the given output stream.
- **Object3d cut(std::function<bool(float x, float y, float z)> predicate) const**
  - Returns a new model containing only the faces whose vertices satisfy the given predicate.
- **void flip()**
  - Reverses the order of the vertices in each face, effectively flipping the model.

### Static Methods

- **static Object3d createCube(float edgeLength)**
  - Creates a cube with the specified edge length.
- **static Object3d createSphere(float radius)**
  - Creates a sphere with the specified radius.

## Example Usage

```cpp
#include "Object3d.hpp"

int main() {
    Object3d model("./bunny.obj");
    Object3d cutModel = model.cut([](float x, float y, float z) -> bool {
        return y - x < 2.5;
    });
    cutModel.save("./bunny_cut.obj");
    return 0;
}
