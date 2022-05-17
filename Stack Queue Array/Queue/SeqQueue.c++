#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MaxSize 50
typedef int Elemtype;
typedef struct SeqQueue
{
    Elemtype data[MaxSize];
    //初始化顺序链表的尾结点和头结点
    int front, rear;
} SeqQueue;
//初始化顺序队列
bool InitSeqQueue(SeqQueue &L)
{
    L.front = 0;
    L.rear = 0;
    return true;
}
//判断队列为空
bool QueueEmpty(SeqQueue &L)
{
    if (L.front == L.rear)
        return true;
    else
    {
        return false;
    }
}
//进队
bool EnSeqQueue(SeqQueue &L, int x)
{
    if (L.rear >= MaxSize - 1)
        return false;
    L.data[L.rear++] = x;
    return true;
}
//出队
bool DeSeqQueue(SeqQueue &L)
{
    if (L.front < 0)
        return false;
    L.data[L.front++] = NULL;
    return true;
}
//获取队头元素
Elemtype getFront(SeqQueue &L)
{
    if (QueueEmpty(L))
        return 0;
    else
    {
        printf("front:%d\n", L.data[L.front]);
        return L.data[L.front];
    }
}

int showQueue(SeqQueue &L)
{
    printf("Queue:");
    for (int i = L.front; i < L.rear; i++)
    {
        printf("->%d", L.data[i]);
    }
    printf("\n");
}

int main()
{
    SeqQueue L;
    InitSeqQueue(L);
    EnSeqQueue(L, 1);
    // getFront(L);
    showQueue(L);
    EnSeqQueue(L, 1);
    showQueue(L);
    DeSeqQueue(L);
    showQueue(L);
}