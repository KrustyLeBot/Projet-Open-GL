#pragma once
#include <math.h>

void drawTriangle(GLfloat x_a, GLfloat y_a, GLfloat z_a, GLfloat x_b, GLfloat y_b, GLfloat z_b, GLfloat x_c, GLfloat y_c, GLfloat z_c, GLint hex_col_a, GLint hex_col_b, GLint hex_col_c)
{
    glBegin(GL_TRIANGLES);
    
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

void drawRectangle(GLfloat x_a, GLfloat y_a, GLfloat z_a, GLfloat x_b, GLfloat y_b, GLfloat z_b, GLfloat x_c, GLfloat y_c, GLfloat z_c, GLfloat x_d, GLfloat y_d, GLfloat z_d, GLint hex_col_a, GLint hex_col_b, GLint hex_col_c, GLint hex_col_d)
{
    drawTriangle
    (
        x_a, y_a, z_a,
        x_b, y_b, z_b,
        x_c, y_c, z_c,
        hex_col_a,
        hex_col_b,
        hex_col_c
    );

    drawTriangle
    (
        x_a, y_a, z_a,
        x_c, y_c, z_c,
        x_d, y_d, z_d,
        hex_col_a,
        hex_col_c,
        hex_col_d
    );
}

void drawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLint hex_col)
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
            hex_col
        );
        lastX = currentX;
        lastY = currentY;
    }  
}

void drawSemiCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLint hex_col)
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
            hex_col
            );
        lastX = currentX;
        lastY = currentY;
    }
}