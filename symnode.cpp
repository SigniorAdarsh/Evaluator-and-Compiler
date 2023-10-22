/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"
// Write your code below this line
SymNode::SymNode()
{
    key = "";
    height = -1;
    par = NULL;
    left = NULL;
    right = NULL;
}

SymNode::SymNode(string k)
{
    key = k;
    height = 0;
    par = NULL;
    left = NULL;
    right = NULL;
}
int htupdater(SymNode *root)
{
    if (root == NULL)
    {
        return -1;
    }
    else
        return root->height;
}
SymNode *SymNode::RightRightRotation()
{
    SymNode *curr = left->par;
    SymNode *nr = left;
    left = nr->right;
    nr->right = curr;
    if (nr != NULL && curr != NULL)
        nr->par = curr->par;
    if (curr != NULL)
        curr->par = nr;
    if (left != NULL)
        left->par = curr;
    curr->height=1+max(htupdater(curr->left),htupdater(curr->right));
    nr->height=1+max(htupdater(nr->left),htupdater(nr->right));
    return nr;
}

SymNode *SymNode::LeftLeftRotation()
{
    SymNode *curr = right->par;
    SymNode *nr = right;
    right = nr->left;
    nr->left = curr;
    if (nr != NULL)
        nr->par = curr->par;
    if (curr != NULL)
        curr->par = nr;
    if (right != NULL)
        right->par = curr;
    curr->height=1+max(htupdater(curr->left),htupdater(curr->right));
    nr->height=1+max(htupdater(nr->left),htupdater(nr->right));
    return nr;
}

SymNode *SymNode::LeftRightRotation()
{
    left = left->LeftLeftRotation();
    return RightRightRotation();
}

SymNode *SymNode::RightLeftRotation()
{
    right = right->RightRightRotation();
    return LeftLeftRotation();
}

SymNode::~SymNode()
{
    par = NULL;
    left = NULL;
    right = NULL;
    address = -1;
    height = -1;
    // khali??
}