#include<stdio.h>
//#include<process.h>
#include<stdlib.h>

void main()
    {
              FILE *fp;
              char ch;
              int count=0,a=0,e=0,i=0,o=0,u=0,A=0,E=0,I=0,O=0,U=0,ws=0,c=0;
             

              fp = fopen("text.txt","r");
              
              if(fp == NULL)
              {
                     printf("\nCan't open file or file doesn't exist."); 
                     exit(0);
              }
              
              

              while((ch = fgetc(fp))!=EOF)
                {
                  if((ch>='A') && (ch<='Z') || (ch>='a') && (ch<='z'))
                  {
                      if(ch=='a')
                       {
                       a++;count++;
       }
      if(ch=='e')
       {
         e++;count++; 
       }
      if(ch=='i')
       {
        i++;count++;
       }
      if(ch=='o')
       {
	o++;count++;
       }
      if(ch=='u')
       {
       u++;count++;
       }
      if(ch=='A') 
       {
       A++;count++;
       }
      if(ch=='E') 
       {
       E++;count++;
       }
      if(ch=='I') 
       {
       I++;count++;
       }
      if(ch=='O') 
       {
       O++;count++;
       } 
      if(ch=='U') 
       {
       U++;count++;
       } 
      
        }
        if(ch==32)
       {
         ws++;
       }  
        printf("%c",ch);
        c++;
                   }                   
              printf("\n\nTotal vowels : %d",count);
              printf("\n\nTotal no of words = %d",ws+1);
              printf("\n\nTotal no of characters = %d",c-ws);
    printf("\n\nOccurance of a = %d",a);
    printf("\nOccurance of e = %d",e);
    printf("\nOccurance of i = %d",i);
    printf("\nOccurance of o = %d",o);
    printf("\nOccurance of u = %d",u);
    printf("\nOccurance of A = %d",A);
    printf("\nOccurance of E = %d",E);
    printf("\nOccurance of I = %d",I);
    printf("\nOccurance of O = %d",O);
    printf("\nOccurance of U = %d",U);
              
              fclose(fp);               

     }
