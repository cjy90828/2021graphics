#include <stdio.h>///�i�Υi��
#include <GL/glut.h>
float angle[20]={}, diff=2;///angle[i]�ƪ�����,����angleOld[i] angleNew[i]

float angleOld[20]={},angleNew[20]={};
int angleID=0; ///Step05 �{�b�n��ĴX�Ө���!!!
int oldX=0;
FILE*fout=NULL;
FILE*fin =NULL;
void timer( int t ){
    glutTimerFunc(30,timer,t+1);///step-02����ʵe
    if( t%10==0){///step03-2�C10frane�NŪ�@���s���
        for(int i=0;i<20;i++) angleOld[i] = angleNew[i];
    if(fin==NULL)fin=fopen("angle.txt","r");
    for(int i=0;i<20;i++)fscanf(fin,"%f",&angleNew[i]);///step03-2�AŪ�s���

    }
    float alpha = (t%10)/10.0;
    for(int i=0;i<20;i++){
            angle[i]= alpha*angleNew[i]+(1-alpha)*angleOld[i];
    }

    glutPostRedisplay();///step-02����ʵe �����e��
}

void mouse(int button,int state,int x,int y)
{
    oldX=x;///��mouse���U�h �O�U��m
}
void motion(int x,int y)
{
    angle[angleID] += x-oldX; ///��x-oldX
    oldX=x;///�b��s��m
    glutPostRedisplay();///�{�b�o�Ӥ���n,

   // if(fout==NULL) fout=fopen("angle.txt","w+");
   // for(int i=0;i<20;i++)fprintf(fout,"%.1f",angle[i]);
   // fprintf(fout,"\n");
   // for(int i=0;i<20;i++)printf("%.1f",angle[i]);
   // printf("\n");///�H�W������A���D�L�F����


}
void keyboard( unsigned char key, int x, int y){ ///Step05
    if(key=='0') angleID=0; ///Step05
    if(key=='1') angleID=1; ///Step05
    if(key=='2') angleID=2; ///Step05
    if(key=='3') angleID=3; ///Step05

    if(key=='s'){///save ��Ҧ����ʧ@�s�ɫ�n����

        if(fout==NULL) fout=fopen("angle.txt","w+");
        for(int i=0;i<20;i++)fprintf(fout,"%.1f",angle[i]);
        fprintf(fout,"\n");
        for(int i=0;i<20;i++)printf("%.1f",angle[i]);
        printf("\n");///�H�W������A���D�L�F����

    }

    if(key=='r'){///read �A�}����~��Ū��


    if(fin==NULL)fin=fopen("angle.txt","r");
    for(int i=0;i<20;i++)fscanf(fin,"%f",&angle[i]);

    glutPostRedisplay();///step-02����ʵe �����e��

    }

    if(key=='p'){///play �Q��timer��Ӽ���

    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
        glutSolidTeapot( 0.3 );///����
        glPushMatrix();///���b��
            glTranslatef(-0.3,0,0);///(3)���b���T���a��
            glRotatef(angle[0], 0,0,1);///(2)���� ///Step05
            glTranslatef(-0.3,0,0);///(1)�����`���त�ߩ��e������
            glutSolidTeapot( 0.3 );///�����u(�S�����|)
            glPushMatrix();
                glTranslatef(-0.3,0,0);///(3)���b���T���a��
                glRotatef(angle[1], 0,0,1);///(2)���� ///Step05
                glTranslatef(-0.3,0,0);///(1)�����`���त�ߩ��e������
                glutSolidTeapot( 0.3 );///����y(���|�F)
            glPopMatrix();
        glPopMatrix();
        glPushMatrix();///�k�b��
            glTranslatef(+0.3, 0,0 );
            glRotatef(-angle[2], 0,0,1);
            glTranslatef(+0.3, 0,0);
            glutSolidTeapot( 0.3 );///�k���u
            glPushMatrix();
                glTranslatef(+0.3, 0,0 );
                glRotatef(-angle[3], 0,0,1);
                glTranslatef(+0.3, 0,0);
                glutSolidTeapot( 0.3 );///�k��y
            glPopMatrix();
        glPopMatrix();
    glPopMatrix();
    glutSwapBuffers();
}
int main( int argc, char ** argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("week16 file");

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);///Step05 ��X�ܦh���`,�|�h��angleID
    glutTimerFunc(0, timer, 0);///Step04-2 �]��1��timer���ʵe
    glutDisplayFunc(display);
    glutMainLoop();
}
