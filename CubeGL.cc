/**
 * A Implementation of the CubeGL class
 * @file        CubeGL.cc
 * @date        2017/01/12 13:34
 */

#include <GL/glut.h>

#include "CubeGL.hh"

void COLOR(ColorE  col)
{
	const GLfloat colors[][3] = {
		{ 0.1, 0.1, 0.1 },
		{ 1.0, 1.0, 0.0 },
		{ 0.8, 0.0, 0.0 },
		{ 1.0, 0.5, 0.0 },
		{ 0.0, 0.8, 0.0 },
		{ 0.0, 0.0, 1.0 },
		{ 0.9, 0.9, 0.9 },
	};

	glColor3f(colors[col][0], colors[col][1], colors[col][2]);
}

float scale = 0.95;
float a = 1.0;


CubeGL::CubeGL() : Cube()
{
	rotating = false;
	angle = 0;

	selax = AXIS_X;
}

CubeGL::~CubeGL()
{
}

void CubeGL::drawArrow()
{
	glPushMatrix();

	glTranslatef(0,0,6);
	glBegin(GL_TRIANGLES);
		glColor3f(1,0,0);
		glVertex3f(0,0,0);
		glVertex3f(0.5,0,1);
		glVertex3f(0,0,0.8);

		glColor3f(1,1,1);
		glVertex3f(0,0,0);
		glVertex3f(0,0,0.8);
		glVertex3f(0,0.5,1);
	glEnd();

	glPopMatrix();
}

void CubeGL::draw()
{
	if (rotating == true) {
		angle += seldeg;
	}

	for (int h=0; h<3; h++) {
		if (rotating && h == selnum) {
			// for animation
			glPushMatrix();
			glRotatef(angle, (selax==AXIS_X)?1:0,
					(selax==AXIS_Y)?1:0,
					(selax==AXIS_Z)?1:0);
		}

		switch (selax) {
			case AXIS_X: drawAxisXLayer(h); break;
			case AXIS_Y: drawAxisYLayer(h); break;
			case AXIS_Z: drawAxisZLayer(h); break;
		}

		if (rotating && h == selnum) {
			glPopMatrix();
		}
	}

	if (rotating == true && (angle <= -90 || angle >= 90)) {
		rotating = false;

		Cube::rotate(seldir);

		glutPostRedisplay();
	}

	drawArrow();
}

void CubeGL::drawPiece(CubePiece& piece)
{
	glPushMatrix();

	glScaled(scale, scale, scale);
	glBegin(GL_QUADS);
		COLOR(piece.front);
		glNormal3f(0, 0, 1);
		glVertex3f( a,  a, 1);
		glVertex3f(-a,  a, 1);
		glVertex3f(-a, -a, 1);
		glVertex3f( a, -a, 1);

		COLOR(piece.left);
		glNormal3f(-1, 0, 0);
		glVertex3f(-1,  a,  a);
		glVertex3f(-1,  a, -a);
		glVertex3f(-1, -a, -a);
		glVertex3f(-1, -a,  a);

		COLOR(piece.right);
		glNormal3f(1, 0, 0);
		glVertex3f(1,  a,  a);
		glVertex3f(1, -a,  a);
		glVertex3f(1, -a, -a);
		glVertex3f(1,  a, -a);

		COLOR(piece.back);
		glNormal3f(0, 0, -1);
		glVertex3f( a,  a, -1);
		glVertex3f( a, -a, -1);
		glVertex3f(-a, -a, -1);
		glVertex3f(-a,  a, -1);

		COLOR(piece.top);
		glNormal3f(0, 1, 0);
		glVertex3f( a, 1,  a);
		glVertex3f( a, 1, -a);
		glVertex3f(-a, 1, -a);
		glVertex3f(-a, 1,  a);

		COLOR(piece.down);
		glNormal3f(0, -1, 0);
		glVertex3f( a, -1,  a);
		glVertex3f(-a, -1,  a);
		glVertex3f(-a, -1, -a);
		glVertex3f( a, -1, -a);
	glEnd();

	glPopMatrix();
}

void CubeGL::drawAxisXLayer(int h)
{
	glPushMatrix();
	glTranslatef((h-1)*2, 2, 2);

	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			drawPiece(elem[h][i][j]);
			glTranslatef(0,0,-2);
		}
		glTranslatef(0,-2,6);
	}
	glPopMatrix();
}

void CubeGL::drawAxisYLayer(int h)
{
	glPushMatrix();
	glTranslatef(-2, (1-h)*2, 2);

	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			drawPiece(elem[i][h][j]);
			glTranslatef(0,0,-2);
		}
		glTranslatef(2,0,6);
	}
	glPopMatrix();
}

void CubeGL::drawAxisZLayer(int h)
{
	glPushMatrix();
	glTranslatef(-2, 2, (1-h)*2);

	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			drawPiece(elem[i][j][h]);
			glTranslatef(0,-2,0);
		}
		glTranslatef(2,6,0);
	}
	glPopMatrix();
}

void CubeGL::rotate(DirectionE dir)
{
	if (rotating == true) return;

	seldir = dir;
	selnum = getRotateRow(dir);
	selax = getAxis(dir);

	if (getRotateDirection(dir) == ROTATE_CW) {
		seldeg = 10;
	} else {
		seldeg = -10;
	}

	startRotate();
}

void CubeGL::startRotate()
{
	rotating = true;
	angle = 0;
}

