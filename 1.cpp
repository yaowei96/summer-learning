#define GLUT_DISABLE_ATEXIT_HACK

#include <gl/glut.h>
#include"math.h"
float angle=0;
float angle2=0;
//��ʼ��OpenGL

void init(void) 
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//���ñ�����ɫ
	glShadeModel(GL_SMOOTH);//������������,������ѡ��ģʽ��GL_FLAT�������䣩��GL_SMOOTH��������ɣ�
}

void Drawpic()
{
		/** ̫�� */

	
	glPushMatrix();	
	
	  glColor3f(1.0f, 0.0f, 0.0f);	/**< ��ɫ */
	  glutWireSphere(1.0,20,20);
		
	glPopMatrix();

  	

 /** ���Ƶ��� */
	glPushMatrix();
  		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(3.0,0.0,0.0);	
	    glColor3f(0.0f, 0.0f, 1.0f);
		glutWireSphere(0.5,20,20);
		
    glPushMatrix();
	
 /** �������� */
		glRotatef(angle2, 0.0f, 0.0f, 1.0f);
	
		glTranslatef(1.0,0.0,0.0);
		
		glColor3f(1.0f, 1.0f, 0.0f);
		glutWireSphere(0.2,20,20);
		

	glPopMatrix();

	glPopMatrix();
 
	glFlush();		

}
//��Ҫ�Ļ��ƹ���
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//�����ɫ����  
	glEnable(GL_DEPTH_TEST);

     glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	
	glTranslatef(0,0,-15);
	glColor3f(1.0,0,0);

	Drawpic();
    glFlush();
}
//�ڴ��ڸı��Сʱ����
void reshape(int w, int h){
       glViewport(0, 0, w, h);//�����ӿ�
       glMatrixMode(GL_PROJECTION);//���õ�ǰΪͶӰ�任ģʽ
       glLoadIdentity();//�õ�λ�����滻��ǰ�任����
       gluPerspective(45, (float)w/h, 4, 100.0);//��������ͶӰ��ͼ��
        glMatrixMode (GL_MODELVIEW);
       glLoadIdentity();
}
void TimerFunction(int value)
{
    angle+=10;
	if(angle==360)
		angle=0;
	
	angle2+=30;
	if(angle2==360)
		angle2=0;
	
	// Redraw the scene with new coordinates
    glutPostRedisplay();
	glutTimerFunc(500,TimerFunction, 1);
}

void main( )
{
	
	
	glutCreateWindow("Basic");//���ô��ڱ���
	init();//��ʼ��OpenGL
	glutDisplayFunc(display);//������ʾ�ص����� 
	glutReshapeFunc(reshape);//����reshape�ص�����
	glutTimerFunc(500,TimerFunction, 1);

	glutMainLoop();//������ѭ��

}

