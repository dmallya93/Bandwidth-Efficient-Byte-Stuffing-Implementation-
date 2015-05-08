#include "frame.c"
#include<stdio.h>
#include<math.h>
void readFromFile()
{
 char c;
 int i,count=0;
 FILE* fp;
 int a[3];
 fp = fopen("message","r");
 while(fscanf(fp,"%c",&c)!=EOF)
  {
    count++;
    a[count-1]=(int)c;
   if(count%3==0)
    {
     count=0;
     convert(a,3); 
    } 
  }
 if(count%3!=0)
  convert(a,count); 
 fclose(fp);
}
