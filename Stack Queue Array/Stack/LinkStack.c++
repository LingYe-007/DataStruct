#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxSize 50
typedef int ElemType;
//定义链栈的结点和结构体
typedef struct LinkNode
{
    ElemType data;
    struct LinkNode *next;
} LinkNode;
typedef LinkNode *LinkList;
//初始化链栈的头结点
void InitLinkList(LinkList &L)
{
    LinkList p;
    p = (LinkList)malloc(sizeof(LinkNode));
    p->next = NULL;
    if (!p)
    {
        printf("初始化失败,自动退出");
        exit(0);
    }
    L = p;
}
//利用头插法插入链栈结点
void InsertLinkList(LinkList &L, ElemType x)
{
    LinkList p;
    p = (LinkList)malloc(sizeof(LinkNode));
    p->next = L->next;
    L->next = p;
    p->data = x;
}
//显示栈中所有的元素,利用函数的递归循环阻塞性来输出合适的值,如果需要先出的话
void showStack(LinkList &L)
{
    if (L->next != NULL)
    {
        showStack(L->next);
    }
    printf("%d->", L->data);
}
//删除栈顶元素
void pop(LinkList &L)
{
    LinkList p;
    if (L->next == NULL)
        return;
    p = L->next;
    L->next = L->next->next;
    printf("del:%d", p->data);
    free(p);
}
//销毁整个栈
void detroyStack(LinkList &L)
{
    LinkList cur, pre;
    cur = pre = L;
    while (cur)
    {
        pre = cur;
        cur = cur->next;
        free(pre);
    }
}
int main()
{
    LinkList L;
    InitLinkList(L);
    for (int i = 0; i < 10; i++)
    {
        InsertLinkList(L, i);
    }
    showStack(L);
    pop(L);
    showStack(L);
    detroyStack(L);
}
