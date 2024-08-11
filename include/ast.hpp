#ifndef AST_H
#define AST_H

#include <string>
#include <vector>

// Forward declarations for various node types
class Expression;
class Statement;
class Declaration;

class ASTNode {
public:
    virtual ~ASTNode() = 0;
};

// Base class for expressions
class Expression : public ASTNode {
public:
    virtual ~Expression() = 0;
};

// Base class for statements
class Statement : public ASTNode {
public:
    virtual ~Statement() = 0;
};

// Base class for declarations
class Declaration : public ASTNode {
public:
    virtual ~Declaration() = 0;
};

// Literal expressions
class IntegerLiteral : public Expression {
public:
    int value;
    IntegerLiteral(int val) : value(val) {}
};

class FloatLiteral : public Expression {
public:
    float value;
    FloatLiteral(float val) : value(val) {}
};

class StringLiteral : public Expression {
public:
    std::string value;
    StringLiteral(const std::string& val) : value(val) {}
};

class BooleanLiteral : public Expression {
public:
    bool value; // true for thik, false for bethik
    BooleanLiteral(bool val) : value(val) {}
};

// Variable expression
class Variable : public Expression {
public:
    std::string name;
    Variable(const std::string& name) : name(name) {}
};

// Binary operations
class BinaryOperation : public Expression {
public:
    enum OpType { ADD, SUB, MUL, DIV, MOD, AND, OR, EQ, NEQ, LT, GT, LE, GE };
    Expression* left;
    Expression* right;
    OpType op;
    BinaryOperation(Expression* l, Expression* r, OpType op) : left(l), right(r), op(op) {}
    ~BinaryOperation() { delete left; delete right; }
};

// Unary operations
class UnaryOperation : public Expression {
public:
    enum OpType { NOT, NEG };
    Expression* expr;
    OpType op;
    UnaryOperation(Expression* e, OpType op) : expr(e), op(op) {}
    ~UnaryOperation() { delete expr; }
};

// Statements
class PrintStatement : public Statement {
public:
    Expression* expr;
    PrintStatement(Expression* e) : expr(e) {}
    ~PrintStatement() { delete expr; }
};

class InputStatement : public Statement {
public:
    std::string varName; 
    InputStatement(const std::string& name) : varName(name) {}
    ~InputStatement() = 0;
};

class AssignmentStatement : public Statement {
public:
    std::string varName;
    Expression* expr;
    AssignmentStatement(const std::string& name, Expression* e) : varName(name), expr(e) {}
    ~AssignmentStatement() { delete expr; }
};

// Declarations
class VariableDeclaration : public Declaration {
public:
    enum Type { INT, FLOAT, CHAR, STRING, VOID };
    Type type;
    std::string varName;
    VariableDeclaration(Type t, const std::string& name) : type(t), varName(name) {}
};

// Function Declaration
class FunctionDeclaration : public Declaration {
public:
    std::string name;
    std::vector<VariableDeclaration*> parameters;
    Declaration* returnType;
    FunctionDeclaration(const std::string& name, std::vector<VariableDeclaration*> params, Declaration* returnType)
        : name(name), parameters(params), returnType(returnType) {}
    ~FunctionDeclaration() { 
        for (auto param : parameters) delete param;
        delete returnType;
    }
};

#endif // AST_H
