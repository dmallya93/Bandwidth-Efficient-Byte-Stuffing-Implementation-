#include<GL/glut.h>
#include<stdio.h>
#include<stdlib.h>
#define pi 3.14159263
#include<string.h>
#include<time.h>
float f[]={0.245,0.3,0.03,0.01,0.02,0.01,0.01};
int inputs=7;
void Init()
{
 glClear(GL_COLOR_BUFFER_BIT);
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 glOrtho(-35,38,-35,38,-1,1);
}
void drawhistogram(int x,float y)
{
 
 int i;
 char text[3]=" ";
 sprintf(text,"%d",x);  
 if(x<=10)
   x=-((10-x)*3);
 else
  x=(x-10)*3;
  if(y<=0.3)
   y=-100*(0.3-y);
  else if(y>=0.3)
   y=100*(y-0.3);
  
 glColor3f(0.0,0.0,1.0);
 glBegin(GL_POLYGON);
 glVertex2f(x,-30); 
 glVertex2f(x+2,-30);
 glVertex2f(x+2,y);
 glVertex2f(x,y);
 glEnd();

 glColor3f(1,1,1);
 glRasterPos2i(x,-32);
for(i = 0; i < strlen(text);i++)
{ 
 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
}
    
}
void display()
{
 int i;
 //int i;
 glClear(GL_COLOR_BUFFER_BIT);
 glColor3f(1.0,1.0,1.0);
 glBegin(GL_LINES);
 glVertex2f(-30,-30);
 glVertex2f(34,-30);
 glVertex2f(-30,-30);
 glVertex2f(-30,30);
 glEnd();

 glBegin(GL_TRIANGLES);
 glVertex2f(-30.5,30);
 glVertex2f(-29.5,30);
 glVertex2f(-30,31);
 glEnd();

 glBegin(GL_TRIANGLES);
 glVertex2f(33,-29.5);
 glVertex2f(33,-30.5);
 glVertex2f(34,-30);
 glEnd();

 for(i=0;i<inputs;i++)
 {
  srand(time(NULL));
   drawhistogram(i,f[i]);
   
 } 

glColor3f(1,1,1);
char text2[]="byte overhead";
glRasterPos2i(-10,-34);
for(i = 0; i < strlen(text2);i++)
{ 
 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text2[i]);
}

glColor3f(1,1,1);
char text1[]="% packets";
glRasterPos2i(-32,32);
for(i = 0; i < strlen(text1);i++)
{ 
 glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text1[i]);
}


 glFlush();
}
int main(int argc,char** argv)
{
 glutInit(&argc,argv);
 glutInitWindowSize(600,600); 
 glutCreateWindow("Hybrid BABS Overhead. Maximum 6 bytes,total 106757 bytes");  
 Init();
 glutDisplayFunc(display);
 glutMainLoop();
 return 0;
}
