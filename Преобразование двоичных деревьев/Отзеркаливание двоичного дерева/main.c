#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef int TValue;

struct TbinTree
{
    TValue Value;
    struct TbinTree* Left;
    struct TbinTree* Right;
};

typedef struct TbinTree* TBinTree;

bool IsEmptyTree(TBinTree tree)
{
    return tree == NULL;
}

TBinTree CreateLeaf(TValue value)
{
    TBinTree tree = malloc(sizeof(*tree));
    assert(!IsEmptyTree(tree));

    tree->Value = value;
    tree->Left = NULL;
    tree->Right = NULL;

    return tree;
}

TBinTree ConvertArrayToBinaryTree(int size, TValue* array)
{
    if (size <= 0) 
    {
        return NULL;
    }
    else 
    {
        int middle = size / 2;
        TBinTree tree = CreateLeaf(array[middle]);
        tree->Left = ConvertArrayToBinaryTree(middle, array);
        tree->Right = ConvertArrayToBinaryTree(size - middle - 1, array + middle + 1);
        return tree;
    }
}

void DestroyTree(TBinTree* tree)
{
    if(!IsEmptyTree(*tree))
    {
        DestroyTree(&(*tree)->Left);
        DestroyTree(&(*tree)->Right);
        free(*tree);
    }
}

TBinTree MirrorTree(TBinTree tree)
{
    if(IsEmptyTree(tree))
    {
        return NULL;
    }

    TBinTree mirrorTree = CreateLeaf(tree->Value);
    mirrorTree->Left = MirrorTree(tree->Right);
    mirrorTree->Right = MirrorTree(tree->Left);

    return mirrorTree;
}

int main()
{
    TValue array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    TBinTree tree = ConvertArrayToBinTree(sizeof(array) / sizeof(*array), array);
    TBinTree mirrorTree = MirrorTree(tree);

    DestroyTree(&tree);
    DestroyTree(&mirrorTree);
}