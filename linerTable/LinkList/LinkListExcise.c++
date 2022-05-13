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
//方便用于申请节点空间
typedef struct Node *LinkList;
//用来定义循环链表
typedef struct CNode
{
    //结构体定义数据类型?
    int data;
    //尾指针指向Node类型的变量
    struct CNode *next;
    struct CNode *prior;
    int freq;
} CNode;
//用来申请一个循环链表的节点空间
typedef struct CNode *CirList;
//用来生成一个循环双链表
int InitCirList(CirList &CL)
{
    CirList p;
    p = (CirList)malloc(sizeof(CNode));
    p->next = NULL;
    p->prior = p; //初始化循环双链表的时候,需要把他的前向指针和后向指针都指向它自己
    CL = p;
    return 0;
}
//用来给一个循环双链表,利用尾插法插入数据
int InsertCirList(CirList &CL, int x)
{
    CirList p, cur;
    cur = CL;
    //找到尾巴结点
    while (cur->next && cur->next != NULL)
    {
        cur = cur->next;
    }
    p = (CirList)malloc(sizeof(CNode));
    p->data = x;
    p->freq = 0;
    p->prior = cur;
    cur->next = p;
    return 0;
}
//初始化一个不带头节点的单链表
int InitLinkListNoHead(LinkList &L)
{
    //直接将链表指向虚无
    L = NULL;
    return 0;
};
//初始化一个带头节点的单链表
int InitLinkList(LinkList &L)
{
    LinkList node;
    node = (LinkList)malloc(sizeof(Node));
    node->next = NULL;
    node->data = INT_MAX;
    if (!node)
    {
        printf("初始化节点失败");
        exit(0);
    }
    L = node;
    return 0;
};
//初始化一个循环单链表
int InitCirLinkList(LinkList &L)
{
    LinkList p;
    p = (LinkList)malloc(sizeof(Node));
    p->data = INT_MAX;
    p->next = p; //将下个节点指向自己。
    L = p;
}
//往一个循环单练表中插入一个元素
int InsertCirLinkElem(LinkList &L, int x)
{
    LinkList p, tail;
    tail = L;
    p = (LinkList)malloc(sizeof(Node));
    //找到尾节点,利用尾插法插入
    while (tail->next != L)
    {
        tail = tail->next;
    }
    p->data = x;
    p->next = tail->next;
    tail->next = p;
}
//插入一个元素
int InsertElem(LinkList &L, int x)
{
    LinkList p;
    p = (LinkList)malloc(sizeof(Node));
    p->data = x;
    if (!L)
    {
        p->next = NULL;
        L = p;
    }
    else
    {
        p->next = L->next;
        L->next = p;
    }
    return 0;
}
//显示这个链表所有的元素
int showList(LinkList L)
{
    printf("LinkList:");
    while (L)
    {
        printf("%d->", L->data);
        L = L->next;
    }
    printf("\n");
    return 0;
}
//显示一个循环双链表的所有元素
int showCirList(CirList CL)
{
    CirList L1;
    L1 = CL->next; //还是要申请节点来遍历？
    printf("CirList:");
    while (L1) // 注意不同节点的边界条件
    {
        printf("->%d", L1->data);
        L1 = L1->next;
    }
    printf("\n over");
}
//显示一个循环带链表
int showCirLinkList(LinkList CL)
{
    LinkList L1;
    L1 = CL->next; //还是要申请节点来遍历？
    printf("CirLinkList:");
    while (CL != L1) // 注意不同节点的边界条件
    {
        printf("->%d", L1->data);
        L1 = L1->next;
    }
    printf("\n over \n");
}
//题1,设计一个递归删除不带头节点的单链表
//不带头节点的链表,只有头节点是删除节点的时候,需要往后移一位,其他一样
int recursionDel(LinkList &L, int x)
{
    LinkList p;
    if (!L)
        return 0;
    //只有L需要删除的时候,L才会往下走
    if (L->data == x)
    {
        //传入的是指针的即是L->next
        p = L;
        //相当于L->next=L->next->next
        L = p->next;
        free(p);
        recursionDel(L, x);
    }
    else if (L && L->next)
    {
        //如果有的话递归传递下个节点的指针
        recursionDel(L->next, x);
    }
    else
        return 0;
}

