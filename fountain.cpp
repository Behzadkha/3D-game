#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <vector>
#include <math.h>
#include "particle.h"
using namespace std;

vector<particle> points;
bool friction = true;
bool pause = true;
bool lightonoff = false;
//extra features
bool closehole = false;
bool drawtrace = false;
bool tornado = false;
float alpha = 0;


int rotateAY = 0;	
int rotateAX = 0;
float eye[3] = {2,3,5};


GLfloat ambient[2][4] = {
    { 1, 1, 1, 1 },
    { 1, 0, 0, 1 }
};
GLfloat diffuse[2][4] = {
    { 1, 0, 0, 1 },
    { 0, 0, 1, 1 }
};
GLfloat specular[2][4] = {
    { 1, 1, 1, 1 },
    { 1, 1, 1, 1 }
};
GLfloat lightPos[2][4] = { 
    { 0, 0, 0, 1 },
    { 0, 0, 0, 1 },
};
GLfloat materialAmbient[4][4] = {
    { 0.2, 0.2, 0.2, 1.0 },
    { 0.0215, 0.1745, 0.0215, 1.0 },
    {0.24725,0.1995,0.0745,1.0},
    {0.19225,0.19225,0.19225,1.0}
};
GLfloat materialDiffuse[4][4] = {
    { 0.8, 0.8, 0.8, 1.0 },
    { 0.07568, 0.61424, 0.07568, 1.0 },
    {0.75164,0.60648,0.22648,1.0},
    {0.50754,0.50754,0.50754,1.0}
};
GLfloat materialSpecular[4][4] = {
    { 0, 0, 0, 1 },
    { 0.633, 0.727811, 0.633, 1.0 },
    {0.628281,0.555802,0.366065,1.0},
    {0.508273,0.508273,0.508273,1.0}
};
GLfloat materialShiny[4] = {
    0,
    0.6,
    0.4,
    0.4
};

void setMaterials(unsigned int index) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materialAmbient[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materialDiffuse[index]);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materialSpecular[index]);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, materialShiny[index]);
}


