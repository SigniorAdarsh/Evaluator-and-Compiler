/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "parser.h"
// Write your expression below this line
Parser::Parser()
{
    symtable = new SymbolTable();
    last_deleted=-1;
}
ExprTreeNode *solver(vector<string> &expression, int s, int e)
{
    ExprTreeNode *node;
    if (s == e)
    {
        node = new ExprTreeNode(expression[s], 0);
        return node;
    }
    if (expression[s] != "(")
    {
        node = new ExprTreeNode(expression[s + 1], 0);
        node->left = solver(expression, s, s);
        node->right = solver(expression, s + 2, e);
        return node;
    }
    else
    {
        int xx = 1;
        int i = s;
        for (i = s + 1; i <= e; i++)
        {
            if (expression[i] == "(")
                xx++;
            if (expression[i] == ")")
                xx--;
            if (xx == 0)
                break;
        }
        if (i != e)
        {
            node = new ExprTreeNode(expression[i + 1], 0);
            node->left = solver(expression, s, i);
            node->right = solver(expression, i + 2, e);
        }
        else
        {
            node = solver(expression, s + 1, e - 1);
        }
        return node;
    }
}
void Parser::parse(vector<string> expression)
{
    ExprTreeNode *root = new ExprTreeNode(expression[1], 0);
    root->left = solver(expression, 0, 0);
    if (expression[2] == "(")
    {
        root->right = solver(expression, 3, expression.size() - 2);
    }
    else
    {
        root->right = solver(expression, 2, 2);
    }
    expr_trees.push_back(root);
    if(root->left->type=="VAR")
    {
        string meranaam=root->left->id;
        int ll=symtable->search(meranaam);
        if(ll==-2)
        {
            symtable->insert(meranaam);
        }
    }
    else if(root->left->type=="DEL")
    {
        symtable->remove(root->right->id);
    }
}
void deleter(ExprTreeNode *root)
{
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
    {
        delete root;
        return;
    }
    deleter(root->left);
    deleter(root->right);
    root->left = NULL;
    root->right = NULL;
    delete root;
    return;
}
Parser::~Parser()
{
    delete symtable;
    int n = expr_trees.size();
    for (int i = 0; i < n; i++)
    {
        deleter(expr_trees[i]);
    }
}