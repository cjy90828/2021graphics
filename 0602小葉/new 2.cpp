#include <stdio.h>
int main(int argc,char**argv)
{
    FILE*fout=NULL;
    fout=fopen("檔名.txt","w+");
    printf("Hello World\n");
    fprintf(fout,"Hello World\n");
}
