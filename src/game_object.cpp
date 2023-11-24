#include "game_object.h"

GameObject::GameObject(CameraObject *_cameraObject, Mesh *_mesh)
{
    position = glm::vec3(0.0f, 0.0f, 0.0f);
    camera = _cameraObject;
    mesh = _mesh;
}

View GameObject::prepareView(){
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::mat4(1.0f) = glm::translate(model, position);
    float angle = 0.0f;
    model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = camera->GetViewMatrix();

    View viewObject;
    viewObject.model = model;
    viewObject.projection = projection;
    viewObject.view = view;

    return viewObject;
}

// make sure to register Shader (shader->UseShader) right before rendering objects
// and also to deRegister after rendering is done 
void GameObject::Render(Shader *shader){
    

    shader->SetUniformVec3("viewPos", camera->GetPosition());
    auto [model, projection, view] = prepareView();
    
    shader->SetUniformMat4("view", view);
    shader->SetUniformMat4("model", model);
    shader->SetUniformMat4("projection", projection);

    // Material
    shader->SetUniformInt("material.diffuse", 0);
    shader->SetUniformInt("material.specular", 1);
    shader->SetUniformFloat("material.shininess", 64.0f);


    mesh->RenderMesh();
}

GameObject::~GameObject(){}

