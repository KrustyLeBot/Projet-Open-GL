#include "Object.h"

extern GLfloat camPosZ;
extern GLfloat rangeZ;

Object::Object(GLboolean frameOnly)
    : m_frameOnly(frameOnly)
    , m_mode(GL_TRIANGLES)
    , m_rotateAngleX(0)
    , m_rotateAngleY(0)
    , m_rotateAngleZ(0)
    , m_centerX(0)
    , m_centerY(0)
    , m_centerZ(0)
    , m_scaleX(0)
    , m_scaleY(0)
    , m_scaleZ(0)
    , m_moveX(0)
    , m_moveY(0)
    , m_moveZ(0)
    , m_moveRelX(0)
    , m_moveRelY(0)
    , m_moveRelZ(0)
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
    glScalef(m_scaleX, m_scaleY, m_scaleZ);
    glRotatef(m_rotateAngleX, 1, 0, 0);
    glRotatef(m_rotateAngleY, 0, 1, 0);
    glRotatef(m_rotateAngleZ, 0, 0, 1);
    glTranslatef(-m_centerX - m_moveRelX, -m_centerY - m_moveRelY, -m_centerZ - m_moveRelZ);
    moveRelativ(0, 0, 0);
    if (m_moveX != 0 || m_moveY != 0 || m_moveZ != 0)
    {
        glTranslatef(-m_moveX, -m_moveY, -m_moveZ);
        m_centerX = m_moveX;
        m_centerY = m_moveY;
        m_centerZ = m_moveZ;
        move(0, 0, 0);
    }
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

void Object::setScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ)
{
    m_scaleX = scaleX;
    m_scaleY = scaleY;
    m_scaleZ = scaleZ;
}

void Object::move(GLfloat moveX, GLfloat moveY, GLfloat moveZ)
{
    m_moveX = moveX;
    m_moveY = moveY;
    m_moveZ = moveZ;
}

void Object::moveRelativ(GLfloat moveX, GLfloat moveY, GLfloat moveZ)
{
    m_moveRelX = moveX;
    m_moveRelY = moveY;
    m_moveRelZ = moveZ;
}