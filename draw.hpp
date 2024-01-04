#pragma once

#include "util.hpp"
#include "Camera.hpp"
#include "Object.hpp"

void DrawMesh(GLuint shadersID, Object object, Camera cam)
{
    setMat4(shadersID, "_M", object.matrix);
    setMat4(shadersID, "_V", cam.viewMatrix);
    setMat4(shadersID, "_P", cam.projectionMatrix);

	setVec3(shadersID, "viewPos", cam.position);

    setFloat(shadersID, "mat.roughness", object.mesh.mat.roughness);
    setFloat(shadersID, "mat.IOR", object.mesh.mat.IOR);
    setBool(shadersID, "mat.metallic", object.mesh.mat.metallic);

    object.mesh.mat.albedo.bind(GL_TEXTURE0);

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

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, object.mesh.UVBO);
    glVertexAttribPointer(
        1,
        2,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, object.mesh.NBO);
    glVertexAttribPointer(
        2,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void*)0
    );

    glDrawArrays(GL_TRIANGLES, 0, object.mesh.triCount * 3);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void Render(std::vector<Object> scene, Camera camera)
{
    for (unsigned int i = 0; i < scene.size(); i++)
    {
        DrawMesh(scene[i].mesh.shadersID, scene[i], camera);
    }
}