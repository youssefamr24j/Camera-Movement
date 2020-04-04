#include <GL/glut.h>
#include <math.h>

static int Arm = 0, Elbow = 0 , RotatingArm=0, LeftLeg = 0, RightLeg =0, LeftKnee = 0 , RightKnee = 0 , RotatingRightLeg=0 , RotatingLeftLeg = 0 , incrementangle = 0;
double eye[] = { 0, 0, -20 };
double center[] = { 0, 0, 1 };
double up[] = { 0, 1, 0 };
double subtrationtemp[]= { 0, 0, 0 };
double crosstemp[]= { 0, 0, 0 };
double speed = 0.0;
double direction[]= { 0, 0, 0 };
int moving, startx, starty;


GLfloat angle = 0.0;   /* in degrees */
GLfloat angle2 = 0.0;   /* in degrees */

void init(void)
{
    glMatrixMode(GL_PROJECTION);
	gluPerspective(65.0, (GLfloat)1024 / (GLfloat)869, 1.0, 60.0);
}

void subtarct (double a[], double b[],double c[])
{
	c[0] = a[0] - b[0] ;
	c[1] = a[1] - b[1] ;
	c[2] = a[2] - b[2] ;
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
	rotatePoint(up,-0.1,eye);
}

void Right()
{
	// implement camera rotation arround vertical window screen axis to the right
	// used by mouse and right arrow
	rotatePoint(up,0.1,eye);
	
	
}

void Up()
{
	// implement camera rotation arround horizontal window screen axis +ve
	// used by up arrow
	subtarct(eye,center,subtrationtemp);
	crossProduct(subtrationtemp,up,crosstemp);
	normalize(crosstemp);
	rotatePoint(crosstemp,0.1,up);
	rotatePoint(crosstemp,0.1,eye);
	

}

void Down()
{	
	// implement camera rotation arround horizontal window screen axis 
	// used by down arrow
	subtarct(eye,center,subtrationtemp);
	crossProduct(subtrationtemp,up,crosstemp);
	normalize(crosstemp);
	rotatePoint(crosstemp,-0.1,up);
	rotatePoint(crosstemp,-0.1,eye);
}

void moveForward()
{
	speed = speed + 0.005;
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	eye[0]    += direction[0] * speed;
	eye[1]    += direction[1] * speed;
	eye[2]    += direction[2] * speed;

	center[0] += direction[0] * speed;
	center[1] += direction[1] * speed;
	center[2] += direction[2] * speed;
}

void moveBack()
{
	speed = speed + 0.005;
	direction[0] = center[0] - eye[0];
	direction[1] = center[1] - eye[1];
	direction[2] = center[2] - eye[2];

	eye[0]    -= direction[0] * speed;
	eye[1]    -= direction[1] * speed;
	eye[2]    -= direction[2] * speed;

	center[0] -= direction[0] * speed;
	center[1] -= direction[1] * speed;
	center[2] -= direction[2] * speed;
}


