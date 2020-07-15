#include "Object.h"

Object::Object(GLboolean frameOnly)
    : m_frameOnly(frameOnly)
    , m_mode(GL_TRIANGLES)
    , m_rotateAngleX(0)
    , m_rotateAngleY(0)
    , m_rotateAngleZ(0)
    , m_centerX(0)
    , m_centerY(0)
    , m_centerZ(0)
{
}

void Object::display()
{
    if (m_frameOnly)
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
    glVertexPointer(3, GL_FLOAT, 0, m_vertices.data());
    glColorPointer(3, GL_FLOAT, 0, m_colors.data());

    /* Send data : 24 vertices */
    glPushMatrix();
    glTranslatef(m_centerX, m_centerY, m_centerZ);
    glRotatef(m_rotateAngleX, 1, 0, 0);
    glRotatef(m_rotateAngleY, 0, 1, 0);
    glRotatef(m_rotateAngleZ, 0, 0, 1);
    glTranslatef(-m_centerX, -m_centerY, -m_centerZ);
    glDrawArrays(m_mode, 0, m_vertices.size() / 3);
    glPopMatrix();

    /* Cleanup states */
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void Object::setRotation(GLfloat rotateAngleX, GLfloat rotateAngleY, GLfloat rotateAngleZ)
{
    m_rotateAngleX = rotateAngleX;
    m_rotateAngleY = rotateAngleY;
    m_rotateAngleZ = rotateAngleZ;
}