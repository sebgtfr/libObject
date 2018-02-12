
#ifndef BTREE_H_
# define BTREE_H_

# define FALSE                  0
# define TRUE                   !FALSE

typedef unsigned char           t_bool;

extern t_bool const             g_false;
extern t_bool const             g_true;

# include <string.h>

typedef int                     (*t_operatorCMP)(void const *, void const *);
typedef void                    (*t_dtor)(void *);

typedef struct                  s_bTreeNode
{
    struct s_bTreeNode          *_left;
    struct s_bTreeNode          *_right;
    char                        _data[0];
}                               *t_bTreeNode;

typedef struct                  s_bTree
{
    t_bTreeNode                 _root;
    t_operatorCMP               __CMP__;
    t_dtor                      __DTOR__;
    unsigned int                _size;
    unsigned int                _sizeElem;
}                               t_bTree;

# define _BTREE_NULL_           (t_bTree){(t_bTreeNode)0, (t_operatorCMP)0, (t_dtor)0, 0, 0};

# define BTREE_CTOR(this, type, cmp, dtor) bTree_ctor(this, sizeof(type), cmp, dtor);

extern t_bTree const            g_nullBTree;

extern void                     bTree_ctor(t_bTree *this,
                                           unsigned int const sizeElem,
                                           t_operatorCMP const cmp,
                                           t_dtor const dtor);
extern void                     bTree_dtorNode(t_bTreeNode node,
                                               t_dtor const dtor);
static inline void              bTree_dtor(t_bTree *this)
{
    bTree_dtorNode(this->_root, this->__DTOR__);
};

extern t_bool                   bTree_push(t_bTree *this, void const *data);
static inline t_bool            bTree_pushValue(t_bTree *this,
                                                long int const value)
{
    return bTree_push(this, &value);
};


extern unsigned int             bTree_depthNode(t_bTreeNode node);
static inline unsigned int      bTree_depth(t_bTree *this)
{
    return bTree_depthNode(this->_root);
};

extern void                     bTree_foreachNode(t_bTreeNode node,
                                                  void (*foreach)(void *));
static inline void              bTree_foreach(t_bTree *this,
                                              void (*foreach)(void *))
{
    return bTree_foreachNode(this->_root, foreach);
};


t_bTreeNode                     bTree_getNodeByDepth(t_bTreeNode node,
                                                     unsigned int depth);
void                            bTree_sort(t_bTree *this);

/* Special Functions */

int                             bTree_cmpInt(void const *iPtr1,
                                             void const *iPtr2);
int                             bTree_cmpLInt(void const *lPtr1,
                                              void const *lPtr2);
int                             bTree_cmpStr(void const *sPtr1,
                                             void const *sPtr2);

#endif /* !BTREE_H_ */
