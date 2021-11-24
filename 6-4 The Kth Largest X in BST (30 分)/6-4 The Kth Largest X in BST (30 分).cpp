// 6-4 The Kth Largest X in BST (30 分).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



typedef struct TNode* BinTree;
struct TNode {
    int Key;
    BinTree Left;
    BinTree Right;
};

BinTree BuildTree(); /* details omitted */
BinTree InsertInto(BinTree T, int X);
int KthLargest(BinTree T, int X);

BinTree InsertInto(BinTree T, int X)
{
    if (!T)
    {
        BinTree b = (BinTree)malloc(sizeof(struct TNode));
        b->Key = X;
        b->Left = b->Right = NULL;
        return b;
    }
    if (X < T->Key) { T->Left = InsertInto(T->Left, X); }
    else if (X > T->Key) { T->Right = InsertInto(T->Right, X); }
    return T;
}


BinTree BuildTree()
{
    int value;
    scanf("%d", &value);
    if (value == 0) { return NULL; }
    BinTree b = (BinTree)malloc(sizeof(struct TNode));
    b->Key = value;
    b->Left = BuildTree();
    b->Right = BuildTree();
    return b;
}

int main()
{
    BinTree T;
    int X;

    T = BuildTree();
    scanf("%d", &X);
    printf("%d", KthLargest(T, X));

    return 0;
}
/* Your function will be put here */

struct TNode* FindMin(BinTree T);
struct TNode* FindMax(BinTree T);
BinTree DeleteFrom(BinTree T, int X);

struct TNode* FindMin(BinTree T)
{
    if (!T) { return NULL; }
    struct TNode* p = T;
    for (; p->Left; p = p->Left)
    {
        ;//do nothing
    }
    return p;
}

struct TNode* FindMax(BinTree T)
{
    if (!T) { return NULL; }
    struct TNode* p = T;
    for (; p->Right; p = p->Right)
    {
        ;//do nothing
    }
    return p;
}

BinTree DeleteFrom(BinTree T, int X)
{
    if (!T) { return NULL; }
    if (X < T->Key) { T->Left = DeleteFrom(T->Left, X); }
    else if (X > T->Key) { T->Right = DeleteFrom(T->Right, X); }
    else if (X == T->Key)
    {
        if (!T->Left && !T->Right)
        {
            free(T);
            return NULL;
        }
        else if (T->Left)
        {
            struct TNode* tmp = FindMax(T->Left);
            T->Key = tmp->Key;
            T->Left = DeleteFrom(T->Left, tmp->Key);
            return T;
        }
        else if (T->Right)
        {
            struct TNode* tmp = FindMin(T->Right);
            T->Key = tmp->Key;
            T->Right = DeleteFrom(T->Right, tmp->Key);
            return T;
        }
    }
    return T;
}

int KthLargest(BinTree T, int X)
{
    BinTree p;
    int cnt = 0;
    while ((p = FindMax(T)) != NULL && p->Key != X)
    {
        T = DeleteFrom(T, p->Key);
    }
    if (!p) { return 0; }
    return cnt + 1;
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
