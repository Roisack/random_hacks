#include "object3d.hpp"
#include "objLoader.hpp"
#include "renderer.hpp"
#include "toolbox.hpp"

// Create a new 3D Object by loading the data from a .obj file
Object3D::Object3D(std::string path)
{
    name = path;
    loadModel(path);
    scale = 5.0f;
    location.x = 1.0;
    location.y = 1.0;
    location.z = 0.0;
    rotation = 0;
}

Object3D::~Object3D()
{
}

// Call the Object Loader to load the .obj, then fill all the required
// fields. Naturally this consists of vertices, normals and indices.
// In future, include materials and animations, stuff like that
void Object3D::loadModel(std::string path)
{
    std::vector<std::vector<double> > data;
    data = objectLoader.readObjectFile(path);
    vertices = data.at(0);
    normals = data.at(1);
    
    indices = tbox.doubleVectorToIntVector(data.at(2));
    
    verticeCount = vertices.size();
    indiceCount = indices.size();
    
    fprintf(stderr, "--------------------------------------\n");
    fprintf(stderr, "Object loaded: %s\n", path.c_str());
    fprintf(stderr, "Vertices: %d\n", verticeCount);
    fprintf(stderr, "Normals: %d\n", normals.size());
    fprintf(stderr, "Indices: %d\n", indiceCount);
    fprintf(stderr, "--------------------------------------\n");
}

// Set the location to which the object is rendered
void Object3D::setLocation(Vector3 in)
{
    location = in;
}

// Set the rotation at which the object is rendered
void Object3D::setRotation(float in)
{
    rotation = in;
}

// Call the renderer with all our data
void Object3D::render()
{
    renderer.renderObject(GL_TRIANGLES, indiceCount, GL_UNSIGNED_INT, indices, vertices, normals, location, rotation, scale);
}
