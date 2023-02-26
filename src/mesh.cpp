#include "mesh.h"

Mesh::Mesh(){
  VAO = 0;
  VBO = 0;
  EBO = 0;
  indexCount = 0;
}

void Mesh::CreateMesh(
    GLfloat* vertices, 
    unsigned int* indices, 
    unsigned int numOfVertices, 
    unsigned int numOfIndices)
{
    indexCount = numOfIndices;
    
    glGenVertexArrays(1, &VAO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    
    // bind the Element Array Buffer Object
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

    // bind Vertex Buffer Object
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 
}

void Mesh::RenderMesh(){
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
   
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
}

void Mesh::ClearMesh(){
    if(EBO != 0){
        glDeleteBuffers(1, &EBO);
        EBO = 0;
    }
    if(VBO != 0){
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if(VAO != 0){
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
    indexCount = 0;
}


Mesh::~Mesh(){
    ClearMesh();
}