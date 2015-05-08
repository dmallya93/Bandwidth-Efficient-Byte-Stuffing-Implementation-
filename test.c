#include<stdio.h>
#include<math.h>
int cbase[6];
int noOfChar;
long aftConv=0;
void initialize()
{
 int i;  
 for(i=0;i<6;i++)
  cbase[i]=0;
 noOfChar=0;
 aftConv=0;
}
void convert(int a[],int n)
{
 initialize();
 int i,k=0,j=0,cnt=0;
 long num=0,temp[6];
 for(i=0;i<n;i++)
 {
  num=num+a[n-i-1]*pow(98,i); 
 }
 printf("\nnum is %ld\n",num);

 
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
 printf("\nNumber of char is %d\n",noOfChar);
 k=0;
 for(i=0;i<noOfChar;i++)
 {
   aftConv=aftConv+cbase[i]*pow(97,(noOfChar-i-1));
 }
   
}
void main()
{
 char c;
 int i,count=0;
 FILE* fp;
 int a[]={97};
 convert(a,1);
 


 printf("\nThe number to base 97 after conversion is as follows:\n");
 for(i=0;i<noOfChar;i++)
  {
    printf("%d",cbase[i]);
  }
 printf("\nIts character equivalent is : \n");
  for(i=0;i<noOfChar;i++)
  {
    printf("%c ",cbase[i]);
  }
 printf("Matches : %ld",aftConv); 
}
