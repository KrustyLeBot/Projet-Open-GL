#include "ObjectRectangle.h"

ObjectRectangle::ObjectRectangle(GLfloat x_a, GLfloat y_a, GLfloat x_b, GLfloat y_b, GLfloat x_c, GLfloat y_c, GLfloat x_d, GLfloat y_d, GLfloat z, GLint hex_col_a, GLint hex_col_b, GLint hex_col_c, GLint hex_col_d, GLboolean frameOnly)
	: Object::Object(frameOnly)
{
    m_mode = GL_QUADS;
    m_centerX = (x_a + x_c)/2;
    m_centerY = (y_a + y_c) / 2;
    m_centerZ = z;


    m_vertices =
    {
        x_a, y_a, z,
        x_b, y_b, z,
        x_c, y_c, z,
        x_d, y_d, z,
    };

    m_colors.push_back(((hex_col_a >> 16) & 0xFF) / 255.0);
    m_colors.push_back(((hex_col_a >> 8) & 0xFF) / 255.0);
    m_colors.push_back(((hex_col_a) & 0xFF) / 255.0);

    m_colors.push_back(((hex_col_b >> 16) & 0xFF) / 255.0);
    m_colors.push_back(((hex_col_b >> 8) & 0xFF) / 255.0);
    m_colors.push_back(((hex_col_b) & 0xFF) / 255.0);

    m_colors.push_back(((hex_col_c >> 16) & 0xFF) / 255.0);
    m_colors.push_back(((hex_col_c >> 8) & 0xFF) / 255.0);
    m_colors.push_back(((hex_col_c) & 0xFF) / 255.0);

    m_colors.push_back(((hex_col_d >> 16) & 0xFF) / 255.0);
    m_colors.push_back(((hex_col_d >> 8) & 0xFF) / 255.0);
    m_colors.push_back(((hex_col_d) & 0xFF) / 255.0);
}