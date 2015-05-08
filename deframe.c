#include "common.c"
#include<stdio.h>
#include<math.h>
void deframe(int a[],int n)
{
 int i,k=0,j=0;
 char c;
 long num=0,temp[6]; 
 for(i=0;i<n;i++)
 {
  num=num+a[n-i-1]*pow(97,i);
  }
 while(num)
 {
  temp[k]=num%98;  
  num/=98;
  k++;   
 }
 noOfChar=k;
 for(i=k-1;i>=0;i--)
  {
   cbase[j]=temp[i];
    j++;
  }
 for(i=0;i<noOfChar;i++)
  {
    printf("%c",cbase[i]);
  }
}

