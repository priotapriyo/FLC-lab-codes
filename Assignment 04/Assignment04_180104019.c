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


/*bool isOperator(char* c)
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


bool isParenthesis(char c)
{
    if(c[0]==')' || c[0]=='(' || c[0]=='}' || c[0]=='{' )
     {
         return true;
     }
    return false;
}*/


int isSeperator(char ch) {
    return ((ch == ';') || (ch == ' ') || (ch == ',') || (ch == '\''));
}
int isOperator(char ch) {
    return ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '=') || (ch == '<') || (ch == '>'));
}
int isParenthesis(char ch) {
    return ((ch == '(') || (ch == ')') || (ch == '{') || (ch == '}') || (ch == '[') || (ch == ']'));
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



int isIdentifier(char * lex) {
    int i, l, s;
    i = 0;
    if (isalpha(lex[i]) || lex[i] == '_') {
        s = 1;
        i++;
    } else {
        s = 0;
        return 0;
    }
    l = strlen(lex);
    if (s == 1) {
        for (i = 1; i < l; i++) {
            if (isalnum(lex[i]) || lex[i] == '_') {
                continue;
            } else {
                s = 0;
                break;
            }
        }
    }
    if (s == 0) return 0;
    else return 1;
}


int isDataType(char * str) {
    char datatypes[8][10] = {"int","long long", "long","double", "float", "unsigned", "short","void" };

    for (int i = 0; i < 8; ++i)
    {
        if (!strcmp(datatypes[i], str))
        {
            return 1;
        }
    }
    return 0;
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


void Delete(char* str){
    int i;

    for(i = 0;i<50;i++)
    {
        str[i] = '\0';
    }
}

/*void UpdateScope(char* str1, char* str2, char* scope)
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
*/

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

struct hashTable {
    char name[10], type[10], datatype[10], scope[10];
    int lineNo, isON;
}
symbolTable[100], allVar[100];

int stack_pointer_scope;
char stack_scope[1000][20];

void push(char * x) {
    strcpy(stack_scope[stack_pointer_scope++], x);
}
void pop() {
    if (stack_pointer_scope > 0 && strcmp(stack_scope[stack_pointer_scope - 1], "main")) stack_pointer_scope--;
}
char * top() {
    return stack_scope[stack_pointer_scope - 1];
}
int empty() {
    return stack_pointer_scope == 0;
}

int symbolTableRow;
void insert(char * name, char * type, char * dtype, char * scope) {
    strcpy(symbolTable[symbolTableRow].name, name);
    strcpy(symbolTable[symbolTableRow].type, type);
    strcpy(symbolTable[symbolTableRow].datatype, dtype);
    strcpy(symbolTable[symbolTableRow].scope, scope);
    symbolTableRow++;
}
int search(char * name, char * type, char * scope) {
    int i = 0;
    for (i = 0; i < symbolTableRow; i++)
    {
        if (strcmp(name, symbolTable[i].name) == 0 && strcmp(type, symbolTable[i].type) == 0 && strcmp(scope, symbolTable[i].scope) == 0)
        {
            return i;
        }
    }
    return -1;
}
int searchIfUndeclared(char * name, char * scope) {
    int i = 0;
    for (i = 0; i < symbolTableRow; i++)
    {
        if (strcmp(name, symbolTable[i].name) == 0 && strcmp(scope, symbolTable[i].scope) == 0)
        {
            return i;
        }
    }
    return -1;
}

int total_line;

void removeCommentandAddLineNumber() {
    FILE * f9 = fopen("input.txt", "r");
    FILE * f10 = fopen("with_lineNo.txt", "w");
    FILE * f11 = fopen("without_line_no.txt", "w");

    int lineNo = 1, newline = 1;
    char c,temp[100], prev[100];
    int indx = 0,firstLine = 0;

    while ((c = fgetc(f9)) != EOF)
    {
        if (firstLine == 0)
        {
            fprintf(f10, "%d ", lineNo);
            lineNo++;
            firstLine = 1;
        }

        if (c == '/')
        {
            char t = fgetc(f9);
            if (t == '/')
            {
                while ((t = fgetc(f9)) != EOF)
                {
                    if (t == '\n') break;
                }
            }
            else if (t == '*')
            {
                while ((t = fgetc(f9)) != EOF)
                {
                    if (t == '*')
                    {
                        char t1 = fgetc(f9);
                        if (t1 == '/') break;
                    }
                }
            }
        }
        else if (c == '\n')
        {
            fputc(c, f11);
            fprintf(f10, "\n%d ", lineNo++);
            newline = 1;
        }
        else if (c == ' ' || (isOperator(c)) || (isSeperator(c)) || (isParenthesis(c)))
        {
            temp[indx] = '\0';
            int ans = isIdentifier(temp) && !isDataType(temp) && !isKeyword(temp);

            if (strlen(temp) == 0 && (isSeperator(c) || isParenthesis(c)))
            {
                if (c == ' ')
                {
                    fprintf(f10, "%c", c);
                    fprintf(f11, "%c", c);
                }
                else if (newline == 0)
                {
                    fprintf(f10, "%c ", c);
                    fprintf(f11, "%c ", c);
                    newline = 1;
                }
                else
                {
                    fprintf(f10, " %c ", c);
                    fprintf(f11, " %c ", c);
                }
            }
            else if (ans == 1)
            {
                if (c == ' ')
                {
                    fprintf(f10, "id %s%c", temp, c);
                    fprintf(f11, "id %s%c", temp, c);
                }
                else
                {
                    fprintf(f10, "id %s %c ", temp, c);
                    fprintf(f11, "id %s %c ", temp, c);
                }
            }
            else
            {
                if (c == ' ')
                {
                    fprintf(f10, "%s%c", temp, c);
                    fprintf(f11, "%s%c", temp, c);
                }
                else
                {
                    fprintf(f10, "%s %c ", temp, c);
                    fprintf(f11, "%s %c ", temp, c);
                }
            }

            strcpy(prev, temp);
            indx = 0;

            while ((c = fgetc(f9)) == ' ');
            if (c == '\n')
            {
                fprintf(f10, "%c%d ", c, lineNo++);
                fprintf(f11, "%c", c);
                newline = 0;
            }
            else if ((isOperator(c)) || (isSeperator(c)) || (isParenthesis(c)))
            {
                fprintf(f10, "%c", c);
                fprintf(f11, "%c", c);
            }
        else
        {
           temp[indx++] = c;
        }

        }
        else {
            temp[indx++] = c;
        }
    }

    fclose(f9);
    fclose(f10);
    fclose(f11);
}

int curly_brace_validity[100], parenthesis_validity[100], if_else_validity[100];
int curly_brace_pointer, parenthesis_pointer, if_else_pointer;

void push2(int stack[], int pointer, int value) {
    stack[pointer] = value;
}
int pop2(int pointer) {
    if (pointer >= 0)
        pointer--;
    return pointer < 0 ? 0 : pointer;
}
int top2(int stack[], int pointer) {
    return stack[pointer - 1];
}
int empty2(int pointer) {
    return pointer == 0;
}

void unbalancedParenthesisAndCurlyBraces(char * line, int line_number) {
    int duplicate = 0, i, len = strlen(line);

    for (i = 0; i < len; i++)
    {
        if (isSeperator(line[i]) && line[i] != ' ' && i != len - 2)
        {
            if (isSeperator(line[i + 2]) && line[i + 2] != ' ')
            {
                duplicate = 1;
                int j;
                for (j = 2; j < len; j++)
                {
                    if (line[j - 2] == 'f' && line[j - 1] == 'o' && line[j] == 'r')
                    {
                        int k = j + 1;
                        int last_closing_parenthesis = -1;

                        while (k < len)
                        {
                            if (line[k] == ')')
                            {
                                last_closing_parenthesis = k;
                                break;
                            }
                            k++;
                        }

                        if (i > j + 1 && i < last_closing_parenthesis && i + 2 > j + 1 && i + 2 < last_closing_parenthesis)
                        {
                            duplicate = 0;
                        }
                    }
                }
            }
        }
        else if (line[i] == '{')
        {
            push2(curly_brace_validity, curly_brace_pointer++, line_number);
        }
        else if (line[i] == '}')
        {
            if (empty2(curly_brace_pointer))
            {
                printf("mismatched } at line %d\n", line_number);
            }
            else
            {
                curly_brace_pointer = pop2(curly_brace_pointer);
            }
        }
        else if (line[i] == '(')
        {
            push2(parenthesis_validity, parenthesis_pointer++, line_number);
        }
        else if (line[i] == ')')
        {
            if (empty2(parenthesis_pointer))
            {
                printf("Unbalanced Parenthesis at line %d\n", line_number);
            }
           else
            {
                parenthesis_pointer = pop2(parenthesis_pointer);
            }
        }

    }

    if (duplicate) {
        printf("Duplicate token at line %d\n", line_number);
    }

}

void UnmatchedIfElse(char * line, int line_number) {
    int len = strlen(line), chkIn = 0;
    char check[100];

    for (int i = 0; i < len; ++i)
    {
        if (isalpha(line[i]))
        {
            check[chkIn++] = line[i];
        }
        else
        {
            check[chkIn] = '\0';
            chkIn = 0;

            if (!strcmp(check, "if"))
            {
                push2(if_else_validity, if_else_pointer++, line_number);
            }
            else if (!strcmp(check, "else"))
            {
                if (empty2(if_else_pointer))
                {
                    printf("Unmatched else at line %d\n", line_number);
                }
                else
                {
                    if_else_pointer = pop2(if_else_pointer);
                }
            }
        }
    }
}


void dataTypeValidity(char * line, int line_number) {
    int len = strlen(line), wIn = 0;
    char word[100];
    char prev[] = "nafi";

    for (int i = 0; i < len; ++i)
    {
        if ((isalpha(line[i]) || line[i] == '_' || isdigit(line[i])) && (line[i] != ' '))
        {
            word[wIn++] = line[i];
        }
        else
        {
            word[wIn] = '\0';
            if (isDataType(word))
            {
                if (isDataType(prev) && (!strcmp(prev, "long") && !strcmp(word, "long")) == 0 && (!strcmp(prev, "else") && !strcmp(word, "if")) == 0)
                {
                    printf("two or more data types in declaration specifiers at line %d\n", line_number);
                }
                else if (!strcmp(word, prev) && (!strcmp(prev, "long") && !strcmp(word, "long")) == 0)
                {
                    printf("Duplicate token at line %d\n", line_number);
                }

            }
            strcpy(prev, word);
            wIn = 0;
        }
    }
}

int last_parenthesis = -1, opening_curly_brace = -1, func_opening_curly_brace = -1;

void generateSymbolTable(char * line, int line_number) {
    char lex[100], previous[100];
    int lex_index = 0, prev_dt_index = 0,isPrevId = 0,i = 0;

    while (i < strlen(line))
    {
        if (line[i] == '{' && strcmp(top(), "global")) strcpy(previous, "notadatatype");
        if (line[i] == '}')
        {
            opening_curly_brace = -1;
            pop();
            strcpy(previous, "notadatatype");
        }
        if (last_parenthesis != -1 && line[i] == ';')
        {
            last_parenthesis = -1;
            pop();
            strcpy(previous, "notadatatype");
        }

        if (last_parenthesis == i || opening_curly_brace == i)
        {
            char new_scope[50];
            sprintf(new_scope, "line %d", line_number);
            push(new_scope);
            strcpy(previous, "notadatatype");

        }
        if (line[i] == ' ')
        {
            lex[lex_index] = '\0';
            lex_index = 0;

            if (isDataType(lex))
            {
                strcpy(previous, lex);
                isPrevId = 0;
            }
            else if (!strcmp(lex, "if") || !strcmp(lex, "else") || !strcmp(lex, "for") || !strcmp(lex, "while"))
            {
                if (!strcmp(lex, "else"))
                {
                    int j;
                    for (j = i + 1; j < strlen(line); j++)
                    {
                        if (line[j] == ';')
                        {
                            last_parenthesis = j;
                            break;
                        }
                    }
                }
                else
                {
                   int j;
                   for (j = i + 1; j < strlen(line); j++)
                    {
                        if (line[j] == ')')
                        {
                          last_parenthesis = j;
                        }

                        if (line[j] == '{')
                        {
                           opening_curly_brace = j;
                        }

                    }
                }
            }
            else if (strcmp(lex, "id"))
            {
                if (strlen(lex) == 1 && lex[0] == ';')
                {
                  strcpy(previous, "notAdataype");
                }


                if (isIdentifier(lex) && !isKeyword(lex) && !isDataType(lex))
                {
                    if (isDataType(previous))
                     {
                        if (i < strlen(line) - 1 && line[i + 1] == '(')
                        {
                            if (search(lex, "func", top()) == -1)
                            {
                              insert(lex, "func", previous, top());
                            }

                            strcpy(previous, "notadatatype");
                            push(lex);
                        }
                        else {
                            if (search(lex, "var", top()) == -1)
                            {
                                insert(lex, "var", previous, top());
                            }
                            else
                            {
                                printf("redeclared variable %s at line %d.\n", lex, line_number);

                            }
                        }
                    }
                    else {
                        if (searchIfUndeclared(lex, top()) == -1 && searchIfUndeclared(lex, "global") == -1)
                        {
                            printf("!!! %s %s %d\n", lex, top(), line_number);

                            if (!strcmp(lex, "printf") || !strcmp(lex, "scanf"))
                            {
                                i += 2;
                                while (line[i++] != '"');
                                continue;
                            }
                            printf("undeclared variable %s at line %d.\n", lex, line_number);
                        }

                    }
                }
                isPrevId = 0;

            }
            else if (!strcmp(lex, "id"))
            {
                isPrevId = 1;
            }
        }
        else
        {
            lex[lex_index++] = line[i];
        }

        i++;
    }
}

void printSymbolTable() {
    int i = 0;
    for (i = 0; i < symbolTableRow; i++)
    {
        printf("%d %s %s %s %s\n", i + 1, symbolTable[i].name, symbolTable[i].type, symbolTable[i].datatype, symbolTable[i].scope);
    }
}


void eleminateId(FILE *source, FILE *target, char sourceFile[30], char targetFile[30]){
    char c;
    int bracketStarting = 0;

    if(source == NULL || target == NULL)
    {
        printf("\nFile cannot be opened");
    }
    else
    {
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
        }
    }
   // DisplayTable();
    //printTableInFile(target);
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

                else if(str[0]=='}')
                {
                    count--;
                    if(count==0)
                    {
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


int main() {

    FILE *f1,*f2,*f3,*f4,*f5,*f6,*f7,*f8, *f9;
    char a,b,input;
    char file[10000],arr[10000];

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
//
    fclose(f6);
    fclose(f7);


    //f1=fopen("input.txt","w");

    char t[9999];
    int i=0;
    int f = 0;
    f8 = fopen("input.txt","w");

    while(scanf("%c",&input))
    {
        if(input == '`')
        {
            break;
        }
        else{
            fputc(input,f8);
            t[i] = input;
            i++;
            f++;
        }

    }
    fclose(f8);

    //char c;
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

    fclose(target);
   // printf("\n\n\n");



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

    //printf("\n\nNumbering the Identifiers : \n\n");

    target = fopen (targetFile3,"r");

    fclose(target);
    printf("\n\n\n");


    removeCommentandAddLineNumber();

    push("global");
    printf("%s\n", top());
    char line[2000];
    int line_index = 0, line_no = 0;

    f9 = fopen("without_line_no.txt", "r");

    char ch;
    while ((ch = fgetc(f9)) != EOF)
    {
        if (ch == '\n')
        {
            line_no++;
            line[line_index] = '\0';
            line_index = 0;

            generateSymbolTable(line, line_no);
            unbalancedParenthesisAndCurlyBraces(line, line_no);
            UnmatchedIfElse(line, line_no);
            dataTypeValidity(line, line_no);
        }
        else
        {
            line[line_index++] = ch;
        }

    }

    while (!empty2(curly_brace_pointer))
    {
        printf("Mismatched { at line %d\n", top2(curly_brace_validity, curly_brace_pointer));
        curly_brace_pointer = pop2(curly_brace_pointer);
    }

    while (!empty2(parenthesis_pointer))
    {
        printf("Unbalanced Parenthesis at line %d\n", top2(parenthesis_validity, parenthesis_pointer));
        parenthesis_pointer = pop2(parenthesis_pointer);
    }

    while (!empty2(if_else_pointer))
    {
        printf("unmatched else at line %d\n", top2(if_else_validity, if_else_pointer));
        if_else_pointer = pop2(if_else_pointer);
    }
    //DisplayTable();
    return 0;
}



