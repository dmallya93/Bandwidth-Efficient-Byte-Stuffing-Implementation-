#include<strings.h>
#include<string.h>
#include<stdio.h>
#include "deframe.c"
char store[10];
int position(char* str,char c,int fromPos)
{
 int i,j,count=0;
 for(i=0;i<strlen(str);i++)
 {
  if(str[i]==c && i >= fromPos)
   {
    return i;
   }
 }
return -2000; 
}
void extract(char* str,int pos1,int pos2)
{
  bzero(store,10);
  int i,j=0;
 for(i=pos1;i<=pos2;i++)
 {
   store[j]=str[i];
   j++; 
 }
 strcat(store,"\0");
 }
void separate(char* k)
{
 char* l;
 int p,start=0,m=0;
 while(1)
  {
    p=position(k,'|',start);
    if(p==-2000)
    break;
    extract(k,start,p-1);
    start=p+1;      
    cbase[m]=atoi(store);
    m++;
  }
 deframe(cbase,m);
}
