#include <GL/freeglut.h>
#include <math.h>
#include "loadBMP.h"
#include "loadTGA.h"
#include <iostream>



float toRad = 3.14159265/180.0;

float radarAngle = 0.0;

GLUquadric *quadric;

float windmill_theta = 0;


//attributes of camera1
int change_flag = 0;		//if the value is i, allowed to change the camera attributes
int cameraValue = 0;		//changing this value will switch to the other camera
float sceneAngle = 0.0;		
float move_distance = 2.0;		//the distance that everytime the camera 1 moves when pressing arrow-up and arrow-down
float camera_to_look = 20.0;	
float camera1_posX = 0.0;
float camera1_posY = 5.0;
float camera1_posZ = 0.0;
float dir_x, dir_y, dir_z;		//the vector of the scene from camera 1
float look_posX = 0, look_posY = 5.0, look_posZ = -50.0;	//the look point
int step = 0;		

float braceTheta = 30.0;
float distanceFromOrigin = 0.0;
//information of car
float car_posX = 0.0;
float car_posY = 0.0;
float car_posZ = 10.0;
float car_theta = 0.0;

//information of the sapceship
float spaceship_posX = 15.0;
float spaceship_posY = 3.0;
float spaceship_posZ = 6.0;
float spaceship_theta = 0.0;
float rotateAngle = 0.0;
int process = 0;

//inforamation of the first alian
float figure1_theta = 0.0;
int figure1_flag = 0;
float figure1_posX = 25.0;
float figure1_posY = 0;
float figure1_posZ = 25.0;
float figure1_walkingAngle = 0.0;

//information of the second alian
float figure2_theta = 0.0;
int figure2_flag = 0;
float figure2_posX = 25.0;
float figure2_posY = 0.0;
float figure2_posZ = 25.0;
float figure2_walkingAngle = 5.0;

//information of the third alian
bool draw_figure3 = true;
float figure3_theta = 0.0;
float figure3_posX = 15.0;
float figure3_posY = 0.1;
float figure3_posZ = -6.0;

GLuint texture_wall;
GLuint texture_building;
GLuint texture_skybox[6];



void loadTexture_wall(void){
	glGenTextures(1, &texture_wall);
	glBindTexture(GL_TEXTURE_2D, texture_wall);
	loadBMP("wall.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);		
}

void loadTexture_building(void){
	glGenTextures(1, &texture_building);
	glBindTexture(GL_TEXTURE_2D, texture_building);
	loadBMP("building.bmp");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

}


void loadTexture_skybox(void){
	glGenTextures(6, texture_skybox);
	
	glBindTexture(GL_TEXTURE_2D, texture_skybox[0]);
	loadBMP("night_front.bmp");
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE ); 
    
	glBindTexture(GL_TEXTURE_2D, texture_skybox[1]);
	loadBMP("night_back.bmp");
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE ); 
    
	glBindTexture(GL_TEXTURE_2D, texture_skybox[2]);
	loadBMP("night_left.bmp");
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE ); 
    
	glBindTexture(GL_TEXTURE_2D, texture_skybox[3]);
	loadBMP("night_right.bmp");
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE ); 
    
	glBindTexture(GL_TEXTURE_2D, texture_skybox[4]);
	loadBMP("night_down.bmp");
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE ); 
    
	glBindTexture(GL_TEXTURE_2D, texture_skybox[5]);
	loadBMP("night_up.bmp");
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE );
    glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );  
     
    
}

