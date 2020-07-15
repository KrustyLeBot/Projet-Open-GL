#include "ObjectSphere.h"

ObjectSphere::ObjectSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSectors, GLint numberOfStacks, GLint hex_col, GLboolean frameOnly)
    : Object::Object(frameOnly)
{
    m_mode = GL_TRIANGLES;
    m_centerX = x;
    m_centerY = y;
    m_centerZ = z;

    numberOfStacks = numberOfStacks / 2;
    GLfloat lastZ_XY = z;
    GLfloat currentZ_Z = z - radius;
    GLfloat lastX_XY = x + radius;
    GLfloat lastY_XY = y;
    GLfloat currentX_Z = x;
    GLfloat currentY_Z = y;
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
            GLfloat lastX_Z = x + (radius * cos(phiRadian) * cos(lastTetaRadian));
            GLfloat lastY_Z = y + (radius * cos(phiRadian) * sin(lastTetaRadian));
            currentX_Z = x + (radius * cos(phiRadian) * cos(tetaRadian));
            currentY_Z = y + (radius * cos(phiRadian) * sin(tetaRadian));

            if (phi != -90.0f)
            {
                m_vertices.push_back(lastX_XY);
                m_vertices.push_back(lastY_XY);
                m_vertices.push_back(lastZ_XY);
                m_colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col) & 0xFF) / 255.0);

                m_vertices.push_back(currentX_Z);
                m_vertices.push_back(currentY_Z);
                m_vertices.push_back(currentZ_Z);
                m_colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col) & 0xFF) / 255.0);

                m_vertices.push_back(currentX_XY);
                m_vertices.push_back(currentY_XY);
                m_vertices.push_back(lastZ_XY);
                m_colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col) & 0xFF) / 255.0);


                m_vertices.push_back(lastX_XY);
                m_vertices.push_back(lastY_XY);
                m_vertices.push_back(lastZ_XY);
                m_colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col) & 0xFF) / 255.0);

                m_vertices.push_back(lastX_Z);
                m_vertices.push_back(lastY_Z);
                m_vertices.push_back(currentZ_Z);
                m_colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col) & 0xFF) / 255.0);

                m_vertices.push_back(currentX_Z);
                m_vertices.push_back(currentY_Z);
                m_vertices.push_back(currentZ_Z);
                m_colors.push_back(((hex_col >> 16) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col >> 8) & 0xFF) / 255.0);
                m_colors.push_back(((hex_col) & 0xFF) / 255.0);
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