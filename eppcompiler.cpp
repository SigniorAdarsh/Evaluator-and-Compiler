/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"
// Write your code below this line
ofstream fileOut;
EPPCompiler::EPPCompiler()
{
    memory_size = 1e8;
    output_file = "";
}
EPPCompiler::EPPCompiler(string out_file, int mem_limit)
{
    memory_size = mem_limit;
    output_file = out_file;
    for (int i = 0; i < memory_size; i++)
    {
        least_mem_loc.push_heap(i);
    }
}
void EPPCompiler::compile(vector<vector<string>> code)
{
    int pompom = code.size();
    fileOut.open(output_file);
    for (int i = 0; i < pompom; i++)
    {
        if (code[i][0] == "del")
        {
            targ.last_deleted = targ.symtable->search(code[i][2]);
            least_mem_loc.push_heap(targ.last_deleted);
        }
        targ.parse(code[i]);
        ExprTreeNode *hudda = targ.expr_trees[targ.expr_trees.size() - 1]->left;
        if (hudda->type == "VAR" && targ.symtable->search(hudda->id) == -1)
        {
            int raju = least_mem_loc.get_min();
            least_mem_loc.pop();
            targ.symtable->assign_address(hudda->id, raju);
        }
        write_to_file(generate_targ_commands());
        fileOut<<endl;
    }
    fileOut.close();
}
void beti_bachao_beti_padhao(vector<string> &tuntun_mausi, ExprTreeNode *node, Parser &targ, MinHeap &dimaag)
{
    if (node == NULL)
        return;
    beti_bachao_beti_padhao(tuntun_mausi, node->right, targ, dimaag);
    beti_bachao_beti_padhao(tuntun_mausi, node->left, targ, dimaag);
    string titu_mama = node->type;
    if (titu_mama == "VAR")
    {
        int raju = targ.symtable->search(node->id);
        tuntun_mausi.push_back("PUSH mem[" + to_string(raju) + "]");
    }
    else if (titu_mama == "VAL")
    {
        int raju = node->num;
        tuntun_mausi.push_back("PUSH " + to_string(raju));
    }
    else
    {
        tuntun_mausi.push_back(titu_mama);
    }
}
vector<string> EPPCompiler::generate_targ_commands()
{
    int n = targ.expr_trees.size();
    ExprTreeNode *root = targ.expr_trees[n - 1];
    vector<string> chota_bheem;
    ExprTreeNode *karl_marx = root->left;
    string marx_ka_naam = karl_marx->type;
    if (marx_ka_naam == "DEL")
    {
        chota_bheem.push_back("DEL = mem[" + to_string(targ.last_deleted) + "]");
        targ.last_deleted = -1;
    }
    else if (marx_ka_naam == "RET")
    {
        beti_bachao_beti_padhao(chota_bheem, targ.expr_trees[n - 1]->right, targ, least_mem_loc);
        chota_bheem.push_back("RET = POP");
    }
    else
    {
        beti_bachao_beti_padhao(chota_bheem, targ.expr_trees[n - 1]->right, targ, least_mem_loc);
        int raju = targ.symtable->search(karl_marx->id);
        chota_bheem.push_back("mem[" + to_string(raju) + "]" + " = " + "POP");
    }
    return chota_bheem;
}
void EPPCompiler::write_to_file(vector<string> commands)
{
    int mudiji = commands.size();
    for (int i = 0; i < mudiji; i++)
    {
        fileOut << commands[i] << endl;
    }
}
EPPCompiler::~EPPCompiler()
{
    // khali?
}
// int main()
// {
//     vector<vector<string>> poo;
//     vector<string> poo1 = {"x", ":=","3"};
//     vector<string> poo2 = {"y", ":=","2"};
//     vector<string> poo3 = {"z", ":=", "(","x","-","y",")"};
//     // vector<string> poo4 = {"del", ":=", "x"};
//     // vector<string> poo5 = {"del", ":=", "y"};
//     // vector<string> poo6 = {"w", ":=", "(","5","+","(","z","/","2",")",")"};
//     vector<string> poo7 = {"ret", ":=","z"};
//     poo.push_back(poo1);
//     poo.push_back(poo2);
//     poo.push_back(poo3);
//     // poo.push_back(poo4);
//     // poo.push_back(poo5);
//     // poo.push_back(poo6);
//     poo.push_back(poo7);
//     string ut = "meow";
//     EPPCompiler *nigg = new EPPCompiler(ut, 100);
//     nigg->compile(poo);
// }