#include<stdio.h>
//#include<conio.h>
#include<string.h>

void main()
 {
  char a[100];
  int i=0;
  
 // clrscr();
  
  printf("Enter String : ");
  gets(a);
  
  printf("\n Length=%d\n",strlen(a));
  
  printf("\n String after removing \"the\" is : ");
  
  for(i=0;i<strlen(a);i++)
   {
    if(a[i]=='t'|| a[i]=='T')
    {
      if(a[i+1]=='h'|| a[i+1]=='H')
      {
      if(a[i+2]=='e'|| a[i+2]=='E')
     {
      i=i+4;
     }
      }
    }
    printf("%c",a[i]);
   }
   a[i]=NULL;
   
  // getch();
 }
