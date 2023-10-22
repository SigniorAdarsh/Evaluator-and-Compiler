/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"
// Write your code below this line
SymbolTable::SymbolTable()
{
    size = 0;
    root = NULL;
}
int comparer(string k1, string k2)
{
    int len1 = k1.length();
    int len2 = k2.length();
    for (int i = 0; i < min(len1, len2); i++)
    {
        if (k1[i] < k2[i])
            return -1;
        if (k1[i] > k2[i])
            return 1;
    }
    if (len1 == len2)
        return 0;
    if (len1 < len2)
        return -1;
    return 1;
}
SymNode *searcher(SymNode *node, string k)
{
    if (node == NULL)
        return NULL;
    if (comparer(node->key, k) == 1)
        return searcher(node->left, k);
    if (comparer(node->key, k) == -1)
        return searcher(node->right, k);
    return node;
}
int SymbolTable::search(string k)
{
    SymNode *temp = searcher(root, k);
    if (temp == NULL)
    {
        return -2;
    }
    return temp->address;
}
int hitter(SymNode *node)
{
    if (node == NULL)
        return -1;
    return node->height;
}
int barabari(SymNode *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return (hitter(node->left) - hitter(node->right));
}
SymNode *inserter(SymNode *node, SymNode *daddy, string k)
{
    if (node == NULL)
    {
        SymNode *nr = new SymNode(k);
        nr->par = daddy;
        return nr;
    }
    if (comparer(k, node->key) == -1)
    {
        node->left = inserter(node->left, node, k);
    }
    else if (comparer(k, node->key) == 1)
    {
        node->right = inserter(node->right, node, k);
    }
    else
        return node;
    node->height = 1 + max(hitter(node->left), hitter(node->right));
    int gharjanahai = barabari(node);
    if (gharjanahai > 1 && comparer(k, node->left->key) == -1)
    {
        return node->RightRightRotation();
    }
    if (gharjanahai < -1 && comparer(k, node->right->key) == 1)
    {
        return node->LeftLeftRotation();
    }
    if (gharjanahai > 1 && comparer(k, node->left->key) == 1)
    {
        return node->LeftRightRotation();
    }
    if (gharjanahai < -1 && comparer(k, node->right->key) == -1)
    {
        return node->RightLeftRotation();
    }
    return node;
}
void SymbolTable::insert(string k)
{
    if (size == 0)
    {
        root = new SymNode(k);
        size++;
        return;
    }
    else
    {
        size++;
        root = inserter(root, NULL, k);
    }
}
SymNode *remover(SymNode *node, string k)
{
    if (node == NULL)
        return node;
    if (comparer(k, node->key) == -1)
    {
        node->left = remover(node->left, k);
    }
    else if (comparer(k, node->key) == 1)
    {
        node->right = remover(node->right, k);
    }
    else
    {
        if (node->left == NULL && node->right == NULL)
        {
            delete node;
            return NULL;
        }
        else if (node->left == NULL)
        {
            SymNode *temp = node->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            node->key = temp->key;
            node->address = temp->address;
            node->right = remover(node->right, temp->key);
        }
        else if (node->right == NULL)
        {
            SymNode *temp = node->left;
            while (temp->right != NULL)
            {
                temp = temp->right;
            }
            node->key = temp->key;
            node->address = temp->address;
            node->left = remover(node->left, temp->key);
        }
        else
        {
            SymNode *temp = node->right;
            while (temp->left != NULL)
            {
                temp = temp->left;
            }
            node->key = temp->key;
            node->address = temp->address;
            node->right = remover(node->right, temp->key);
        }
    }
    node->height = 1 + max(hitter(node->left), hitter(node->right));
    if (barabari(node) > 1 && barabari(node->left) >= 0)
    {
        return node->RightRightRotation();
    }
    else if (barabari(node) > 1 && barabari(node->left) < 0)
    {
        return node->LeftRightRotation();
    }
    else if (barabari(node) < -1 && barabari(node->right) > 0)
    {
        return node->RightLeftRotation();
    }
    else if (barabari(node) < -1 && barabari(node->right) <= 0)
    {
        return node->LeftLeftRotation();
    }
    else
        return node;
}
void SymbolTable::remove(string k)
{
    int ff = search(k);
    if (ff == -2)
        return;
    size--;
    root = remover(root, k);
}
void SymbolTable::assign_address(string k, int idx)
{
    SymNode *temp = searcher(root, k);
    if (temp == NULL)
        return;
    temp->address = idx;
}

int SymbolTable::get_size()
{
    return size;
}

SymNode *SymbolTable::get_root()
{
    return root;
}
void delter(SymNode *node)
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
    delter(node->left);
    delter(node->right);
    node->left = NULL;
    node->right = NULL;
    delete node;
    return;
}
SymbolTable::~SymbolTable()
{
    size = 0;
    delter(root);
}
// void printLevelOrder(SymNode* root)
// {
//     // Base Case
//     if (root == NULL)
//         return;

//     // Create an empty queue for level order traversal
//     queue<SymNode*> q;

//     // Enqueue Root and initialize height
//     q.push(root);

//     while (q.empty() == false) {

//         // Print front of queue and remove it from queue
//         SymNode* node = q.front();
//         cout << node->key <<node->height<< " ";
//         q.pop();

//         // Enqueue left child
//         if (node->left != NULL)
//             q.push(node->left);

//         // Enqueue right child
//         if (node->right != NULL)
//             q.push(node->right);
//     }
// }
// int main()
// {
//     SymbolTable ayo;
//     ayo.insert("s");
//     printLevelOrder(ayo.get_root());
//     cout<<"nn"<<endl;
//     ayo.insert("h");
//     printLevelOrder(ayo.get_root());
//     cout<<"nn"<<endl;
//     ayo.insert("a");
//     printLevelOrder(ayo.get_root());
//     cout<<"nn"<<endl;
//     ayo.insert("c");
//     printLevelOrder(ayo.get_root());
//     cout<<"nn"<<endl;
//     SymNode*root=ayo.get_root();
//     ayo.insert("b");
//     printLevelOrder(ayo.get_root());
//     cout<<"nn"<<endl;
//     ayo.insert("e");
//     printLevelOrder(ayo.get_root());
//     cout<<"nn"<<endl;
//     ayo.remove("e");
//     printLevelOrder(ayo.get_root());
//     cout<<"nn"<<endl;
//     ayo.remove("a");
//     printLevelOrder(ayo.get_root());
//     cout<<"nn"<<endl;
//     ayo.remove("b");
//     printLevelOrder(ayo.get_root());
//     cout<<"nn"<<endl;
// }