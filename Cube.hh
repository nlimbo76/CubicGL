/**
 * A header of the Cube class
 * @file        Cube.hh
 * @date        2017/01/09 20:05
 */

#ifndef __CUBE_HH
#define __CUBE_HH

#include <stdio.h>

#define dbg(fmt, args...) do { fprintf(stderr, "dbg) " fmt, ## args ); } while(0)

enum ColorE {
	NONE,
	YELLOW,
	RED,
	ORANGE,
	GREEN,
	BLUE,
	WHITE,
};

enum DirectionE {
	UP_CW, UP_CCW,
	LEFT_CW, LEFT_CCW,
	RIGHT_CW, RIGHT_CCW,
	DOWN_CW, DOWN_CCW,
	FRONT_CW, FRONT_CCW,
	BACK_CW, BACK_CCW,
};

enum RotateAxisE {
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
};

enum RotateDirE {
	ROTATE_CW,
	ROTATE_CCW,
};

class CubePiece
{
public:
	CubePiece();

	CubePiece& operator= (const CubePiece& r);

	void rotate(RotateAxisE& ax, RotateDirE& dir);

	void reset();

private:
public:
	ColorE  top; 
	ColorE  left; 
	ColorE  right; 
	ColorE  front; 
	ColorE  back; 
	ColorE  down; 
};

struct ActionT {
	RotateAxisE	ax;
	RotateDirE	cw;
	int			bmCol;	// column bit-mask for multi cols.
	bool		bDouble;

	ActionT() {
		ax = AXIS_X;
		cw = ROTATE_CW;
		bDouble = false;
		bmCol = (1 << 0);
	}
};


/**
 * @class   Cube
 * @brief   
 */
class Cube
{
public:
	Cube(int dim = 3);
	virtual ~Cube();

	void rotate(DirectionE dir);
	void rotate(const char* dir);

	RotateAxisE	getAxis(DirectionE dir);
	RotateDirE	getRotateDirection(DirectionE dir);
	int			getRotateRow(DirectionE dir);

	void output();

protected:
	void rotate(ActionT& act);
	bool parseCommand(const char* cmd, ActionT& act);

	int			N;		// cube dimension 
	CubePiece***  elem;

private:

};

#endif /* __CUBE_HH */

