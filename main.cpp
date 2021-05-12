///display highscore - done!!
///arrow keys - done!!
///plane has crashed - done!!
///check for the coordinates - speed constant - done!!
///customize plane - done!!
///instructions - done!!



#include<windows.h>
#include<graphics.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
#include <stdlib.h>
#include<conio.h>
#include<string>
#define rad (3.1416/180)
#define EN_SIZE 20

using namespace std;

int highscore = 0;
int score = 0;
int crash = 0;
int f,f1,f2,f3,f4,f5,f6;
float zoom=4;
int houseArr[5000][5000];
float tX=0,tY=0,tZ=-8,rX=0,rY=0,rZ=4;
float tZ1=-20,tZ2=-40,tZ3=-60,tZ4=-80,tZ5=-100,tZ6=-120;
float rotX=0,rotY=0,rotZ=0;
float angle=0;
float xEye=0.0f,yEye=5.0f,zEye=30.0f;
float cenX=0,cenY=0,cenZ=0,roll=0;
float radius=0;
float theta=0,slope=0;
float speed = 0.3;
float angleBackFrac = 0.2;
float r[] = {0.1,0.4,0.0,0.9,0.2,0.5,0.0,0.7,0.5,0.0};
float g[] = {0.2,0.0,0.4,0.5,0.2,0.0,0.3,0.9,0.0,0.2};
float b[] = {0.4,0.5,0.0,0.7,0.9,0.0,0.1,0.2,0.5,0.0};
int TIME=0;
bool START = false;
float torusPosX[7] = {1,-2,3,-4,-2,0,2};
float torusPosY[7] = {2,3,10,6,7,4,3};
char * buf;


const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };


float R=0.40; float G=0.6; float B=1; //plane
float Rw=0.0; float Gw=0.1; float Bw=0.6; //wings


static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 1000.0); //left,right,bottom,top,nearVal,farVal
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void drawStrokeText(char* str,int x,int y,int z)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y+8,z);
	  glScalef(0.002f,0.002f,z);

	  for (c=str; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();
}

void drawStrokeText2(char* str,int x,int y,int z)
{
	  char *c;
	  glPushMatrix();
	  glTranslatef(x, y+8,z);
	  glScalef(0.005f,0.005f,z);

	  for (c=str; *c != '\0'; c++)
	  {
    		glutStrokeCharacter(GLUT_STROKE_ROMAN , *c);
	  }
	  glPopMatrix();
}


void fan(){
    ///center
    glColor3d(0,0,0);
    glPushMatrix();
        glTranslated(0,0,0);
        glScaled(1,1,0.7);
        glutSolidSphere(0.8,30,30);
    glPopMatrix();

    ///blades
    glColor3d(R,G,B);
    glPushMatrix();
        glTranslated(0,0,0);
        glRotated(5,0,1,0);
        glScaled(0.5,2.5,0.05);
        glutSolidSphere(1,30,30);
    glPopMatrix();

    glColor3d(R,G,B);
    glPushMatrix();
        glTranslated(0,0,0);
        glRotated(-5,0,1,0);
        glRotated(90,0,0,1);
        glScaled(0.5,2.5,0.05);
        glutSolidSphere(1,30,30);
    glPopMatrix();

}

