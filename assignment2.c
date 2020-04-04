#include <GL/glut.h>
#include <math.h>

static int shoulder = 0, shoulder2 = 0, elbow = 0, fingerBase = 0, fingerUp = 0, rhip = 0, rhip2 = 0, rknee = 0, lknee = 0, lhip = 0, lhip2 = 0 ;
double eye[] = { 0, 0, -20 };
double center[] = { 0, 0, 1 };
double up[] = { 0, 1, 0 };

void init(void)
{
    glMatrixMode(GL_PROJECTION);
	gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);
}

void crossProduct(double a[], double b[], double c[])
{
	c[0] = a[1] * b[2] - a[2] * b[1];
	c[1] = a[2] * b[0] - a[0] * b[2];
	c[2] = a[0] * b[1] - a[1] * b[0];
}

void normalize(double a[])
{
	double norm;
	norm = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	norm = sqrt(norm);
	a[0] /= norm;
	a[1] /= norm;
	a[2] /= norm;
}

void rotatePoint(double a[], double theta, double p[])
{

	double temp[3];
	temp[0] = p[0];
	temp[1] = p[1];
	temp[2] = p[2];

	temp[0] = -a[2] * p[1] + a[1] * p[2];
	temp[1] = a[2] * p[0] - a[0] * p[2];
	temp[2] = -a[1] * p[0] + a[0] * p[1];

	temp[0] *= sin(theta);
	temp[1] *= sin(theta);
	temp[2] *= sin(theta);

	temp[0] += (1 - cos(theta))*(a[0] * a[0] * p[0] + a[0] * a[1] * p[1] + a[0] * a[2] * p[2]);
	temp[1] += (1 - cos(theta))*(a[0] * a[1] * p[0] + a[1] * a[1] * p[1] + a[1] * a[2] * p[2]);
	temp[2] += (1 - cos(theta))*(a[0] * a[2] * p[0] + a[1] * a[2] * p[1] + a[2] * a[2] * p[2]);

	temp[0] += cos(theta)*p[0];
	temp[1] += cos(theta)*p[1];
	temp[2] += cos(theta)*p[2];

	p[0] = temp[0];
	p[1] = temp[1];
	p[2] = temp[2];

}

void Left()
{
	// implement camera rotation arround vertical window screen axis to the left
	// used by mouse and left arrow
}

void Right()
{
	// implement camera rotation arround vertical window screen axis to the right
	// used by mouse and right arrow
}

void Up()
{
	// implement camera rotation arround horizontal window screen axis +ve
	// used by up arrow
}

void Down()
{	
	// implement camera rotation arround horizontal window screen axis 
	// used by down arrow
}

void moveForward()
{
}

void moveBack()
{
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
   	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	// draw head

	// draw trunck
	// call the robotic body draw function here
	glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: Left(); break;
	case GLUT_KEY_RIGHT: Right(); break;
	case GLUT_KEY_UP:    Up(); break;
	case GLUT_KEY_DOWN:  Down(); break;
	}

	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	// List all youe keyboard keys from assignment two her for body movement
	switch (key)
	{
	case 'f':
		moveForward();
		glutPostRedisplay();
		break;
	case 'b':
		moveBack()
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("body");
	init();
	glutDisplayFunc(display);
    	glutSpecialFunc(specialKeys);
	glutKeyboardFunc(keyboard);

	glutMainLoop();
	return 0;
}
