// 6-2 Percolate Up and Down (20 分).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
#define MinData -1

typedef struct HeapStruct* PriorityQueue;
struct HeapStruct {
    ElementType* Elements;
    int Capacity;
    int Size;
};

PriorityQueue Initialize(int MaxElements); /* details here */
void PercolateUp(int p, PriorityQueue H);
void PercolateDown(int p, PriorityQueue H);

PriorityQueue Initialize(int MaxElements)
{
    PriorityQueue pq = (PriorityQueue)malloc(sizeof(HeapStruct));
    pq->Capacity = MaxElements;
    pq->Size = 0;
    pq->Elements = (ElementType*)calloc(MaxElements + 1, sizeof(ElementType));
    return pq;
}

void Insert(ElementType X, PriorityQueue H)
{
    int p = ++H->Size;
    H->Elements[p] = X;
    PercolateUp(p, H);
}

ElementType DeleteMin(PriorityQueue H)
{
    ElementType MinElement;
    MinElement = H->Elements[1];
    H->Elements[1] = H->Elements[H->Size--];
    PercolateDown(1, H);
    return MinElement;
}

int main()
{
    int n, i, op, X;
    PriorityQueue H;

    scanf("%d", &n);
    H = Initialize(n);
    for (i = 0; i < n; i++) {
        scanf("%d", &op);
        switch (op) {
        case 1:
            scanf("%d", &X);
            Insert(X, H);
            break;
        case 0:
            printf("%d ", DeleteMin(H));
            break;
        }
    }
    printf("\nInside H:");
    for (i = 1; i <= H->Size; i++)
        printf(" %d", H->Elements[i]);
    return 0;
}

/* Your function will be put here */

void PercolateUp(int p, PriorityQueue H)
{
    int i = p, j = p / 2;
    while (j >= 1)
    {
        if (H->Elements[j] > H->Elements[i])
        {
            ElementType tmp = H->Elements[j];
            H->Elements[j] = H->Elements[i];
            H->Elements[i] = tmp;
            i = j;
            j = j / 2;
        }
        else { break; }
    }
}

void PercolateDown(int p, PriorityQueue H)
{
    int i = p, j = p * 2;
    while (j <= H->Size)
    {
        //找下面两个最小的
        if (j + 1 <= H->Size && H->Elements[j + 1] < H->Elements[j]) { j = j + 1; }
        if (H->Elements[i] > H->Elements[j])
        {
            //交换
            ElementType tmp = H->Elements[j];
            H->Elements[j] = H->Elements[i];
            H->Elements[i] = tmp;
            i = j;
            j = j * 2;
        }
        else { break; }
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
