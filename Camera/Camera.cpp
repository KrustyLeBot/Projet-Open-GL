#include "Camera.h"

Camera::Camera()
{
}

void Camera::setPosition(GLfloat x, GLfloat y, GLfloat z)
{
	glTranslatef(x, y, z);
}

void Camera::lookAt(GLfloat x, GLfloat y, GLfloat z)
{
	glRotatef(x, 1, 0, 0);
	glRotatef(y, 0, 1, 0);
	glRotatef(z, 0, 0, 1);
}