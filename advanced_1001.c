#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int* getInput()
{
    int i;
    int* res = (int *)malloc(sizeof(int)*2);
    for(i = 0; i < 2; i++)
    {
        scanf("%d", &res[i]);
    }
    return res;
}

void reverseString(char* s, int n)
{
    int i = 0;
    int j = n - 1;
    while(i < j)
    {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++;
        j--;
    }
    s[n] = '\0';
}

char* transferSum(int* nums)
{
    int sum = nums[0] + nums[1];
    /*printf("in tranfserSum, nums[0] = %d, nums[1] = %d, sum = %d\n", nums[0], nums[1], sum);*/
    free(nums);
    char sign = '+';
    char* res = (char *)malloc(sizeof(char)*11);
    if(sum < 0)
    {
        sign = '-';
        sum = -1*sum;
        /*printf("after change the sign, sum = %d\n", sum);*/
    }
    int i = 0;
    while(sum != 0)
    {
        int tmp = sum%10;
        /*printf("tmp = %d\n", tmp);*/
        res[i] = tmp + '0';
        /*printf("(char)tmp = %c\n", res[i]);*/
        i++;
        sum = sum/10;
        if((i%4 == 3) && (sum != 0))
        {
            res[i] = ',';
            i++;
        }
    }
    if(sign == '-')
    {
        res[i] = '-';
        i++;
    }
    
    if(i != 0)
        reverseString(res, i);
    else
        res = "0";
    return res;
}

int main()
{
    int* inputNums;
    char* dightNums;
    inputNums = getInput();
    dightNums = transferSum(inputNums);
    printf("%s", dightNums);
    return 0;
}

