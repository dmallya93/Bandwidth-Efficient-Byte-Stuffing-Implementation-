#include<stdio.h>
#include<string.h>
char packet[200];
void convertIntArrayToString(int a[],int size)
{
 int i;
 char tu[4];
 for(i=0;i<size;i++)
 {
  sprintf(tu,"%d",a[i]);
  strcat(packet,tu);
  strcat(packet,"|"); 
 }
  printf("%s\n",packet); 
}
