#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>


void eleminateId(FILE *source, FILE *target, char sourceFile[30], char targetFile[30]);
void tableGenerate(FILE *source, FILE *target, char sourceFile[30], char targetFile[30]);
void numberedTable(FILE *source, FILE *target, char sourceFile[30], char targetFile[30]);

int sl = 0;
char table[50][50][50];

bool isKeyword(char* c)
{
    if(strlen(c)==2 && c[0]=='i' && c[1]=='f')
    {
       return true;
    }

    if(strlen(c)==4 && c[0]=='e' && c[1]=='l' && c[2]=='s' && c[3]=='e')
    {
       return true;
    }

    if(strlen(c)==5 && c[0]=='w' && c[1]=='h' && c[2]=='i' && c[3]=='l' && c[4]=='e' )
    {
       return true;
    }

    if(strlen(c)==3 && c[0]=='f' && c[1]=='o' && c[2]=='r')
    {
        return true;
    }

    if(strlen(c)==3 && c[0]=='i' && c[1]=='n' && c[2]=='t')
    {
        return true;
    }

    if(strlen(c)==5 && c[0]=='f' && c[1]=='l' && c[2]=='o' && c[3]=='a' && c[4]=='t' )
    {
        return true;
    }

    if(strlen(c)==6 && c[0]=='d' && c[1]=='o' && c[2]=='u' && c[3]=='b' && c[4]=='l' && c[5]=='e' )
    {
        return true;
    }

    if(strlen(c)==4 && c[0]=='c' && c[1]=='h' && c[2]=='a' && c[3]=='r')
    {
        return true;
    }

    if(strlen(c)==6 && c[0]=='r' && c[1]=='e' && c[2]=='t' && c[3]=='u' && c[4]=='r' && c[5]=='n' )
    {
        return true;
    }

    return false;
}


bool isDigit(char c)
{
    if(c>='0' && c<='9')
    {
         return true;
    }
    return false;
}


bool isOperator(char* c)
{
    if (c[0] == '+' || c[0] == '-' || c[0] == '*' || c[0] == '/' || c[0] == '%' || c[0] == '>' || c[0] == '<' || c[0] == '=' || c[0] == '!')
    {
         return (true);
    }
    return (false);
}

bool isSeparator(char* c)
{
    if(c[0]==';' || c[0]==',' || c[0]=='\'')
       {
         return true;
       }
    return false;
}


bool isParenthesis(char* c)
{
    if(c[0]==')' || c[0]=='(' || c[0]=='}' || c[0]=='{' )
     {
         return true;
     }
    return false;
}

int isNumerical(char *lex){
    int i = 0, l, s;

    if(isdigit(lex[i]))
    {
        s=1;
        i++;
    }
    else if(lex[i]=='.')
    {
        s=2;
        i++;
    }
    else
    {
        s=0;
    }

    l=strlen(lex);

    if(s==1)
    {
       for(;i<l;i++)
       {
         if(isdigit(lex[i]))
         {
             s=1;
         }

         else if(lex[i]=='.')
         {
            s=2;
            i++;
            break;
         }
        else
        {
            s=0;
            break;
        }
      }
    }

    if(s==2)
    {
      if(isdigit(lex[i]))
       {
         s=3;
         i++;
       }
      else
      {
        s=0;
      }

    }

    if(s==3)
    {
      for(;i<l;i++)
      {
        if(isdigit(lex[i]))
        {
           s=3;
        }

        else
        {
           s=0;
           break;
        }

      }
    }

    if(s==3)
    {
        s=1;
    }

    return s;
}




int isNum_rec(char *lex)
{
    int i=0, l, s;

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
    else
        s=0;

    l=strlen(lex);

    if(s==1)
        for(; i<l; i++)
        {
            if(isDigit(lex[i]))
            {
              s=1;
            }

            else if(lex[i]=='.')
            {
                s=2;
                i++;

                break;
            }
            else
            {
                s=0;
                break;
            }
        }

    if(s==2)
        if(isDigit(lex[i]))
        {
            s=3;
            i++;
        }
        else
        {
             s=0;
        }

    if(s==3)
        for(; i<l; i++)
        {
            if(isDigit(lex[i]))
            {
                s=3;
            }
            else
            {
                s=0;
                break;
            }
        }
    if(s==3)
    {
        s=1;
    }

    return s;
}

