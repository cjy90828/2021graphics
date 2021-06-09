#include <stdio.h>///可割可棄
#include <GL/glut.h>
float angle[20]={}, diff=2;///angle[i]化的角度,內插angleOld[i] angleNew[i]

float angleOld[20]={},angleNew[20]={};
int angleID=0; ///Step05 現在要改第幾個角度!!!
int oldX=0;
FILE*fout=NULL;
FILE*fin =NULL;
void timer( int t ){
    glutTimerFunc(30,timer,t+1);///step-02播放動畫
    if( t%10==0){///step03-2每10frane就讀一筆新資料
        for(int i=0;i<20;i++) angleOld[i] = angleNew[i];
    if(fin==NULL)fin=fopen("angle.txt","r");
    for(int i=0;i<20;i++)fscanf(fin,"%f",&angleNew[i]);///step03-2再讀新資料

    }
    float alpha = (t%10)/10.0;
    for(int i=0;i<20;i++){
            angle[i]= alpha*angleNew[i]+(1-alpha)*angleOld[i];
    }

    glutPostRedisplay();///step-02播放動畫 重劃畫面
}

void mouse(int button,int state,int x,int y)
{
    oldX=x;///當mouse按下去 記下位置
}
void motion(int x,int y)
{
    angle[angleID] += x-oldX; ///用x-oldX
    oldX=x;///在更新位置
    glutPostRedisplay();///現在這個比較好,

   // if(fout==NULL) fout=fopen("angle.txt","w+");
   // for(int i=0;i<20;i++)fprintf(fout,"%.1f",angle[i]);
   // fprintf(fout,"\n");
   // for(int i=0;i<20;i++)printf("%.1f",angle[i]);
   // printf("\n");///以上兩行讓你知道印了什麼


}
void keyboard( unsigned char key, int x, int y){ ///Step05
    if(key=='0') angleID=0; ///Step05
    if(key=='1') angleID=1; ///Step05
    if(key=='2') angleID=2; ///Step05
    if(key=='3') angleID=3; ///Step05

    if(key=='s'){///save 把所有的動作存檔後要關掉

        if(fout==NULL) fout=fopen("angle.txt","w+");
        for(int i=0;i<20;i++)fprintf(fout,"%.1f",angle[i]);
        fprintf(fout,"\n");
        for(int i=0;i<20;i++)printf("%.1f",angle[i]);
        printf("\n");///以上兩行讓你知道印了什麼

    }

    if(key=='r'){///read 再開之後才能讀檔


    if(fin==NULL)fin=fopen("angle.txt","r");
    for(int i=0;i<20;i++)fscanf(fin,"%f",&angle[i]);

    glutPostRedisplay();///step-02播放動畫 重劃畫面

    }

    if(key=='p'){///play 利用timer整個播放

    }
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
    glutCreateWindow("week16 file");

    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);///Step05 整合很多關節,會去改angleID
    glutTimerFunc(0, timer, 0);///Step04-2 設第1個timer做動畫
    glutDisplayFunc(display);
    glutMainLoop();
}