void skybox(void){
	loadTexture_skybox();
	
	float width = 200.0;
	float height = 50.0;

	glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 1.0);
	//Map to the front face
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_skybox[0]);
	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);		glVertex3f(-width/2, 0, -width/2);
		glTexCoord2f(1.0, 0.0);		glVertex3f(width/2, 0, -width/2);
		glTexCoord2f(1.0, 1.0);		glVertex3f(width/2, height, -width/2);
		glTexCoord2f(0.0, 1.0);		glVertex3f(-width/2, height, -width/2);
	glEnd();
	
	
	//Map to the back face
	glBindTexture(GL_TEXTURE_2D, texture_skybox[1]);
	glNormal3f(0, 0, -1);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0, 0.0);		glVertex3f(width/2, 0.0, width/2);
		glTexCoord2f(1.0, 0.0);		glVertex3f(-width/2, 0.0, width/2);
		glTexCoord2f(1.0, 1.0);		glVertex3f(-width/2, height, width/2);
		glTexCoord2f(0.0, 1.0);		glVertex3f(width/2, height, width/2);
	glEnd();

	
	//Map to the left face
	glBindTexture(GL_TEXTURE_2D, texture_skybox[2]);
	glNormal3f(1, 0, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);		glVertex3f(-width/2, 0.0, width/2);
		glTexCoord2f(1.0, 0.0);		glVertex3f(-width/2, 0.0, -width/2);
		glTexCoord2f(1.0, 1.0);		glVertex3f(-width/2, height, -width/2);
		glTexCoord2f(0.0, 1.0);		glVertex3f(-width/2, height, width/2);
	glEnd();
	
	//Map to the right face
	glBindTexture(GL_TEXTURE_2D, texture_skybox[3]);
	glNormal3f(-1, 0, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);		glVertex3f(width/2, 0, -width/2);
		glTexCoord2f(1.0, 0.0);		glVertex3f(width/2, 0, width/2);
		glTexCoord2f(1.0, 1.0);		glVertex3f(width/2, height, width/2);
		glTexCoord2f(0.0, 1.0);		glVertex3f(width/2, height, -width/2);
	glEnd();
	
	//Map to the bottom face
	glBindTexture(GL_TEXTURE_2D, texture_skybox[4]);
	glNormal3f(0, 1, 0);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0);		glVertex3f(-width/2, 0, width/2);
		glTexCoord2f(1.0, 0.0);		glVertex3f(width/2, 0, width/2);
		glTexCoord2f(1.0, 1.0);		glVertex3f(width/2, 0, -width/2);
		glTexCoord2f(0.0, 1.0);		glVertex3f(-width/2, 0, -width/2);
	glEnd();
	
	//Map to the top face
	glBindTexture(GL_TEXTURE_2D, texture_skybox[5]);
	glNormal3f(0, -1, 0);
	glBegin(GL_QUADS);	
		glTexCoord2f(0.0, 0.0);		glVertex3f(width/2, height, width/2);
		glTexCoord2f(1.0, 0.0);		glVertex3f(-width/2, height, width/2);
		glTexCoord2f(1.0, 1.0);		glVertex3f(-width/2, height, -width/2);
		glTexCoord2f(0.0, 1.0);		glVertex3f(width/2, height, -width/2);
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	
}


void drawWall(void){
	loadTexture_wall();
	
	float x1, z1, x2, z2, x3, z3, x4, z4;
	float sa1, sa2, ca1, ca2;
	
	glColor3f(0.0, 0.0, 0.0);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	for(int i = 15; i < 180; i += 33){
		float angleWall1 = i * toRad;
		float angleWall2 = (i + 27) * toRad;
		ca1=cos(angleWall1); ca2=cos(angleWall2);
		sa1=sin(angleWall1); sa2=sin(angleWall2);
		
		x1=-(60-1)*sa1; z1=(60-1)*ca1; 
		x2=-(60+1)*sa1; z2=(60+1)*ca1;
		x3=-(60+1)*sa2; z3=(60+1)*ca2;
		x4=-(60-1)*sa2; z4=(60-1)*ca2;
		
		glNormal3f(0., 1., 0.);       //Quad 1 facing up
		glTexCoord2f(0, 1/3);	glVertex3f(x1, 8.0, z1);
		glTexCoord2f(1, 1/3);	glVertex3f(x2, 8.0, z2);
		glTexCoord2f(1, 2/3);	glVertex3f(x3, 8.0, z3);
		glTexCoord2f(0, 2/3);	glVertex3f(x4, 8.0, z4); 

		glNormal3f(-sa1, 0.0, -ca1);   //Quad 2 facing inward
		glTexCoord2f(0, 0);		glVertex3f(x1, 0.0, z1);
		glTexCoord2f(1, 0);		glVertex3f(x1, 8.0, z1);
		glNormal3f(-sa2 ,0.0, -ca2);
		glTexCoord2f(1, 1);		glVertex3f(x4, 8.0, z4);
		glTexCoord2f(0, 1);		glVertex3f(x4, 0.0, z4);

		glNormal3f(sa1, 0.0, ca1);   //Quad 3 facing outward
		glVertex3f(x2, 8.0, z2);
		glVertex3f(x2, 0.0, z2);
		glNormal3f(sa2, 0.0, ca2);
		glVertex3f(x3, 0.0, z3);
		glVertex3f(x3, 8.0, z3);
	}

	



	for(int i = 15; i < 180; i += 33){
		float angleWall1 = i * toRad;
		float angleWall2 = (i + 27) * toRad;
		ca1=cos(angleWall1); ca2=cos(angleWall2);
		sa1=sin(angleWall1); sa2=sin(angleWall2);
		
		x1=(60-1)*sa1; z1=(60-1)*ca1; 
		x2=(60+1)*sa1; z2=(60+1)*ca1;
		x3=(60+1)*sa2; z3=(60+1)*ca2;
		x4=(60-1)*sa2; z4=(60-1)*ca2;
		
		glNormal3f(0., 1., 0.);       //Quad 1 facing up
		glTexCoord2f(0, 1/3);	glVertex3f(x1, 8.0, z1);
		glTexCoord2f(1, 1/3);	glVertex3f(x2, 8.0, z2);
		glTexCoord2f(1, 2/3);	glVertex3f(x3, 8.0, z3);
		glTexCoord2f(0, 2/3);	glVertex3f(x4, 8.0, z4); 

		glNormal3f(-sa1, 0.0, -ca1);   //Quad 2 facing inward
		glTexCoord2f(0, 0);		glVertex3f(x1, 0.0, z1);
		glTexCoord2f(1, 0);		glVertex3f(x1, 8.0, z1);
		glNormal3f(-sa2 ,0.0, -ca2);
		glTexCoord2f(1, 1);		glVertex3f(x4, 8.0, z4);
		glTexCoord2f(0, 1);		glVertex3f(x4, 0.0, z4);

		glNormal3f(sa1, 0.0, ca1);   //Quad 3 facing outward
		glVertex3f(x2, 8.0, z2);
		glVertex3f(x2, 0.0, z2);
		glNormal3f(sa2, 0.0, ca2);
		glVertex3f(x3, 0.0, z3);
		glVertex3f(x3, 8.0, z3);
	}
	glEnd();
	
	glDisable(GL_TEXTURE_2D);
	
}