//menu
void plane(){
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t*90.0;

    /// Main body
    glColor3d(R,G,B); //color - cylinder
    glPushMatrix();
        glTranslated(0,0,0);
        glScaled(3,0.4,0.5);
        glutSolidSphere(1,30,30);
    glPopMatrix();

    glColor3d(0,0,0); //color - cockpit
    glPushMatrix();
        glTranslated(1.7,0.1,0);
        glScaled(1.5,0.7,0.8);
        glRotated(40,0,1,0);
        glutSolidSphere(0.45,30,30);
    glPopMatrix();

    ///front wings

    ///Right wing
    glColor3d(Rw,Gw,Bw); //color
    glPushMatrix();
        glTranslated(0,0,1.2);
        glRotated(-50,0,1,0);
        glScaled(0.7,0.1,3);
        glRotated(25,0,1,0);
        glutSolidCube(1);
    glPopMatrix();

    ///propeller1
    glColor3d(Rw,Gw,Bw); //color
    glPushMatrix();
        glTranslated(-0.3,-0.15,1.5);
        glRotated(90,0,1,0);
        /// FAN
        glPushMatrix();
            glTranslated(0,0,0.5);
            glRotated(10*a,0,0,1);
            glScaled(0.1,0.1,0.1);
            fan();
       glPopMatrix();
        glScaled(0.1,0.1,0.9);
        glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();

    ///propeller2
    glColor3d(Rw,Bw,Gw); //color
    glPushMatrix();
        glTranslated(0.2,-0.15,0.9);
        glRotated(90,0,1,0);
        /// FAN
        glPushMatrix();
            glTranslated(0,0,0.5);
            glRotated(10*a,0,0,1);
            glScaled(0.1,0.1,0.1);
            fan();
       glPopMatrix();
        glScaled(0.1,0.1,0.9);
        glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();

   ///Left wing
    glColor3d(Rw,Gw,Bw); //color
    glPushMatrix();
        glTranslated(0,0,-1.2);
        glRotated(50,0,1,0);
        glScaled(0.7,0.1,3);
        glRotated(-25,0,1,0);
        glutSolidCube(1);
    glPopMatrix();

    ///propeller1
    glColor3d(Rw,Gw,Bw); //color
    glPushMatrix();
        glTranslated(-0.3,-0.15,-1.5);
        glRotated(90,0,1,0);
        /// FAN
        glPushMatrix();
            glTranslated(0,0,0.5);
            glRotated(10*a,0,0,1);
            glScaled(0.1,0.1,0.1);
            fan();
       glPopMatrix();
        glScaled(0.1,0.1,0.9);
        glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();

    ///propeller2
    glColor3d(Rw,Gw,Bw); //color
    glPushMatrix();
        glTranslated(0.2,-0.15,-0.9);
        glRotated(90,0,1,0);
        /// FAN
        glPushMatrix();
            glTranslated(0,0,0.5);
            glRotated(10*a,0,0,1);
            glScaled(0.1,0.1,0.1);
            fan();
       glPopMatrix();
        glScaled(0.1,0.1,0.9);
        glutSolidTorus(0.5,0.5,50,50);
    glPopMatrix();


    ///rear wings
    glPushMatrix();
        glTranslated(-2.8,0,0);
        glScaled(0.8,0.5,0.3);

        ///Right
        glColor3d(Rw,Gw,Bw); //color
        glPushMatrix();
            glTranslated(0.4,0,1.5);
            glRotated(-30,0,1,0);
            glScaled(0.7,0.1,3);
            glRotated(10,0,1,0);
            glutSolidCube(1);
        glPopMatrix();

        ///left
        glColor3d(Rw,Gw,Bw);  //color
        glPushMatrix();
            glTranslated(0.4,0,-1.5);
            glRotated(30,0,1,0);
            glScaled(0.7,0.1,3);
            glRotated(-10,0,1,0);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();

    ///vertical
        glColor3d(Rw,Gw,Bw); //color
        glPushMatrix();
            glTranslated(-2.7,0.5,0);
            glRotated(45,0,0,1);
            glScaled(0.8,2,0.1);
            glRotated(-20,0,0,1);
            glutSolidCube(0.5);
    glPopMatrix();

}


void singleHouse(int R,int G,int B){
    glColor3d(r[R%10],g[G%10],b[B%10]); //for basic cubes
    glPushMatrix();
        glTranslated(0,0,0);
        glutSolidCube(1);
    glPopMatrix();

    glColor3d(0,0,0); //window on front right side
    glPushMatrix();
        glTranslated(0.2,0,0);
        glScaled(0.3,0.3,1.001);
        glutSolidCube(1);
    glPopMatrix();

    glColor3d(0,0,0); //window on front left side
    glPushMatrix();
        glTranslated(-0.2,0,0);
        glScaled(0.3,0.3,1.001);
        glutSolidCube(1);
    glPopMatrix();

    glColor3d(0,0,0); //window towards us
    glPushMatrix();
        glTranslated(0,0,0.2);
        glScaled(1.001,0.3,0.3);
        glutSolidCube(1);
    glPopMatrix();

    glColor3d(0,0,0); //window away from us
    glPushMatrix();
        glTranslated(0,0,-0.2);
        glScaled(1.001,0.3,0.3);
        glutSolidCube(1);
    glPopMatrix();

}


void house(int n,int R,int G){ //n is 1-5,
    for(int i=0;i<n;i++){
        glPushMatrix();
            glTranslated(0,0.8+i,0);
            singleHouse(G,R,i);
        glPopMatrix();
    }
}

