/**
 * A Implementation of the Cube class
 * @file        Cube.cc
 * @date        2017/01/09 20:05
 */

#include <stdio.h>

#include <GL/glut.h>

#include "Cube.hh"

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


CubePiece::CubePiece()
{
	reset();
}

CubePiece& CubePiece::operator= (const CubePiece& r)
{
	top = r.top;
	left = r.left;
	right = r.right;
	front = r.front;
	back = r.back;
	bottom = r.bottom;

	return *this;
}

void CubePiece::reset()
{
	top = YELLOW;
	left = RED;
	right = ORANGE;
	front = GREEN;
	back = BLUE;
	bottom = WHITE;
}

void CubePiece::rotate(DirectionE dir)
{
	ColorE tmp;
	switch (dir) {
		case UP_CW:
		case BOTTOM_CCW:
			tmp=left; left=front; front=right; right=back; back=tmp; break;
		case UP_CCW:
		case BOTTOM_CW:
			tmp=left; left=back; back=right; right=front; front=tmp; break;
		case LEFT_CCW:
		case RIGHT_CW:
			tmp=top; top=front; front=bottom; bottom=back; back=tmp; break;
		case LEFT_CW:
		case RIGHT_CCW:
			tmp=top; top=back; back=bottom; bottom=front; front=tmp; break;
		case FRONT_CW:
		case BACK_CCW:
			tmp=top; top=left; left=bottom; bottom=right; right=tmp; break;
		case FRONT_CCW:
		case BACK_CW:
			tmp=top; top=right; right=bottom; bottom=left; left=tmp; break;
	}
}

void CubePiece::draw()
{
	glPushMatrix();

	glScaled(scale, scale, scale);
	glBegin(GL_QUADS);
		COLOR(front);
		glNormal3f(0, 0, 1);
		glVertex3f( a,  a, 1);
		glVertex3f(-a,  a, 1);
		glVertex3f(-a, -a, 1);
		glVertex3f( a, -a, 1);

		COLOR(left);
		glNormal3f(-1, 0, 0);
		glVertex3f(-1,  a,  a);
		glVertex3f(-1,  a, -a);
		glVertex3f(-1, -a, -a);
		glVertex3f(-1, -a,  a);

		COLOR(right);
		glNormal3f(1, 0, 0);
		glVertex3f(1,  a,  a);
		glVertex3f(1, -a,  a);
		glVertex3f(1, -a, -a);
		glVertex3f(1,  a, -a);

		COLOR(back);
		glNormal3f(0, 0, -1);
		glVertex3f( a,  a, -1);
		glVertex3f( a, -a, -1);
		glVertex3f(-a, -a, -1);
		glVertex3f(-a,  a, -1);

		COLOR(top);
		glNormal3f(0, 1, 0);
		glVertex3f( a, 1,  a);
		glVertex3f( a, 1, -a);
		glVertex3f(-a, 1, -a);
		glVertex3f(-a, 1,  a);

		COLOR(bottom);
		glNormal3f(0, -1, 0);
		glVertex3f( a, -1,  a);
		glVertex3f(-a, -1,  a);
		glVertex3f(-a, -1, -a);
		glVertex3f( a, -1, -a);
	glEnd();

	glPopMatrix();
}


Cube::Cube()
{
	rotating = false;
	angle = 0;

	curDir = UP_CW;

	selnum = 0;
	selax = AXIS_X;
}

Cube::~Cube()
{
}

void Cube::rotate(DirectionE dir)
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

	startRotate();
}

void Cube::startRotate()
{
	rotating = true;
	angle = 0;
}

