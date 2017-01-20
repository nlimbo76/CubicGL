
#include <GL/freeglut.h>

#include "CubeGL.hh"

CubeGL cube(3);

float deltaPitch = 0;
float deltaYaw = 0;

float pitch = 30.0;
float yaw = -30.0;
float roll = 0.0;

float zoom = 30;

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

void drawBitmapText(const char *str, float x, float y, float z)
{
    glRasterPos3f(x, y, z); //문자열이 그려질 위치 지정
 
    while (*str)
    {
        //GLUT_BITMAP_TIMES_ROMAN_24 폰트를 사용하여 문자열을 그린다.
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *str);
 
        str++;
    }
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
        drawBitmapText("+X", 5, 0.0, 0.0);
        drawBitmapText("-X", -5, 0.0, 0.0);
    glPopMatrix();
 
    glPushMatrix(); //Y축 녹색
        glColor3f(0.0, 1.0, 0.0);
        glBegin(GL_LINES);
            glVertex3f(0.0, 5.0, 0.0);
            glVertex3f(0.0, -5.0, 0.0);
        glEnd();
        drawBitmapText("+Y", 0.0, 5, 0.0);
        drawBitmapText("-Y", 0.0, -5, 0.0);
    glPopMatrix();
 
    glPushMatrix(); //Z축 파란색
        glColor3f(0.0, 0.0, 1.0);
        glBegin(GL_LINES);
            glVertex3f(0.0, 0.0, 5.0);
            glVertex3f(0.0, 0.0, -5.0);
        glEnd();
        drawBitmapText("+Z", 0.0, 0.0, 5);
        drawBitmapText("-Z", 0.0, 0.0, -5);
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

	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'T');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'e');
	glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 's');

    glTranslatef(0, 0, -zoom);
	pitch += deltaPitch;
	yaw += deltaYaw;
    glRotatef(pitch, 1.0, 0.0, 0.0);
    glRotatef(yaw, 0.0, 1.0, 0.0);
    glRotatef(roll, 0.0, 0.0, 1.0);

    draw_line();

	cube.draw();
 
    glutSwapBuffers();
}

#if 0
void timer(int value)
{
	if (cube.isRotating() == true) {
		glutPostRedisplay();
	}

	glutTimerFunc(30, timer, 0);
}
#endif

void keyboard(unsigned char key, int x, int y)
{
	if (key == 27) {
		exit(0);
	}

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
}

void special(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP:
			deltaPitch = 2.0;
			break;
		case GLUT_KEY_DOWN:
			deltaPitch = -2.0;
			break;
		case GLUT_KEY_LEFT:
			deltaYaw = -5.0;
			break;
		case GLUT_KEY_RIGHT:
			deltaYaw = 5.0;
			break;
	}
}

void specialRelease(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP:
		case GLUT_KEY_DOWN:
			deltaPitch = 0;
			break;

		case GLUT_KEY_LEFT:
		case GLUT_KEY_RIGHT:
			deltaYaw = 0;
			break;
	}
}

int lastX = 0;
int lastY = 0;
int clicked = GLUT_LEFT_BUTTON;
int modifier = 0;

void mouseClick(int button, int state, int x, int y)
{
	modifier = glutGetModifiers();

	if (state == GLUT_DOWN) {
		if (button == GLUT_LEFT_BUTTON) {
			if (state == GLUT_DOWN) {
				lastX = x;
				lastY = y;
				clicked = button;
			} else {
				clicked = 0;
			}
		} else if (button == 3) {	// wheel up
			zoom -= 2; if (zoom < 0) zoom=0;
		} else if (button == 4) {	// wheel down
			zoom += 2; if (zoom > 50) zoom=50;
		}
	}
}

void mouseMove(int x, int y)
{
	if (modifier == GLUT_ACTIVE_SHIFT) {

	} else {
		int dx = x - lastX;
		int dy = y - lastY;

		// scroll limit 
		yaw += dx;
		if (yaw > 360) yaw = 0;
		else if (yaw < -360) yaw = 0;

		pitch += dy;
		if (pitch > 85) pitch = 85;
		else if (pitch < -85) pitch = -85;

		lastX = x;
		lastY = y;
	}

    //glutPostRedisplay();
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

	glutIgnoreKeyRepeat(1);
	glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
	glutSpecialUpFunc(specialRelease);

	//glutTimerFunc(30, timer, 0);
	glutIdleFunc(display);

    glutReshapeFunc(reshape);

	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);


    glutMainLoop();          

	return 0;
}
