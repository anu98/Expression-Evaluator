#include <iostream>
#include <string>
#include <stack>

class ASTNode
{
    //declare members
protected:
    std::string val;
    ASTNode *left;
    ASTNode *right;

public:
    ASTNode(std::string val, ASTNode *left, ASTNode *right)
    {
        this->val = val;
        this->left = left;
        this->right = right;
    }

    std::string Get_Value()
    {
        return val;
    }
    
    ASTNode* Get_Value_L()
    {
        return right;
    }

    ASTNode* Get_Value_R()
    {
        return left;
    }

    bool isLeafNode()
    {
        return (left == NULL && right == NULL);
    }

    virtual int evaluate()=0;
    virtual std::string str(ASTNode* node) = 0;
};

class OpNode : public ASTNode
{
protected:
    int oper(int, int, std::string);
    int traverse(ASTNode *);
    std::string evalString(ASTNode *);

public:
    OpNode(std::string val, ASTNode *left, ASTNode *right) : ASTNode(val, left, right) {}
    int evaluate() override;
    std::string str(ASTNode* node) override;

    virtual ~OpNode() = default;
};

class ValNode : public ASTNode
{
public:
    ValNode(std::string val, ASTNode * left , ASTNode *right) : ASTNode(val, NULL, NULL){}
    int evaluate() override
    {
        return std::stoi(val);
    }
    std::string str(ASTNode* node) override
    {
        return val;
    }
    virtual ~ValNode() = default;
};

class BuildAST
{
private:
    static ASTNode* newValNode(std::string);
    static ASTNode* newBinaryNode(std::stack<ASTNode *>&, std::stack<char>&);
    static std::string exSubDig(std::string &, int);
    static bool isOperator(char);
    static int precedence(char);
public:
    static ASTNode *build(std::string);
};