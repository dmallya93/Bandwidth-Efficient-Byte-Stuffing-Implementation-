#include "deframe.c"
#include<stdio.h>
#include<math.h>
#include "arrayConv.c"
void convert(int a[],int n)
{
 initialize();
 int i,k=0,j=0;
 char c;
 long num=0,temp[6];
 
 for(i=0;i<n;i++)
 {
  num=num+a[n-i-1]*pow(98,i); 
 }
 while(num)
 {
  temp[k]=num%97;  
  num/=97;
  k++;   
 }
 noOfChar=k;
 for(i=k-1;i>=0;i--)
  {
   cbase[j]=temp[i];
    j++;
  }
 convertIntArrayToString(cbase,noOfChar);
}

