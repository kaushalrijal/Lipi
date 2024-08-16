#include "code_generator.hpp"

std::string CodeGenerator::generate(ASTNode* root){
    Program* program= dynamic_cast<Program*>(root);
    std::string code = "#include <iostream>\n\nint main(){\n";

    for(auto node : program->nodes){
        Statement* stmt = dynamic_cast<Statement*>(node);
        if(stmt){
            code += generateStatement(stmt) + "\n";
        }
    }

    code += "return 0;\n";
    return code;
}

std::string CodeGenerator::generateStatement(Statement *stmt){
    if(auto printStmt = dynamic_cast<PrintStatement*>(stmt)){
        return "std::cout << " + generateExpression(printStmt->expr) + ";";
    } else if (auto assignStmt = dynamic_cast<AssignmentStatement* >(stmt)){
        return assignStmt->varName + "=" + generateExpression(assignStmt->expr) + ";";
    } else if (auto inputStmt = dynamic_cast<InputStatement* >(stmt)){
        return "cin >> " + inputStmt->varName + ";";
    }

    return "";
}

std::string CodeGenerator::generateExpression(Expression *expr){
    // handle integers
    if(auto intLiteral = dynamic_cast<IntegerLiteral*>(expr)){
        return std::to_string(intLiteral->value);
    } else if (auto floatLiteral = dynamic_cast<FloatLiteral*>(expr)) { // float literals
        return std::to_string(floatLiteral->value);
    } else if (auto stringLiteral = dynamic_cast<StringLiteral*>(expr)) { // strings
        return "\"" + stringLiteral->value + "\"";
    } else if (auto charLiteral = dynamic_cast<CharacterLiteral*>(expr)) { // characters
        return "'" + std::string(1, charLiteral->value) + "'";
    } else if (auto boolLiteral = dynamic_cast<BooleanLiteral*>(expr)) {
        return boolLiteral->value ? "true" : "false";
    } else if (auto binaryOp = dynamic_cast<BinaryOperation *>(expr)){
        std::string left = generateExpression(binaryOp->left);
        std::string right = generateExpression(binaryOp->right);
        std::string op;
        switch (binaryOp->op) {
            // ADD, SUB, MUL, DIV, MOD, AND, OR, EQ, NEQ, LT, GT, LE, GE
            case BinaryOperation::ADD: op = " + "; break;
            case BinaryOperation::SUB: op = " - "; break;
            case BinaryOperation::MUL: op = " * "; break;
            case BinaryOperation::DIV: op = " / "; break;
            case BinaryOperation::MOD: op = " % "; break;
            case BinaryOperation::AND: op = " && "; break;
            case BinaryOperation::OR: op = " || "; break;
            case BinaryOperation::EQ: op = " == "; break;
            case BinaryOperation::NEQ: op = " != "; break;
            case BinaryOperation::LT: op = " < "; break;
            case BinaryOperation::GT: op = " > "; break;
            case BinaryOperation::LE: op = " <= "; break;
            case BinaryOperation::GE: op = " >= "; break;
        }
        return "(" + left + op + right + ")";
    } else if (auto varExpr = dynamic_cast<Variable *>(expr)){
        return varExpr->name;
    } else if (auto unaryOp = dynamic_cast<UnaryOperation*>(expr)) {
        std::string operand = generateExpression(unaryOp->expr);
        std::string op;
        
        switch (unaryOp->op) {
            case UnaryOperation::NEG: op = "-"; break; 
            case UnaryOperation::NOT: op = "!"; break; 
            default: op = ""; break; 
        }
        return op + operand;
    }
    return "";
}

std::string CodeGenerator::generateDeclaration(Declaration *){
    
}