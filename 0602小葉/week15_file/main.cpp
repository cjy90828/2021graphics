#include <stdio.h>///可割可棄
#include <GL/glut.h>
float angle[20]={}, diff=2;///Step05 本來只有1個角度,現在有很多個,初始為0
int angleID=0; ///Step05 現在要改第幾個角度!!!
void timer( int t ){
    glutTimerFunc( 30, timer, t+1 );
    angle[angleID] += diff; ///Step05
    if(angle[angleID]>90) diff=-2; ///Step05
    if(angle[angleID]<0) diff=+2; ///Step05
    glutPostRedisplay();///現在這個比較好, 以前會用 display()重畫
}
void keyboard( unsigned char key, int x, int y){ ///Step05
    if(key=='0') angleID=0; ///Step05
    if(key=='1') angleID=1; ///Step05
    if(key=='2') angleID=2; ///Step05
    if(key=='3') angleID=3; ///Step05
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glutSolidTeapot( 0.3 );///身體
        glPushMatrix();///左半邊
            glTranslatef(-0.3,0,0);///(3)掛在正確的地方
            glRotatef(angle[0], 0,0,1);///(2)旋轉 ///Step05
            glTranslatef(-0.3,0,0);///(1)把關節旋轉中心放到畫面中心
            glutSolidTeapot( 0.3 );///左手臂(沒有重疊)
            glPushMatrix();
                glTranslatef(-0.3,0,0);///(3)掛在正確的地方
                glRotatef(angle[1], 0,0,1);///(2)旋轉 ///Step05
                glTranslatef(-0.3,0,0);///(1)把關節旋轉中心放到畫面中心
                glutSolidTeapot( 0.3 );///左手肘(重疊了)
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();///右半邊
            glTranslatef(+0.3, 0,0 );
            glRotatef(-angle[2], 0,0,1);
            glTranslatef(+0.3, 0,0);
            glutSolidTeapot( 0.3 );///右手臂
            glPushMatrix();
                glTranslatef(+0.3, 0,0 );
                glRotatef(-angle[3], 0,0,1);
                glTranslatef(+0.3, 0,0);
                glutSolidTeapot( 0.3 );///右手肘
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}
int main( int argc, char ** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week15 file");

    glutKeyboardFunc(keyboard);///Step05 整合很多關節,會去改angleID
    glutTimerFunc(0, timer, 0);///Step04-2 設第1個timer做動畫
    glutDisplayFunc(display);
    glutMainLoop();
}
