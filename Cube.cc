/**
 * A Implementation of the Cube class
 * @file        Cube.cc
 * @date        2017/01/09 20:05
 */

#include <stdio.h>
#include <string.h>

#include "Cube.hh"

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
	down = r.down;

	return *this;
}

void CubePiece::reset()
{
	top = YELLOW;
	left = RED;
	right = ORANGE;
	front = GREEN;
	back = BLUE;
	down = WHITE;
}

void CubePiece::rotate(DirectionE dir)
{
	ColorE tmp;
	switch (dir) {
		case UP_CW:
		case DOWN_CCW:
			tmp=left; left=front; front=right; right=back; back=tmp; break;
		case UP_CCW:
		case DOWN_CW:
			tmp=left; left=back; back=right; right=front; front=tmp; break;
		case LEFT_CCW:
		case RIGHT_CW:
			tmp=top; top=front; front=down; down=back; back=tmp; break;
		case LEFT_CW:
		case RIGHT_CCW:
			tmp=top; top=back; back=down; down=front; front=tmp; break;
		case FRONT_CW:
		case BACK_CCW:
			tmp=top; top=left; left=down; down=right; right=tmp; break;
		case FRONT_CCW:
		case BACK_CW:
			tmp=top; top=right; right=down; down=left; left=tmp; break;
	}
}



//
// Cube class implements
//

Cube::Cube()
{
}

Cube::~Cube()
{
}

RotateAxisE Cube::getAxis(DirectionE dir)
{
	RotateAxisE ax = AXIS_X;

	switch (dir) {
		case LEFT_CW:
		case LEFT_CCW:
		case RIGHT_CW:
		case RIGHT_CCW:
			ax = AXIS_X;
			break;

		case UP_CW:
		case UP_CCW:
		case DOWN_CW:
		case DOWN_CCW:
			ax = AXIS_Y;
			break;

		case FRONT_CW:
		case FRONT_CCW:
		case BACK_CW:
		case BACK_CCW:
			ax = AXIS_Z;
			break;
	}

	return ax;
}

// via Rotate Axis
RotateDirE Cube::getRotateDirection(DirectionE dir)
{
	RotateDirE rd = ROTATE_CW;

	switch (dir) {
		case UP_CCW:
		case LEFT_CW:
		case RIGHT_CCW:
		case DOWN_CW:
		case FRONT_CCW:
		case BACK_CW:
			rd = ROTATE_CW;
			break;

		case UP_CW:
		case LEFT_CCW:
		case RIGHT_CW:
		case DOWN_CCW:
		case FRONT_CW:
		case BACK_CCW:
			rd = ROTATE_CCW;
			break;
	}

	return rd;
}

int Cube::getRotateRow(DirectionE dir)
{
	int idx = 0;

	switch (dir) {
		case UP_CW:
		case UP_CCW:
		case LEFT_CW:
		case LEFT_CCW:
		case FRONT_CW:
		case FRONT_CCW:
			idx = 0;
			break;

		case DOWN_CW:
		case DOWN_CCW:
		case RIGHT_CW:
		case RIGHT_CCW:
		case BACK_CW:
		case BACK_CCW:
			idx = 2;
			break;
	}

	return idx;
}

void Cube::rotate(DirectionE dir)
{
	int row = getRotateRow(dir);

	CubePiece* pCube[3][3];	// for easy rotating
	memset(pCube, 0, sizeof(pCube));

	for (int i=0; i<3; i++) {
		for (int j=0; j<3; j++) {
			switch( getAxis(dir) ) {
				case AXIS_X:
					pCube[i][j] = & elem[row][i][j];
					break;
				case AXIS_Y:
					pCube[i][j] = & elem[i][row][j];
					break;
				case AXIS_Z:
					pCube[i][j] = & elem[j][i][row];
					break;
			}
			pCube[i][j]->rotate(dir);
		}
	}


	CubePiece tmp;

	if (getRotateDirection(dir) == ROTATE_CW) {
		for (int k=0; k<N; k++) {
			tmp = *pCube[k][0];
			*pCube[k][0]	= *pCube[0][N-k];
			*pCube[0][N-k]	= *pCube[N-k][N];
			*pCube[N-k][N]	= *pCube[N][k];
			*pCube[N][k]	= tmp;
		}
	} else {
		for (int k=0; k<N; k++) {
			tmp = *pCube[k][0];
			*pCube[k][0]	= *pCube[N][k];
			*pCube[N][k]	= *pCube[N-k][N];
			*pCube[N-k][N]	= *pCube[0][N-k];
			*pCube[0][N-k]	= tmp;
		}
	}
}


void Cube::output(void)
{
	// TOP
	for (int d=3; d>0; d--) {
		fprintf(stderr, "%*s|", 1+6+1, " ");
		for (int x=0; x<3; x++) {
			fprintf(stderr, " %d", elem[x][0][d-1].top);
		}
		fprintf(stderr, " |\n");
	}

	fprintf(stderr, "---------------------------------\n");

	for (int y=0; y<3; y++) {

		fprintf(stderr, "|");

		// LEFT
		for (int d=3; d>0; d--) {
			fprintf(stderr, " %d", elem[0][y][d-1].left);
		}

		fprintf(stderr, " |");

		// FRONT
		for (int x=0; x<3; x++) {
			fprintf(stderr, " %d", elem[x][y][0].front);
		}

		fprintf(stderr, " |");

		// RIGHT
		for (int d=0; d<3; d++) {
			fprintf(stderr, " %d", elem[2][y][d].right);
		}

		fprintf(stderr, " |");

		// BACK
		for (int x=3; x>0; x--) {
			fprintf(stderr, " %d", elem[x-1][y][2].back);
		}

		fprintf(stderr, " |\n");
	}

	fprintf(stderr, "---------------------------------\n");

	// BOTTOM
	for (int d=0; d<3; d++) {
		fprintf(stderr, "%*s|", 1+6+1, " ");
		for (int x=0; x<3; x++) {
			fprintf(stderr, " %d", elem[x][2][d-1].down);
		}
		fprintf(stderr, " |\n");
	}
}