void environment(int n){

    /// Ground
    glColor3d(0.0,0.3,0.1);
    glPushMatrix();
        glTranslated(0,0,0);
        glScaled(EN_SIZE*2,0.3,EN_SIZE*2);
        glutSolidCube(1);
    glPopMatrix();

    ///rings
    glColor3d(1,0.9,0.00);
    glPushMatrix();
        glTranslated(torusPosX[n],torusPosY[n],0);
        glScaled(0.3,0.3,0.3);
        glutSolidTorus(0.5,3,30,30);
    glPopMatrix();

    ///buildings
    for(int i=-(EN_SIZE/2)+1;i<(EN_SIZE/2);i+=2){
            for(int j=-(EN_SIZE/2)+1;j<(EN_SIZE/2);j+=2){
                if(houseArr[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1]!=0){ //repeat building pattern
                    glPushMatrix();
                        glTranslated(i,0,j);
                        house(houseArr[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1],i,j);
                    glPopMatrix();
                }

                else
                    if(i>=-5&&i<=5){} //to keep runway space

                else{ //construct building for first time
                    houseArr[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1]=(rand()%5)+1;
                    glPushMatrix();
                        glTranslated(i,0,j);
                        house(houseArr[i+(EN_SIZE/2)+1][j+(EN_SIZE/2)+1],i,j);
                    glPopMatrix();

                }
            }
        }
}


void draw(){

    f=0;f1=0;f2=0;f3=0;f4=0;f5=0;f6=0;

    ///Plane
    //rotation tilt
    if(rotX>10)rotX=10;
    if(rotX<-10)rotX=-10;
    if(rotZ>10)rotZ=10;
    if(rotZ<-10)rotZ=-10;

    glPushMatrix();
        //initial position
        glTranslated(0,1,0);
        glRotated(90,0,1,0);
        glRotated(5,0,0,1);

        glRotated(rotX,1,0,0);
        glRotated(rotY,0,1,0);
        glRotated(rotZ,0,0,1);
        glScaled(0.4,0.4,0.4);
        plane();
    glPopMatrix();


    ///Environment
    if(tY>0.1)tY= 0.1; //ground
    if(tY<-15)tY= -15; //sky

    if(tX>=5 && tY>=-4){
        crash=1;
        START = false;
    }if(tX<=-5 && tY>=-4){
        crash=1;
        START = false;
    }

    ///rings/hoops
    //cout<<tX<<" "<<tY<<" "<<tZ<<endl;
    f=0;f1=0;f2=0;f3=0;f4=0;f5=0;f6=0;

    ///-1,-1
    if(tX<=-0.5 && tX>=-1.5 && tY<=-0.5 && tY>=-1.5 && tZ>=-8.3 && tZ<=-7.7){
        f=1;
        cout<<"hello ring0"<<endl;
    }
    if(f==1){score=score+1;}


    ///2.1, -1.8
    if(tX>=1.6 && tX<=2.6 && tY>=-2.3 && tY<=-1.3 && tZ1>=-8.3 && tZ1<=-7.7){
        f1=1;
        //cout<<"hello ring1"<<endl;
    }
    if(f1==1){score=score+1;}


    ///-3, -9
    if(tX>=-3.5 && tX<=-2.5 && tY>=-9.5 && tY<=-8.5 && tZ2>=-8.3 && tZ2<=-7.7){
        f2=1;
        //cout<<"hello ring2"<<endl;
    }
    if(f2==1){score=score+1;}


    ///4,-5
    if(tX<=4.5 && tX>=3.5 && tY<=-4.5 && tY>=-5.5 && tZ3>=-8.3 && tZ3<=-7.7){
        f3=1;
        //cout<<"hello ring3"<<endl;
    }
    if(f3==1){score=score+1;}


    ///1.8, -6
    if(tX>=1.3 && tX<=2.3 && tY>=-6.5 && tY<=-5.5 && tZ4>=-8.3 && tZ4<=-7.7){
        f4=1;
        //cout<<"hello ring4"<<endl;
    }
    if(f4==1){score=score+1;}


    ///0,-3
    if(tX<=0.5 && tX>=-0.5 && tY<=-2.5 && tY>=-3.5 && tZ5>=-8.3 && tZ5<=-7.7){
        f5=1;
        //cout<<"hello ring5"<<endl;
    }
    if(f5==1){score=score+1;}


    ///-1.95, -1.95
    if(tX>=-2.45 && tX<=-1.45 && tY>=-2.45 && tY<=-1.45 && tZ6>=-8.3 && tZ6<=-7.7){
        f6=1;
        //cout<<"hello ring6"<<endl;
    }
    if(f6==1){score=score+1;}

    //cout<<f<<" "<<f1<<" "<<f2<<" "<<f3<<" "<<f4<<" "<<f5<<" "<<f6<<endl;


    glPushMatrix();
        glTranslated(tX,tY,tZ);
        environment(0);
    glPopMatrix();

    glPushMatrix();
      glTranslated(tX,tY,tZ1);
        environment(1);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ2);
        environment(2);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ3);
        environment(3);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ4);
        environment(4);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ5);
        environment(5);
    glPopMatrix();

    glPushMatrix();
        glTranslated(tX,tY,tZ6);
        environment(6);
    glPopMatrix();



    tZ+=speed;
    tZ1+=speed;
    tZ2+=speed;
    tZ3+=speed;
    tZ4+=speed;
    tZ5+=speed;
    tZ6+=speed;

   /*cout<<"TZ0 "<<tZ<<" "<<"TZ1 "<<tZ1<<" "<<"TZ2 "<<tZ2<<" "<<"TZ3 "<<tZ3<<" "
   <<"TZ4 "<<tZ4<<" "<<"TZ5 "<<tZ5<<" "<<"TZ6 "<<tZ6<<" "<<endl;*/

    if(tZ>=20)tZ=-110;
    if(tZ1>=20)tZ1=-110;
    if(tZ2>=20)tZ2=-110;
    if(tZ3>=20)tZ3=-110;
    if(tZ4>=20)tZ4=-110;
    if(tZ5>=20)tZ5=-110;
    if(tZ6>=20)tZ6=-110;


    ///plane gets pivoted back to original position
    if(rotX>0)rotX-=angleBackFrac;
    if(rotX<0)rotX+=angleBackFrac;
    if(rotY>0)rotY-=angleBackFrac;
    if(rotY<0)rotY+=angleBackFrac;
    if(rotZ>0)rotZ-=angleBackFrac;
    if(rotZ<0)rotZ+=angleBackFrac;
    //cout<<rotX<<" "<<rotY<<" "<<rotZ<<endl;


    ///speed variables

    speed = 0.6; //constant speed
    //cout<<speed<<endl;
    //cout<<score<<endl;

}