void drawFloor()
{
	//4 quads to have a hole
    glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(-1.2,-0.02,1.2);
	glVertex3f(-1.0,-0.02,1.2);
	glVertex3f(-1.0,-0.02,-1.2);
	glVertex3f(-1.2,-0.02,-1.2);
	setMaterials(3);
    glEnd();

    glBegin(GL_QUADS);
	glColor3f(0, 1, 0);
	glVertex3f(-0.8,-0.02,1.2);
	glVertex3f(0.8,-0.02,1.2);
	glVertex3f(0.8,-0.02,-1.2);
	glVertex3f(-0.8,-0.02,-1.2);
	setMaterials(3);
    glEnd();

    glBegin(GL_QUADS);
	glColor3f(1, 0, 0);
	glVertex3f(1.0,-0.02,1.2);
	glVertex3f(1.2,-0.02,1.2);
	glVertex3f(1.2,-0.02,-1.2);
	glVertex3f(1.0,-0.02,-1.2);
	setMaterials(3);
    glEnd();
///////////////////////////////
    glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(1.0,-0.02,1.2);
	glVertex3f(0.8,-0.02,1.2);
	glVertex3f(0.8,-0.02,0.8);
	glVertex3f(1.0,-0.02,0.8);
	setMaterials(3);
    glEnd();

    glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(1.0,-0.02,0.6);
	glVertex3f(0.8,-0.02,0.6);
	glVertex3f(0.8,-0.02,-1.2);
	glVertex3f(1.0,-0.02,-1.2);
	setMaterials(3);
    glEnd();
//////////////////////////////////////
    glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-1.0,-0.02,1.2);
	glVertex3f(-0.8,-0.02,1.2);
	glVertex3f(-0.8,-0.02,0.3);
	glVertex3f(-1.0,-0.02,0.3);
	setMaterials(3);
    glEnd();

    glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glVertex3f(-1.0,-0.02,-1.2);
	glVertex3f(-0.8,-0.02,-1.2);
	glVertex3f(-0.8,-0.02,-0.3);
	glVertex3f(-1.0,-0.02,-0.3);
	setMaterials(3);
    glEnd();

    if(closehole){
    	glBegin(GL_QUADS);
		glColor3f(1, 0, 1);
		glVertex3f(-1.0,-0.02,-0.3);
		glVertex3f(-0.8,-0.02,-0.3);
		glVertex3f(-0.8,-0.02,0.3);
		glVertex3f(-1.0,-0.02,0.3);
		setMaterials(3);
 		glEnd();
 		glBegin(GL_QUADS);
		glColor3f(1, 0, 1);
		glVertex3f(1.0,-0.02,0.8);
		glVertex3f(0.8,-0.02,0.8);
		glVertex3f(0.8,-0.02,0.6);
		glVertex3f(1.0,-0.02,0.6);
		setMaterials(3);
   		 glEnd();
    }
}
//remove the trace
void removeTrace(int i){
	points[i].tracex.clear();
	points[i].tracey.clear();
	points[i].tracez.clear();
}
void drawTraces(int i){
	//draw traces
   		for(int j = 0; j<(int)points[i].tracex.size(); j++){
			glPushMatrix();
			glColor3f(0,0,1);
			glTranslatef(points[i].tracex[j], points[i].tracey[j], points[i].tracez[j]);
			glutSolidSphere(0.01,3,3);
			glPopMatrix();
		}
}
void drawPoints(){

	for(int i = 0; i< (int)points.size(); i++){
		glPushMatrix();
    	glColor3f(points[i].red,points[i].green,points[i].blue);
    	glTranslatef(points[i].px, points[i].py, points[i].pz);
    	glRotatef(points[i].rx,1,0,0);
    	glRotatef(points[i].ry,0,1,0);
    	glRotatef(points[i].rz,0,0,1);
    	setMaterials(points[i].material);
   		glutSolidSphere(0.02,10,10);
   		glPopMatrix();
   		drawTraces(i);
    }
}
void addTraces(int val){
        if(drawtrace){
        	for(int i =0; i< (int)points.size(); i++){
        		points[i].tracex.push_back(points[i].px);
	    		points[i].tracey.push_back(points[i].py);
	    		points[i].tracez.push_back(points[i].pz);	
   		}
    }
    glutTimerFunc(70, addTraces, 0); // 1sec = 1000, 60fps = 1000/60 = ~17
}
void createParticles(int val){
    if (pause){
        particle point;
   		points.push_back(point);
    }
    glutTimerFunc(70, createParticles, 0); // 1sec = 1000, 60fps = 1000/60 = ~17
}
//Tornado
void startTornado(){
    for(int i = 0; i < (int)points.size(); i++){
    	double x = 1 * cos(5);
		 double z = 1 * sin(5);
		 double deltaX = z * cos(alpha) - x * sin(alpha);
 		double deltaZ = x * cos(alpha) + z * sin(alpha);
 		points[i].px = deltaX/1.5;
 		points[i].pz = deltaZ/1.5;
			 alpha += 0.1;
    }
}
//update the particle movement from pointsAnimation
void updateParticle(int in){
	if(tornado){
		startTornado();	
	}
	else{
		points[in].py = points[in].py + (points[in].dy * points[in].speed);
		points[in].dy -= 9.8;	
		points[in].px = points[in].px + (points[in].dx * points[in].speed);
		points[in].pz = points[in].pz + (points[in].dz * points[in].speed);
	}
	
	//delete after they fall pass -1.0s
	if(points[in].py <= -1.0){
		points.erase(points.begin()+in);
		removeTrace(in);
	}
	//animation for when the particle has almost stopped.
	if(points[in].speed <= 0.0002){
		points[in].py -= 0.001;
	}
}
void particleAge(int i){
//age
	if(points[i].age == 400){
		points.erase(points.begin()+i);
		removeTrace(i);
	}
	points[i].age ++;
}
void Collision(int i){
//Collision detection with the floor + hole
	if(points[i].py <= 0.20 && points[i].px <= 1.2 && points[i].px >= -1.2 && points[i].pz <= 1.2 && points[i].pz >= -1.2){
		//if the point is on one of the holes
		if(((points[i].px >= -1.0 && points[i].px <= -0.8 && points[i].pz >= -0.3 && points[i].pz <= 0.3 ||
		(points[i].px >= 0.8 && points[i].px <= 1.0 && points[i].pz >= 0.6 && points[i].pz <= 0.8)) && !closehole)){
			points[i].speed = 0.0001;
			updateParticle(i);
		}
		//if it hits the floor, reduce the speed
		if(friction){
				points[i].speed -= (points[i].speed * 0.1);
		}
	}
}
//Particle animation
void pointsAnimation(int val){
    for(int i =0; i< (int)points.size(); i++){
    	particleAge(i);
    	//Rotate
    	points[i].rx++;
    	points[i].ry++;
    	points[i].rz++;
    	//checks the next movement and if the points are on the floor
		if(points[i].py + (points[i].dy * points[i].speed) < 0 && points[i].px <= 1.2 && points[i].px >= -1.2 && points[i].pz <= 1.2 && points[i].pz >= -1.2){
				if(((points[i].px >= -1.0 && points[i].px <= -0.8 && points[i].pz >= -0.3 && points[i].pz <= 0.3)||
				 (points[i].px >= 0.8 && points[i].px <= 1.0 && points[i].pz >= 0.6 && points[i].pz <= 0.8))&& !closehole){
					//Prevents the points to get stuck inside the hole
					points[i].px = points[i].px - (points[i].dx * points[i].speed);
					points[i].pz = points[i].pz - (points[i].dz * points[i].speed);
				}
				else{
					//POINTS CONTINUE FALLING WHEN THE HOLE IS CLOSED
					if(points[i].px >= -1.0 && points[i].px <= -0.8 && points[i].pz >= -0.3 && points[i].pz <= 0.3){}
					else if(points[i].px >= 0.8 && points[i].px <= 1.0 && points[i].pz >= 0.6 && points[i].pz <= 0.8){}
					else{
						//floor collision. Inverts its movement direction
						points[i].dy = points[i].dy * -1;
					}	
				}	
		}
		else {
			//updates the particle and deletes it if its height is equal to -0.4
			updateParticle(i);
		}
		
		Collision(i);
		
	}
		glutTimerFunc(17, pointsAnimation, 0); // 1sec = 1000, 60fps = 1000/60 = ~17
}
  
 

