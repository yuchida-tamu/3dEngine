#pragma once

#include <vector>

#include "shader.h"
#include "game_object.h"
#include "light.h"
#include "camera.h"

namespace Renderer {
    void RenderScene(CameraObject *camera, Shader *shader, std::vector<GameObject *> gameObjects, std::vector<Light *> lights);
};  