#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#define TRUE 1
#define FALSE 0

double log2(double n)
{
    return log(n)/log(2);
}

int isInt(double n)
{
    if((int)n == n)
        return TRUE;
    else
        return FALSE;
}

int isEven(int n)
{
    if(n%2 == 0)
    {
        return TRUE;
    }
    else
        return FALSE;
}

int powOf2(int n)
{
    double pow = log2(n);
    if(isInt(pow))
    {
        return pow;
    }
    else{
        return 0;
    }
}


int countStep(int n)
{
    int count = 0;
    while(n != 1)
    {
        int pow = powOf2(n);
        if(pow != 0)
        {
            count += pow;
            return count;
        }
        else{
            if(isEven(n))
            {
                n = n/2;
                count++;
            }
            else{
                n = 3*n + 1;
                n = n/2;
                count++;
            }
        }
    }
    return count;
}

int main()
{
    int num;
    scanf("%d", &num);
    int count = countStep(num);
    printf("%d", count);
    return 0;
}
