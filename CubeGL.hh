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
	void drawAxisXLayer(int h);
	void drawAxisYLayer(int h);
	void drawAxisZLayer(int h);

	void drawPiece(const CubePiece& piece);
	void drawArrow();

	virtual void rotate(DirectionE dir);
	void startRotate();

	bool isRotating() { return rotating; }

protected:

	DirectionE	seldir;
	RotateAxisE	selax;
	int		seldeg;
	int		selnum;

	bool	rotating;
	int		angle;



private:


};

#endif /* __CUBEGL_HH */

