#pragma once

#include "shader.h"
#include "camera.h"
#include "shader.h"

#include "shaders_paths.h"

 float vertices[] = {
    1.0f,   1.0f,   0.0f,
    -1.0f,  1.0f,   0.0f,
    -1.0f,  -1.0f,  0.0f,
    -1.0f,  -1.0f,  0.0f,
    1.0f,   -1.0f,  0.0f,
    1.0f,   1.0f,   0.0f
};

class Grid {
    private:
        uint VAO, VBO;
        Shader* shader; 

    public:
        Grid(){
            VAO = 0;
            VBO = 0;
        }

        void Initialize(){
            shader = new Shader(GRID_VERTEX_SHADER_PATH, GRID_FRAGMENT_SHADER_PATH);   

            glGenVertexArrays(1, &VAO);
            // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
            glBindVertexArray(VAO);
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
            // position attribute
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }

        void Render(CameraObject *camera)
        {
            shader->UseShader();
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::mat4(1.0f) = glm::translate(model, glm::vec3{
                    0.0f, 0.0f, 0.0f
                });
                glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
                glm::mat4 view = camera->GetViewMatrix();
                shader->SetUniformMat4("view", view);
                shader->SetUniformMat4("model", model);
                shader->SetUniformMat4("projection", projection);
                // Draw
                glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
                glDrawArrays(GL_TRIANGLES, 0, 6);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                glBindVertexArray(0);
            glUseProgram(0);
        };
};