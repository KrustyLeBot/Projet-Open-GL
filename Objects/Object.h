#pragma once
#include <vector>
#include "../glad/glad.h"

class Object
{
public:
	Object(GLboolean frameOnly);
	void display();
	void setRotation(GLfloat rotateAngleX, GLfloat rotateAngleY, GLfloat rotateAngleZ);
	void setScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ);

protected:
	std::vector<GLfloat> m_vertices;
	std::vector<GLfloat> m_colors;
	GLenum m_mode;
	GLboolean m_frameOnly;

	GLfloat m_rotateAngleX;
	GLfloat m_rotateAngleY;
	GLfloat m_rotateAngleZ;

	GLfloat m_centerX;
	GLfloat m_centerY;
	GLfloat m_centerZ;

	GLfloat m_scaleX;
	GLfloat m_scaleY;
	GLfloat m_scaleZ;
};

