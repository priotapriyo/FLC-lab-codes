#include <stdio.h>
#include <string.h>

char str[1000];
int pos = 0;
int f = 0;

void initialize()
{
    f = 0;
    pos = 0;
}

void A()
{
    if (strlen(str) < 2)
    {
        f = 0;
        return;
    }
    if (str[pos] != 'a')
    {
        f = 0;
        return;
    }

    pos++;
    X();

    if (f == 1)
    {
        if (pos + 1 == strlen(str) && str[pos] == 'd')
        {
            pos++;
            f = 1;
            return;
        }
        else
        {
            f = 0;
            return;
        }
    }
    else
    {
        f = 0;
        return;
    }
}


void X()
{
    if (pos + 2 < strlen(str) && str[pos] == 'b' && str[pos + 1] == 'b')
    {
        pos += 2;
        X();
        return;
    }
    if (pos + 2 < strlen(str) && str[pos] == 'b' && str[pos + 1] == 'c')
    {
        pos += 2;
        X();
        return;
    }
    f = 1;
    return;
}


void Exp()
{
    Term();
    if (pos == strlen(str) || f == 0)
    {
        return;
    }
    if (str[pos] == '+' || str[pos] == '-')
    {
        pos++;
        Term();
    }
}


void Term()
{
    Factor();
    if (pos == strlen(str) || f == 0)
    {
        return;
    }
    if (str[pos] == '*' || str[pos] == '/')
    {
        pos++;
        Factor();
    }
}


void Factor()
{
    ID();

    if (f == 1)
        return;

    NUM();

    if (f == 1)
        return;
    if (pos < strlen(str) && str[pos] == '(')
    {
        pos++;

        Exp();

        if (f == 1)
        {
            if (pos < strlen(str) && str[pos] == ')')
            {
                pos++;
                f = 1;
                return;
            }
            f = 0;
            return;
        }
        f = 0;
        return;
    }
    f = 0;
    return;
}

void ID()
{
    if (pos < strlen(str) && str[pos] >= 'a' && str[pos] <= 'e')
    {
        pos++;
        f = 1;
        return;
    }
    f = 0;
    return;
}

void NUM()
{
    if (pos < strlen(str) && str[pos] >= '0' && str[pos] <= '9')
    {
        pos++;
        f = 1;
        return;
    }
    f = 0;
    return;
}


int main()
{
    printf("Enter the string: ");
    scanf("%s", str);

    initialize();
    A();
    X();

    printf("CFG 1 status: ");
    if (f && pos == strlen(str))
        printf("Matched\n");
    else
        printf("Not matched\n");

    initialize();
    Exp();
   /* Term();
    Factor();
    ID();
    NUM();*/

    printf("CFG 2 status: ");
    if (f == 1 && pos == strlen(str))
        printf("Matched\n");
    else
        printf("Not matched\n");

}

