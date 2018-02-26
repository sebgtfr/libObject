
#include <stdlib.h>
#include <string.h>
#include "BTree.h"

t_bool const                    g_false = FALSE;
t_bool const                    g_true = TRUE;

t_bTree const                   g_nullBTree = _BTREE_NULL_;

void                            bTree_ctor(t_bTree *this,
                                           unsigned int const sizeElem,
                                           t_operatorCMP const cmp,
                                           t_dtor const dtor)
{
    *this = g_nullBTree;
    this->_sizeElem = sizeElem;
    this->__CMP__ = cmp;
    this->__DTOR__ = dtor;
}

void                            bTree_dtorNode(t_bTreeNode node,
                                               t_dtor const dtor)
{
    if (node)
        {
            bTree_dtorNode(node->_left, dtor);
            bTree_dtorNode(node->_right, dtor);
            if (dtor)
                dtor(&node->_data);
            free(node);
        }
}

static void                     bTree_place(t_bTree *this, t_bTreeNode node)
{
    if (!this->_root)
        this->_root = node;
    else
        {
            t_bTreeNode root = this->_root;

            while (root != node)
                {
                    if (this->__CMP__(&root->_data, &node->_data) > 0)
                        {
                            if (!root->_left)
                                root->_left = node;
                            root = root->_left;
                        }
                    else
                        {
                            if (!root->_right)
                                root->_right = node;
                            root = root->_right;
                        }
                }
        }
    ++this->_size;
}

t_bool                          bTree_push(t_bTree *this, void const *data)
{
    if (!this->__CMP__)
        return g_false;

    t_bTreeNode                 newNode = malloc(sizeof(struct s_bTreeNode)
                                                 + this->_sizeElem);

    if (newNode)
        {
            newNode->_left = NULL;
            newNode->_right = NULL;
            (void)memcpy(&newNode->_data, data, this->_sizeElem);
            bTree_place(this, newNode);
            return g_true;
        }
    return g_false;
}

unsigned int                    bTree_depthNode(t_bTreeNode node)
{
    if (node)
        {
            unsigned int                left = bTree_depthNode(node->_left);
            unsigned int                right = bTree_depthNode(node->_right);

            return 1 + ((left > right) ? left : right);
        }
    return 0;
}

t_bTreeNode                     bTree_getNodeByDepth(t_bTreeNode node,
                                                     unsigned int depth)
{
    if (node && depth)
        {
            --depth;

            t_bTreeNode         left = bTree_getNodeByDepth(node->_left, depth);
            t_bTreeNode         right = bTree_getNodeByDepth(node->_right, depth);

            return (left) ? left : right;
        }
    return node;
}

static void                     bTree_sortNode(t_bTree *this, t_bTreeNode node,
                                               t_bTreeNode newRoot)
{
    if (node)
        {
            bTree_sortNode(this, node->_left, newRoot);
            bTree_sortNode(this, node->_right, newRoot);
            if (node != newRoot)
                {
                    node->_left = NULL;
                    node->_right = NULL;
                    bTree_place(this, node);
                }
        }
}

void                            bTree_sort(t_bTree *this)
{
    if (this->_root)
        {
            unsigned int        depthLeft = bTree_depthNode(this->_root->_left);
            unsigned int        depthRight = bTree_depthNode(this->_root->_right);
            int                 diff = depthLeft - depthRight;

            if (((diff < 0) ? -diff : diff) > 1)
                {
                    unsigned int    depth = (depthLeft + depthRight) / 2;
                    t_bTreeNode     newRoot = bTree_getNodeByDepth((diff < 0) ? this->_root->_right : this->_root->_left, depth - 1);

                    if (newRoot && newRoot != this->_root)
                        {
                            t_bTreeNode        oldRoot = this->_root;

                            this->_root = NULL;
                            if (bTree_push(this, &newRoot->_data))
                                {
                                    bTree_sortNode(this, oldRoot, newRoot);
                                    this->_size = (this->_size + 1) / 2;
                                    free(newRoot);
                                }
                            else
                                this->_root = oldRoot;
                        }
                }
        }
}

void                            bTree_foreachNode(t_bTreeNode node,
                                                  void (*foreach)(void *))
{
    if (node && foreach)
        {
            bTree_foreachNode(node->_left, foreach);
            foreach(&node->_data);
            bTree_foreachNode(node->_right, foreach);
        }
}

/* Special functions */

int                             bTree_cmpInt(void const *iPtr1,
                                             void const *iPtr2)
{
    int const                   i1 = *(int *)iPtr1;
    int const                   i2 = *(int *)iPtr2;

    if (i1 < i2)
        return -1;
    else if (i1 > i2)
        return 1;
    return 0;
}

int                             bTree_cmpLInt(void const *lPtr1,
                                              void const *lPtr2)
{
    int const                   l1 = *(int *)lPtr1;
    int const                   l2 = *(int *)lPtr2;

    if (l1 < l2)
        return -1;
    else if (l1 > l2)
        return 1;
    return 0;
}

int                             bTree_cmpStr(void const *sPtr1,
                                             void const *sPtr2)
{
    return strcmp((char const *)sPtr1, (char const *)sPtr2);
}
