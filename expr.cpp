// Implement the methods here
#include "expr.h"
#include <vector>
#include <string>
#include <iostream>


int OpNode::oper(int x, int y, std::string op)
{ 

    if (op == "+") {
        return x+y;

    } else if(op == "-") {
        return x-y;
    }
    else if(op=="*"){
        return x*y;
    }
    else if(op=="/"){
        return x/y;
    }


    return 0;
}

int OpNode::traverse(ASTNode* node)
{
    return oper(node->Get_Value_L()->evaluate(),node->Get_Value_R()->evaluate(),node->Get_Value());
}

int OpNode::evaluate(){
    return traverse(this);
}
int BuildAST::precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/') 
        return 2;

    return 0;
}
bool BuildAST::isOperator(char c)
{
    return (!isdigit(c));
}

std::string OpNode::str(ASTNode* node) {
    std::string output ="";
    if(node->Get_Value_L() == NULL && node->Get_Value_R()==NULL)
    {output += node->Get_Value();}
    else
    {

        output += "("+node->Get_Value();

        output+=str(node->Get_Value_L());
        output+=str(node->Get_Value_R())+")";
    }
    return output;

    
}




ASTNode *BuildAST::newBinaryNode(std::stack<ASTNode *>& nodes, std::stack<char>& char_stack)
{
    char operate = char_stack.top();
    char_stack.pop();

    ASTNode *left = nodes.top();
    nodes.pop();

    ASTNode *right = nodes.top();
    nodes.pop();

    return new OpNode(std::string(1,operate), left, right); 
}
ASTNode *BuildAST::newValNode(std::string val)
{

    return new ValNode(val,NULL,NULL); 
}

ASTNode *BuildAST::build(std::string s)
{

    std::stack<char> char_stack;
    std::stack<ASTNode*> nodes;

    //shunting yard algo
    //modify SYA for AST:

    s = "(" + s + ")";
    int l = s.size();

    
    for (int i = 0; i < l; i++)
    {

        if (std::isdigit(s[i])) {
            // output+=s[i]
            //insert creation of new valnode
            std::string Fvalue=std::string(1,s[i]);
            for(int j=1;j<l;j++){
                if(isdigit(s[i+j])){
                    Fvalue= Fvalue+s[i+j];
                }
                else{
                    break;
                }
            }
            
            nodes.push(newValNode(Fvalue));
            int FL=Fvalue.length();
            i=i+FL-1;

        }
        

        else if (s[i] == '(') {
                char_stack.push('(');
        }

        else if (s[i] == ')')
        {

            while (!char_stack.empty() && char_stack.top() != '(')
            {
                //output += char_stack.top();
                //char_stack.pop();
                //creation of new Operand Node
                
                nodes.push(newBinaryNode(nodes, char_stack));
            }

            char_stack.pop();
        }
        else
        {
            if (isOperator(char_stack.top()))
            {
                while (precedence(s[i]) < precedence(char_stack.top()))
                {
                   // output += char_stack.top();
                    //char_stack.pop();
                    nodes.push(newBinaryNode(nodes,char_stack));
                }
                char_stack.push(s[i]);
            }
        }
    }
    while (!char_stack.empty())
    {
       // output += char_stack.top();
        //char_stack.pop();
        nodes.push(newBinaryNode(nodes,char_stack));
    }
    return nodes.top();
}