#define GLUT_DISABLE_ATEXIT_HACK

#include <gl/glut.h>
#include"math.h"
float angle=0;
float angle2=0;
//初始化OpenGL

void init(void) 
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);//设置背景颜色
	glShadeModel(GL_SMOOTH);//设置明暗处理,有两种选择模式：GL_FLAT（不渐变）和GL_SMOOTH（渐变过渡）
}

void Drawpic()
{
		/** 太阳 */

	
	glPushMatrix();	
	
	  glColor3f(1.0f, 0.0f, 0.0f);	/**< 红色 */
	  glutWireSphere(1.0,20,20);
		
	glPopMatrix();

  	

 /** 绘制地球 */
	glPushMatrix();
  		glRotatef(angle, 0.0f, 0.0f, 1.0f);
		glTranslatef(3.0,0.0,0.0);	
	    glColor3f(0.0f, 0.0f, 1.0f);
		glutWireSphere(0.5,20,20);
		
    glPushMatrix();
	
 /** 绘制月亮 */
		glRotatef(angle2, 0.0f, 0.0f, 1.0f);
	
		glTranslatef(1.0,0.0,0.0);
		
		glColor3f(1.0f, 1.0f, 0.0f);
		glutWireSphere(0.2,20,20);
		

	glPopMatrix();

	glPopMatrix();
 
	glFlush();		

}
//主要的绘制过程
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//清除颜色缓存  
	glEnable(GL_DEPTH_TEST);

     glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	
	glTranslatef(0,0,-15);
	glColor3f(1.0,0,0);

	Drawpic();
    glFlush();
}
//在窗口改变大小时调用
void reshape(int w, int h){
       glViewport(0, 0, w, h);//设置视口
       glMatrixMode(GL_PROJECTION);//设置当前为投影变换模式
       glLoadIdentity();//用单位矩阵替换当前变换矩阵
       gluPerspective(45, (float)w/h, 4, 100.0);//设置正交投影视图体
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
	
	
	glutCreateWindow("Basic");//设置窗口标题
	init();//初始化OpenGL
	glutDisplayFunc(display);//设置显示回调函数 
	glutReshapeFunc(reshape);//设置reshape回调函数
	glutTimerFunc(500,TimerFunction, 1);

	glutMainLoop();//进入主循环

}