//题二.带头节点的链表,删除所有值为X的节点
int delX(LinkList &L, int x)
{
    LinkList p, q;
    p = L;
    while (p)
    {
        if (p->next && p->next->data == x)
        {
            q = p->next;
            p->next = q->next;
            free(q);
        }
        else
        {
            p = p->next;
        }
    }
}
//题三,设L为带头节点的单链表,编写算法实现从尾到头的反向输出每个节点的值
//不用递归的话,也可以先将单链表逆置后再输出
int reverse(LinkList L)
{
    //利用函数的递归性,如果函数内部调用函数,会先执行完这个函数
    if (L->next != NULL)
    {
        reverse(L->next);
    }
    if (L != NULL)
        printf("%d", L->data);
}
void R_Head(LinkList L)
{
    //如果头节点不为空的话,reverse
    if (L->next != NULL)
        reverse(L->next);
}
//题四.编写一个在头结点的单链表中删除一个最小值节点的高效算法
void delMin(LinkList L)
{
    LinkList pre, cur, q;
    int min = INT_MAX;
    cur = L;
    while (cur)
    {
        if (cur->data < min)
        {
            min = cur->data;
            pre = cur;
        }
        cur = cur->next;
    }
    q = pre->next;
    pre->next = q->next;
    free(q);
}
//题5 编写算法将带头节点的单链表原地逆置
int RerverseLinkList(LinkList &L)
{
    LinkList pre, cur, p;
    //跳过头节点
    cur = L->next;
    //将第一个元素指向NULL
    pre = NULL;
    while (cur)
    {
        //记录p下一个节点
        p = cur->next;
        //将当前节点指向前驱
        cur->next = pre;
        //解决掉了 移位
        pre = cur;
        cur = p;
    }
    //将头节点连接到最后一个节点
    L->next = pre;
}
//题6,一个带头节点的链表,设计一个算法让他有序递增
int desc(LinkList &L)
{
    //采用直接插入排序算法
    LinkList pre, cur, L1, L2, p;
    cur = L->next->next;
    InitLinkList(L1);
    //处理第一个节点
    L1->next = L->next;
    L1->next->next = NULL;
    //当cur没有遍历完时
    while (cur)
    {
        L2 = L1->next;
        pre = L1;
        //插入到比这个节点大的第一个
        while (L2 && cur->data > L2->data)
        {
            pre = L2;
            L2 = L2->next;
        }
        if (!L2)
        {
            pre->next = cur;
            cur = cur->next;
        }
        else
        {
            //记录cur的下一个节点
            p = cur->next;
            //将L2的前向节点指向pre
            cur->next = L2;
            pre->next = cur;
            cur = p;
        }
    }
    L = L1;
}
//题七,设一个带表头结点的单链表L,编写一个函数,删除表中给定介于两者值之间的所有数
int delRange(LinkList &L, int x, int y)
{
    LinkList pre, cur, p;
    cur = L->next;
    pre = L;
    //在范围内就直接跳过,然后用前驱连接到后一个
    while (cur)
    {
        if (cur->data >= x && cur->data <= y)
        {
            p = cur;
            cur = cur->next;
            pre->next = cur;
            free(p);
        }
        else
        {
            pre = cur;
            cur = cur->next;
        }
    }
}
//题8寻找公共节点的时候,应该想到拓扑结构是Y型
LinkList findCommon(LinkList &L1, LinkList &L2)
{
    LinkList n, m;
    n = L1->next;
    m = L2->next;
    while (n->data != m->data)
    {
        if (!n || !m)
        {
            if (!n)
                n = L2;
            if (!m)
                m = L1;
        }
        else
        {
            n = n->next;
            m = m->next;
        }
    }
    return m;
}
//题9,以此寻找最小的节点释放min值
int releaseMin(LinkList &L)
{
    //用来寻找最小值的前驱
    LinkList pre, cur, min, minPre;
    cur = L->next;
    while (cur)
    {
        pre = L;
        min = L->next;
        // minPre = min;
        while (cur)
        { //更新min
            if (cur && cur->data <= min->data)
            {
                minPre = pre;
                min = cur;
            }
            pre = cur;
            //最后一个容易丢掉
            cur = cur->next;
        };
        //删除cur节点
        printf("del:%d", min->data);
        if (minPre != min)
        {
            minPre->next = min->next;
        }
        //处理最小值节点在最头部的情况
        else
        {
            L->next = min->next;
        }
        free(min);
        cur = L->next;
    }
    //最后释放头节点
    free(L);
    return 0;
}
// 10.分裂链表,将一个带头节点的链表分解成两个带头节点的链表,A中为奇数,B中为偶数
LinkList devideList(LinkList &L)
{
    LinkList cur, pre, L1, q;
    int flag = 1;
    cur = L->next;
    //这里没有初始化会不会是要自己写初始化函数
    InitLinkList(L1);
    // 同时处理两个链表的节点关系
    while (cur)
    {
        if (flag % 2 == 0)
        { //如果是奇数,就把这个节点连接到L1上
            pre->next = cur->next;
            q = cur->next;
            cur->next = L1->next;
            L1->next = cur;
            cur = q;
        }
        else
        { //如果是偶数就跳过
            pre = cur;
            cur = cur->next;
        }
        flag++;
    }
    return L1;
}
//题11,利用尾插法来建立L1
LinkList devideTail(LinkList &L)
{
    //尾插法,需要一个节点来保存L1的尾节点
    LinkList L1, pre, tail, cur;
    int flag = 1;
    cur = L->next;
    InitLinkList(L1);
    tail = L1;
    while (cur)
    {
        if (flag % 2 == 0)
        { //在L1尾部插入一个元素,并且让这个元素与L断链
            pre->next = cur->next;
            tail->next = cur;
            tail = cur;
            tail->next = NULL;
            cur = pre->next;
        }
        else
        {
            pre = cur;
            cur = cur->next;
        }
        flag++;
    }
    return L1;
}
//题12,递增有序的单链表中,有相同的元素存在,去掉不存在的元素
int orderLink(LinkList &L)
{
    LinkList pre, cur, q;
    pre = L;
    cur = L->next;
    while (cur)
    {
        if (pre->data == cur->data)
        {
            //如果前驱等于当前的,删除当前的
            pre->next = cur->next;
            q = cur;
            cur = cur->next;
            free(q);
        }
        else
        {
            pre = cur;
            cur = cur->next;
        }
    }
    return 0;
}
//题13 将两个递增的单链表,归并成一个元素值递减的单链表,并要求用原来的节点存放
//用个数组排序后?修改节点数据？ 用头插法
LinkList mergeOrder(LinkList &L1, LinkList &L2)
{
    //以L3为主体,然后利用头插法来做
    LinkList L3;
    LinkList pt1, pt2, p;
    InitLinkList(L3);
    pt1 = L1->next;
    pt2 = L2->next;
    //首先将两个单链表长度都存在的遍历完
    while (pt2 && pt1)
    {
        if (pt1->data <= pt2->data)
        {                         //将pt1头插到L3后
            p = pt1->next;        //记录pt1的后向节点,防止断链
            pt1->next = L3->next; //改变pt1的后向指针
            L3->next = pt1;       //将头节点拼起来
            pt1 = p;
        }
        else
        {
            p = pt2->next;
            pt2->next = L3->next;
            L3->next = pt2;
            pt2 = p;
        }
    }
    //哪个链表非空,处理哪个
    if (pt2)
    { //将pt2直接赋给pt1这样运算方便
        pt1 = pt2;
    }
    while (pt1)
    {
        p = pt1->next;
        pt1->next = L3->next;
        L3->next = pt1;
        pt1 = p;
    }
    return L3;
}

