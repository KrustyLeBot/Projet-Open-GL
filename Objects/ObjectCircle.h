#pragma once
#include "Object.h"
class ObjectCircle :
	public Object
{
public:
	ObjectCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSides, GLint hex_col, GLboolean frameOnly);

protected:
};

