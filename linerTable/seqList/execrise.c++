#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 5
//从顺序表中删除具有最小值的元素并由函数返回被删元素的值。空出的以为由最后一个元素填补
typedef int ElemType;
//我感觉动态申请应该再申请5吧
typedef struct Sqlist
{
    int *head;
    int Length;
    //用Size来记录现在拥有的空间
    int Size;
} Sqlist;

//可以通过指定函数类型是结构体来返回一个顺序表
void InitList(Sqlist &L)
{
    //申请顺序表的空间,通过对L下标的顺序数字来访问数据
    (L).head = (int *)malloc(SIZE * sizeof(int));
    (L).Size = 5;
    (L).Length = 0;
    //通过Size来记录当前顺序表占用的空间
    if (!(L).head)
    {
        printf("初始化失败");
        exit(0);
    }
}

void ShowList(Sqlist L)
{
    //如果只是遍历的话好像没什么限制
    for (int i = 0; i < (L).Length; i++)
    {
        printf("%d->", (L).head[i]);
        /* code */
    };
    printf("\n");
}

//动态链表的插入应该是关键了
int Insert(Sqlist &L, int e)
{
    Sqlist p;
    if ((L).Size <= (L).Length)
    {
        //这个申请新空间都是不是还要把东西都搬过来
        p.head = (int *)malloc(((L).Size + 5) * sizeof(int));
        p.Size = (L).Size + 5;
        p.Length = (L).Length;
        for (int i = 0; i < p.Length; i++)
        {
            //利用p节点将原来的数据搬过来
            p.head[i] = (L).head[i];
        };
        p.head[p.Length] = e;
        p.Length++;
        (L).Length++;
        L = p;
    }
    else
    {
        (L).head[(L).Length] = e;
        (L).Length++;
    }
    return 0;
}
//题一,用于删除最小元素,并由最大元素替换
int delMin(Sqlist &L)
{
    int min, MinIndex = 0;
    //进行遍历找到最小的元素
    for (int i = 1; i < (L).Length; i++)
    {
        if ((L).head[i] < (L).head[MinIndex])
        {
            MinIndex = i;
        }
    }
    //进行最小元素的替换
    for (int j = 0; j < (L).Length; j++)
    {
        min = (L).head[MinIndex];
        /* code */
        if ((L).head[j] == min)
        {
            (L).head[j] = (L).head[(L).Length - 1];
        }
        (L).Length--;
    }
    return min;
}

//题目二,设计一个高效算法将顺序表L的所有元素逆置;
int Reverse(Sqlist &L)
{
    //左右指针对碰
    int left = 0, right = (L).Length - 1;
    int tmp;
    while (left <= right)
    {
        tmp = (L).head[left];
        (L).head[left] = (L).head[right];
        (L).head[right] = tmp;
        left++;
        right--;
        /* code */
    }
    return 1;
}
//题三,删除所有线性表中值为X的值
int delAllX(Sqlist L, int X)
{
    //记录线性表前面为X的值
    int flag = 0;
    for (int i = 0; i < (L).Size; i++)
    {
        if ((L).head[i] != X)
        {
            for (int j = 0; j < flag; j++)
            {
                (L).head[i - flag] = (L).head[i];
            }
        }
        else
        {
            flag++;
        }
    }
    //! import 移动后,游标遍历完后数组长度应该减少。
    (L).Length = (L).Length - flag;
}
//题四,删除有序顺序表中,给定值在(m,n)范围内的所有元素,判断顺序表为空或者s,t范围不合理
int delRange(Sqlist L, int m, int n)
{
    //判断L是否为空
    if (!(L).head)
    {
        printf("111");
        return 0;
    }
    //判断(m,n)的范围是否合理
    if (n < (L).head[0] && m > (L).head[(L).Length - 1])
    {
        printf("222");
        return 0;
    }
    int left = 0, right = (L).Length - 1;
    //找到要删除的中间段
    while ((L).head[left] < m || (L).head[right] > n)
    {
        //在他前面有多少不满足条件的
        if ((L).head[left] < m)
            left++;
        //在他后面有多少不满足条件的
        if ((L).head[right] > n)
            right--;
    }
    //思路要清晰,想到左右游标应该是怎么样的
    for (int i = left; i <= left + (L).Length - right; i++)
    {
        (L).head[i] = (L).head[right + i - left + 1];
    }
    (L).Length = (L).Length - (right - left) - 1;
}
//题六去重,删除顺序表中的重复项
int delDulicate(Sqlist &L)
{
    int i = 0, j = 0;
    for (; j < (L).Length; j++)
    {
        if ((L).head[j] != (L).head[j + 1])
        {
            (L).head[i] = (L).head[j];
            i++;
        }
    }
    (L).Length = i;
}
//题七,把两个有序链表合并成一个有序列表
//本次思路为,先将两链表的公共部分合并,然后再遍历没有遍历完的链表,将没有遍历完的放进去。
int mergeListSort(Sqlist &L1, Sqlist &L2)
{
    int one = 0, two = 0, i = 0;
    Sqlist L3;
    InitList(L3);
    if (!(L1).head)
        (L3) = (L2);
    if (!(L2).head)
        (L3) = (L1);
    while (one < (L1).Length || two < (L2).Length)
    {
        if ((L1).head[one] < (L2).head[two] && one <= (L1).Length - 1)
        {
            Insert(L3, (L1).head[one]);
            one++;
        }
        if ((L1).head[one] >= (L2).head[two] && two <= (L2).Length - 1)
        {
            Insert(L3, (L2).head[two]);
            two++;
        }
    }
    while (one < L1.Length && two == L2.Length)
    {
        Insert(L3, (L1).head[one]);
        one++;
    }
    while (two < L2.Length && one == L1.Length)
    {
        Insert(L3, (L2).head[two]);
        two++;
    }
    L1 = L3;
    //释放链表内存
}
//题八 在一维数组中存放两个线性表编写一个函数,将数组中两个函数的位置互换
//返回一合并后的链表
Sqlist mergeList(Sqlist &L, Sqlist &L1)
{
    Sqlist L4;
    //如果一个链表需要插入的之前,需要先初始化一下
    InitList(L4);
    for (int i = 0; i < L.Length; i++)
    {
        Insert(L4, L.head[i]);
    }
    for (int j = 0; j < L1.Length; j++)
    {
        Insert(L4, L1.head[j]);
    }
    return L4;
}
//将两个线性表对调,原地对换->拥有的问题是数据会覆盖
//利用排序的多次对换
int reverse(Sqlist &L3, int left, int right)
{
    int tmp;
    if (left > right || right > L3.Length)
        return 0;
    //取中间进行兑换
    int mid = (left + right) / 2;
    for (int i = 0; i < mid - left; i++)
    {
        tmp = L3.head[left + i];
        L3.head[left + i] = L3.head[right - i];
        L3.head[right - i] = tmp;
    }
}
void Exchange(Sqlist &L3, int m, int n)
{
    //首先将左右两边对换
    reverse(L3, 0, m + n - 1);
    ShowList(L3);
    //再将表二兑换;
    reverse(L3, 0, n - 1);
    ShowList(L3);
    //再将表一对换;
    reverse(L3, n, n + m - 1);
}

