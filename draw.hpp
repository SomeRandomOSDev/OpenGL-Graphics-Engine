#pragma once

#include "util.hpp"
#include "Camera.hpp"

void DrawMesh(GLuint shadersID, GLuint VBO, unsigned int triCount, Camera cam)
{
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 mvp = cam.projectionMatrix * cam.viewMatrix * model;

    GLuint mvpID = glGetUniformLocation(shadersID, "MVP");

    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

    {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );

        glDrawArrays(GL_TRIANGLES, 0, triCount * 3);
        glDisableVertexAttribArray(0);
    }
}