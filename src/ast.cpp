#include "ast.hpp"

// Pure virtual destructor implementations
ASTNode::~ASTNode() = default;

Expression::~Expression() = default;

Statement::~Statement() = default;

Declaration::~Declaration() = default;

// Destructor implementations for concrete classes
IntegerLiteral::~IntegerLiteral() = default;

FloatLiteral::~FloatLiteral() = default;

StringLiteral::~StringLiteral() = default;

BooleanLiteral::~BooleanLiteral() = default;

Variable::~Variable() = default;

BinaryOperation::~BinaryOperation() {
    delete left;
    delete right;
}

UnaryOperation::~UnaryOperation() {
    delete expr;
}

PrintStatement::~PrintStatement() {
    delete expr;
}

InputStatement::~InputStatement() = default;

AssignmentStatement::~AssignmentStatement() {
    delete expr;
}

VariableDeclaration::~VariableDeclaration() = default;

FunctionDeclaration::~FunctionDeclaration() {
    for (auto param : parameters) {
        delete param;
    }
    delete returnType;
}
