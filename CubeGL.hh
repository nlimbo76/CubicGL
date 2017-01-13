/**
 * A header of the CubeGL class
 * @file        CubeGL.hh
 * @date        2017/01/12 13:31
 */

#ifndef __CUBEGL_HH
#define __CUBEGL_HH

#include "Cube.hh"

/**
 * @class   CubeGL
 * @brief   
 */
class CubeGL : public Cube
{
public:
	CubeGL(int dim = 3);
	virtual ~CubeGL();

	void draw();

	void rotate(DirectionE dir);

	bool isRotating() { return rotating; }

protected:
	void drawAxisXLayer(int h);
	void drawAxisYLayer(int h);
	void drawAxisZLayer(int h);

	void drawPiece(const CubePiece& piece);
	void drawArrow();

	void startRotate();

	DirectionE	seldir;
	RotateAxisE	selax;
	int		seldeg;
	int		selnum;

	bool	rotating;
	int		angle;



private:


};

#endif /* __CUBEGL_HH */

