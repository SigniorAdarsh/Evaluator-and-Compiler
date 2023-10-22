/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "minheap.h"
// Write your code below this line

MinHeap::MinHeap()
{
    size = 0;
    root = NULL;
}
void Hipup(HeapNode *node)
{
    if (node->par == NULL)
        return;
    if (node->par->val > node->val)
    {
        int temp = node->val;
        node->val = node->par->val;
        node->par->val = temp;
        Hipup(node->par);
    }
}
void MinHeap::push_heap(int num)
{
    if (size == 0)
    {
        root = new HeapNode(num);
        size++;
        return;
    }
    size++;
    HeapNode *temp = NULL;
    int boom=size;
    int loggy=0;
    while(boom>1)
    {
        boom/=2;
        loggy++;
    }
    boom=size;
    int ml=1;
    for(int i=0;i<loggy;i++)
    {
        ml*=2;
    }
    temp=root;
    HeapNode*papaji=root;
    while(true)
    {
        papaji=temp;
        int byml=boom%ml;
        if(byml<ml/2)
        {
            temp=temp->left;
        }
        else
        {
            temp=temp->right;
        }
        boom%=ml;
        ml/=2;
        if(temp==NULL)
            break;
    }
    temp=papaji;
    if (temp->left == NULL)
    {
        temp->left = new HeapNode(num);
        temp->left->par = temp;
        Hipup(temp->left);
    }
    else
    {
        temp->right = new HeapNode(num);
        temp->right->par = temp;
        Hipup(temp->right);
    }
}
int MinHeap::get_min()
{
    return root->val;
}
void Hipdown(HeapNode *node)
{
    if (node->left == NULL)
        return;
    HeapNode *temp = node->left;
    if (node->right != NULL)
    {
        if (node->right->val < node->left->val)
            temp = node->right;
    }
    if (temp->val < node->val)
    {
        int fff = temp->val;
        temp->val = node->val;
        node->val = fff;
        Hipdown(temp);
    }
}
void MinHeap::pop()
{
    int insize=size;
    size--;
    if (size == 0)
    {
        delete root;
        root = NULL;
        return;
    }
    HeapNode *temp = NULL;
    int boom=insize;
    int loggy=0;
    while(boom>1)
    {
        boom/=2;
        loggy++;
    }
    boom=insize;
    int ml=1;
    for(int i=0;i<loggy;i++)
    {
        ml*=2;
    }
    temp=root;
    HeapNode*papaji=root;
    while(true)
    {
        papaji=temp;
        int byml=boom%ml;
        if(byml<ml/2)
        {
            temp=temp->left;
        }
        else
        {
            temp=temp->right;
        }
        boom%=ml;
        ml/=2;
        if(temp==NULL||ml==1)
            break;
    }
    root->val = temp->val;
    if (papaji->right == NULL)
    {
        delete papaji->left;
        papaji->left = NULL;
    }
    else
    {
        delete papaji->right;
        papaji->right = NULL;
    }
    Hipdown(root);
    // cout<<"HEAP"<<endl;
    // cout<<root->val<<"root"<<endl;
    // cout<<root->left->val<<endl;
    // cout<<root->right->val<<endl;
}
void deltr(HeapNode *node)
{
    if (node == NULL)
    {
        return;
    }
    if (node->left == NULL && node->right == NULL)
    {
        delete node;
        return;
    }
    deltr(node->left);
    deltr(node->right);
    node->left = NULL;
    node->right = NULL;
    delete node;
    return;
}
MinHeap::~MinHeap()
{
    size = 0;
    deltr(root);
}
// int main()
// {
//     MinHeap*pippi=new MinHeap();
//     pippi->push_heap(42);
//     pippi->push_heap(34);
//     pippi->push_heap(22);
//     pippi->push_heap(69);
//     pippi->push_heap(78);
//     pippi->push_heap(103);
//     pippi->push_heap(88);
//     HeapNode*roo=pippi->root;
//     cout<<"printing heap"<<endl;
//     cout<<roo->val<<endl;
//     cout<<roo->left->val<<endl;
//     cout<<roo->right->val<<endl;
//     cout<<roo->left->left->val<<endl;
//     cout<<roo->left->right->val<<endl;
//     cout<<roo->right->left->val<<endl;
//     cout<<roo->right->right->val<<endl;
//     cout<<"printing heap"<<endl;
//     pippi->pop();
//     roo=pippi->root;
//     cout<<roo->val<<endl;
//     cout<<roo->left->val<<endl;
//     cout<<roo->right->val<<endl;
//     cout<<roo->left->left->val<<endl;
//     cout<<roo->left->right->val<<endl;
//     cout<<roo->right->left->val<<endl;
//     cout<<roo->right->right->val<<endl;
//     cout<<"printing heap"<<endl;
//     pippi->pop();
//     roo=pippi->root;
//     cout<<roo->val<<endl;
//     cout<<roo->left->val<<endl;
//     cout<<roo->right->val<<endl;
//     cout<<roo->left->left->val<<endl;
//     cout<<roo->left->right->val<<endl;
//     cout<<"printing heap"<<endl;
//     pippi->pop();
//     roo=pippi->root;
//     cout<<roo->val<<endl;
//     cout<<roo->left->val<<endl;
//     cout<<roo->right->val<<endl;
//     cout<<roo->left->left->val<<endl;
//     cout<<"printing heap"<<endl;
//     pippi->pop();
//     roo=pippi->root;
//     cout<<roo->val<<endl;
//     cout<<roo->left->val<<endl;
//     cout<<roo->right->val<<endl;
//     cout<<"printing heap"<<endl;
//     pippi->pop();
//     roo=pippi->root;
//     cout<<roo->val<<endl;
//     cout<<roo->left->val<<endl;
//     cout<<"printing heap"<<endl;
//     pippi->pop();
//     roo=pippi->root;
//     cout<<roo->val<<endl;
// }