#pragma once
#include <math.h>
#include <vector>

void drawTriangle(GLfloat x_a, GLfloat y_a, GLfloat z_a, GLfloat x_b, GLfloat y_b, GLfloat z_b, GLfloat x_c, GLfloat y_c, GLfloat z_c, GLint hex_col_a, GLint hex_col_b, GLint hex_col_c, GLboolean frameOnly)
{
    if (frameOnly)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    glBegin(GL_TRIANGLE_STRIP);
    
    glColor3f(
        ((hex_col_a >> 16) & 0xFF) / 255.0,
        ((hex_col_a >> 8) & 0xFF) / 255.0,
        ((hex_col_a) & 0xFF) / 255.0
    );
    glVertex3f(x_a, y_a, z_a);

    glColor3f(
        ((hex_col_b >> 16) & 0xFF) / 255.0,
        ((hex_col_b >> 8) & 0xFF) / 255.0,
        ((hex_col_b) & 0xFF) / 255.0
    );
    glVertex3f(x_b, y_b, z_b);

    glColor3f(
        ((hex_col_c >> 16) & 0xFF) / 255.0,
        ((hex_col_c >> 8) & 0xFF) / 255.0,
        ((hex_col_c) & 0xFF) / 255.0
    );
    glVertex3f(x_c, y_c, z_c);
    glEnd();
}

void drawRectangle(GLfloat x_a, GLfloat y_a, GLfloat z_a, GLfloat x_b, GLfloat y_b, GLfloat z_b, GLfloat x_c, GLfloat y_c, GLfloat z_c, GLfloat x_d, GLfloat y_d, GLfloat z_d, GLint hex_col_a, GLint hex_col_b, GLint hex_col_c, GLint hex_col_d, GLboolean frameOnly)
{
    drawTriangle
    (
        x_a, y_a, z_a,
        x_b, y_b, z_b,
        x_c, y_c, z_c,
        hex_col_a,
        hex_col_b,
        hex_col_c,
        frameOnly
    );

    drawTriangle
    (
        x_a, y_a, z_a,
        x_c, y_c, z_c,
        x_d, y_d, z_d,
        hex_col_a,
        hex_col_c,
        hex_col_d,
        frameOnly
    );
}

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLint hex_col, GLboolean frameOnly)
{
    GLfloat lastX = x + radius;
    GLfloat lastY = y;

    for (GLfloat a = 0.0f; a < (360.0f + (360.0f / numberOfSides)); a += 360.0f / numberOfSides)
    {
        GLfloat radian = a * 3.1415926535897932384626433832795 / 180;
        GLfloat currentX = x + (radius * cos(radian));
        GLfloat currentY = y + (radius * sin(radian));
        drawTriangle
        (
            lastX, lastY, z,
            currentX, currentY, z,
            x, y, z,
            hex_col,
            hex_col,
            hex_col,
            frameOnly
        );
        lastX = currentX;
        lastY = currentY;
    }  
}

void drawSemiCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLint hex_col, GLboolean frameOnly)
{
    GLfloat lastX = x + radius;
    GLfloat lastY = y;

    for (GLfloat a = 0.0f; a < (180.0f + (180.0f / numberOfSides)); a += 180.0f / numberOfSides)
    {
        GLfloat radian = a * 3.1415926535897932384626433832795 / 180;
        GLfloat currentX = x + (radius * cos(radian));
        GLfloat currentY = y + (radius * sin(radian));
        drawTriangle
        (
            lastX, lastY, z,
            currentX, currentY, z,
            x, y, z,
            hex_col,
            hex_col,
            hex_col,
            frameOnly
        );
        lastX = currentX;
        lastY = currentY;
    }
}

void drawSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSectors, GLint numberOfStacks, GLint hex_col, GLboolean frameOnly)
{
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
                drawTriangle
                (
                    lastX_XY, lastY_XY, lastZ_XY,
                    currentX_Z, currentY_Z, currentZ_Z,
                    currentX_XY, currentY_XY, lastZ_XY,
                    hex_col,
                    hex_col,
                    hex_col,
                    frameOnly
                    );

                drawTriangle
                (
                    lastX_XY, lastY_XY, lastZ_XY,
                    lastX_Z, lastY_Z, currentZ_Z,
                    currentX_Z, currentY_Z, currentZ_Z,
                    hex_col,
                    hex_col,
                    hex_col,
                    frameOnly
                    );
            }
            lastX_XY = currentX_XY;
            lastY_XY = currentY_XY;
        }
        lastX_XY = currentX_Z;
        lastY_XY = currentY_Z;
        lastZ_XY = currentZ_Z;
        currentRadius = radius * cos(phiRadian);
    }
}