// Task Topic: Lighting and Materials
// Student Name: Tianlei.Shi
// Student ID: 1824152
// Programme of study: Information and Computer Science

// General explanation here if necessary
/*
I have finished a Solar System with lighting and materials.
In this system, the Sum is the only one light source£¬and you can see that
Other planets are light, if the side is facing the sun and dark, if the side
is facing away from the sun. Additionally, to make the far side of the planet
visible, I added some faint ambient light.
Ambient, specular, diffuse and other technologies are used in this task. Every
planet has it own lighting and materials.
Viewing change and keyboard interactive were also used in this coursework.
You can change viewing point by pressing "a" or "d".
*/

// Main body of code with necessary comments

/*
Task 1 (Week10) - Lighting and Materials
  Light sources and effects
  Materials properties
  Combined effects of lighting and materials
*/

#define FREEGLUT_STATIC
#include <stdlib.h>
#include <GL/freeglut.h>

// preset the function framework, for main function use
void init(void);   // set ambient and other lights
void display(void);   // set display function
void myIdleFunc(void);
void myKeyBoardFunc(void);   // press "a"/"A" and "d"/"D" to interactive

// set global variable
// preset the stars parameter, firstly they are all in one line
float sun = 360;
float mercury = 360;
float venus = 360;
float earth = 360;
float mars = 360;
float jupiter = 360;
float saturn = 360;
float uranus = 360;
float neptune = 360;
float pluto = 360;

GLint winWidth = 900, winHeight = 600; // set window's size
GLfloat Viewx = 0.0, Viewy = 1.0, Viewz = 0.0; // set view-up vector
GLfloat xref = 0.0, yref = 50.0, zref = 0.0; // set the point of look-at
GLfloat xo = 0.0, yo = 1000.0, zo = 1500.0; // set the origin of viewing

// set co-ordinate limits for window
GLfloat xwMax = 40.0, ywMax = 60.0, xwMin = -40.0, ywMin = -60.0;

// set positions for planes
GLfloat dnear = 150.0, dfar = 2500.0;

// set view function
void myReshapeFunc(GLint Width_, GLint Height_)
{
	glViewport(0, 0, Width_, Height_);
}

// set keyboard interactive
void myKeyboardFunc(unsigned char key, int x, int y)
{
	// press "a" to change view
	if (key == 'a' || key == 'A')
		xo = 0.0, yo = 1000.0, zo = 1500.0;   // change view point to overlook

	// press "d" to change view
	if (key == 'd' || key == 'D')
		xo = 0.0, yo = 1000.0, zo = 1.0;   // change view point to eye level
}

// run program
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	// create window
	glutInitWindowPosition(100, 100);   // set window position
	glutInitWindowSize(winWidth, winHeight);   // set window size
	glutCreateWindow("Solar System");

	// show the Solar System
	glutDisplayFunc(display);
	glutIdleFunc(myIdleFunc);
	glutReshapeFunc(myReshapeFunc);
	glutKeyboardFunc(myKeyboardFunc);
	init();

	// loop draw the Solar System
	glutMainLoop();
}

// set initial function
void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);   // clear color
	glColor3f(0.0, 0.0, 0.0);   // set color as black
	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);

	glFrustum(xwMin, xwMax, ywMin, ywMax, dnear, dfar);	  // limit the location
	glShadeModel(GL_SMOOTH);   // set shade model

	// preset light and materials
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };   // set diffuse
	GLfloat light_ambient[] = { 0.0f, 0.5f, 0.5f, 1.0f };   // set ambient
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

	// set material reflective
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  // specular reflection parameter
	GLfloat mat_shininess[] = { 50.0 };               // specular parameter

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	// make the light source effective
	glEnable(GL_LIGHTING);  // activate the light
	glEnable(GL_LIGHT0);    // activate the light symbol constant

	// activate depth test
	glEnable(GL_DEPTH_TEST);
}

// set location change function
void myIdleFunc(void)
{
	// change in position coordinates per second
	sun += 1.0;
	mercury += 1.4;
	venus += 1.2;
	earth += 1.0;
	mars += 0.9;
	jupiter += 0.8;
	saturn += 0.5;
	uranus += 0.6;
	neptune += 0.4;
	pluto += 0.2;

	// redraw stars at their new coordinates
	glutPostRedisplay();
}

