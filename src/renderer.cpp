#include "renderer.h"

namespace Renderer {
    void RenderScene(CameraObject *camera, Shader *shader, std::vector<GameObject *> gameObjects, std::vector<Light *> lights){
        shader->UseShader();
        shader->SetUniformVec3("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        shader->SetUniformVec3("viewPos", camera->GetPosition());;
        for(Light* light : lights)
        {
            light->SetUniform(shader);
        }

        for(GameObject * obj: gameObjects)
        {
            obj->Render(shader);
        }

        glUseProgram(0);

    }
}