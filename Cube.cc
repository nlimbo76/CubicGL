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

void CubePiece::rotate(RotateAxisE& ax, RotateDirE& dir)
{
	ColorE tmp;
	if (ax == AXIS_X) {
		if (dir == ROTATE_CW) {
			tmp=top; top=back; back=down; down=front; front=tmp;
		} else {
			tmp=top; top=front; front=down; down=back; back=tmp;
		}
	} else if (ax == AXIS_Y) {
		if (dir == ROTATE_CW) {
			tmp=left; left=back; back=right; right=front; front=tmp;
		} else {
			tmp=left; left=front; front=right; right=back; back=tmp;
		}
	} else {
		if (dir == ROTATE_CW) {
			tmp=top; top=right; right=down; down=left; left=tmp;
		} else {
			tmp=top; top=left; left=down; down=right; right=tmp;
		}
	}
}



//
// Cube class implements
//

Cube::Cube(int dim)
{
	if (dim < 2 || dim > 12) dim = 3;

	N = dim;

	elem = new CubePiece**[N];
	for (int x=0; x<N; x++) {
		elem[x] = new CubePiece*[N];
		for (int y=0; y<N; y++) {
			elem[x][y] = new CubePiece[N];
		}
	}
}

Cube::~Cube()
{
	delete[] elem;
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
			idx = (N-1);
			break;
	}

	return idx;
}

bool Cube::parseCommand(const char* cmdstr, ActionT& act)
{
	int len = strlen(cmdstr);

	if (len <= 0) return false;

	int idx = 0;
	bool reverse = false;
	bool twice_rotate = false;
	RotateAxisE	ax;
	RotateDirE	cw;

	char cmd = cmdstr[0];

	if (len > 1) {
		const char* p = & cmdstr[1];

		if (*p == '\'') {	// reverse
			reverse = true;
			p++;
		}

		if (*p == '2') {
			twice_rotate = true;
		}
	}

	switch (cmd) {
		case 'U':	ax=AXIS_Y;	cw=ROTATE_CCW;	idx=1<<0;		break;
		case 'D':	ax=AXIS_Y;	cw=ROTATE_CW;	idx=1<<(N-1);	break;
		case 'F':	ax=AXIS_Z;	cw=ROTATE_CCW;	idx=1<<0;		break;
		case 'B':	ax=AXIS_Z;	cw=ROTATE_CW; 	idx=1<<(N-1);	break;
		case 'L':	ax=AXIS_X;	cw=ROTATE_CW; 	idx=1<<0;		break;
		case 'R':	ax=AXIS_X;	cw=ROTATE_CCW;	idx=1<<(N-1);	break;

		case 'u':	ax=AXIS_Y;	cw=ROTATE_CCW;	idx=3<<0;		break;
		case 'd':	ax=AXIS_Y;	cw=ROTATE_CW; 	idx=3<<(N-2);	break;
		case 'f':	ax=AXIS_Z;	cw=ROTATE_CCW;	idx=3<<0;		break;
		case 'b':	ax=AXIS_Z;	cw=ROTATE_CW; 	idx=3<<(N-2);	break;
		case 'l':	ax=AXIS_X;	cw=ROTATE_CW; 	idx=3<<0;		break;
		case 'r':	ax=AXIS_X;	cw=ROTATE_CCW;	idx=3<<(N-2);	break;

		case 'x':
		case 'y':
		case 'z':
			return false;

		default:
			return false;
	}

	if (idx == 0) return false;

	if (reverse == true)
		cw = (cw == ROTATE_CW) ? ROTATE_CCW : ROTATE_CW;

	act.ax = ax;
	act.cw = cw;
	act.bmCol = idx;
	act.bDouble = twice_rotate;

	return true;
}

void Cube::rotate(const char* dir)
{
	ActionT act;

	if (parseCommand(dir, act) == false) {
		return;
	}

	rotate(act);

	if (act.bDouble) rotate(act);
}

void Cube::rotate(ActionT& act)
{
	CubePiece* pCube[N][N];	// for easy rotating

	for (int row = 0; row < N; row++) {
		if ((act.bmCol & (1<<row)) == 0) continue;

		memset(pCube, 0, sizeof(pCube));

		for (int x=0; x<N; x++) {
			for (int y=0; y<N; y++) {
				switch( act.ax ) {
					case AXIS_X:
						pCube[x][y] = & elem[row][x][y];
						break;
					case AXIS_Y:
						pCube[x][y] = & elem[x][row][y];
						break;
					case AXIS_Z:
						pCube[x][y] = & elem[y][x][row];
						break;
				}
				pCube[x][y]->rotate(act.ax, act.cw);
			}
		}


		CubePiece tmp;

		if (act.cw == ROTATE_CW) {
			for (int base=0; base<N/2; base++) {

				int s=base;		// start element
				int e=N-base-1;	// end element

				for (int k=s; k<e; k++) {
					int j = e - k + s;

					tmp				= *pCube[k][s];
					*pCube[k][s]	= *pCube[s][j];
					*pCube[s][j]	= *pCube[j][e];
					*pCube[j][e]	= *pCube[e][k];
					*pCube[e][k]	= tmp;
				}
			}
		} else {
			for (int base=0; base<N/2; base++) {

				int s=base;		// start element
				int e=N-base-1;	// end element

				for (int k=s; k<e; k++) {
					int j = e - k + s;

					tmp				= *pCube[k][s];
					*pCube[k][s]	= *pCube[e][k];
					*pCube[e][k]	= *pCube[j][e];
					*pCube[j][e]	= *pCube[s][j];
					*pCube[s][j]	= tmp;
				}
			}
		}
	}
}

void Cube::rotate(DirectionE dir)
{
	ActionT act;
	act.ax = getAxis(dir);
	act.cw = getRotateDirection(dir);
	act.bmCol = 1 << getRotateRow(dir);

	rotate(act);
}


void Cube::output(void)
{
	// TOP
	for (int d=N; d>0; d--) {
		fprintf(stderr, "%*s|", 1+(N*2)+1, " ");
		for (int x=0; x<N; x++) {
			fprintf(stderr, " %d", elem[x][0][d-1].top);
		}
		fprintf(stderr, " |\n");
	}

	fprintf(stderr, "---------------------------------\n");

	for (int y=0; y<N; y++) {

		fprintf(stderr, "|");

		// LEFT
		for (int d=N; d>0; d--) {
			fprintf(stderr, " %d", elem[0][y][d-1].left);
		}

		fprintf(stderr, " |");

		// FRONT
		for (int x=0; x<N; x++) {
			fprintf(stderr, " %d", elem[x][y][0].front);
		}

		fprintf(stderr, " |");

		// RIGHT
		for (int d=0; d<N; d++) {
			fprintf(stderr, " %d", elem[N-1][y][d].right);
		}

		fprintf(stderr, " |");

		// BACK
		for (int x=N; x>0; x--) {
			fprintf(stderr, " %d", elem[x-1][y][N-1].back);
		}

		fprintf(stderr, " |\n");
	}

	fprintf(stderr, "---------------------------------\n");

	// BOTTOM
	for (int d=0; d<N; d++) {
		fprintf(stderr, "%*s|", 1+(N*2)+1, " ");
		for (int x=0; x<N; x++) {
			fprintf(stderr, " %d", elem[x][N-1][d].down);
		}
		fprintf(stderr, " |\n");
	}
}

