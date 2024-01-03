#pragma once

namespace
{
    GLfloat triDATA[1 * 3 * 3]
    {
        1, -1, 0,
        0, 1, 0,
        -1, -1, 0
    };
    GLfloat triDATA_UVs[1 * 3 * 2]
    {
        1, 0,
        0.5f, 1,
        0, 0,
    };

    GLfloat triDATA_Normals[1 * 3 * 3]
    {
        0, 0, 1,
        0, 0, 1,
        0, 0, 1
    };

    GLfloat emptyMeshDATA[1 * 3 * 3]
    {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0
    };

    GLfloat emptyMeshDATA_UVs[1 * 3 * 2]
    {
        0, 0,
        0, 0,
        0, 0,
    };

    GLfloat emptyMeshDATA_Normals[1 * 3 * 3]
    {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0
    };
}