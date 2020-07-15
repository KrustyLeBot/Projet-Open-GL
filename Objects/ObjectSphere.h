#pragma once
#include "Object.h"

class ObjectSphere :
	public Object
{
public:
	ObjectSphere(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLint numberOfSectors, GLint numberOfStacks, GLint hex_col, GLboolean frameOnly);

protected:
};

