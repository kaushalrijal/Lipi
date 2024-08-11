#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

// Base class for all AST nodes
class ASTNode {
public:
    virtual ~ASTNode() = default;
};

// Node for variable declarations and assignments
class VariableDeclarationNode : public ASTNode {
public:
    std::string type;
    std::string variableName;
    ASTNode* initialValue;  // Can be null if no initial value is assigned

    VariableDeclarationNode(const std::string& type, const std::string& name, ASTNode* value = nullptr)
        : type(type), variableName(name), initialValue(value) {}
};

class AssignmentNode : public ASTNode {
public:
    std::string variableName;
    ASTNode* value;

    AssignmentNode(const std::string& name, ASTNode* value)
        : variableName(name), value(value) {}
};

// Node for print statements
class PrintNode : public ASTNode {
public:
    ASTNode* expression;

    PrintNode(ASTNode* expr) : expression(expr) {}
};

// Node for input statements
class InputNode : public ASTNode {
public:
    std::string variableName;

    InputNode(const std::string& name) : variableName(name) {}
};

// Node for if statements
class IfNode : public ASTNode {
public:
    ASTNode* condition;
    ASTNode* thenBlock;
    ASTNode* elseBlock;  // Can be null if no else block

    IfNode(ASTNode* cond, ASTNode* thenBlk, ASTNode* elseBlk = nullptr)
        : condition(cond), thenBlock(thenBlk), elseBlock(elseBlk) {}
};

// Node for while statements
class WhileNode : public ASTNode {
public:
    ASTNode* condition;
    ASTNode* block;

    WhileNode(ASTNode* cond, ASTNode* blk) : condition(cond), block(blk) {}
};

// Node for for statements
class ForNode : public ASTNode {
public:
    ASTNode* initStatement;
    ASTNode* condition;
    ASTNode* increment;
    ASTNode* block;

    ForNode(ASTNode* init, ASTNode* cond, ASTNode* incr, ASTNode* blk)
        : initStatement(init), condition(cond), increment(incr), block(blk) {}
};

// Node for function definitions
class FunctionDefinitionNode : public ASTNode {
public:
    std::string returnType;  // Use "khali" for void functions
    std::string functionName;
    std::vector<VariableDeclarationNode*> parameters;
    ASTNode* body;

    FunctionDefinitionNode(const std::string& returnType, const std::string& name,
                           const std::vector<VariableDeclarationNode*>& params, ASTNode* body)
        : returnType(returnType), functionName(name), parameters(params), body(body) {}
};

// Node for return statements
class ReturnNode : public ASTNode {
public:
    ASTNode* value;  // Can be null if returning nothing

    ReturnNode(ASTNode* val = nullptr) : value(val) {}
};

// Node for expressions
class ExpressionNode : public ASTNode {
public:
    virtual ~ExpressionNode() = default;
};

// Concrete expression nodes
class LiteralNode : public ExpressionNode {
public:
    std::string value;

    LiteralNode(const std::string& val) : value(val) {}
};

class IdentifierNode : public ExpressionNode {
public:
    std::string name;

    IdentifierNode(const std::string& name) : name(name) {}
};

class BinaryOperationNode : public ExpressionNode {
public:
    ExpressionNode* left;
    std::string op;  // Operator (e.g., "+", "-", "*", "/")
    ExpressionNode* right;

    BinaryOperationNode(ExpressionNode* left, const std::string& op, ExpressionNode* right)
        : left(left), op(op), right(right) {}
};

class UnaryOperationNode : public ExpressionNode {
public:
    std::string op;  // Operator (e.g., "-", "!")
    ExpressionNode* operand;

    UnaryOperationNode(const std::string& op, ExpressionNode* operand)
        : op(op), operand(operand) {}
};

// Node for blocks of statements
class BlockNode : public ASTNode {
public:
    std::vector<ASTNode*> statements;

    BlockNode(const std::vector<ASTNode*>& stmts) : statements(stmts) {}
};

#endif // AST_H