int isId(char* c)
{
    int i=0, x=0;

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

void InsertSlNoInTable(int i, int j, int sl){
    int x = sl;
    int count = 0;

    while(sl != 0){
        sl = sl / 10;
        count++;
    }

    int k;
    for(k = count-1; k >= 0; k--){
        table[i][j][k] = (x % 10) + 48;
        x = x / 10;
    }
    table[i][j][count]  = '\0';
}

void InsertStringInTable(int i, int j, char* str2){
    int k;

    for(k = 0;k<strlen(str2);k++)
    {
        table[i][j][k] = str2[k];
    }

    table[i][j][k]  = '\0';
}

void Insert(int sl, char* name, char* idtype, char* dataType, char* scope){
    InsertSlNoInTable(sl,0,sl+1);
    InsertStringInTable(sl,1,name);
    InsertStringInTable(sl,2,idtype);
    InsertStringInTable(sl,3,dataType);
    InsertStringInTable(sl,4,scope);
}

void Delete(char* str){
    int i;

    for(i = 0;i<50;i++)
    {
        str[i] = '\0';
    }
}

void UpdateScope(char* str1, char* str2, char* scope)
{
    int i;
    int a = Search(str1,scope);
    int b = Search(str2,scope);

    if(a==-1)
        a = Search(str1,"global");

    if(b==-1)
        b = Search(str2,"global");


    if(a!=-1)
    {
        for(i = 0; table[b][5][i] != '\0'; i++)
        {
            table[a][5][i] = table[b][5][i];
        }
        table[a][5][i]  = '\0';
    }

}

void UpdateId(char str1[], char str2[], char scope[]){
    int a = Search(str1,scope),k;

    if(a!=-1)
    {
        for(k = 0;k<strlen(str2);k++)
        {
            table[a][2][k] = str2[k];
        }
        table[a][2][k]  = '\0';
    }
}

int Search(char* str, char* scope){
   int i,k;
   char str2[50], str3[50];

   for(i = 0; i < sl; i++)
   {
       Delete(str2);
       Delete(str3);

       for(k = 0; table[i][1][k] != '\0'; k++)
       {
           str2[k] =  table[i][1][k];
       }

       for(k = 0;table[i][4][k]!='\0';k++)
       {
           str3[k] =  table[i][4][k];
       }

       if(strcmp(str,str2) == 0 && strcmp(scope,str3) == 0)
           return i;
   }
   return -1;
}

void DisplayTable()
{
    int i,j;

    printf("\t\t\t\t\tTable\t\t\n\n");
    printf("Sl.No.\t\tName\t\tId Type\t\tData Type\tScope\t\tValue\n");
    printf("\n");

    for(i = 0;i<sl;i++)
    {
        int bl = 0, k;
        char s[50];

        Delete(s);

        for(k = 0;table[i][2][k]!='\0';k++)
        {
            s[k] = table[i][2][k];
        }

        if(strcmp("func",s)==0)
            bl = 1;

        for(j = 0;j<6;j++)
        {
            if(bl==1 && j==5)
                continue;

            printf("%s\t\t",table[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

void printTableInFile(FILE *target)
{
    int i,j;
    fputs("Sl.No.\t\tName\tId Type\t\t\tData Type\t\t\tScope\t\t\tValue", target);
    fputs("\n", target);

    for(i = 0;i<sl;i++)
    {
        int bl = 0,k;
        char s[50];
        Delete(s);

        for(k = 0;table[i][2][k]!='\0';k++)
        {
            s[k] = table[i][2][k];
        }

        if(strcmp("func",s)==0)
            bl = 1;

        for(j = 0;j<6;j++)
        {
            if(bl==1 && j==5)
                continue;

            fputs(table[i][j], target);
            fputs("\t\t\t", target);
        }
        fputs("\n", target);
    }
}



void CopyIdToArray(char* str1, char* str2){
    int i, j;
    Delete(str1);

    for(i = 3,j = 0;i<strlen(str2);i++,j++){
        str1[j] = str2[i];
    }
}

void CopyStringToArray(char* str1, char* str2){
    int i;

    Delete(str1);

    for(i = 0; i < strlen(str2); i++)
    {
        str1[i] = str2[i];
    }
}

int isDataType(char str1[]){
    int n = 5;

    char str2[5][20] = {"int","float","double","char", "void"};
    int i;
    for(i = 0;i<n;i++)
    {
        if(strcmp(str1,str2[i])==0)
            return 1;
    }
    return 0;
}



int main()
{
    FILE *f1,*f2,*f3,*f4,*f5,*f6,*f7;
    char a,b,input;
    char file[10000],arr[10000];

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
    f2=fopen("ass1_result.txt","w");


    while((a=fgetc(f1))!=EOF)
    {

        if(a=='/')
        {
            char c,d,e,f;

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



    f5=fopen("ass1_result.txt","r");
    f6=fopen("separated_lexeme.txt","w");

    while((a=fgetc(f5))!=EOF)
    {
       if(a == '+' || a == '*' || a == '/' || a == ',' || a == ';' || a == '>' || a == '<' || a == '='|| a == '(' || a == ')' ||a == '[' || a == ']' || a == '{' || a == '}')
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

    int store=0;

    while((a=fgetc(f3))!=EOF)
    {
        file[store++]=a;

    }

    fclose(f3);
    int kk=0;

    for(int i=0; file[i]!='\0'; i++)
    {

        if(file[i]==' ' && file[i+1]==' ')
            continue;
        else
            arr[kk++]=file[i];


    }
    f4=fopen("extra_space_removed.txt","w");

    for(int i=0; file[i]!='\n'; i++)
    {
        fprintf(f4,"%c",arr[i]);
    }

    fclose(f4);

    f6 = fopen("extra_space_removed.txt","r");
    f7 = fopen("ass2_result.txt","w");


    char string[100000];
    int yy=0;
    while((a=fgetc(f6))!=EOF)
    {
        if(a!=' ')
        {
            string[yy++]=a;
        }
        else
        {
            string[yy]='\0';
            yy=0;


            if(isKeyword(string)==true)
            {
                fprintf(f7,"[kw %s] ",string);
            }
            else if(isId(string)==1)
            {
                fprintf(f7,"[id %s] ",string);
            }
            else if(isNum_rec(string)==1)
            {
               fprintf(f7,"[num %s] ",string);
            }
            else if(isParenthesis(string)==true)
            {
                fprintf(f7,"[par %s] ",string);

            }
            else if(isOperator(string)==true)
            {
                fprintf(f7,"[op %s] ",string);
            }

            else if(isSeparator(string)==true)
            {
                fprintf(f7,"[sp %s] ",string);
            }
            else
            {
                fprintf(f7,"[unkn %s] ",string);
            }

        }

    }

    fclose(f6);
    fclose(f7);

    char c;
    char sourceFile[30] = "ass2_result.txt";
    char targetFile1[30] = "id_eleminate.txt";
    char targetFile2[30] = "table.txt";
    char targetFile3[30] = "numbered_table.txt";
    FILE *source, *target;

    // step 1
    source = fopen(sourceFile, "r");
    target = fopen(targetFile1, "w");
    eleminateId(source, target, sourceFile, targetFile1);

    fclose(source);
    fclose(target);
    target = fopen (targetFile1,"r");

    while( (c = fgetc(target)) != EOF)
    {
        printf("%c",c);
    }

    fclose(target);
    printf("\n\n\n");



    // step 2
    source = fopen(targetFile1, "r");
    target = fopen(targetFile2, "w");
    tableGenerate(source, target, sourceFile, targetFile1);

    // 4
    source = fopen(targetFile1, "r");
    target = fopen(targetFile3, "w");
    numberedTable(source, target, sourceFile, targetFile1);


    remove(targetFile2);

    fclose(source);
    fclose(target);

    printf("\n\nNumbering the Identifiers : \n\n");

    target = fopen (targetFile3,"r");
    while( (c = fgetc(target)) != EOF)
    {
        printf("%c",c);
    }
    fclose(target);
    printf("\n\n\n");

}


// step 1
void eleminateId(FILE *source, FILE *target, char sourceFile[30], char targetFile[30]){
    char c;
    int bracketStarting = 0;

    if(source == NULL || target == NULL)
    {
        printf("\nFile cannot be opened");
    }
    else{
        fputc(' ',target);

        while( (c = fgetc(source)) != EOF)
        {
            if(bracketStarting == 0 && c == '[')
            {
                bracketStarting = 1;
                fputc('[',target);

                continue;
            }
            if(bracketStarting == 1)
            {
                if(c == 'i')
                {
                    c = fgetc(source);

                    if(c == 'd')
                    {
                        fputs("id ",target);

                        continue;
                    }
                }
                else if(c == ' ')
                {
                    bracketStarting = 0;

                    continue;
                }
            }
            else
            {
                fputc(c,target);
            }
        }
    }
    fclose(source);
    fclose(target);
}


// step 2
void tableGenerate(FILE *source, FILE *target, char sourceFile[30], char targetFile[30]){
    int count = 0;
    char c, str[100], name[100], dataType[100], scope[100], value[100],previous[100], temp[100];

    CopyStringToArray(scope,"global");

    while( (c = fgetc(source)) != EOF)
    {
        int i = 0;
        if(c=='[')
        {
            while(1)
            {
                c = fgetc(source);
                if(c==']')
                    break;

                str[i] = c;
                i++;
            }

            if((str[0]=='i' && str[1]=='d' && str[2]==' ') && strlen(str)>3)
            {
               CopyIdToArray(temp,str);

               if(Search(temp,scope) == -1 && strcmp(previous,"=")!=0 )
               {
                   Insert(sl,temp,"var",dataType, scope);
                   sl++;
               }
               else{
                   if(strcmp(previous,"=") == 0)
                   {
                      UpdateScope(name,temp,scope);
                   }

                   else if(strcmp(previous,"return") == 0)
                   {
                      UpdateScope(scope,temp,scope);
                   }
               }
               CopyIdToArray(name,str);
            }

            else if(isDataType(str))
            {
               CopyStringToArray(dataType,str);
            }

            else if(isNumerical(str))
            {
               if(strcmp(previous, "=") == 0)
               {
                   if(Search(name, scope) != -1)
                   {
                       InsertStringInTable(Search(name,scope), 5, str);
                   }
                   else if(Search(name,"global") != -1 )
                   {
                       InsertStringInTable(Search(name,"global"), 5, str);
                   }
               }

               else if(strcmp(previous,"return") == 0)
               {
                   if(Search(scope,"global") != -1)
                   {
                      InsertStringInTable(Search(scope,"global"), 5, str);
                   }

               }
               CopyStringToArray(value,str);
            }

            else if(strlen(str)==1)
            {
                if(str[0]=='(')
                {
                    if(previous[0]=='i' && previous[1]=='d' && previous[2]==' ' && strlen(previous)>3)
                    {
                        if(count==0)
                        {
                            CopyStringToArray(scope,name);
                            UpdateId(name,"func","global");
                        }
                    }
                }
                else if(str[0]=='{'){
                    count++;
                }
                else if(str[0]=='}')
                {
                    count--;

                    if(count==0)
                    {
                        CopyStringToArray(scope,"global");
                    }
                }
            }
            CopyStringToArray(previous,str);
        }
        else
        {
            Delete(str);
            i = 0;
        }
    }
    DisplayTable();
    printTableInFile(target);
    fclose(source);
    fclose(target);
}


//step4
void numberedTable(FILE *source, FILE *target, char sourceFile[30], char targetFile[30]){
    int i, count = 0;
    char c, str[100], name[100], dataType[100], scope[100], value[100],previous[100], temp[100];


    while( (c = fgetc(source)) != EOF)
    {
        if(c=='[')
        {
            while(1)
            {
                c = fgetc(source);
                if(c==']')
                    break;
                str[i] = c; i++;
            }

            if((str[0]=='i' && str[1]=='d' && str[2]==' ') && strlen(str)>3)
            {
                Delete(temp);
                CopyIdToArray(temp,str);

                fputs("[id",target);

                if(Search(temp,scope) != -1)
                {
                    fprintf(target," %d", Search(temp,scope) + 1);
                }
                else
                {
                    fprintf(target," %d", Search(temp,"global") + 1);
                }

                fputc(']',target);
                CopyIdToArray(name,str);
            }

            else if(strlen(str)==1)
            {
                if(str[0]=='(')
                {
                    if(previous[0]=='i' && previous[1]=='d' && previous[2]==' ' && strlen(previous)>3)
                    {
                        if(count==0)
                        {
                            CopyStringToArray(scope,name);
                        }
                    }
                }

                else if(str[0]=='{')
                {
                    count++;
                }

                else if(str[0]=='}'){
                    count--;
                    if(count==0){
                        CopyStringToArray(scope,"global");
                    }
                }
                fputc('[',target);
                fputc(str[0],target);
                fputc(']',target);
            }

            else
            {
                fputc('[',target);
                fputs(str, target);
                fputc(']',target);
            }

            CopyStringToArray(previous,str);
        }
        else
        {
            fputc(c,target);
            Delete(str);
            i = 0;
        }
    }
}



