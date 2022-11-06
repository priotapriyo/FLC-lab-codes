#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include <stdbool.h>

bool isKey(char* c)
{
    if(strlen(c)==3 && c[0]=='i' && c[1]=='n' && c[2]=='t')
        return true;

    if(strlen(c)==5 && c[0]=='f' && c[1]=='l' && c[2]=='o' && c[3]=='a' && c[4]=='t' )
        return true;

    if(strlen(c)==6 && c[0]=='d' && c[1]=='o' && c[2]=='u' && c[3]=='b' && c[4]=='l' && c[4]=='e' )
        return true;

    if(strlen(c)==2 && c[0]=='i' && c[1]=='f')
        return true;

    if(strlen(c)==4 && c[0]=='e' && c[1]=='l' && c[2]=='s' && c[3]=='e')
        return true;

    if(strlen(c)==5 && c[0]=='w' && c[1]=='h' && c[2]=='i' && c[3]=='l' && c[4]=='e' )
        return true;

    if(strlen(c)==3 && c[0]=='f' && c[1]=='o' && c[2]=='r')
        return true;

    if(strlen(c)==4 && c[0]=='c' && c[1]=='h' && c[2]=='a' && c[3]=='r')
        return true;

    if(strlen(c)==6 && c[0]=='r' && c[1]=='e' && c[2]=='t' && c[3]=='u' && c[4]=='r' && c[5]=='n' )
        return true;
    return false;
}


bool isDigit(char c)
{
    if(c>='0' && c<='9')
        return true;
    return false;
}

bool isSeparator(char* c)
{
    if(c[0]==';' || c[0]==',' || c[0]=='\'')
        return true;
    return false;
}

bool isOperator(char *c)
{
    if (c[0] == '+' || c[0] == '-' || c[0] == '*' || c[0] == '/' || c[0] == '%' || c[0] == '=' || c[0] == '<' || c[0] == '>' || c[0] == '!')
        return (true);
    return (false);
}

bool isParenthesis(char* c)
{
    if(c[0]==')' || c[0]=='(' || c[0]=='}' || c[0]=='{' )
        return true;
    return false;
}

int isId(char* c)
{
    int i=0;
    int x = 0;
    for(i=0; i<strlen(c); i++)
    {
        if((c[i]>='a' && c[i]<='z') || (c[i]>='A' && c[i]<='Z') || c[i]=='_')
        {
            x = 1;
            continue;
        }
        else if(isDigit(c[i])==true)
        {
            if(x==0)
                return 0;
        }
        else return 0;
    }
    return 1;
}


int isNumerical(char *lex)
{
    int i = 0,s,l;

    if(isDigit(lex[i]))
    {
        s=1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }
    else s=0;

    l=strlen(lex);

    if(s==1)
    {
        for (i=0; i<l; i++)
        {
            if(isDigit(lex[i]))
            {
                s = 1;
            }
            else if(lex[i]=='.')
            {
                s = 2;
                i++;
                break;
            }
            else
            {
                s = 0;
                break;
            }
        }

    }

    if(s == 2)
        {
            if(isDigit(lex[i]))
            {
                s = 3;
                i++;
            }
            else
            {
                s = 0;
            }
        }

        if(s == 3)
        {
            for(i=0; i<l; i++)
            {
                if(isDigit(lex[i]))
                {
                    s = 3;
                }
                else
                {
                    s = 0;
                    break;
                }
            }
        }

        if(s == 3)
        {
            s=1;
        }
    return s;
}


int main()
{
    FILE *f1,*f2,*f3,*f4,*f5,*f6,*f7;
    char a,b,input,file[10000],arr[10000],string[100000];
    int y = 0;


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

   /* f2=fopen("result.txt","r");

    while((input=fgetc(f2))!=EOF)
    {
        printf("%c",input);
    }

    fclose(f2);*/

     //return 0;


    f5=fopen("result.txt","r");
    f6=fopen("separated_lexeme.txt","w");

    while((a=fgetc(f5))!=EOF)
    {
        if(a == '+' || a == '*' || a == '-' || a == '/' || a == ',' || a == ';' || a == '>' || a == '<' || a == '=' || a == '(' || a == ')' || a == '[' || a == ']' || a == '{' || a == '}')
        {
            fputc(' ',f6);
            fputc(a,f6);
            fputc(' ',f6);
        }
        else
        {
            fputc(a,f6);
        }

    }

    fclose(f5);
    fclose(f6);

    f3=fopen("separated_lexeme.txt","r");

    int store=0, k=0;

    while((a=fgetc(f3))!=EOF)
    {
        file[store++]=a;

    }
    fclose(f3);

    for(int i=0; file[i]!='\0'; i++)
    {
        if(file[i]==' ' && file[i+1]==' ')
        {
            continue;
        }
        else
        {
            arr[k++]=file[i];
        }
    }

    f4=fopen("extra_space_removed.txt","w");

    for(int i=0; file[i]!='\n'; i++)
    {
        fprintf(f4,"%c",arr[i]);
    }
    fclose(f4);

    f6=fopen("extra_space_removed.txt","r");
    f7 = fopen("ass2_result.txt","w");

    while((a=fgetc(f6))!=EOF)
    {
        if(a!=' ')
        {
            string[y++]=a;
        }
        else
        {
            string[y]='\0';
            y=0;

            if(isKey(string)==true)
            {
                fprintf(f7,"[kw %s]",string);
            }
            else if(isSeparator(string)==true)
            {
                fprintf(f7,"[sp %s]",string);
            }
            else if(isOperator(string)==true)
            {
                fprintf(f7,"[op %s]",string);
            }
            else if(isParenthesis(string)==true)
            {
                fprintf(f7,"[par %s]",string);
            }
            else if(isNumerical(string)==1)
            {
                fprintf(f7,"[Num %s]",string);
            }
            else if(isId(string)==1)
            {
                fprintf(f7,"[Id %s]",string);
            }
            else
            {
                fprintf(f7,"[unkn %s]",string);
            }
        }
    }

    fclose(f6);
    fclose(f7);

    f7=fopen("ass2_result.txt","r");

    while((input=fgetc(f7))!=EOF)
    {
        printf("%c",input);
    }

    fclose(f7);

    return 0;


}


