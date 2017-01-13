
#include <stdio.h>
#include <string.h>

#include "Cube.hh"


Cube cube(3);

int main(int argc, char** argv)
{
	char cmd[128];
	int len;

	cube.output();

	fprintf(stderr, " press 'q' to quit! \n");

	do {
		if (fgets(cmd, sizeof(cmd), stdin) <= 0) {
			break;
		}

		len = strlen(cmd);
		cmd[len-1] = '\0';

		char* p = &cmd[0];
		if (*p == 'q')	break;

		for (; *p; p++) {

			cube.rotate(p);

			if (strlen(p) > 1) {
				if (*(p+1) == '\'' || *(p+1) == '2') {
					p++;
				}
			}
#if 0
			int dir = -1;
			bool twice = false;

			if (*p == 'u') {
				dir = UP_CW;
			} else if (*p == 'd') {
				dir = DOWN_CW;
			} else if (*p == 'l') {
				dir = LEFT_CW;
			} else if (*p == 'r') {
				dir = RIGHT_CW;
			} else if (*p == 'f') {
				dir = FRONT_CW;
			} else if (*p == 'b') {
				dir = BACK_CW;
			} 

			if (*(p+1) == '\'') {
				dir++;
				p++;
			}

			if (*(p+1) == '2') {
				twice = true;
				p++;
			}

			if (dir >= 0 && dir <= BACK_CCW) {
				cube.rotate( (DirectionE)dir );
				if (twice) 
					cube.rotate( (DirectionE)dir );

			} else {
				fprintf(stderr, " pass wrong cmd : %x\n", *p);
			}
#endif
		}

		cube.output();
		fprintf(stderr, "\n");

	} while(1);
	
	return 0;
}
