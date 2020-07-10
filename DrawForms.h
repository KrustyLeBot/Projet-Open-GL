#pragma once
#include <math.h>

void display(std::vector<GLfloat>& vertices, std::vector<GLfloat>& colors, GLenum mode, GLboolean frameOnly)
{
    if (frameOnly)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    /* We have a color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());
    glColorPointer(3, GL_FLOAT, 0, colors.data());

    /* Send data : 24 vertices */
    glDrawArrays(mode, 0, vertices.size() / 3);

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void drawRectangle(GLfloat x_a, GLfloat y_a, GLfloat z_a, GLfloat x_b, GLfloat y_b, GLfloat z_b, GLfloat x_c, GLfloat y_c, GLfloat z_c, GLfloat x_d, GLfloat y_d, GLfloat z_d, GLint hex_col_a, GLint hex_col_b, GLint hex_col_c, GLint hex_col_d, GLboolean frameOnly)
{
    std::vector<GLfloat> vertices = 
    {
        x_a, y_a, z_a,
        x_b, y_b, z_b,
        x_c, y_c, z_c,
        x_d, y_d, z_d,
    };
    std::vector<GLfloat> colors;

    colors.push_back(((hex_col_a >> 16) & 0xFF) / 255.0);
    colors.push_back(((hex_col_a >> 8) & 0xFF) / 255.0);
    colors.push_back(((hex_col_a) & 0xFF) / 255.0);

    colors.push_back(((hex_col_b >> 16) & 0xFF) / 255.0);
    colors.push_back(((hex_col_b >> 8) & 0xFF) / 255.0);
    colors.push_back(((hex_col_b) & 0xFF) / 255.0);

    colors.push_back(((hex_col_c >> 16) & 0xFF) / 255.0);
    colors.push_back(((hex_col_c >> 8) & 0xFF) / 255.0);
    colors.push_back(((hex_col_c) & 0xFF) / 255.0);

    colors.push_back(((hex_col_d >> 16) & 0xFF) / 255.0);
    colors.push_back(((hex_col_d >> 8) & 0xFF) / 255.0);
    colors.push_back(((hex_col_d) & 0xFF) / 255.0);

    display(vertices, colors, GL_QUADS, frameOnly);
}

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLint hex_col, GLboolean frameOnly)
{
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;

    GLfloat lastX = x + radius;
    GLfloat lastY = y;

    for (GLfloat a = 0.0f; a < (360.0f + (360.0f / numberOfSides)); a += 360.0f / numberOfSides)
    {
        GLfloat radian = a * 3.1415926535897932384626433832795 / 180;
        GLfloat currentX = x + (radius * cos(radian));
        GLfloat currentY = y + (radius * sin(radian));

        vertices.push_back(lastX);
        vertices.push_back(lastY);
        vertices.push_back(z);
        colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
        colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
        colors.push_back(((hex_col) & 0xFF) / 255.0);

        vertices.push_back(currentX);
        vertices.push_back(currentY);
        vertices.push_back(z);
        colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
        colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
        colors.push_back(((hex_col) & 0xFF) / 255.0);

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
        colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
        colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
        colors.push_back(((hex_col) & 0xFF) / 255.0);

        lastX = currentX;
        lastY = currentY;
    }  
    display(vertices, colors, GL_TRIANGLES, frameOnly);
}

