
#include "BTree.h"

void printInt(void *data)
{
    printf("%d\n", *(int *)data);
}

int main(void)
{
    int                         tableau[]={7,5,3,1,2,4};
    t_bTree                     tree;

    BTREE_CTOR(&tree, int, bTree_cmpInt, NULL);
    for (unsigned char i = 0; i < 6; ++i)
        {
            bTree_push(&tree, &tableau[i]);
        }
    bTree_pushValue(&tree, 6);
    bTree_sort(&tree);
    bTree_foreach(&tree, printInt);
    bTree_dtor(&tree);
}