void drawTower(void){
	float angleTower = 6.0 / 2 * toRad;
	float towerSize = sin(angleTower) * 60 * 2;
	
	loadTexture_wall();
	glBindTexture(GL_TEXTURE_2D, texture_wall);
	glEnable(GL_TEXTURE_2D);
	
	glColor3f(0.0, 0.0, 0.0);
	for(int i = 0; i < 6; i ++){
		glPushMatrix();
			glRotatef(i*33 + 15, 0, 1, 0);
			glTranslatef(-towerSize/2, 0.0, 60.0);
			glScalef(1.0, 2.0, 0.8);
			
			glPushMatrix();
				glRotatef(-90, 1, 0, 0);
				gluCylinder(quadric, towerSize/2, towerSize/2, towerSize, 100, 100);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0.0, towerSize, 0.0);
				glRotatef(-90, 1, 0, 0);
				gluCylinder(quadric, towerSize/2, 0, towerSize/2, 100, 100);
			glPopMatrix();
			
		glPopMatrix();
	
	}
		
		
	for(int i = 0; i < 6; i ++){
		glPushMatrix();
			glRotatef(-(i*33 + 15), 0, 1, 0);
			glTranslatef(towerSize/2, 0.0, 60.0);
			glScalef(1.0, 2.0, 0.8);
			
			glPushMatrix();
				glRotatef(-90, 1, 0, 0);
				gluCylinder(quadric, towerSize/2, towerSize/2, towerSize, 100, 100);
			glPopMatrix();
			
			glPushMatrix();
				glTranslatef(0.0, towerSize, 0.0);
				glRotatef(-90, 1, 0, 0);
				gluCylinder(quadric, towerSize/2, 0, towerSize/2, 100, 100);
			glPopMatrix();
			
		glPopMatrix();
		

	}
	glDisable(GL_TEXTURE_2D);
	
}


void drawCar(void){
	
	glColor3f(1.0, 1.0, 0.5);
	glPushMatrix();
		glTranslatef(0.0, 2.0, 0.0);
		
		glPushMatrix();
			glTranslatef(0.0, 0.8, 0.0);
			glScalef(1.0, 0.2, 1.0);
			glutSolidCone(2, 4, 50, 50);
		glPopMatrix();
		
		glPushMatrix();
			glColor3f(0.0, 0.0, 0.0);
			glTranslatef(0.0, 0.8, -0.2);
			glScalef(2.0, 0.2, 0.4);
			glutSolidCube(1.0);
		glPopMatrix();
		
		//draw three wheels for the car
		glColor3f(0.0, 0.0, 1.0);
		glPushMatrix();
			glTranslatef(0.0, 0.0, 3.0);
			glRotatef(90, 0, 1, 0);
			gluDisk(quadric, 0.25, 0.6, 50, 50);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(-1, 0.0, 0.2);
			glRotatef(90, 0, 1, 0);
			gluDisk(quadric, 0.25, 0.6, 50, 50);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(1, 0.0, 0.2);
			glRotatef(90, 0, 1, 0);
			gluDisk(quadric, 0.25, 0.6, 50, 50);
		glPopMatrix();
	glPopMatrix();
}

