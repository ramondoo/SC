#pragma once
#include "GL/GL.h"

void uLookAtf(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx,
	GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy, GLfloat upz);

void uRotate(float *m, GLfloat angle, GLfloat x, GLfloat y, GLfloat z);

void mult_vect(float *r, float *m, float *v);