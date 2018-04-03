//
//#ifdef _WIN32
//#include <windows.h>
//#include <tchar.h>
//#include <mmsystem.h>
////#define snprintf _snprintf
//#endif
//
//#include "gl.h"
////#include "ug.h"
//#include <math.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stdlib.h>
//#include <fstream>
//#include <iostream>
//#include <vector>
//#include <string>
//#include <sstream>
//
//#ifndef M_PI  /* some math header doesn't define it */
//#define M_PI 3.14159265359f
//#endif
//
//
//
//
//void DrawBowl()
//{
//	float m[16];
//	float modelmat[16], projmat[16];
//
//	glGetFloatv(GL_MODELVIEW_MATRIX, modelmat);
//	glGetFloatv(GL_PROJECTION_MATRIX, projmat);
//	m[2] = modelmat[2];
//	m[6] = modelmat[6];
//	m[10] = modelmat[10];
//	m[14] = modelmat[14];
//	doDrawBowl();
//
//}
//
//GLvoid DrawGLScene0()
//{
//	static unsigned long begin_time; /* first time thisfunction is called */
//	static unsigned long time, diftime, oldtimeframe; /* last one used to compute frame per sec */
//	static int nbframe = 0;
//	float fps;
//	static int flag_firstcall = 1;
//	static float angle = 0.0f;
//	char wndtitle[256];
//	float dist; /* camera distance from origin */
//
//	if (flag_firstcall)
//	{
//		oldtimeframe = timeGetTime();
//		flag_firstcall = 0;
//		begin_time = oldtimeframe;
//	}
//
//	time = timeGetTime();
//
//	angle = (float)(timeGetTime() - begin_time) / 100; /* angle in degree */
//	angle = (angle + 180.0f) / 180.0f * M_PI;          /* angle in radian */
//													   /* compute camera distance from the origin */
//	if (maxDist*tan(aperture*M_PI / 360.0f)*2.0f < maxZ)
//		dist = maxZ / tan(aperture*M_PI / 360.0f) / 2.0f;
//	else
//		dist = 0.5f + maxDist;
//
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	/* glMatrixMode(GL_MODELVIEW); */
//	glLoadIdentity();
//	ugluLookAtf(dist*cosf(angle), dist*sinf(angle), maxZ,                /* eye position */
//		0.0f, 0.0f, maxZ + 1.0f - dist*tan(aperture*M_PI / 360.0f),  /* target       */
//		0.0f, 0.0f, 1.0f);                                     /* up vector    */
//
//
//	draw();
//
//	if (time - oldtimeframe > 200.0f)
//	{
//		fps = (float)nbframe*1000.0f / (float)(time - oldtimeframe);
//		oldtimeframe = time;
//		nbframe = 0;
//	}
//	nbframe++;
//}
//
//
//void do_load_obj()
//{
//	load_obj("./front.obj", vertices, textures, element);
//}
//
//void doDrawBowl()
//{
//	drawBowl(&vertices[0], &textures[0], &element[0], element.size());
//}