#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<strings.h>
#include<unistd.h>
#include<time.h>
char text[30000];
char buffer[100];
void unstuff(char* frame)
{
 int i,j=0;
 char repository[30];   
 //printf("\nduring unstuffing : %s\n",frame); 
 //FILE* fp;
 //fp=fopen("Unstuffed","a");
 for(i=1;i<strlen(frame)-1;)
  {
   if(frame[i]=='#')
   {
    repository[j]=frame[i+1];
     j++;
    i+=2;
   }
  else
   {
    repository[j]=frame[i];
    j++;
    i+=1;
   }
  }
 repository[i]='\0';
 strcat(text,repository); 
 //fclose(fp);
}
void produceFrames()
{
 FILE* fp;
 int noOfCharacters,i,k;
 char esc='#',c,flag='@';
 printf("\nContents of file are\n");
 system("cat Unframed");
 fp=fopen("Unframed","r");
 if(fp==NULL)
 {
  printf("\nError in reading file\n");
  fclose(fp);
  exit(1);
 }
 else
 {
   i=1; 
   noOfCharacters=0;
   buffer[0]=flag;
   k=0; 
   while(fscanf(fp,"%c",&c)!=EOF)
   {
    
     
     if(c=='@' || c==esc)
      {
       
       buffer[i]=esc;
       i++;
      }
     buffer[i]=c;
     i++;
     noOfCharacters++;
     if(noOfCharacters==20)
     {
      
      buffer[i]='@';
      i++;
      buffer[i]='\0';
      k++;
      printf("\nFrame %d : %s",k,buffer);
      unstuff(buffer); 
      bzero(buffer,100);
      
      buffer[0]=flag;
      noOfCharacters=0;
      i=1;           
     }
      
   }
   buffer[i]='@';
   i++; 
   buffer[i]='\0';
   unstuff(buffer); 
   printf("\nFrame %d : %s",(k+1),buffer);
 }
}
int main(int argc,char** argv)
{
 produceFrames();
 printf("\nAfter unstuffing\n");
 printf("\n%s\n",text);
 return 0;
}
