#pragma once
#include "Object.h"
class ObjectRectangle :
	public Object
{
public:
	ObjectRectangle(GLfloat x_a, GLfloat y_a, GLfloat x_b, GLfloat y_b, GLfloat x_c, GLfloat y_c, GLfloat x_d, GLfloat y_d, GLfloat z, GLint hex_col_a, GLint hex_col_b, GLint hex_col_c, GLint hex_col_d, GLboolean frameOnly);

protected:
};