//题14,A,B是两个单链表,元素依次递增,设计一个算法从公共元素产生单链表C
LinkList commonC(LinkList &L1, LinkList &L2)
{
    LinkList pt1, pt2, L3, p, pre;
    pt1 = L1;
    pt2 = L2;
    InitLinkList(L3);
    while (pt1->next && pt2->next)
    {
        if (pt1->next->data > pt2->next->data) //如果pt1大,就后移pt2
        {
            pt2 = pt2->next;
        }
        else if (pt1->next->data < pt2->next->data)
        {
            pt1 = pt1->next;
        }
        else
        { //找到了公共节点,不破坏是不是就是说新生成节点,头插法插入L3
            p = (LinkList)malloc(sizeof(Node));
            p->data = pt1->next->data;
            pre = L3->next;
            L3->next = p;
            p->next = pre;
            //找到公共节点后两个都要往下走
            pt1 = pt1->next;
            pt2 = pt2->next;
        }
    }
    return L3;
}
// 15题两个链表A和B分别表示两个集合,其元素递增排列,编写函数,算AB交集
int intersetion(LinkList &L1, LinkList &L2)
{ //使用归并排序,值相同的插到L1上,其他节点全部释放;
    LinkList pt1, pt2, a, q;
    pt1 = L1->next;
    pt2 = L2->next;
    a = L1;
    while (pt1 && pt2)
    { //遍历两者
        if (pt1->data == pt2->data)
        { //假如两者相等的话,就把上个连接到
            a->next = pt2;
            a = pt2;
            q = pt1;
            pt1 = pt1->next;
            free(q);
            pt2 = pt2->next;
        }
        else if (pt1->data < pt2->data)
        {
            q = pt1;
            pt1 = pt1->next;
            free(q);
        }
        else
        {
            q = pt2;
            pt2 = pt2->next;
            free(q);
        }
    }
    while (pt1)
    {
        q = pt1;
        pt1 = pt1->next;
        free(q);
    }
    while (pt2)
    {
        q = pt2;
        pt2 = pt2->next;
        free(q);
    }
    a->next = NULL; // 最后一步很重要,只有因为需要把指向节点的后继指针清空
}
// 16题两个整数序列存入单链表中,判断是不是连续子序列
int isSequence(LinkList &L, LinkList &L1)
{
    LinkList pt1, pt2, exper1, exper2;
    pt1 = L->next;
    pt2 = L1->next;
    while (pt1)
    {
        if (pt1->data == pt2->data)
        { //如果两者的数据相同试探指针开始试探
            exper2 = pt2->next;
            exper1 = pt1->next;
            while (exper1 && exper2)
            {
                if (exper1->data == exper2->data)
                {
                    exper1 = exper1->next;
                    exper2 = exper2->next;
                }
                else
                {
                    break;
                }
            }
            if (!exper1 || !exper2)
            {
                return 1;
            }
        }
        pt1 = pt1->next;
    }
    return 0;
}
// 题17 设计一个算法来判断带头节点的循环双链表是否对称
int judgeCir(CirList &L1)
{
    //通过尾节点和头节点同时开始遍历,到头节点和尾节点的时候应该完全一样
    CirList head, tail;
    head = L1;
    tail = L1->next;
    //循环双链表可以通过L->prior找到尾节点。
    while (tail->next != head)
    { //找到为节点
        tail = tail->next;
    }
    head = head->next;
    while (head != tail)
    {
        if (head->data == tail->data)
        {
            head = head->next;
            tail = tail->prior;
        }
        else
        {
            printf("This CirList is not Symmetrical");
            return 0;
        }
    }
    printf("This CirList is  Symmetrical");
}

//题18 两个循环单链表,链表头指针为h1和h2将h2链接到h1后
int ConnectCirLinkList(LinkList &L1, LinkList &L2)
{
    //找L1的tail
    LinkList tail;
    tail = L1->next;
    while (tail->next != L1)
    {
        tail = tail->next;
    }
    tail->next = L2->next;
    tail = tail->next;
    // L2的尾节点的next指向L1
    while (tail->next != L2)
    {
        tail = tail->next;
    }
    tail->next = L1;
}
//题19,带头节点的循环单链表,反复找到结点值最小的结点输出 del 懂的都懂,记录当前结点的前向结点
int delMinCirList(LinkList &L)
{
    LinkList pre, min, p;
    pre = L;
    min = L;
    //判断条件->表是否为空
    while (L->next != L)
    {
        if (pre->next == L) //遍历完一轮就删除最小值的结点
        {
            p = min->next;
            min->next = min->next->next;
            printf("del->%d", min->next->data);
            free(p);
        }
        if (pre->next->data < min->next->data)
        {
            min = pre;
        }
        pre = pre->next;
    }
}

int main()
{
    CirList L;
    InitCirList(L);
    for (int i = 0; i < 10; i++)
    {
        InsertCirList(L, i);
    }
    showCirList(L);
}