void Cube::rotateCommit(int h)
{
	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			switch(selax) {
				case AXIS_X:
					elem[h][i][j].rotate(curDir);
					break;
				case AXIS_Y:
					elem[i][h][j].rotate(curDir);
					break;
				case AXIS_Z:
					elem[i][j][h].rotate(curDir);
					break;
			}
		}
	}

	CubePiece tmp;

	switch (curDir) {
		case UP_CW:
		case BOTTOM_CCW:
			tmp = elem[0][h][0];
			elem[0][h][0] = elem[2][h][0];
			elem[2][h][0] = elem[2][h][2];
			elem[2][h][2] = elem[0][h][2];
			elem[0][h][2] = tmp;
			tmp = elem[1][h][0];
			elem[1][h][0] = elem[2][h][1];
			elem[2][h][1] = elem[1][h][2];
			elem[1][h][2] = elem[0][h][1];
			elem[0][h][1] = tmp;
			break;
		case UP_CCW:
		case BOTTOM_CW:
			tmp = elem[0][h][0];
			elem[0][h][0] = elem[0][h][2];
			elem[0][h][2] = elem[2][h][2];
			elem[2][h][2] = elem[2][h][0];
			elem[2][h][0] = tmp;
			tmp = elem[1][h][0];
			elem[1][h][0] = elem[0][h][1];
			elem[0][h][1] = elem[1][h][2];
			elem[1][h][2] = elem[2][h][1];
			elem[2][h][1] = tmp;
			break;
		case LEFT_CCW:
		case RIGHT_CW:
			tmp = elem[h][0][0];
			elem[h][0][0] = elem[h][2][0];
			elem[h][2][0] = elem[h][2][2];
			elem[h][2][2] = elem[h][0][2];
			elem[h][0][2] = tmp;
			tmp = elem[h][1][0];
			elem[h][1][0] = elem[h][1][0];
			elem[h][1][0] = elem[h][2][1];
			elem[h][2][1] = elem[h][1][2];
			elem[h][1][2] = tmp;
			break;
		case LEFT_CW:
		case RIGHT_CCW:
			tmp = elem[h][0][0];
			elem[h][0][0] = elem[h][0][2];
			elem[h][0][2] = elem[h][2][2];
			elem[h][2][2] = elem[h][2][0];
			elem[h][2][0] = tmp;
			tmp = elem[h][1][0];
			elem[h][1][0] = elem[h][0][1];
			elem[h][0][1] = elem[h][1][2];
			elem[h][1][2] = elem[h][2][1];
			elem[h][2][1] = tmp;
			break;

		case FRONT_CW:
		case BACK_CCW:
			tmp = elem[0][0][h];
			elem[0][0][h] = elem[0][2][h];
			elem[0][2][h] = elem[2][2][h];
			elem[2][2][h] = elem[2][0][h];
			elem[2][0][h] = tmp;
			tmp = elem[1][0][h];
			elem[1][0][h] = elem[0][1][h];
			elem[0][1][h] = elem[1][2][h];
			elem[1][2][h] = elem[2][1][h];
			elem[2][1][h] = tmp;
			break;
		case FRONT_CCW:
		case BACK_CW:
			tmp = elem[0][0][h];
			elem[0][0][h] = elem[2][0][h];
			elem[2][0][h] = elem[2][2][h];
			elem[2][2][h] = elem[0][2][h];
			elem[0][2][h] = tmp;
			tmp = elem[1][0][h];
			elem[1][0][h] = elem[1][0][h];
			elem[1][0][h] = elem[2][1][h];
			elem[2][1][h] = elem[1][2][h];
			elem[1][2][h] = tmp;
			break;
	}
#if 0
	fprintf(stderr,  " Rotate dir=%d axis=%d  h=%d\n", curDir, selax, h);
	for (int y=0; y<3; y++) {
		for (int x=0; x<3; x++) {
			fprintf(stderr, " %d", elem[x][y][0].front);
		}
		fprintf(stderr, "\n");
	}
	fprintf(stderr, "--------\n");
#endif
}

void Cube::drawArrow()
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

void Cube::draw()
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
		rotateCommit(selnum);

		//glutPostRedisplay();
	}

	drawArrow();
}

void Cube::drawAxisXLayer(int h)
{
	glPushMatrix();
	glTranslatef((h-1)*2, 2, 2);

	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			elem[h][i][j].draw();
			glTranslatef(0,0,-2);
		}
		glTranslatef(0,-2,6);
	}
	glPopMatrix();
}

void Cube::drawAxisYLayer(int h)
{
	glPushMatrix();
	glTranslatef(-2, (1-h)*2, 2);

	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			elem[i][h][j].draw();
			glTranslatef(0,0,-2);
		}
		glTranslatef(2,0,6);
	}
	glPopMatrix();
}

void Cube::drawAxisZLayer(int h)
{
	glPushMatrix();
	glTranslatef(-2, 2, (1-h)*2);

	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			elem[i][j][h].draw();
			glTranslatef(0,-2,0);
		}
		glTranslatef(2,6,0);
	}
	glPopMatrix();
}

