#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

class Mesh
{
private:
    unsigned int VAO, VBO, EBO;
    GLsizei indexCount;
   
public:
    Mesh();
    void CreateMesh(
        GLfloat* vertices, 
        unsigned int* indices, 
        unsigned int verticesCount,
         unsigned int indicesCount );
    void RenderMesh();
    void ClearMesh();
    ~Mesh();
};