void drawRadar(void){
	glColor3f(0.0, 1.0, 0.0);
	glPushMatrix();
		glRotatef(radarAngle, 0, 1, 0);
		glPushMatrix();
			glRotatef(-90, 1, 0, 0);
			gluCylinder(quadric, 0.1, 0.1, 0.6, 50, 50);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.0, 0.6, 0.0);
			glRotatef(30, 0, 0, 1);
			glScalef(1.0, 0.2, 1.0);
			glutSolidSphere(1, 50, 50);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.0, 0.8, 0.0);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(quadric, 0.1, 0.1, 0.5, 50, 50);
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0.0, 1.5, 0.0);
			glutSolidSphere(0.2, 50, 50);
		glPopMatrix();
	glPopMatrix();
}

void drawBuilding(void){
	loadTexture_building();
	glBindTexture(GL_TEXTURE_2D, texture_building);
	
	glEnable(GL_TEXTURE_2D);
	
	glColor4f(0.0, 1.0, 1.0, 1.0);
	glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		gluCylinder(quadric, 8.0, 6.0, 12.0, 100, 100);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	
	glPushMatrix();
		glTranslatef(0.0, 13.0, 0.0);
		gluSphere(quadric, 6.0, 100, 100);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.0, 19, 0.0);
		drawRadar();
	glPopMatrix();
}

void drawHouse(void){
	loadTexture_building();
	glBindTexture(GL_TEXTURE_2D, texture_building);
	
	glEnable(GL_TEXTURE_2D);
	
	glPushMatrix();
		gluSphere(quadric, 4.0, 100, 100);
	glPopMatrix();
	
	glDisable(GL_TEXTURE_2D);
}

void drawWindmill(void){
	
	glColor3f(1.0, 0.0, 0.0);
	glPushMatrix();
		glRotatef(-90, 1, 0, 0);
		glutSolidCone(4.0, 6.0, 100, 100);
	glPopMatrix();
	
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(0.0, 6.5, 0.0);
		glutSolidSphere(0.5, 50, 50);
	glPopMatrix();
	
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(0.0, 6.5, 2.0);
		glRotatef(windmill_theta, 0, 0, 1);
		glPushMatrix();
			glScalef(0.1, 6.0, 0.1);
			glutSolidCube(1.0);
		glPopMatrix();
		
		glPushMatrix();
			glScalef(6.0, 0.1, 0.1);
			glutSolidCube(1.0);
		glPopMatrix();
		
		//draw 4 fans of the windmill
		for(int i = 0; i < 4; i ++){
			glPushMatrix();
				glRotatef(90 * i, 0, 0, 1);
				glTranslatef(1.0, 2.0, 0.0);
				glScalef(2.0, 1.0, 0.1);
				glutSolidCube(1.0);
			glPopMatrix();
		}
		
		glutSolidSphere(0.5, 20, 20);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0, 6.5, 1);
		gluCylinder(quadric, 0.1, 0.1, 2, 10, 10);
	glPopMatrix();
}

void drawSurface(void){
	
	float white[4] = {1., 1., 1., 1.};
	float black[4] = {0};
	glColor3f(0.0, 1.0, 1.0); 
	glNormal3f(0.0, 1.0, 0.0);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);

	glBegin(GL_QUADS);

	for(int i = -100; i < 100; i++){
		for(int j = -100;  j < 100; j++){
			glVertex3f(i, 0.0, j);
			glVertex3f(i, 0.0, j+1);
			glVertex3f(i+1, 0.0, j+1);
			glVertex3f(i+1, 0.0, j);
		}
	}

	glEnd();
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
}

void drawBrace(void){
	glPushMatrix();
		glColor3f(1.0, 0.0, 0.0);
		glutSolidSphere(0.5, 50, 50);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.0, 1.0, 0.0);
		glTranslatef(0.0, -0.5, 0.0);
		glRotatef(90, 1, 0, 0);
		gluCylinder(quadric, 0.5, 0.5, 3.0, 50, 50);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.0);
		glTranslatef(0.0, -3.5, 0.0);
		glRotatef(90, 1, 0, 0);
		glutSolidCone(0.5, 0.5, 50, 50);
	glPopMatrix();
}


