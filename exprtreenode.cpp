/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

// Write your code below this line

ExprTreeNode::ExprTreeNode()
{
    type = "eqval";
    left = NULL;
    right = NULL;
    id = "";
}
ExprTreeNode::ExprTreeNode(string t, int v)
{
    if (t.length() > 1)
    {
        if (t == ":=")
        {
            type = "eqval";
            left = NULL;
            right = NULL;
            num = v;
            id = "";
        }
        else
        {
            if (t == "del")
            {
                type = "DEL";
                left = NULL;
                right = NULL;
                id = "";
            }
            else if (t == "ret")
            {
                type = "RET";
                left = NULL;
                right = NULL;
                id = "";
            }
            else if (t[0] != '-')
            {
                int x = t[0] - '0';
                if (x >= 0 && x <= 9)
                {
                    type = "VAL";
                    left = NULL;
                    right = NULL;
                    num = stoi(t);
                    id = "";
                }
                else
                {
                    type = "VAR";
                    left = NULL;
                    right = NULL;
                    id = t;
                }
            }
            else
            {
                type = "VAL";
                left = NULL;
                right = NULL;
                num = stoi(t);
                id = "";
            }
        }
    }
    else
    {
        if (t == "+")
        {
            type = "ADD";
            left = NULL;
            right = NULL;
            id = "";
        }
        else if (t == "-")
        {
            type = "SUB";
            left = NULL;
            right = NULL;
            id = "";
        }
        else if (t == "*")
        {
            type = "MUL";
            left = NULL;
            right = NULL;
            id = "";
        }
        else if (t == "/")
        {
            type = "DIV";
            left = NULL;
            right = NULL;
            id = "";
        }
        else
        {
            int x = t[0] - '0';
            if (x >= 0 && x <= 9)
            {
                type = "VAL";
                left = NULL;
                right = NULL;
                num = stoi(t);
                id = "";
            }
            else
            {
                type = "VAR";
                left = NULL;
                right = NULL;
                id = t;
            }
        }
    }
}
// Can be "ADD", "SUB", "MUL", "DIV", "MOD", "VAL" or "VAR" (for variable)
ExprTreeNode::~ExprTreeNode()
{
    // khali?
}