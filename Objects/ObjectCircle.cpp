#include "ObjectCircle.h"

ObjectCircle::ObjectCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLint hex_col, GLboolean frameOnly)
	: Object::Object(frameOnly)
{
    m_mode = GL_TRIANGLES;
    m_centerX = x;
    m_centerY = y;
    m_centerZ = z;

    GLfloat lastX = x + radius;
    GLfloat lastY = y;

    for (GLfloat a = 0.0f; a < (360.0f + (360.0f / numberOfSides)); a += 360.0f / numberOfSides)
    {
        GLfloat radian = a * 3.1415926535897932384626433832795 / 180;
        GLfloat currentX = x + (radius * cos(radian));
        GLfloat currentY = y + (radius * sin(radian));

        m_vertices.push_back(lastX);
        m_vertices.push_back(lastY);
        m_vertices.push_back(z);
        m_colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
        m_colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
        m_colors.push_back(((hex_col) & 0xFF) / 255.0);

        m_vertices.push_back(currentX);
        m_vertices.push_back(currentY);
        m_vertices.push_back(z);
        m_colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
        m_colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
        m_colors.push_back(((hex_col) & 0xFF) / 255.0);

        m_vertices.push_back(x);
        m_vertices.push_back(y);
        m_vertices.push_back(z);
        m_colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
        m_colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
        m_colors.push_back(((hex_col) & 0xFF) / 255.0);

        lastX = currentX;
        lastY = currentY;
    }
}