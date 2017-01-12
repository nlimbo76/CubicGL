
#include <stdio.h>

#include "Cube.hh"


Cube cube;

int main(int argc, char** argv)
{
	int key;

	cube.output();

	while((key = getchar()) > 0) {
		if (key == 'x') break;

		if (key == 'w') {
			cube.rotate(UP_CW);
		} else if (key == 's') {
			cube.rotate(DOWN_CW);
		} else if (key == 'a') {
			cube.rotate(LEFT_CW);
		} else if (key == 'd') {
			cube.rotate(RIGHT_CW);
		} else if (key == 'q') {
			cube.rotate(FRONT_CW);
		} else if (key == 'e') {
			cube.rotate(BACK_CW);
		} else if (key == 'W') {
			cube.rotate(UP_CCW);
		} else if (key == 'S') {
			cube.rotate(DOWN_CCW);
		} else if (key == 'A') {
			cube.rotate(LEFT_CCW);
		} else if (key == 'D') {
			cube.rotate(RIGHT_CCW);
		} else if (key == 'Q') {
			cube.rotate(FRONT_CCW);
		} else if (key == 'E') {
			cube.rotate(BACK_CCW);
		}

		cube.output();
	}

	printf("--\n");
	
	return 0;
}