static void display(void)
{

    //glutGet(GLUT_ELAPSED_TIME) - no of milliseconds elapsed when glut init is called
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0; //seconds
    double a = t*90.0;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    gluLookAt(	0.0, 4.5, 10.0,
                0, 4, 0,
                0, 1.0f, 0.0f); //(eye position, centre position, reference)

    if(START){

        glPushMatrix();
            glTranslated(0,0,0);
            glScaled(zoom,zoom,zoom); //current matrix is multiplied by a scaling matrix
            glRotated(0,0,1,0);
            draw();
        glPopMatrix();

        drawStrokeText("PRESS H - TO KNOW ABOUT THE PLANE CONTROLS",-8,0.9,0);
        drawStrokeText("SCORE : ",3,0,0);
        char str[3];
        int x=score;
        itoa(x,str,10);
        drawStrokeText(str,5,0,0);
    }
    else{

        glPushMatrix();
            glTranslated(0,3,0);
            glRotated(a,0,1,0);
            glScaled(1.5,1.5,1.5);
            plane();
        glPopMatrix();

        drawStrokeText("Press G to Start the Game! Right Click Mouse to explore more options!",-8,-1,0);
        drawStrokeText2("PILOT YOUR PLANE!",-3,0,0);
        drawStrokeText("HIGHSCORE :",5,-1,0);

        drawStrokeText("CURRENT SCORE :",5,-2,0);
        char str1[3];
        int x=score;
        itoa(x,str1,10);
        drawStrokeText(str1,8,-2,0);

        char str2[3];
        if(highscore<x){
            highscore=x;
        }
        itoa(highscore,str2,10);
        drawStrokeText(str2,7,-1,0);

        if(crash==1){
        drawStrokeText("YOUR PLANE CRASHED :(",-2,-2,0);
        }

    }

    glutSwapBuffers();
}


void processSpecialKeys(int key, int x, int y)
{
    float frac = 0.15;
    float rotFrac = 1;
	switch(key) {
		case GLUT_KEY_UP:
            tY-=frac;
            rotZ+=rotFrac;
            break;
        case GLUT_KEY_DOWN:
            tY+=frac;
            rotZ-=rotFrac;
            break;
        case GLUT_KEY_LEFT:
            tX+=frac;
            rotX-=rotFrac*3;
            rotY+=rotFrac/2;
            break;
        case GLUT_KEY_RIGHT:
            tX-=frac;
            rotX+=rotFrac*3;
            rotY-=rotFrac/2;
            break;
	}
}