// set display function
// set differ lighting and materials for every planet, and because we preset light 
// and materials in init function, so color will have a deviation here.
void display(void)
{
	// generally preset
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// set view point
	gluLookAt(xo, yo, zo, xref, yref, zref, Viewx, Viewy, Viewz);

	//draw lighting and materials of Sun
	glPushMatrix();
	GLfloat Sun_position[] = { 0.0f, 0.0f, 1.5f, 1.0f };   // set Sun position
	glLightfv(GL_LIGHT0, GL_POSITION, Sun_position);
	glTranslated(0.0f, 0.0f, 1.5f);
	glRotatef(sun, 0, 1, 0);
	glPushMatrix();

	// draw a yellow ball of light
	glDisable(GL_LIGHTING);   // close lighting to draw the Sun
	glColor3f(1.0, 0.5, 0.2);   // set color of Sun

	GLfloat Sun_diffuse[] = { 1.0f, 0.5f, 0.2f, 1.0f, };   // set diffuse of Sun
	GLfloat Sun_ambient[] = { 1.0f, 0.0f, 0.0f, 1.0f, };   // set ambient of Sun
	GLfloat Sun_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f, };  // set specular of Sun

	// set lighting and materials
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Sun_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Sun_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Sun_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);

	glutSolidSphere(60, 40, 40);   // draw a sphere as Sun
	glEnable(GL_LIGHTING);   // open lighting
	glPopMatrix();
	glPopMatrix();

	//draw lighting and materials of Mercury
	glPushMatrix();
	glColor3f(0.8, 0.5, 0.2);
	glTranslatef(0, 0, 0);
	glRotatef(mercury, 0, 1, 0);   // change the rotate angle of Mercury
	glPushMatrix();
	glTranslatef(85, 0, 0);

	GLfloat Mercury_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f, };   // set specular of Mercury
	GLfloat Mercury_ambient[] = { 0.412f, 0.412f, 0.412f, 1.0f, };    // set ambient of Mercury
	GLfloat Mercury_diffuse[] = { 0.9f, 0.3f, 0.3f, 1.0f, };   // set diffuse of Mercury

	// set lighting and materials
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Mercury_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Mercury_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Mercury_diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 5.0);

	glutSolidSphere(8, 8, 8);   // draw a sphere as Mercury
	glPopMatrix();
	glPopMatrix();

	//draw lighting and materials of Venus
	glPushMatrix();
	glColor3f(0.8, 0.8, 1.0);
	glTranslatef(0, 0, 0);
	glRotatef(venus, 0, 1, 0);   // change the rotate angle of Venus
	glPushMatrix();
	glTranslatef(120, 0, 0);

	GLfloat Venus_ambient[] = { 1.0f, 0.89f, 1.0f, 0.71f, };   // set ambient of Venus
	GLfloat Venus_diffuse[] = { 0.2f, 0.9f, 0.2f, 1.0f, };   // set diffuse of Venus
	GLfloat Venus_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f, };   // set specular of Venus

	// set lighting and materials
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Venus_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Venus_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Venus_specular);

	glutSolidSphere(10, 10, 10);   // draw a sphere as Venus
	glPopMatrix();
	glPopMatrix();

	//draw lighting and materials of Earth
	glPushMatrix();
	glColor3f(0.1, 0.3, 1.0);
	glTranslatef(0, 0, 0);
	glRotatef(earth, 0, 1, 0);   // change the rotate angle of Earth
	glPushMatrix();
	glTranslatef(145, 0, 0);

	GLfloat earth_ambient[] = { 0.0f, 0.2f, 0.7f, 1.0f, };   // set ambient of Earth
	GLfloat earth_diffuse[] = { 0.8f, 0.5f, 0.5f, 1.0f, };   // set diffuse of Earth
	GLfloat earth_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f, };   // set specular of Earth

	// set lighting and materials
	glMaterialfv(GL_FRONT, GL_AMBIENT, earth_ambient);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);  // specular
	glMaterialfv(GL_FRONT, GL_DIFFUSE, earth_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, earth_specular);

	glutSolidSphere(10, 10, 10);   // draw a sphere as Earth
	glPopMatrix();
	glPopMatrix();

	//draw lighting and materials of Mars
	glPushMatrix();
	glColor3f(1.0, 0.2, 0.2);
	glTranslatef(0, 0, 0);
	glRotatef(mars, 0, 1, 0);   // change the rotate angle of Mars
	glPushMatrix();
	glTranslatef(175, 0, 0);

	GLfloat Mars_ambient[] = { 0.9f, 0.2f, 0.1f, 1.0f, };   // set ambient of Mars
	GLfloat Mars_diffuse[] = { 0.9f, 0.5f, 0.5f, 1.0f, };   // set diffuse of Mars
	GLfloat Mars_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f, };   // set specular of Mars

	// set lighting and materials
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Mars_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Mars_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Mars_ambient);

	glutSolidSphere(8, 8, 8);   // draw a sphere as Mars
	glPopMatrix();
	glPopMatrix();

	//draw lighting and materials of Jupiter
	glPushMatrix();
	glColor3f(0.8, 0.5, 0.5);
	glTranslatef(0, 0, 0);
	glRotatef(jupiter, 0, 1, 0);   // change the rotate angle of Jupiter
	glPushMatrix();
	glTranslatef(220, 0, 0);

	GLfloat Jupiter_ambient[] = { 0.87f, 0.72f, 0.3f, 1.0f, };   // set ambient of Jupiter
	GLfloat Jupiter_diffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f, };   // set diffuse of Jupiter
	GLfloat Jupiter_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f, };   // set specular of Jupiter

	// set lighting and materials
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Jupiter_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Jupiter_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Jupiter_specular);

	glutSolidSphere(20, 20, 20);   // draw a sphere as Jupiter
	glPopMatrix();
	glPopMatrix();

	//draw lighting and materials of Saturn
	glPushMatrix();
	glColor3f(1.0, 1.0, 0.7);
	glRotatef(saturn, 0, 1, 0);   // change the rotate angle of Saturn
	glTranslatef(280, 0, 0);

	GLfloat Saturn_ambient[] = { 1.0f, 0.4f, 0.7f, 1.0f, };   // set ambient of Saturn
	GLfloat Saturn_diffuse[] = { 0.9f, 0.5f, 0.5f, 1.0f, };   // set diffuse of Saturn
	GLfloat Saturn_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f, };   // set specular of Saturn

	// set lighting and materials
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Saturn_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Saturn_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Saturn_diffuse);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50.0);

	glutSolidSphere(20, 20, 20);   // draw a sphere as Saturn

	//draw the rings Of Saturn
	glPushMatrix();
	glColor3f(0.8, 0.4, 0.2);
	glRotatef(83, 1, 0, 0);
	glutSolidTorus(1, 23, 5, 30);   // draw ring
	glTranslatef(200, 0, 0);
	glPopMatrix();
	glPopMatrix();

	//draw lighting and materials of Uranus
	glPushMatrix();
	glColor3f(0.6, 0.7, 0.6);
	glTranslatef(0, 0, 0);
	glRotatef(uranus, 0, 1, 0);   // change the rotate angle of Uranus

	glPushMatrix();
	glTranslatef(340, 0, 0);

	GLfloat Uranus_ambient[] = { 1.0f, 0.2f, 0.0f, 1.0f, };   // set ambient of Uranus
	GLfloat Uranus_diffuse[] = { 0.0f, 0.5f, 0.5f, 1.0f, };   // set diffuse of Uranus
	GLfloat Uranus_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f, };   // set specular of Uranus

	// set lighting and materials
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Uranus_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 65.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Uranus_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Uranus_diffuse);

	glutSolidSphere(16, 16, 16);   // draw a sphere as Uranus
	glPopMatrix();
	glPopMatrix();

	//draw lighting and materials of Neptune
	glPushMatrix();
	glColor3f(0.2, 0.5, 1.0);
	glTranslatef(0, 0, 0);
	glRotatef(neptune, 0, 1, 0);   // change the rotate angle of Neptune
	glPushMatrix();
	glTranslatef(380, 0, 0);

	GLfloat Neptune_ambient[] = { 1.0f, 0.2f, 0.8f, 1.0f, };   // set ambient of Neptune
	GLfloat Neptune_diffuse[] = { 0.9f, 0.5f, 0.5f, 1.0f, };   // set diffuse of Neptune
	GLfloat Neptune_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f, };   // set specular of Neptune

	// set lighting and materials
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Neptune_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Neptune_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 3.0);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Neptune_specular);

	glutSolidSphere(16, 16, 16);   // draw a sphere as Neptune
	glPopMatrix();
	glPopMatrix();

	//draw lighting and materials of Pluto
	glPushMatrix();
	glColor3f(0.5, 0.1, 1.0);
	glTranslatef(0, 0, 0);
	glRotatef(pluto, 0, 1, 0);   // change the rotate angle of Pluto
	glPushMatrix();
	glTranslatef(420, 0, 0);

	GLfloat Pluto_ambient[] = { 1.0f, 0.2f, 0.8f, 1.0f, };   // set ambient of Pluto
	GLfloat Pluto_diffuse[] = { 0.9f, 0.5f, 0.5f, 1.0f, };   // set diffuse of Pluto
	GLfloat Pluto_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f, };   // set specular of Pluto

	// set lighting and materials
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Pluto_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Pluto_specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Pluto_ambient);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 10.0);

	glutSolidSphere(4, 4, 4);   // draw a sphere as Pluto
	glPopMatrix();
	glPopMatrix();

	// show
	glutSwapBuffers();
}