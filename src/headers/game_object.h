#include <vector>
#include <glm/glm.hpp>
#include "camera.h"
#include "shader.h"
#include "mesh.h"

struct View {
    glm::mat4 model, projection, view;
};

class GameObject 
{
    private:
        // TODO: create Transform class
        glm::vec3 position;
        CameraObject *camera;
        Mesh *mesh;
    
        // TODO: create Material class
        View prepareView();

    public: 
        GameObject(CameraObject *_cameraObject, Mesh *_mesh);
        void Render(Shader *shader);
        ~GameObject();
};