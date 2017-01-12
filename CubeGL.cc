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
		//Cube::rotate();
		Cube::rotateCommit(selnum);

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

		COLOR(piece.bottom);
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
	curDir = dir;

	switch (dir) {
		case UP_CW:
		case UP_CCW:
		case LEFT_CW:
		case LEFT_CCW:
		case FRONT_CW:
		case FRONT_CCW:
			selnum = 0;
			break;

		case BOTTOM_CW:
		case BOTTOM_CCW:
		case RIGHT_CW:
		case RIGHT_CCW:
		case BACK_CW:
		case BACK_CCW:
			selnum = 2;
			break;
	}

	switch (dir) {
		case LEFT_CW:
		case LEFT_CCW:
		case RIGHT_CW:
		case RIGHT_CCW:
			selax = AXIS_X;
			break;

		case UP_CW:
		case UP_CCW:
		case BOTTOM_CW:
		case BOTTOM_CCW:
			selax = AXIS_Y;
			break;

		case FRONT_CW:
		case FRONT_CCW:
		case BACK_CW:
		case BACK_CCW:
			selax = AXIS_Z;
			break;
	}

	switch (dir) {
		case UP_CCW:
		case LEFT_CW:
		case RIGHT_CCW:
		case BOTTOM_CW:
		case FRONT_CCW:
		case BACK_CW:
			seldeg = 10;
			break;

		case UP_CW:
		case LEFT_CCW:
		case RIGHT_CW:
		case BOTTOM_CCW:
		case FRONT_CW:
		case BACK_CCW:
			seldeg = -10;
			break;
	}

#if 0
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			switch(selax) {
				case AXIS_X:
					pCube[i][j] = & elem[selnum][i][j];
					break;
				case AXIS_Y:
					pCube[i][j] = & elem[i][selnum][j];
					break;
				case AXIS_Z:
					pCube[i][j] = & elem[j][i][selnum];
					break;
			}
		}
	}
#endif

	startRotate();
}

void CubeGL::startRotate()
{
	rotating = true;
	angle = 0;
}

