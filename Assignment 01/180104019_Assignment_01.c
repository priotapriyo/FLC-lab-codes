#include <stdio.h>
#include<stdlib.h>

int main()
{
    FILE *f1,*f2;
    char a,b,input;


    f1=fopen("input.txt","w");

    while(1)
    {
        scanf("%c",&input);
        if(input=='`')
            break;
        fputc(input,f1);
    }


    fclose(f1);


    f1=fopen("input.txt","r");
    f2=fopen("result.txt","w");


    while((a=fgetc(f1))!=EOF)
    {

        if(a=='/')
        {
            char c,d;
            if((c=fgetc(f1))=='/')
            {
                while((c=fgetc(f1))!=EOF)
                {
                    if(c=='\n')
                        break;
                }

            }
            else if(c=='*')
            {
                while((c=fgetc(f1))!=EOF)
                    if(c=='*')
                    {
                        d=fgetc(f1);
                        if(d=='/')
                            break;
                    }




            }
            else
            {
                fputc(a,f2);
                fputc(c,f2);
            }



        }
        else if(a=='\n')
        {
            continue;
        }
        else
        {
            fputc(a,f2);
        }


    }


    fclose(f1);
    fclose(f2);

    f2=fopen("result.txt","r");

    while((input=fgetc(f2))!=EOF)
    {
        printf("%c",input);
    }

    fclose(f2);

     return 0;

}

