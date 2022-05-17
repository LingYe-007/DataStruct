#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxSize 50
typedef int ElemType;
typedef struct stack
{
    //定义栈中元素的最大个数
    ElemType data[MaxSize]; //系统自动分配空间大小
    //存放栈顶指针
    int top;
} stack;

void InitStack(stack &s)
{
    //将栈顶指针指向-1
    s.top = -1;
};
//判断当前栈是否为空
bool StackEmpty(stack &s)
{
    if (s.top == -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}
//栈弹出元素
ElemType Pop(stack &s)
{
    ElemType x;
    if (StackEmpty(s))
        return 0;
    else
    {
        x = s.data[s.top--];
        printf("\nPop:%d", x);
    }
    return x;
}

//读取栈顶元素
ElemType getTop(stack &s)
{
    ElemType x;
    if (s.top == -1)
        return 0;
    else
        return s.data[s.top];
}

//往栈中添加某一元素
int Push(stack &s, ElemType x)
{
    if (s.top >= MaxSize - 1)
        return 0;
    s.data[++s.top] = x;
    return 1;
}
//显示栈中的所有元素
void showStack(stack &s)
{
    printf("Stack->");
    for (int i = 0; i <= s.top; i++)
    {
        printf("->%d", s.data[i]);
    }
}
//销毁栈
void DestroyStack(stack &s)
{
    free(s.data);
}

int main()
{
    stack s;
    InitStack(s);
    Push(s, 1);
    Push(s, 2);
    Pop(s);
    showStack(s);
    DestroyStack(s);
    showStack(s);
    return 0;
}
