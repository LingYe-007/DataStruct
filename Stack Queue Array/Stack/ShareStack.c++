#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxSize 20
typedef int ElemType;
typedef struct stack
{
    //定义栈中元素的最大个数
    ElemType *data;
    //存放两个栈顶指针
    int top[2];
} stack;
void InitShareStack(stack &L)
{
    L.data = (ElemType *)malloc(sizeof(ElemType) * MaxSize);
    L.top[0] = 0;
    L.top[1] = MaxSize - 1;
}
void push(int i, ElemType x, stack &L)
{
    if (L.top[1] - L.top[0] == 1)
        return;
    else
    {
        switch (i)
        {
        case 0:
            L.data[++L.top[0]] = x;
            break;

        case 1:
            L.data[--L.top[1]] = x;
            break;
        }
    }
}
void pop(int i, stack &L)
{
    if ((i == 0 && L.top[0] <= 0) || (i == 1 && L.top[1] >= MaxSize - 1))
        return;
    switch (i)
    {
    case 0:
        printf("pop:%d", L.data[L.top[0]--]);
        break;
    case 1:
        printf("pop:%d", L.data[L.top[1]++]);
        break;
    }
}

int main()
{
    stack L;
    InitShareStack(L);
    for (int i = 0; i < 10; i++)
    {
        push(0, i, L);
    }
    for (int i = 0; i < 10; i++)
    {
        push(1, i + 10, L);
    }
    pop(0, L);
    return 0;
}
