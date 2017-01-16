
#include <GL/glut.h>

#include "CubeGL.hh"

CubeGL cube(3);

float pitch = 30.0;
float yaw = -30.0;
float roll = 0.0;

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_LINE);
}

void reshape(GLsizei width, GLsizei height) 
{  
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); 
 
    gluPerspective(45, (GLfloat)width / (GLfloat)height, 1.0, 100.0); 
	//glFrustum(-1,1, -1,1, 1, 100);
 
    glMatrixMode(GL_MODELVIEW);
}
 
#if 1
void draw_line()
{
    glPushMatrix();
 
    glPushMatrix(); //X축 붉은색
        glColor3f(1.0, 0.0, 0.0);
        glBegin(GL_LINES);
            glVertex3f(5.0, 0.0, 0.0);
            glVertex3f(-5.0, 0.0, 0.0);
        glEnd();
    glPopMatrix();
 
    glPushMatrix(); //Y축 녹색
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
            glVertex3f(0.0, 5.0, 0.0);
            glVertex3f(0.0, -5.0, 0.0);
        glEnd();
    glPopMatrix();
 
    glPushMatrix(); //Z축 파란색
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINES);
            glVertex3f(0.0, 0.0, 5.0);
            glVertex3f(0.0, 0.0, -5.0);
        glEnd();
    glPopMatrix();
 
    glPopMatrix();
 
    glFlush();
}
#endif
 
void display() 
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
 
#if 0	// lighting
	//GLfloat light[] = { 0.9,0.5,0.1,1 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light);

	//GLfloat ambient[] = { 0.2, 0.2, 0.2, 1 };
	//glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	//glLightfv(GL_LIGHT0, GL_DIFFUSE, ambient);
	//glLightfv(GL_LIGHT0, GL_SPECULAR, ambient);

	GLfloat pos[] = { -5, 5, -5, 1 };
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
#endif

    glTranslatef(0, 0, -30);
    glRotatef(pitch, 1.0, 0.0, 0.0);
    glRotatef(yaw, 0.0, 1.0, 0.0);
    glRotatef(roll, 0.0, 0.0, 1.0);


	cube.draw();

    draw_line();
 
    glutSwapBuffers();
}

void timer(int value)
{
	if (cube.isRotating() == true) {
		glutPostRedisplay();
	}

	glutTimerFunc(30, timer, 0);
}

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		exit(0);
	}
#if 0
    else if (key == 43) // +키
    {
        roll += 5.0;
    }
    else if (key == 45) //-키
    {
        roll -= 5.0;
    }
#endif

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

	glutPostRedisplay();
}

void special(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        pitch += 5.0;
    }
    else if (key == GLUT_KEY_DOWN)
    {
        pitch -= 5.0;
    }
    else if (key == GLUT_KEY_RIGHT)
    {
        yaw += 5.0;
    }
    else if (key == GLUT_KEY_LEFT)
    {
        yaw -= 5.0;
    }
    glutPostRedisplay();
}

int lastX = 0;
int lastY = 0;
bool clicked = false;

void mouseClick(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			lastX = x;
			lastY = y;
			clicked = true;
		} else {
			clicked = false;
		}
	}
}

void mouseMove(int x, int y)
{
	int dx = x - lastX;
	int dy = y - lastY;

	// scroll limit 
	if (yaw + dx > 360) yaw = 0;
	else if (yaw + dx < -360) yaw = 0;
	else
		yaw += dx;

	if (pitch + dy > 85) pitch = 85;
	else if (pitch + dy < -85) pitch = -85;
	else
		pitch += dy;

	lastX = x;
	lastY = y;

    glutPostRedisplay();
}
 

int main(int argc, char** argv)
{
	glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(1000, 900);
    glutCreateWindow("OpenGL Example");

	init();

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);

    glutReshapeFunc(reshape);

	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);


	glutTimerFunc(30, timer, 0);

    glutMainLoop();          


	return 0;
}