void drawSpaceship(void){
	
	glPushMatrix();
		glColor3f(0.0, 0.0, 0.8);
		glTranslatef(0.0, 4.5, 0.0);
		glScalef(1.0, 0.5, 1.0);
		glutSolidSphere(2.0, 50, 50);
	glPopMatrix();
	
	glPushMatrix();
		glColor3f(0.8, 0.8, 0.0);
		glTranslatef(0.0, 2.0, 0.0);
		glScalef(2.0, 0.5, 2.0);
		glutSolidSphere(4, 100, 100);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(5, 0.4, 0.0);
		glRotatef(braceTheta, 0, 0, 1);
		drawBrace();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(120, 0, 1, 0);
		glTranslatef(5, 0.4, 0.0);
		glRotatef(braceTheta, 0, 0, 1);
		drawBrace();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(240, 0, 1, 0);
		glTranslatef(5, 0.4, 0.0);
		glRotatef(braceTheta, 0, 0, 1);
		drawBrace();
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(2.0, 4.0, -2.0);
		drawRadar();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(rotateAngle, 0, 1, 0);
		glPushMatrix();
			glColor3f(0.5, 0.5, 0.5);
			glTranslatef(0.0, 2.0, 0.0);
			glRotatef(90, 1, 0, 0);
			gluDisk(quadric, 8.0, 14.0, 100, 100);
		glPopMatrix();
		
		glColor3f(0.0, 0.0, 1.0);
		for(int i = 0; i < 12; i ++){
			glPushMatrix();
				glRotatef(i * 30, 0, 1, 0);
				glTranslatef(0.0, 2.0, 11.0);
				glutSolidSphere(0.5, 10, 10);
			glPopMatrix();
		}
	glPopMatrix();
}

void drawLimb(void){
	glColor3f(0.0, 0.0, 0.0);
	
	glPushMatrix();
		glutSolidSphere(0.2, 50, 50);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0, -(0.5 + 0.2), 0.0);
		glScalef(0.2, 1.0, 0.2);	
		glutSolidCube(1.0);
	glPopMatrix();
	
	glPushMatrix();
		glTranslatef(0.0, -(0.5 + 0.4 + 0.2), 0.0);
		glutSolidSphere(0.2, 50, 50);
	glPopMatrix();
	
}

void drawAlian(float theta){
	glColor3f(0.0, 1.0, 1.0);
	glPushMatrix();
		glTranslatef(0.0, 2.0, 0.0);
		glPushMatrix();					//body
			glScalef(1.0, 2.0, 0.5);
			glutSolidCube(1.0);
		glPopMatrix();
		
		glPushMatrix();					//left arm
			glTranslatef(0.6, 0.8, 0.0);
			glRotatef(-theta, 1, 0, 0);
			drawLimb();
		glPopMatrix();
		
		glPushMatrix();					//right arm
			glTranslatef(-0.6, 0.8, 0.0);
			glRotatef(theta, 1, 0, 0);
			drawLimb();
		glPopMatrix();
		
		glPushMatrix();					//left leg
			glTranslatef(0.6, -0.8, 0.0);
			glRotatef(theta, 1, 0, 0);
			drawLimb();
		glPopMatrix();
		
		glPushMatrix();					//right leg
			glTranslatef(-0.6, -0.8, 0.0);
			glRotatef(-theta, 1, 0, 0);
			drawLimb();
		glPopMatrix();
		
		glPushMatrix();					//head
			glTranslatef(0.0, 1.5, 0.0);
			glRotatef(90, 1, 0, 0);
			glutSolidCone(0.5, 0.5, 50, 50);
		glPopMatrix();
	glPopMatrix();
	
}

void straightRoadComponent(bool fourWhiteLines){
	float beginX = -6.0;
	float endX = 6.0;
	
	float x1, x2;
	
	float white1 = 1.0;
	float white2 = 4.5;
	
	glColor3f(0.2, 0.2, 0.2);
	glNormal3f(-1, 0, 0);
	glBegin(GL_QUADS);
		glVertex3f(beginX, 0.0, 0.0);
		glVertex3f(beginX, 0.0, 1.0);
		glVertex3f(beginX, 0.1, 1.0);
		glVertex3f(beginX, 0.1, 0.0);
	glEnd();
	
	for(float i = beginX; i < endX; i += 0.5){
		if(fourWhiteLines){
			if(i == white1 or i == white2 or i == -white1 or i == -white2){
				glColor3f(1.0, 1.0, 1.0);
			}else{
				glColor3f(0.2, 0.2, 0.2);
			}
		}else{
			if(i == white1 or i == - white1){
				glColor3f(1.0, 1.0, 1.0);
			}else{
				glColor3f(0.2, 0.2, 0.2);
			}
		}
		
		x1 = i;
		x2 = i + 0.5;
		
		glNormal3f(0, 1, 0);
		glBegin(GL_QUADS);
			glVertex3f(x1, 0.1, 0.0);
			glVertex3f(x2, 0.1, 0.0);
			glVertex3f(x2, 0.1, 1);
			glVertex3f(x1, 0.1, 1);
		glEnd();
		
	}
	
	glColor3f(0.2, 0.2, 0.2);
	glNormal3f(1, 0, 0);
	glBegin(GL_QUADS);
		glVertex3f(endX, 0.0, 0.0);
		glVertex3f(endX, 0.1, 0.0);
		glVertex3f(endX, 0.1, 1.0);
		glVertex3f(endX, 0.0, 1.0);
	glEnd();
}


