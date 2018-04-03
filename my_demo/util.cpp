#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <cxcore.hpp>
#include <cv.hpp>

#include "mysdl.h"
#include "gl.h"
#include "vgl.h"

#ifndef M_PI
#define M_PI       3.14159265358979323846   // pi
#endif

static void __identf(GLfloat m[])
{
	memset(m, 0, sizeof m[0] * 16);
	m[0] = m[5] = m[10] = m[15] = 1.0f;
}

static void normalizef(float v[3])
{
	float r;

	r = (float)sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
	if (r == 0.0)
		return;
	r = 1.f / r;

	v[0] *= r;
	v[1] *= r;
	v[2] *= r;
}

static void crossf(float v0[3], float v1[3], float r[3])
{
	r[0] = v0[1] * v1[2] - v0[2] * v1[1];
	r[1] = v0[2] * v1[0] - v0[0] * v1[2];
	r[2] = v0[0] * v1[1] - v0[1] * v1[0];
}

void uLookAtf(GLfloat eyex, GLfloat eyey, GLfloat eyez, GLfloat centerx,
	GLfloat centery, GLfloat centerz, GLfloat upx, GLfloat upy, GLfloat upz)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLfloat forward[3], side[3], up[3];
	GLfloat m[4][4];

	forward[0] = centerx - eyex;
	forward[1] = centery - eyey;
	forward[2] = centerz - eyez;

	normalizef(forward);

	up[0] = upx;
	up[1] = upy;
	up[2] = upz;

	crossf(forward, up, side);

	normalizef(side);
	crossf(side, forward, up);

	__identf(&m[0][0]);
	m[0][0] = side[0];
	m[1][0] = side[1];
	m[2][0] = side[2];

	m[0][1] = up[0];
	m[1][1] = up[1];
	m[2][1] = up[2];

	m[0][2] = -forward[0];
	m[1][2] = -forward[1];
	m[2][2] = -forward[2];

	glMultMatrixf(&m[0][0]);
	glTranslatef(-eyex, -eyey, -eyez);
}

void mult_vect(float *r, float *m, float *v) 
{
	float w;
	w = m[3] * v[0] + m[7] * v[1] + m[11] * v[2] + m[15];
	r[0] = (m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3]) / w;
	r[1] = (m[4] * v[0] + m[5] * v[1] + m[6] * v[2] + m[7]) / w;
	r[2] = (m[8] * v[0] + m[9] * v[1] + m[10] * v[2] + m[11])/w;
}

void uRotate(float *m, GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
	GLfloat sinAngle, cosAngle;
	GLfloat mag = sqrtf(x * x + y * y + z * z);

	sinAngle = sinf(angle * M_PI / 180.0f);
	cosAngle = cosf(angle * M_PI / 180.0f);
	if (mag > 0.0f)
	{
		GLfloat xx, yy, zz, xy, yz, zx, xs, ys, zs;
		GLfloat oneMinusCos;


		x /= mag;
		y /= mag;
		z /= mag;

		xx = x * x;
		yy = y * y;
		zz = z * z;
		xy = x * y;
		yz = y * z;
		zx = z * x;
		xs = x * sinAngle;
		ys = y * sinAngle;
		zs = z * sinAngle;
		oneMinusCos = 1.0f - cosAngle;

		m[0] = (oneMinusCos * xx) + cosAngle;
		m[1] = (oneMinusCos * xy) - zs;
		m[2] = (oneMinusCos * zx) + ys;
		m[3] = 0.0F;

		m[4] = (oneMinusCos * xy) + zs;
		m[5] = (oneMinusCos * yy) + cosAngle;
		m[6] = (oneMinusCos * yz) - xs;
		m[7] = 0.0F;

		m[8] = (oneMinusCos * zx) - ys;
		m[9] = (oneMinusCos * yz) + xs;
		m[10] = (oneMinusCos * zz) + cosAngle;
		m[11] = 0.0F;

		m[12] = 0.0F;
		m[13] = 0.0F;
		m[14] = 0.0F;
		m[15] = 1.0F;

	}
}
