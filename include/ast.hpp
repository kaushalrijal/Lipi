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
    virtual ~ASTNode() = default;
    virtual void print() = 0;
};

// Base class for expressions
class Expression : public ASTNode {
public:
    virtual ~Expression() = default;
};

// Base class for statements
class Statement : public ASTNode {
public:
    virtual ~Statement() = default;
};

// Base class for declarations
class Declaration : public ASTNode {
public:
    virtual ~Declaration() = default;
};

// Program node to represent entire program
class Program : public ASTNode {
public:
    std::vector<ASTNode*> nodes;

    Program(const std::vector<ASTNode*>& nodes) : nodes(nodes) {}

    void print();
    
    ~Program() {
        for (auto node : nodes) {
            delete node;
        }
    }
};

// Literal expressions
class IntegerLiteral : public Expression {
public:
    int value;
    IntegerLiteral(int val) : value(val) {}
    void print();
};

class FloatLiteral : public Expression {
public:
    float value;
    FloatLiteral(float val) : value(val) {}
    void print();
};

class CharacterLiteral : public Expression {
public:
    char value;
    CharacterLiteral(char val) : value(val) {}
    void print();;
};

class StringLiteral : public Expression {
public:
    std::string value;
    StringLiteral(const std::string& val) : value(val) {}
    void print();;
};

class BooleanLiteral : public Expression {
public:
    bool value; // true for thik, false for bethik
    BooleanLiteral(bool val) : value(val) {}
    void print();;
};

// Variable expression
class Variable : public Expression {
public:
    std::string name;
    Variable(const std::string& name) : name(name) {}
    void print();
};

// Binary operations
class BinaryOperation : public Expression {
public:
    enum OpType { ADD, SUB, MUL, DIV, MOD, AND, OR, EQ, NEQ, LT, GT, LE, GE };
    Expression* left;
    Expression* right;
    OpType op;

    BinaryOperation(Expression* l, Expression* r, OpType op) : left(l), right(r), op(op) {}
    
    void print();;

    ~BinaryOperation() { delete left; delete right; }
};

// Unary operations
class UnaryOperation : public Expression {
public:
    enum OpType { NOT, NEG } op;
    Expression* expr;
    UnaryOperation(Expression* e, OpType opt) : expr(e), op(opt) {}

    void print();

    ~UnaryOperation() { delete expr; }
};

// class for function calls
class FunctionCall : public Expression {
public:
    std::string functionName;
    std::vector<ASTNode*> arguments;

    FunctionCall(const std::string& functionName, std::vector<ASTNode*> args)
        : functionName(functionName), arguments(args) {}

    void print();

    ~FunctionCall() {
        for (auto arg : arguments) delete arg;
    }
};


// Statements
class PrintStatement : public Statement {
public:
    Expression* expr;
    PrintStatement(Expression* e) : expr(e) {}

    void print();

    ~PrintStatement() { delete expr; }
};

class InputStatement : public Statement {
public:
    std::string varName; 
    InputStatement(const std::string& name) : varName(name) {}

    void print();

    ~InputStatement() = default;
};

class AssignmentStatement : public Statement {
public:
    std::string varName;
    Expression* expr;
    AssignmentStatement(const std::string& name, Expression* e) : varName(name), expr(e) {}

    void print();

    ~AssignmentStatement() { delete expr; }
};

// Classes for control flow statement
class IfStatement : public Statement {
public:
    Expression* condition;
    Statement* thenBranch;
    Statement* elseBranch;

    IfStatement(Expression* cond, Statement* thenStmt, Statement* elseStmt = nullptr)
        : condition(cond), thenBranch(thenStmt), elseBranch(elseStmt) {}

    void print();

    ~IfStatement() {
        delete condition;
        delete thenBranch;
        delete elseBranch;
    }
};

class WhileStatement : public Statement {
public:
    Expression* condition;
    Statement* body;

    WhileStatement(Expression* cond, Statement* bodyStmt)
        : condition(cond), body(bodyStmt) {}

    void print();

    ~WhileStatement() {
        delete condition;
        delete body;
    }
};

class ForStatement : public Statement {
public:
    Statement* initializer;
    Expression* condition;
    Statement* increment;
    Statement* body;

    ForStatement(Statement* initStmt, Expression* condExpr, Statement* incrExpr, Statement* bodyStmt)
        : initializer(initStmt), condition(condExpr), increment(incrExpr), body(bodyStmt) {}

    void print();

    ~ForStatement() {
        delete initializer;
        delete condition;
        delete increment;
        delete body;
    }
};

// Block Statement for collection of statements & declarations
class BlockStatement : public Statement {
public:
    std::vector<ASTNode*> nodes;

    BlockStatement(const std::vector<ASTNode*>& nodes) : nodes(nodes) {}

    void print();

    ~BlockStatement() {
        for (auto node : nodes) {
            delete node;
        }
    }
};

class ReturnStatement : public Statement {
public:
    Expression* ret_expr;
    ReturnStatement(Expression* ret) : ret_expr(ret) {}
    void print();

};

// Statement for function call
class FunctionCallStatement : public Statement {
public:
    std::string functionName;
    std::vector<ASTNode*> args;

    FunctionCallStatement(const std::string& functionName, const std::vector<ASTNode*>& args)
        : functionName(functionName), args(args) {}

    ~FunctionCallStatement() {
        for (auto arg : args) {
            delete arg;
        }
    }

    void print();
};


// Declarations
class VariableDeclaration : public Declaration {
public:
    enum Type { INT, FLOAT, CHAR, STRING, VOID };
    Type type;
    std::string varName;
    VariableDeclaration(Type t, const std::string& name) : type(t), varName(name) {}

    void print();
};

// Function Declaration
class FunctionDeclaration : public Declaration {
public:
    std::string name;
    std::vector<VariableDeclaration*> parameters;
    VariableDeclaration* returnType;
    Statement* body;
    FunctionDeclaration(const std::string& name, std::vector<VariableDeclaration*> params, VariableDeclaration* returnType, Statement* functionBody)
        : name(name), parameters(params), returnType(returnType), body(functionBody) {}

    void print();

    ~FunctionDeclaration() { 
        for (auto param : parameters) delete param;
        delete returnType;
        delete body;
    }
};

#endif 