void drawRoundRoad(float beginZ, float endZ){
	float theta = 1.0 * toRad;
	float white1 = beginZ + 1;
	float white2 = endZ - 1;
	
	float x1, z1, x2, z2;
	glColor3f(0.2, 0.2, 0.2);
	for(float angle = 0.0; angle < 360.0; angle ++){
		glPushMatrix();
		glRotatef(-angle, 0, 1, 0);
		for(float i = beginZ; i < endZ; i += 0.5){
			x1 = sin(theta) * i;
			z1 = cos(theta) * i;
			x2 = sin(theta) * (i + 0.5);
			z2 = cos(theta) * (i + 0.5);
			
			if(i == white1 or i == white2){
				glColor3f(1.0, 1.0, 1.0);
			}else{
				glColor3f(0.2, 0.2, 0.2);
			}
			glNormal3f(0.0, 1.0, 0.0);		//face up
			glBegin(GL_QUADS);
			glVertex3f(x1, 0.09, z1);
			glVertex3f(0.0, 0.09, i);
			glVertex3f(0.0, 0.09, i + 0.5);
			glVertex3f(x2, 0.09, z2);
			glEnd();
		}
		
		glColor3f(0.2, 0.2, 0.2);
		glNormal3f(0.0, 0.0, -1.0);			//face inward
		glBegin(GL_QUADS);
		glVertex3f(sin(theta) * beginZ, 0.0, beginZ);
		glVertex3f(0.0, 0.0, beginZ);
		glVertex3f(0.0, 0.09, beginZ);
		glVertex3f(sin(theta) * beginZ, 0.09, beginZ);
		glEnd();
		
		glPopMatrix();

	}

}

void drawPad(void){
	float radious = 6.0;
	float x1, x2, z1, z2;
	float theta = 1.0 * toRad;
	
	glColor3f(0.5, 0.5, 0.5);

	for(float angle = 0.0; angle < 360.0; angle ++){
		glPushMatrix();
		glRotatef(-angle, 0, 1, 0);
		for(float i = 0.0; i < radious; i ++){
			x1 = sin(theta) * i;
			z1 = cos(theta) * i;
			x2 = sin(theta) * (i + 1);
			z2 = cos(theta) * (i + 1);
		
			glNormal3f(0.0, 1.0, 0.0);		//face up
			glBegin(GL_QUADS);
			glVertex3f(x1, 0.1, z1);
			glVertex3f(0.0, 0.1, i);
			glVertex3f(0.0, 0.1, i + 1);
			glVertex3f(x2, 0.1, z2);
			glEnd();
		}
		
		glNormal3f(0.0, 0.0, 1.0);			//face outward
		glBegin(GL_QUADS);
		glVertex3f(sin(theta) * radious, 0.0, radious);
		glVertex3f(sin(theta) * radious, 0.1, radious);
		glVertex3f(0.0, 0.1, radious);
		glVertex3f(0.0, 0.0, radious);
		glEnd();
		
		glPopMatrix();
	}

}

void drawRoad(void){
	float white[4] = {1., 1., 1., 1.};
	float black[4] = {0};
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, black);

	
	float beginRoundRoad1 = 40.0;
	float endRoundRoad1 = 45;
	
	float beginRoundRoad2 = 25.0;
	float endRoundRoad2 = 30.0;
	
	drawRoundRoad(beginRoundRoad1, endRoundRoad1);
	drawRoundRoad(beginRoundRoad2, endRoundRoad2);
	int length = 120;
	
	for(float i = 0; i < length; i ++){
		glPushMatrix();
			glTranslatef(0.0, 0.0, 1.0 * i);
			if(i > beginRoundRoad1 and i < endRoundRoad1 and i > beginRoundRoad2 and i < endRoundRoad2){
				straightRoadComponent(false);
			}else{
				straightRoadComponent(true);
			}
		glPopMatrix();
	}
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);


}

void drawLaunchPad(void){
	glColor3f(0.5, 0.5, 0.5);
	
	glPushMatrix();
	glTranslatef(15, 1, 6);
	glScalef(1.0, 0.05, 1.0);
	glutSolidCube(10);
	glPopMatrix();
}

