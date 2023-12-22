#pragma once

#include "util.hpp"
#include "Camera.hpp"
#include "Object.hpp"

void DrawMesh(GLuint shadersID, Object object, Camera cam)
{
    glm::mat4 model = object.matrix;

    glm::mat4 mvp = cam.projectionMatrix * cam.viewMatrix * model;

    GLuint mvpID = glGetUniformLocation(shadersID, "MVP");

    glUniformMatrix4fv(mvpID, 1, GL_FALSE, &mvp[0][0]);

    {
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, object.mesh.VBO);
        glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
        );

        glDrawArrays(GL_TRIANGLES, 0, object.mesh.triCount * 3);
        glDisableVertexAttribArray(0);
    }
}