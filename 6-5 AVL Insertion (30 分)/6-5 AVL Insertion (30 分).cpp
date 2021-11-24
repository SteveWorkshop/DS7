// 6-5 AVL Insertion (30 分).cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode* PtrToAVLNode;
struct AVLNode {
    int Key;
    PtrToAVLNode Left;
    PtrToAVLNode Right;
    int Height;
};
typedef PtrToAVLNode AVLTree;

AVLTree Insert(AVLTree T, int Key);
void PostOrderPrint(AVLTree T); /* details here */
void InOrderPrint(AVLTree T);   /* details here */

void _PostOrderPrint(AVLTree T)
{
    if (!T) { return; }
    _PostOrderPrint(T->Left);
    _PostOrderPrint(T->Right);
    printf(" %d", T->Key);
}

void PostOrderPrint(AVLTree T)
{
    printf("Post-order:");
    _PostOrderPrint(T);
    printf("\n");
}

void _InOrderPrint(AVLTree T)
{
    if (!T) { return; }
    _InOrderPrint(T->Left);
    printf(" %d", T->Key);
    _InOrderPrint(T->Right);
}

void InOrderPrint(AVLTree T)
{
    printf("In-order:");
    _InOrderPrint(T);
    printf("\n");
}

int main()
{
    int N, Key, i;
    AVLTree T = NULL;

    scanf("%d", &N);
    for (i = 0; i < N; i++) {
        scanf("%d", &Key);
        T = Insert(T, Key);
    }
    PostOrderPrint(T);
    InOrderPrint(T);

    return 0;
}
/* Your function will be put here */

#define MY_MAX(a, b) ((a) > (b)) ? (a) : (b)

int getHight(PtrToAVLNode root)
{
    if (!root) { return 0; }
    return root->Height;
}

int getBalanceFactor(PtrToAVLNode root)
{
    return getHight(root->Left)-getHight(root->Right);
}

void updateHight(PtrToAVLNode root)
{
    root->Height = MY_MAX(getHight(root->Left), getHight(root->Right)) + 1;
}

AVLTree leftRotation(AVLTree root)
{
    AVLTree tmp = root->Right;
    root->Right = tmp->Left;
    tmp->Left = root;
    updateHight(root);
    updateHight(tmp);
    return tmp;
}

AVLTree rightRotation(AVLTree root)
{
    AVLTree tmp = root->Left;
    root->Left = tmp->Right;
    tmp->Right = root;
    updateHight(root);
    updateHight(tmp);
    return tmp;
}

AVLTree Insert(AVLTree T, int Key)
{
    if (!T) 
    {
        AVLTree root = (AVLTree)malloc(sizeof(struct AVLNode));
        root->Key = Key;
        root->Height = 1;
        root->Left = root->Right = NULL;
        return root;
    }
    if (Key < T->Key) 
    { 
        T->Left = Insert(T->Left, Key); 
        updateHight(T);
        if (getBalanceFactor(T) == 2)
        {
            if (getBalanceFactor(T->Left) == 1)
            {
                T = rightRotation(T);
            }
            else if (getBalanceFactor(T->Left) == -1)
            {
                T->Left = leftRotation(T->Left);
                T = rightRotation(T);
            }
        }
        return T;
    }
    else if (Key > T->Key) 
    { 
        T->Right = Insert(T->Right, Key); 
        updateHight(T);
        if (getBalanceFactor(T) == -2)
        {
            if (getBalanceFactor(T->Right) == -1)
            {
                T = leftRotation(T);
            }
            else if (getBalanceFactor(T->Right) == 1)
            {
                T->Right = rightRotation(T->Right);
                T = leftRotation(T);
            }
        }
        return T;
    }
    
    return T;
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