void initialise(void){
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	float grey[4] = {0.2, 0.2, 0.2, 1.0};
	float white[4]  = {1.0, 1.0, 1.0, 1.0};
	float blue[4] = {0.0, 0.0, 1.0, 1.0};
	//float red[4] = {1.0, 0.0, 0.0, 1.0};
	
	glEnable(GL_LIGHTING);
	
	glEnable(GL_LIGHT0);
	float light0_pos[4] = {-10, 20.0, -10, 1.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, grey);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);
	glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
	
	//the spot light on the car
	glEnable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT, blue);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT1, GL_SPECULAR, white);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF,40.0);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 0.01);
    
    //glEnable(GL_LIGHT2);
    glLightfv(GL_LIGHT2, GL_AMBIENT, blue);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, blue);
    glLightfv(GL_LIGHT2, GL_SPECULAR, blue);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF,5.0);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 0.01);	
	
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	
	glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	
	quadric = gluNewQuadric();
	gluQuadricDrawStyle(quadric, GLU_FILL );
	gluQuadricNormals(quadric, GLU_SMOOTH );
	gluQuadricTexture(quadric, GL_TRUE);

	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60., 1.0, 5.0, 1000.0); 
	
}

void display(void){
	float lgt1_pos[] = {0.0f, 0.8f, 4.0f, 1.0f};
	float lgt1_dir[] = {0.0f, -1.0f, 1.0f, 1.0f};
	
	float lgt2_pos[] = {0.0f, 1.0f, 0.0f, 1.0f};
	float lgt2_dir[] = {0.0f, -1.0f, 0.0f, 1.0f};

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	if(cameraValue == 0){
		float radious = toRad * sceneAngle;
		dir_x = -sin(radious);
		dir_y = 0;
		dir_z = -cos(radious);
		
		if(change_flag == 1){
			if(step > 0){
				camera1_posX += move_distance * dir_x;
				camera1_posZ += move_distance * dir_z;
			}else if(step < 0){
				camera1_posX -= move_distance * dir_x;
				camera1_posZ -= move_distance * dir_z;
			}
			
			look_posX = camera1_posX + camera_to_look * dir_x;
			look_posY = camera1_posY + camera_to_look * dir_y;
			look_posZ = camera1_posZ + camera_to_look * dir_z;
		
		}
		
		gluLookAt(camera1_posX, camera1_posY, camera1_posZ, look_posX, look_posY, look_posZ, 0, 1, 0);
		
		change_flag = 0;

	}else if(cameraValue == 1){
		gluLookAt(spaceship_posX, spaceship_posY, spaceship_posZ, 0, 0, 0, 0, 1, 0);
	}
	
	
	
	drawSurface();	
	skybox();
	
	drawRoad();
	drawWall();
	drawTower();
	drawLaunchPad();

	glPushMatrix();
		glTranslatef(15.0, 0.0, -6.0);
		drawPad();
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-10, 0, -35);
		glScalef(0.8, 0.8, 0.8);
		drawBuilding();
	glPopMatrix();
	

	for(float theta = 0.0; theta < 60.0; theta += 20.0){
		glPushMatrix();
			glRotatef(120.0 + theta, 0, 1, 0);
			glTranslatef(0.0, 0.0, 35);
			drawHouse();
		glPopMatrix();
	}

	for(float theta = 0.0; theta < 60.0; theta += 20.0){
		glPushMatrix();
			glRotatef(-(80.0 + theta), 0, 1, 0);
			glTranslatef(0.0, 0.0, 35);
			drawHouse();
		glPopMatrix();
	}
	
	glPushMatrix();
		glTranslatef(-15, 0, 15);
		glRotatef(120, 0, 1, 0);
		drawWindmill();
	glPopMatrix();
	
	//glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
		glTranslatef(spaceship_posX, spaceship_posY, spaceship_posZ);
		glLightfv(GL_LIGHT2, GL_POSITION, lgt2_pos);
		glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, lgt2_dir);
		glScalef(0.5, 0.5, 0.5);
		drawSpaceship();
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(figure1_walkingAngle, 0, 1, 0);
		glTranslatef(figure1_posX, figure1_posY, figure1_posZ);
		drawAlian(figure1_theta);
	glPopMatrix();
	
	glPushMatrix();
		glRotatef(figure2_walkingAngle, 0, 1, 0);
		glTranslatef(figure2_posX, figure2_posY, figure2_posZ);
		drawAlian(figure2_theta);
	glPopMatrix();
	
	
	
	if(draw_figure3){
		glPushMatrix();
			glTranslatef(figure3_posX, figure3_posY, figure3_posZ);
			drawAlian(figure3_theta);
		glPopMatrix();
	}
	
	
	glPushMatrix();
		glTranslatef(car_posX, car_posY, car_posZ);
		glRotatef(car_theta, 0, 1, 0);
		glLightfv(GL_LIGHT1, GL_POSITION, lgt1_pos);
		glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, lgt1_dir);
		drawCar();
		
	glPopMatrix();
	
	glFlush();
	glutSwapBuffers();
}

