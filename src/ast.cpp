 #include "ast.hpp"
#include <iostream>

// Function to print an integer literal
void IntegerLiteral::print() {
    std::cout << "IntegerLiteral: " << value << std::endl;
}

// Function to print a float literal
void FloatLiteral::print() {
    std::cout << "FloatLiteral: " << value << std::endl;
}

// Function to print a character literal
void CharacterLiteral::print() {
    std::cout << "CharacterLiteral: " << value << std::endl;
}

// Function to print a string literal
void StringLiteral::print() {
    std::cout << "StringLiteral: " << value << std::endl;
}

// Function to print a boolean literal
void BooleanLiteral::print() {
    std::cout << "BooleanLiteral: " << (value ? "thik" : "bethik") << std::endl;
}

// Function to print a variable expression
void Variable::print() {
    std::cout << "Variable: " << name << std::endl;
}

// Function to print a binary operation
void BinaryOperation::print() {
    std::cout << "BinaryOperation: ";
    left->print();
    std::cout << " Operator: " << op << " ";
    right->print();
}

// Function to print a unary operation
void UnaryOperation::print() {
    std::cout << "UnaryOperation: ";
    std::cout << " Operator: " << op << " ";
    expr->print();
}

// Function to print a print statement
void PrintStatement::print() {
    std::cout << "PrintStatement: ";
    expr->print();
}

// Function to print an input statement
void InputStatement::print() {
    std::cout << "InputStatement: variable = " << varName << std::endl;
}

// Function to print an assignment statement
void AssignmentStatement::print() {
    std::cout << "AssignmentStatement: variable = " << varName << std::endl;
    expr->print();
}

// Function to print an if statement
void IfStatement::print() {
    std::cout << "IfStatement: condition ";
    condition->print();
    std::cout << "Then: ";
    thenBranch->print();
    if (elseBranch) {
        std::cout << "Else: ";
        elseBranch->print();
    }
}

// Function to print a while statement
void WhileStatement::print() {
    std::cout << "WhileStatement: condition ";
    condition->print();
    std::cout << "Body: ";
    body->print();
}

// Function to print a for statement
void ForStatement::print() {
    std::cout << "ForStatement: ";
    std::cout << "Initializer: ";
    if (initializer) initializer->print();
    std::cout << "Condition: ";
    condition->print();
    std::cout << "Increment: ";
    if (increment) increment->print();
    std::cout << "Body: ";
    body->print();
}

// Function to print a block statement
void BlockStatement::print() {
    std::cout << "BlockStatement: ";
    for (auto node : nodes) {
        node->print();
    }
}

void ReturnStatement::print() {
    std::cout << "ReturnStatement: variable = " << varName << std::endl;
}

// Function to print a variable declaration
void VariableDeclaration::print() {
    std::cout << "VariableDeclaration: type = " << type << ", name = " << varName << std::endl;
}

// Function to print a function declaration
void FunctionDeclaration::print() {
    std::cout << "FunctionDeclaration: name = " << name << std::endl;
    std::cout << "Parameters: ";
    for (auto param : parameters) {
        param->print();
    }
    std::cout << "Body: ";
    body->print();
    std::cout << "Return Type: ";
    returnType->print();
}

// Function to print a program node
void Program::print() {
    std::cout << "Program: " << std::endl;
    for (auto node : nodes) {
        node->print();
    }
}
