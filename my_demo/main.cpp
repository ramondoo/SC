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
#include "util.h"

#ifndef M_PI
#define M_PI       3.14159265358979323846   // pi
#endif




#define	WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

/* Re-introduce 32-bit word encoding of 32-bit RGBA values */
#define GL_UNSIGNED_INT_8_8_8_8           0x8035
#define GL_UNSIGNED_INT_8_8_8_8_REV       0x8367

MySDL_Surface *sdlSurface;
VGL_Surface glSurface;

std::vector<GLfloat> vertices;
std::vector<GLfloat> textures;
std::vector<GLuint> element;

__inline static void glColor3fv(const GLfloat *v) {
	glColor4f(v[0], v[1], v[2], 1.0f);
}

void load_obj(const char* filename,
	std::vector<GLfloat> &vertices,
	std::vector<GLfloat> &textures,
	std::vector<GLuint> &elements)
{
	//vertices.push_back(0);
	//vertices.push_back(0);
	//vertices.push_back(0);

	//vertices.push_back(5000);
	//vertices.push_back(0);
	//vertices.push_back(0);

	//vertices.push_back(0);
	//vertices.push_back(5000);
	//vertices.push_back(0);

	//textures.push_back(1);
	//textures.push_back(0);
	//textures.push_back(0);


	//textures.push_back(0);
	//textures.push_back(1);
	//textures.push_back(0);



	//textures.push_back(0);
	//textures.push_back(0);
	//textures.push_back(1);

	//elements.push_back(0);
	//elements.push_back(1);
	//elements.push_back(2);

	//return;

	std::ifstream ifs(filename, std::ios::in);
	if (!ifs)
	{
		std::cerr << "Cannot open " << filename << std::endl;
		exit(1);
	}

	std::string line;

	while (std::getline(ifs, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			std::istringstream s(line.substr(2));
			GLfloat fff;
			s >> fff;
			vertices.push_back(fff);
			s >> fff;
			vertices.push_back(fff);
			s >> fff;
			vertices.push_back(fff);

			s >> fff;
			textures.push_back(fff);
			s >> fff;
			textures.push_back(fff);
			s >> fff;
			textures.push_back(fff);

		}
		else if (line.substr(0, 2) == "f ")
		{
			std::istringstream s(line.substr(2));
			GLuint a, b, c;
			s >> a;
			s >> b;
			s >> c;
			a--; b--; c--;

			elements.push_back(a);
			elements.push_back(b);
			elements.push_back(c);
		}
		else if (line[0] == '#')
		{
			/* ignoring this line */
		}
		else
		{
			/* ignoring this line */
		}
	}

	ifs.close();
}




void drawBowl(GLfloat* vertex, GLfloat* color, GLuint* faces, int numIdx)
{
	//glColor3fv(
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	glBegin(GL_TRIANGLES);
	
	for (int j = 0; j < numIdx; j += 3)
	{
		glColor3fv(&color[faces[j + 0] * 3]);
		glVertex3fv(&vertex[faces[j + 0] * 3]);

		glColor3fv(&color[faces[j + 1] * 3]);
		glVertex3fv(&vertex[faces[j + 1] * 3]);

		glColor3fv(&color[faces[j + 2] * 3]);
		glVertex3fv(&vertex[faces[j + 2] * 3]);
	}

	glEnd();

}






//
/// \brief multiply matrix specified by result with a perspective matrix and return new matrix in result
/// \param fovy Field of view y angle in degrees
/// \param aspect Aspect ratio of screen
/// \param nearZ Near plane distance
/// \param farZ Far plane distance
//
void myPerspective(float fovy, float aspect, float nearZ, float farZ)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float top = nearZ * tanf(0.5f * M_PI * fovy / 180.0f);

	glFrustumf(
		-aspect*top,  /* left   */
		aspect*top,   /* right  */
		-top,         /* bottom */
		top,          /* top    */
		nearZ, 
		farZ);

	glMatrixMode(GL_MODELVIEW);
}

void display(void)
{
	int64 st = cv::getTickCount();
	static int degrees = 0;

	GLfloat m[4][4];

	uRotate((float*)m, degrees, 0, 0, 1);

	degrees += 1;
	if (degrees == 360)
		degrees = 0;

	float eye[3] = { 0, -8000, 5000 };
	float up[3] = { 0, 5000, 8000 };

	float eyer[3] = { 0, 0, 17000 };
	float upr[3] = { 0, 1, 0 };

	mult_vect(eyer, &m[0][0], eye);
	mult_vect(upr,  &m[0][0], up);

	float t = sqrt(upr[0] * upr[0] + upr[1] * upr[1] + upr[2] * upr[2]);



	uLookAtf(eyer[0], eyer[1], eyer[2], 0, 0, 0, upr[0]/t, upr[1]/t, upr[2]/t);


	myPerspective(100.0f, ((float)WINDOW_WIDTH)/ WINDOW_HEIGHT, 2.0f, 42000.0f);

	

	drawBowl(&vertices[0], &textures[0], &element[0], element.size());



	vglSwapBuffers(sdlSurface, glSurface);


	int64 et = cv::getTickCount();
	printf("time=%f ms\n", (et - st)*1000.0 / cv::getTickFrequency());


	cv::Mat img(sdlSurface->h, sdlSurface->w, CV_8UC4, sdlSurface->pixels, sdlSurface->pitch);
	cv::Mat v[4];
	cv::split(img, v);

	cv::swap(v[0], v[2]);
	cv::Mat img2;
	cv::merge(v, 3, img2);

	cv::namedWindow("T");
	cv::imshow("T", img2);
	cv::waitKey(10);
}


void resize(int x, int y)
{
	//glScissor(WINDOW_WIDTH/10, WINDOW_HEIGHT/10, WINDOW_WIDTH*7/10, WINDOW_HEIGHT*7/10);
	glScissor(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glEnable(GL_SCISSOR_TEST);

	display();
}





int main(int argc, char* argv[])
{
	load_obj("./bowl.obj", vertices, textures, element);

	vglInitialize();

	union {
		GLubyte rgba[4];
		GLuint mask;
	} translate;
	GLuint redMask, greenMask, blueMask, alphaMask;
	translate.mask = 0, translate.rgba[0] = 0xffu, redMask = translate.mask;
	translate.mask = 0, translate.rgba[1] = 0xffu, greenMask = translate.mask;
	translate.mask = 0, translate.rgba[2] = 0xffu, blueMask = translate.mask;
	translate.mask = 0, translate.rgba[3] = 0 /*xffu */, alphaMask = translate.mask;

	sdlSurface = MySDL_CreateRGBSurface(WINDOW_WIDTH, WINDOW_HEIGHT, 32,
		redMask, greenMask, blueMask, alphaMask);

	glSurface = vglCreateSurface(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8_REV, 0);

	vglMakeCurrent(glSurface, glSurface);

	resize(WINDOW_WIDTH, WINDOW_HEIGHT);
	display();

	for (;;)
	{
		display();
	}

	return 0;
}