static void key(unsigned char key, int x, int y)
{
    float frac = 0.15;
    float rotFrac = 1;
    switch (key)
    {
        case 'g'://start
            START=true;
            crash=0;
            score=0;
            tX=0,tY=0;
            break;
        case 'm'://menu
            START=false;
            break;

        case 'z'://zoom in
            zoom+=0.05;
            break;
        case 'Z'://zoom out
            zoom-=0.05;

        case 'w'://up
            tY-=frac;
            rotZ+=rotFrac;
            break;
        case 's'://down
            tY+=frac;
            rotZ-=rotFrac;
            break;
        case 'a'://left
            tX+=frac;
            rotX-=rotFrac*3;
            rotY+=rotFrac/2;
            break;
        case 'd'://right
            tX-=frac;
            rotX+=rotFrac*3;
            rotY-=rotFrac/2;
            break;
        case 'q'://quit
            exit(0);
            break;
        case 'h' ://help
            MessageBox(NULL,
                                "Press G - to start a new game\n"
                                "Press M - to get back to the main page\n\n"

                                "Press W or UP arrow key - to go Up\n"
                                "Press S or DOWN arrow key - to go Down\n"
                                "Press A or LEFT arrow key - to go Left\n"
                                "Press D or RIGHT arrow key - to go Right\n"
                                "Press z to zoom IN and SHIFT+z to zoom OUT\n\n"

                                "Right Click Mouse Button to CUSTOMISE your plane color!\n"

                                "\n\nALL THE BEST!"

                            ,"CONTROLS", MB_OK);
    }

    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

void GoMenu (int value) //right click mouse
{
      switch(value)
      {
            case 1://purple
                  R=0.9; G=0.6; B=1;
                  Rw=0.47;Gw=0.00;Bw=0.70;
                  break;

            case 2://blue
                  Rw=0.0; Gw=0.1; Bw=0.6;
                  R=0.40;G=0.60;B=1;
                  break;

            case 3://orange
                  Rw=1.00; Gw=0.40; Bw=0.10;
                  R=1;G=0.6;B=0.20;
                  break;

            case 4://maroon
                  R=1; G=0.4; B=0.6;
                  Rw=0.50;Gw=0.00;Bw=0.16;
                  break;

            case 5:
                 MessageBox(NULL,
                                "Aye Aye Pilot! Welcome to our game ! \n\n"
                                "The only objective for you is to go as far as possible without crash landing. "
                                "Try to score maximum points by passing through hoops that come along the way. "
                                "Whenever you pass through a hoop, your score will be incremented by 1! \n\n\n"

                                "Here are some instructions for you that will help you maneuver the plane better ! \n"
                                "Press G - to start a new game\n"
                                "Press M - to get back to the main page\n\n"

                                "Press W or UP arrow key - to go Up\n"
                                "Press S or DOWN arrow key - to go Down\n"
                                "Press A or LEFT arrow key - to go Left\n"
                                "Press D or RIGHT arrow key - to go Right\n"
                                "Press z to zoom IN and SHIFT+z to zoom OUT\n\n"

                                "Right Click Mouse Button to CUSTOMISE your plane color!\n"

                                "PRESS 'h' to acquaint yourself with controls in case you forget!"

                                "\n\nALL THE BEST and hope you beat the high score :P"

                            ,"INSTRUCTIONS", MB_OK);
                 break;

             case 6:
                 exit(0);
                 break;

      }
        glutPostRedisplay();

}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(0,0);
	glutInitWindowSize(1366,720);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

    glutCreateWindow("PILOT YOUR PLANE");


    ///menu
    int sub1 = glutCreateMenu(GoMenu);
    glutAddMenuEntry("Purple",1);
    glutAddMenuEntry("Blue",2);
    glutAddMenuEntry("Orange",3);
    glutAddMenuEntry("Maroon",4);

    glutCreateMenu(GoMenu);
    glutAddSubMenu("PLANE COLORS", sub1);
    glutAddMenuEntry("HELP",5);
    glutAddMenuEntry("EXIT",6);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutSpecialFunc(processSpecialKeys);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();

    return EXIT_SUCCESS;
}