//Called from the display function
void draw3DScene(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(eye[0], eye[1], eye[2], 0, 0, 0, 0, 1, 0);
    //lights
	for (unsigned int i = 0; i < 2; i++) {
        glLightfv(GL_LIGHT0 + i, GL_POSITION, lightPos[i]);
        glLightfv(GL_LIGHT0 + i, GL_AMBIENT, ambient[i]);
        glLightfv(GL_LIGHT0 + i, GL_DIFFUSE, diffuse[i]);
        glLightfv(GL_LIGHT0 + i, GL_SPECULAR, specular[i]);
    }
    glPushMatrix();
    
    //rotate about the Y axis by angle rotateAY
    glRotatef(rotateAY,0 ,1 , 0);
    //rotate about the X axis by angle rotateAY
    glRotatef(rotateAX,1 ,0 , 0);
    drawFloor();
    drawPoints();
   
    
    //pop the matrix back to what it was prior to the rotation
    glPopMatrix();

}
void display()
{
    draw3DScene();
    glutSwapBuffers();
	glutPostRedisplay();
}
void handleReshape(int w, int h){
	glViewport(0,0,w,h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45,1,1,100);
	glMatrixMode(GL_MODELVIEW);
}
//keyboard function
void kbd(unsigned char key, int x, int y)
{
	switch (key){
		case 'q':
			exit(0);
			break;
		case 'f':
			friction = !friction;
			break;
		case ' ':
			pause = !pause;
			break;
		case 'r':
			points.clear();
			break;
		case 'l':
			lightonoff = !lightonoff;
			if(lightonoff){
				glEnable(GL_LIGHTING);
    			glEnable(GL_LIGHT0);
    			glEnable(GL_LIGHT1);
    			glCullFace(GL_BACK);
    			glShadeModel(GL_SMOOTH);
			}
			else{
				glDisable(GL_LIGHTING);
			}
    		break;
    	//light controll
		case '1':
			lightPos[0][0]+=0.05;
			break;
		case '2':
			lightPos[0][0]-=0.05;
			break;
		case '3':
			lightPos[0][1]+=0.05;
			break;
		case '4':
			lightPos[0][1]-=0.05;
			break;	
		case '5':
			lightPos[0][2]+=0.05;
			break;
		case '6':
			lightPos[0][2]-=0.05;
			break;

    	case '7':
			lightPos[1][0]+=0.05;
			break;
		case '8':
			lightPos[1][0]-=0.05;
			break;
		case '9':
			lightPos[1][1]+=0.05;
			break;
		case '0':
			lightPos[1][1]-=0.05;
			break;	
		case '-':
			lightPos[1][2]+=0.05;
			break;
		case '=':
			lightPos[1][2]-=0.05;
			break;
    	

    	case 'c':
    		closehole = !closehole;
    		break;
    	case 't':
    		drawtrace = !drawtrace;
    		for(int i = 0; i< (int)points.size(); i++){
    			points[i].tracex.clear();
    			points[i].tracey.clear();
    			points[i].tracez.clear();
    		}
    		break;
    	case 's':
    		tornado = !tornado;
    		break;
    	
	}

}
//arrows for rotating the scene aboute x and y axis
void specialKeys(int key ,int x, int y){
	switch(key){
		case GLUT_KEY_UP:{
			rotateAX++; 
			break;
		}
		case GLUT_KEY_DOWN:{
			rotateAX--;	
			break;
		}
		case GLUT_KEY_LEFT:{
			rotateAY++;
			break;
		}
		case GLUT_KEY_RIGHT:{
			rotateAY--; 	
			break;
		}

	}
}


int main(int argc, char** argv)
{
	printf("%s\n", "keyboard commands");
	printf("%s\n", "f: Friction mode toggle.\nArrow key-Left and Right: rotate about y axis.\nArrow Key-Up and Down: rotate aboute x axis\nspace bar: Start/Stop Simulation\nr: Reset\nl: Lighting");
	printf("%s\n", "1 and 2: moves the first light along the x axis\n3 and 4: moves the first light along the y axis\n5 and 6: movoes the first light along the z axis\n7 and 8: moves the second light along the x axis\n9 and 0: moves the second light along the y axis\n- and =: moves the second light along the z axis\nq: Quites");
	printf("%s\n", "c: Closes the hole\nt: Particle Trail\n*Bonus*\ns: Tornado(using sin and cos)");
	glutInit(&argc, argv);
	glutInitWindowSize(800, 800);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("3D Particles");
	glutReshapeFunc(handleReshape);
	glEnable(GL_DEPTH_TEST);
	glutTimerFunc(0, pointsAnimation, 0);
	glutTimerFunc(0, createParticles, 0);
	glutTimerFunc(0, addTraces, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glutKeyboardFunc(kbd);
	glutSpecialFunc(specialKeys);
	glutDisplayFunc(display);
	glutMainLoop();

	return 0;
}















