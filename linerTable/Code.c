#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;
typedef struct Node
{
    //结构体定义数据类型?
    int data;
    //尾指针指向Node类型的变量
    struct Node *next;
} Node;

//尾插法LinkList也定义为node类型  ???
typedef struct Node *LinkList;

//*L 选取指针,导致首地址是不变的,我们武法
int InitList(LinkList *L)
{
    //指针自身 = (指针类型*）malloc（sizeof（指针类型）*数据数量?
    (*L) = (LinkList)malloc(sizeof(Node));
    // malloc分配失败会返回null
    if (!L)
    {
        printf("分配内存失败！\n");
        // 0为正常退出?,1为异常退出?,其他数字为异腿粗?
        exit(0);
    }
    //将L的尾指针指向Null
    (*L)->next = NULL;
    return 0;
}
//打印出链表的所有元素?
void ShowList(LinkList *L)
{
    LinkList p;
    p = (*L)->next;
    if (p == NULL)
    {
        printf("这是一个空链表！\n");
    }
    printf("单链表?");
    while (p != NULL)
    {
        printf("-> %d", p->data);
        p = p->next;
    }
    printf("\n");
}

//只有通过所谓的尾插法和头插法创建
int ListInsertTail(LinkList *L, int e)
{
    //创建节点p
    LinkList p, r;
    r = *L;
    //为p申请一个节点的空间
    p = (LinkList)malloc(sizeof(Node));
    p->data = e;
    //找到链表的尾节点?
    while (r->next != NULL)
    {
        r = r->next;
    }
    //将r的next指向p节点
    r->next = p;
    r = p;
    r->next = NULL;
    return 0;
}

//头插法,把元素插到链表最开始
int ListInsertHead(LinkList *L, int e)
{
    //创建节点P,用于插与头部
    LinkList p;
    p = (LinkList)malloc(sizeof(Node));
    p->next = *L;
    p->data = e;
    p->next = (*L)->next;
    (*L)->next = p;
    return 0;
}

//按位插入法,通过i值来决定来插入哪一个
int ListInsertOrder(LinkList *L, int e, int i)
{
    //创建节点p,r p用于复制*L的地址,r用来连接新节点;
    int j = 1; // 现在在哪个位置
    LinkList p, r;
    r = (LinkList)malloc(sizeof(Node));
    p = *L;
    //注意,即便是你现在初始化为1,但有区别
    while (j < i && p != NULL)
    {
        p = p->next;
        j++;
    };
    r->data = e;
    r->next = p->next;
    p->next = r;
    return 0;
}

// 通过链表的值来定位
int LocateElem(LinkList *L, int e)
{
    //用来判断链表应该在什么地方
    int j = 0;
    //创捷P节点来模拟L指针的地址;
    LinkList p;
    p = *L;
    while (p->next != NULL)
    {
        if (p->data == e)
            break;
        p = p->next;
        j++;
    }
    printf("%d\n", j);
    return j;
}

//按位查找操作,获取表L第i个位置的元素
int GetElem(LinkList *L, int e)
{
    int i = 1;
    LinkList p;
    p = *L;
    while (i <= e)
    {
        p = p->next;
        i++;
    }
    printf("%d", p->data);
    return 0;
}

//删除第i个元素的元素,并用e返回删除元素的值
int ListDelete(LinkList *L, int i, elemtype *e)
{
    int j = 1;
    LinkList p, q;
    p = *L;
    while (j < i && p->next)
    {
        p = p->next;
        j++;
    };
    q = p->next;
    p->next = q->next;
    //将该地址的值赋予q->data这个数据。
    (*e) = q->data;
    free(q);
    printf("e的值是\n%d", e);
    return 0;
}

int Empty(LinkList L)
{
    if (L->next)
    {
        printf("我是真的");
        return 1;
    }
    else
    {   
        printf("我是假的");
        return 0;
    }
}

//删除整个链表,通过访问节点并且将其节点内存释放,再将其尾节点置空。

int main()
{
    //因为这个已经申明L是一个指针了,这个指向的是它的内容
    LinkList L;
    //定义一个m变量
    elemtype m;
    // L的存储地址传给指针类型的变量?
    InitList(&L);
    Empty(L);
    ListInsertTail(&L, 2);
    ListInsertHead(&L, 1);
    ListInsertHead(&L, 3);
    ListInsertOrder(&L, 5, 1);
    ListInsertOrder(&L, 6, 2);
    //将m变量的地址传给del,用于函数给该地址赋值用于返回
    ListDelete(&L, 3, &m);
    ShowList(&L);
    LocateElem(&L, 6);
    GetElem(&L, 1);
    Empty(L);
    printf("\n%d", m);
}