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

class CharacterLiteral : public Expression {
public:
    char value;
    CharacterLiteral(char val) : value(val) {}
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
    enum OpType { NOT, NEG } op;
    Expression* expr;
    UnaryOperation(Expression* e, OpType opt) : expr(e), op(opt) {}
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
    ~InputStatement() = default;
};

class AssignmentStatement : public Statement {
public:
    std::string varName;
    Expression* expr;
    AssignmentStatement(const std::string& name, Expression* e) : varName(name), expr(e) {}
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

    ~WhileStatement() {
        delete condition;
        delete body;
    }
};

class ForStatement : public Statement {
public:
    Statement* initializer;
    Expression* condition;
    Expression* increment;
    Statement* body;

    ForStatement(Statement* initStmt, Expression* condExpr, Expression* incrExpr, Statement* bodyStmt)
        : initializer(initStmt), condition(condExpr), increment(incrExpr), body(bodyStmt) {}

    ~ForStatement() {
        delete initializer;
        delete condition;
        delete increment;
        delete body;
    }
};

// Block Statement for collection of statements
class BlockStatement : public Statement {
public:
    std::vector<Statement*> statements;

    BlockStatement(const std::vector<Statement*>& stmts) : statements(stmts) {}

    ~BlockStatement() {
        for (auto stmt : statements) {
            delete stmt;
        }
    }
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