//题九:线性表中的元素有序递增,并且按照顺序存储在计算机内,设置一个算法完成用最少时间内查找X元素。
//若找到将其于后继元素为交换
int findX(Sqlist &L, int x)
{
    int mid, tmp;
    int left = 0, right = L.Length - 1;
    //这里是需要相等的
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (x > L.head[mid])
        {
            //决定是去mid的左半部分查询还是右半部分查询
            left = mid + 1;
        }
        else if (x < L.head[mid])
        {
            right = mid - 1;
        }
        if (L.head[mid] == x)
        {
            break;
        }
    }

    if (L.head[mid] == x && mid != L.Length - 1)
    //和后继元素交换位置
    {
        tmp = L.head[mid];
        L.head[mid] = L.head[mid + 1];
        L.head[mid + 1] = tmp;
        return mid;
    }
    if (left > right)
    //将该元素插到表中
    {
        Insert(L, x);
        //决定是左插还是右插
        for (int j = L.Length - 1; j > mid; j--)
        {
            L.head[j] = L.head[j - 1];
        }
        L.head[mid] = x;
    }
}
//题10,将n个元素组成的顺序表进行左移
int shiftLeft(Sqlist &L, int q)
{
    //思路把全部元素逆置,然后把左移单位的数组逆置,然后把靠左边的数组逆置
}
//题11 找出主元素 投票办法
int findMain(Sqlist &L)
{
    int flag = 0, main = L.head[0];
    for (int i = 1; i < L.Length; i++)
    {
        if (main == L.head[i])
            flag++;
        else
        {
            flag--;
        }
        if (!flag)
        {
            main = L.head[i];
        }
    }
    printf("main:", main);
    return main;
}
// 12题,给定一个n的数组,找出未出现的最小正整数,要求时间效率比较高,故利用空间换时间
int findMin(Sqlist L)
{
    int i, *B;
    B = (int *)malloc(sizeof(int) * L.Length);
    //给某个申请的存储空间充填重复元素.
    memset(B, 0, sizeof(int) * L.Length);
    for (int j = 0; j < L.Length; j++)
    {
        if (L.head[j] <= L.Length && L.head[i] > 0)
        {
            //把L包含值对应的方块赋值为1
            B[L.head[j]-1]=1;
        }
    }
    //找到第一个为0的值
    for (int i = 0; i < L.Length; i++)
    {
        if(B[i]==0) break;
    }
    return i+1;
}

//题13 定义
int main()
{
    Sqlist L;
    Sqlist L1;
    Sqlist L3;
    //  传入的应该是头节点的地址
    InitList(L);
    InitList(L1);
    for (int j = 0; j < 10; j++)
    {
        Insert(L, 8);
    }
    for (int i = 0; i < 5; i++)
    {
        Insert(L, i);
    }
    ShowList(L);
    findMain(L);
    ShowList(L);
}