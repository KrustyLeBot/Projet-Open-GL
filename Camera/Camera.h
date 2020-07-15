#pragma once
#include "../glad/glad.h"

class Camera
{
public:
	Camera();
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void lookAt(GLfloat x, GLfloat y, GLfloat z);

protected:
};

