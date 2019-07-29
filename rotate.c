#include<stdio.h>
//#include<process.h>
#include<stdlib.h> 
   void main()
        {
              FILE *fp;
              char ch;

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
                      if(ch=='Z')
                       {
                        ch='A';
                         }
                      else if(ch=='z')
                       {
       ch='a';
         }
     else
      {
       ch++;
         }
        }
     printf("%c",ch);
      }
 }        