void special(int key, int x, int y){
	step = 0;
	
	switch(key){
		case GLUT_KEY_UP: 
			step = 1;
			change_flag = 1;
			break;
		case GLUT_KEY_DOWN:
			step = -1;
			change_flag = 1;
			break;
		case GLUT_KEY_LEFT:
			sceneAngle += 5.0;
			change_flag = 1;
			break;
		case GLUT_KEY_RIGHT:
			sceneAngle -= 5.0;
			change_flag = 1;
			break;
	}
	
	glutPostRedisplay();
}


void firstAlianTimer(void){
		if(figure1_flag == 0 && figure1_theta > -20.0){
			figure1_theta -= 1.0;
		}
		
		if(figure1_flag == 1 && figure1_theta < 20.0){
			figure1_theta += 1.0;
		}
		
		if(figure1_theta == -20.0 || figure1_theta == 20.0){
			figure1_flag = 1 - figure1_flag; 
			figure1_walkingAngle ++;
		}
}

void secondAlianTimer(void){
		if(figure2_flag == 0 && figure2_theta > -20.0){
			figure2_theta -= 1.0;
		}
		
		if(figure2_flag == 1 && figure2_theta < 20.0){
			figure2_theta += 1.0;
		}
		
		if(figure2_theta == -20.0 || figure2_theta == 20.0){
			figure2_flag = 1 - figure2_flag; 
			figure2_walkingAngle ++;
		}
}

bool finishBoarding(void){
	bool isReady = false;
	if(figure3_posY < 8){
		figure3_posY += 0.1;
	}else{
		isReady = true;
	}
	return isReady;
}

bool readyForBoarding(void){
	bool isReady = false;
	if(spaceship_posY < 10){
		spaceship_posY += 0.2;
	}else if(spaceship_posZ > figure3_posZ){
		spaceship_posZ -= 0.2;
	}else{
		isReady = true;
	}
	
	return isReady;
}

bool readyToLeave(void){
	bool isReady = false;
	if(braceTheta >= 90.0){
		isReady = true;
	}else{
		braceTheta ++;
	}
	
	return isReady;
}

bool readyToFly(void){
	bool isReady = false;
	if(spaceship_posY < 40){
		spaceship_posY += 0.2;
	}else if(spaceship_posX < 65.0){
		spaceship_posX += 0.2;
	}else{
		isReady = true;
	}
	return isReady;
}



void carTimer(void){
	if(car_posZ < 80 and car_theta == 0.0){
		car_posZ += 1;
	}else if(car_posZ == 80.0 and car_theta < 180.0){
		car_theta ++;
	}else if(car_posZ > 10.0 and car_theta == 180.0){
		car_posZ --;
	}else if(car_posZ == 10.0 and car_theta > 0){
		car_theta --;
	}
}

void myTimer(int value){
	carTimer();
	radarAngle += 2;
	rotateAngle ++;
	windmill_theta += 2;
	
	firstAlianTimer();
	secondAlianTimer();
	
	if(process == 1){
		if(readyToLeave()){
			if(readyForBoarding()){
				glEnable(GL_LIGHT2);
				if(finishBoarding()){
					draw_figure3 = false;
					glDisable(GL_LIGHT2);
					if(readyToFly()){
						process = 2;
					}
				}
			}
		}
	}
	
	if(process == 2){
		if(spaceship_posZ < 0.0){
			spaceship_posZ += 0.2;
		}else{
			process = 3;
		}
	}
	
	if(process == 3){
		spaceship_posX = cos(spaceship_theta * toRad) * 65.0;
		spaceship_posZ = sin(spaceship_theta * toRad) * 65.0;
		spaceship_theta += 1.0;
	}
	
	
	glutPostRedisplay();
	value ++;
	glutTimerFunc(100, myTimer, value);
	
	
}


void keyboard(unsigned char key, int x, int y){
	switch(key){
		case ' ':
			process = 1;
			break;
		case 's':
			cameraValue = 1 - cameraValue;
			break;
	}
	
}



int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);           //single or double ?
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Spaceport");
	
	initialise();
	
	glutDisplayFunc(display);
	glutSpecialFunc(special);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(100, myTimer, 0);
	glutMainLoop();
	return 0;
}