void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT );
   	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], up[0], up[1], up[2]);

	glPushMatrix();
	glTranslatef(0,1,0);
	//Head
	glPushMatrix();
	glTranslatef(0,1.65,0);
	glutSolidSphere(0.4,20,20);
	glPopMatrix();
	//Body
	glPushMatrix();
	glScalef(1.25,2.5,0.5);
	glutWireCube(1);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0,1.075,0);
	glRotatef((GLfloat) RotatingArm,1.0,0.0,0.0);
	glTranslatef(0.0,-1.075,0);
	//Right Arm
	//Upper Shoulder
	glPushMatrix();
	glTranslatef(0.7,1.075,0);
	glRotatef((GLfloat) Arm,0.0,0.0,1.0);
	glTranslatef(-0.7,-1.075,0);
	glPushMatrix();
	glTranslatef(0.8,0.7,0);
	glScalef(0.2,0.75,0.3);
	glutWireCube(1);
	glPopMatrix();
	//Lower Shoulder
	glPushMatrix();
	glTranslatef(0.7,0.325,0);
	glRotatef((GLfloat) Elbow,0.0,0.0,1.0);
	glTranslatef(-0.7,-0.325,0);
	glTranslatef(0.8,0,0);
	glScalef(0.2,0.75,0.3);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	
	
	//Left Arm
	//Upper Shoulder
	glPushMatrix();
	glTranslatef(-0.7,1.075,0);
	glRotatef(-(GLfloat) Arm,0.0,0.0,1.0);
	glTranslatef(0.7,-1.075,0);
	glPushMatrix();
	glTranslatef(-0.8,0.7,0);
	glScalef(0.2,0.75,0.3);
	glutWireCube(1);
	glPopMatrix();
	//Lower Shoulder
	glPushMatrix();
	glTranslatef(-0.7,0.325,0);
	glRotatef(-(GLfloat) Elbow,0.0,0.0,1.0);
	glTranslatef(0.7,-0.325,0);
	glTranslatef(-0.8,0,0);
	glScalef(0.2,0.75,0.3);
	glutWireCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//Right Leg
	//Upper Leg
	glPushMatrix();
	glTranslatef(0.625,-1.3,0);
	glRotatef((GLfloat) RotatingRightLeg,0.0,0.0,1.0);
	glTranslatef(-0.625,1.3,0);
	glTranslatef(0.0,-1.3,0);
	glRotatef((GLfloat) RightLeg,1.0,0.0,0.0);
	glTranslatef(0.0,1.3,0);
	glPushMatrix();
	glTranslatef(0.425,-1.8,0);
	glScalef(0.4,1,0.5);
	glutWireCube(1);
	glPopMatrix();
	//Lower Leg
	glPushMatrix();
	glTranslatef(0.0,-2.3,0);
	glRotatef((GLfloat) RightKnee,1.0,0.0,0.0);
	glTranslatef(0.0,2.3,0);
	glPushMatrix();
	glTranslatef(0.425,-2.8,0);
	glScalef(0.4,1,0.5);
	glutWireCube(1);
	glPopMatrix();
	//Feet
	glPushMatrix();
	glTranslatef(0.425,-3.37,0.15);
	glScalef(0.4,0.15,0.8);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	//Left Leg
	//Upper Leg
	glPushMatrix();
	glTranslatef(-0.625,-1.3,0);
	glRotatef(-(GLfloat) RotatingLeftLeg,0.0,0.0,1.0);
	glTranslatef(0.625,1.3,0);
	glTranslatef(0.0,-1.3,0);
	glRotatef((GLfloat) LeftLeg,1.0,0.0,0.0);
	glTranslatef(0.0,1.3,0);
	glPushMatrix();
	glTranslatef(-0.425,-1.8,0);
	glScalef(0.4,1,0.5);
	glutWireCube(1);
	glPopMatrix();
	//Lower Leg
	glPushMatrix();
	glTranslatef(0.0,-2.3,0);
	glRotatef((GLfloat) LeftKnee,1.0,0.0,0.0);
	glTranslatef(0.0,2.3,0);
	glPushMatrix();
	glTranslatef(-0.425,-2.8,0);
	glScalef(0.4,1,0.5);
	glutWireCube(1);
	glPopMatrix();
	//Feet
	glPushMatrix();
	glTranslatef(-0.425,-3.37,0.15);
	glScalef(0.4,0.15,0.8);
	glutSolidCube(1);
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();
	glPopMatrix();

	
	glPopMatrix();
	glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT: Left();  break;
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
		moveBack();
		glutPostRedisplay();
		break;
	case 'a':
      if(Arm < 180)
         Arm = (Arm + 5) % 360;
      glutPostRedisplay();
      break;
   case 'A':
      if(Arm > 0)
         Arm = (Arm - 5) % 360;
      glutPostRedisplay();
      break;
   case 'e':
      if(Elbow < 145)
         Elbow = (Elbow + 5) % 360;
      glutPostRedisplay();
      break;
   case 'E':
      if(Elbow > 0)
         Elbow = (Elbow - 5) % 360;
      glutPostRedisplay();
      break;
   case 'w':
      RotatingArm = (RotatingArm + 5) % 360;
      glutPostRedisplay();
      break;
   case 'W':
      RotatingArm = (RotatingArm - 5) % 360;
      glutPostRedisplay();
      break;      
   case 'l' :
      if( LeftLeg < 45)
         LeftLeg = (LeftLeg + 5) % 360;
      glutPostRedisplay();
      break;
   case 'L':
      if( LeftLeg > -180)
         LeftLeg = (LeftLeg - 5) % 360;
      glutPostRedisplay();
      break;
   case 'r' :
      if( RightLeg < 45)
         RightLeg = (RightLeg + 5) % 360;
      glutPostRedisplay();
      break;
   case 'R':
      if( RightLeg > -180)
         RightLeg = (RightLeg - 5) % 360;
      glutPostRedisplay();
      break;   
   case 'k':
      if(LeftKnee < 90)
         LeftKnee = (LeftKnee + 5) % 360;
      glutPostRedisplay();
      break;
   case 'K':
      if(LeftKnee > 0)
         LeftKnee = (LeftKnee - 5) % 360;
      glutPostRedisplay();
      break;
   case 'n':
      if(RightKnee < 90)
         RightKnee = (RightKnee + 5) % 360;
      glutPostRedisplay();
      break;
   case 'N':
      if(RightKnee > 0)
         RightKnee = (RightKnee - 5) % 360;
      glutPostRedisplay();
      break;
   case 'x':
      RotatingRightLeg = (RotatingRightLeg + 5) % 360;
      glutPostRedisplay();
      break;
   case 'X':
      RotatingRightLeg = (RotatingRightLeg - 5) % 360;
      glutPostRedisplay();
      break;            
   case 'z':
      RotatingLeftLeg = (RotatingLeftLeg + 5) % 360;
      glutPostRedisplay();
      break;
   case 'Z':
      RotatingLeftLeg = (RotatingLeftLeg - 5) % 360;
      glutPostRedisplay();
      break;            
   case 27:
      exit(0);
      break;
	default:
		break;
	}
}


static void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
      moving = 1;
      startx = x;
      starty = y;
    }
    if (state == GLUT_UP) {
      moving = 0;
    }
  }
}


static void motion(int x, int y)
{
  if (moving) {
    angle = angle + (x - startx);
    angle2 = angle + (y - starty);
	if(angle < 0)
	{
		Left();
		
	}
		
	else
	{
		Right();
		

	}
		
    startx = x;
    starty = y;
    glutPostRedisplay();
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
	glutMouseFunc(mouse);
    glutMotionFunc(motion);

	glutMainLoop();
	return 0;
}