void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSectors, GLint numberOfStacks, GLint hex_col, GLboolean frameOnly)
{
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> colors;
    numberOfStacks = numberOfStacks / 2;
    GLfloat lastZ_XY = z;
    GLfloat currentZ_Z = z;
    GLfloat lastX_XY = x + radius;
    GLfloat lastY_XY = y;
    GLfloat currentX_Z = 0.0f;
    GLfloat currentY_Z = 0.0f;
    GLfloat currentRadius = radius;

    for (GLfloat phi = -90.0f; phi <= (90.0f); phi += 90.0f / numberOfStacks)
    {
        GLfloat phiRadian = phi * 3.1415926535897932384626433832795 / 180;
        currentZ_Z = z + (radius * sin(phiRadian));

        for (GLfloat teta = 0.0f; teta < (360.0f); teta += 360.0f / numberOfSectors)
        {
            GLfloat tetaRadian = teta * 3.1415926535897932384626433832795 / 180;
            GLfloat currentX_XY = x + (currentRadius * cos(tetaRadian));
            GLfloat currentY_XY = y + (currentRadius * sin(tetaRadian));
            GLfloat lastTetaRadian = (teta - (360.0f / numberOfSectors)) * 3.1415926535897932384626433832795 / 180;
            GLfloat lastX_Z = z + (radius * cos(phiRadian) * cos(lastTetaRadian));
            GLfloat lastY_Z = z + (radius * cos(phiRadian) * sin(lastTetaRadian));
            currentX_Z = z + (radius * cos(phiRadian) * cos(tetaRadian));
            currentY_Z = z + (radius * cos(phiRadian) * sin(tetaRadian));

            if (phi != -90.0f)
            {
                vertices.push_back(lastX_XY);
                vertices.push_back(lastY_XY);
                vertices.push_back(lastZ_XY);
                colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                colors.push_back(((hex_col) & 0xFF) / 255.0);

                vertices.push_back(currentX_Z);
                vertices.push_back(currentY_Z);
                vertices.push_back(currentZ_Z);
                colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                colors.push_back(((hex_col) & 0xFF) / 255.0);

                vertices.push_back(currentX_XY);
                vertices.push_back(currentY_XY);
                vertices.push_back(lastZ_XY);
                colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                colors.push_back(((hex_col) & 0xFF) / 255.0);


                vertices.push_back(lastX_XY);
                vertices.push_back(lastY_XY);
                vertices.push_back(lastZ_XY);
                colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                colors.push_back(((hex_col) & 0xFF) / 255.0);

                vertices.push_back(lastX_Z);
                vertices.push_back(lastY_Z);
                vertices.push_back(currentZ_Z);
                colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                colors.push_back(((hex_col) & 0xFF) / 255.0);

                vertices.push_back(currentX_Z);
                vertices.push_back(currentY_Z);
                vertices.push_back(currentZ_Z);
                colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                colors.push_back(((hex_col) & 0xFF) / 255.0);
            }
            lastX_XY = currentX_XY;
            lastY_XY = currentY_XY;
        }
        lastX_XY = currentX_Z;
        lastY_XY = currentY_Z;
        lastZ_XY = currentZ_Z;
        currentRadius = radius * cos(phiRadian);
    }
    display(vertices, colors, GL_TRIANGLES, frameOnly);
}

void drawCube()
{
    std::vector<GLfloat> vertices =
    {
        -0.5f, -0.5f, -0.5f,   -0.5f, -0.5f,  0.5f,   -0.5f,  0.5f,  0.5f,   -0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,    0.5f, -0.5f,  0.5f,    0.5f,  0.5f,  0.5f,    0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,   -0.5f, -0.5f,  0.5f,    0.5f, -0.5f,  0.5f,    0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,   -0.5f,  0.5f,  0.5f,    0.5f,  0.5f,  0.5f,    0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,   -0.5f,  0.5f, -0.5f,    0.5f,  0.5f, -0.5f,    0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,   -0.5f,  0.5f,  0.5f,    0.5f,  0.5f,  0.5f,    0.5f, -0.5f,  0.5f
    };

    std::vector<GLfloat> colors =
    {
        0, 0, 1,   0, 0, 1,   0, 1, 1,   0, 1, 0,
        1, 0, 0,   1, 0, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 0,   0, 0, 1,   1, 0, 1,   1, 0, 0,
        0, 1, 0,   0, 1, 1,   1, 1, 1,   1, 1, 0,
        0, 0, 1,   0, 1, 0,   1, 1, 0,   1, 0, 0,
        0, 0, 1,   0, 1, 1,   1, 1, 1,   1, 0, 1
    };

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    /* We have a color array and a vertex array */
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices.data());
    glColorPointer(3, GL_FLOAT, 0, colors.data());

    /* Send data : 24 vertices */
    glDrawArrays(GL_QUADS, 0, vertices.size() / 3);

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}