/**
 * A header of the Cube class
 * @file        Cube.hh
 * @date        2017/01/09 20:05
 */

#ifndef __CUBE_HH
#define __CUBE_HH


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
	BOTTOM_CW, BOTTOM_CCW,
	FRONT_CW, FRONT_CCW,
	BACK_CW, BACK_CCW,
};

enum RotateAxisE {
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
};

class CubePiece
{
public:
	CubePiece();
	CubePiece(CubePiece& s);

	void rotate(DirectionE dir);
	void draw();

	void reset();

private:
public:
	ColorE  top; 
	ColorE  left; 
	ColorE  right; 
	ColorE  front; 
	ColorE  back; 
	ColorE  bottom; 
};

/**
 * @class   Cube
 * @brief   
 */
class Cube
{
public:
	Cube();
	virtual ~Cube();

	void draw();
	void drawAxisXLayer(int h);
	void drawAxisYLayer(int h);
	void drawAxisZLayer(int h);

	void rotate(DirectionE dir);
	void rotateCommit(int h);
	void startRotate();
	bool isRotating() { return rotating; }

protected:
	CubePiece  elem[3][3][3];

	bool	rotating;
	int		angle;

	DirectionE curDir;
	int		selnum;
	int		seldeg;
	RotateAxisE	selax;

private:

};

#endif /* __CUBE_HH */

