#include <stdexcept>
#include "semantic_analyzer.hpp"

void SemanticAnalyzer::analyzeStatement(Statement *stmt){
    if(auto* printStmt = dynamic_cast<PrintStatement*>(stmt)){
        analyzeExpression(printStmt->expr);
    } else if(auto* assignmentStmt = dynamic_cast<AssignmentStatement*>(stmt)) {
        // Check if the variable is declared
        symbolTable.lookupVariable(assignmentStmt->varName);
        analyzeExpression(assignmentStmt->expr);
    } else if (auto* ifStmt = dynamic_cast<IfStatement*>(stmt)) {
        analyzeExpression(ifStmt->condition);
        analyzeStatement(ifStmt->thenBranch);
        if (ifStmt->elseBranch) {
            analyzeStatement(ifStmt->elseBranch);
        }
    } else if (auto* whileStmt = dynamic_cast<WhileStatement*>(stmt)) {
        analyzeExpression(whileStmt->condition);
        analyzeStatement(whileStmt->body);
    } else if (auto* forStmt = dynamic_cast<ForStatement*>(stmt)) {
        if (forStmt->initializer) {
            analyzeStatement(forStmt->initializer);
        }
        analyzeExpression(forStmt->condition);
        if (forStmt->increment) {
            analyzeExpression(forStmt->increment);
        }
        analyzeStatement(forStmt->body);
    } else if (auto* blockStmt = dynamic_cast<BlockStatement*>(stmt)) {
        for (auto* s : blockStmt->statements) {
            analyzeStatement(s);
        }
    }
}

void SemanticAnalyzer::analyzeExpression(Expression* expr){
    if(auto* variable = dynamic_cast<Variable*>(expr)) {
        // Check if varibale is declared
        symbolTable.lookupVariable(variable->name);
    } else if (auto* binaryOp = dynamic_cast<BinaryOperation*>(expr)) {
        analyzeExpression(binaryOp->left);
        analyzeExpression(binaryOp->right);
    } else if (auto* unaryOp = dynamic_cast<UnaryOperation*>(expr)) {
        analyzeExpression(unaryOp->expr);
    }
}

void SemanticAnalyzer::analyzeDeclaration(Declaration* decl){
    if(auto* varDecl = dynamic_cast<VariableDeclaration*>(decl)){
        if(varDecl->type == VariableDeclaration::VOID){
            throw std::runtime_error("Variable cannot have void type");
        }
        symbolTable.declareVariable(varDecl->varName, static_cast<VarType>(varDecl->type));

    } else if(auto * funcDecl = dynamic_cast<FunctionDeclaration*>(decl)){
        try {
            symbolTable.lookupVariable(funcDecl->name);
            throw std::runtime_error("Function " + funcDecl->name + " already declared!");
        } catch (const std::runtime_error&){
            // nothing...
        }

        symbolTable.declareVariable(funcDecl->name, VarType::Khali);

        for (auto* param : funcDecl->parameters) {
            if (param->type == VariableDeclaration::VOID) {
                throw std::runtime_error("Function parameter cannot have VOID type.");
            }
        }

        if (auto* returnTypeDecl = dynamic_cast<VariableDeclaration*>(funcDecl->returnType)) {
            if (returnTypeDecl->type == VariableDeclaration::VOID) {
                throw std::runtime_error("Function must have a non-VOID return type.");
            }
        }
    }
}

std::string varTypeToString(VarType type) {
    switch (type) {
        case VarType::Purna:
            return "Purna (Integer)";
        case VarType::Dasa:
            return "Dasa (Float)";
        case VarType::Akshar:
            return "Akshar (Character)";
        case VarType::Paath:
            return "Paath (String)";
        case VarType::Thik_Bethik:
            return "Thik/Bethik (Boolean)";
        case VarType::Khali:
            return "Khali (Void)";
        default:
            return "Unknown Type";
    }
}

void SemanticAnalyzer::checkType(Expression* expr, VarType expectedType){
    VarType actualType;
    if (auto* varExpr = dynamic_cast<Variable*>(expr)) {
        actualType = symbolTable.lookupVariable(varExpr->name);
    } else if (auto* intLiteral = dynamic_cast<IntegerLiteral*>(expr)) {
        actualType = VarType::Purna;
    } else if (auto* floatLiteral = dynamic_cast<FloatLiteral*>(expr)) {
        actualType = VarType::Dasa;
    } else if (auto* stringLiteral = dynamic_cast<StringLiteral*>(expr)) {
        actualType = VarType::Paath;
    } else if (auto* charLiteral = dynamic_cast<CharacterLiteral*>(expr)) {
        actualType = VarType::Akshar;
    } else if (auto* boolLiteral = dynamic_cast<BooleanLiteral*>(expr)) {
        actualType = VarType::Thik_Bethik;
    } else {
        throw std::runtime_error("Unknown expression type in type check");
    }

    if (actualType != expectedType) {
        throw std::runtime_error("Type mismatch: Expected " + varTypeToString(expectedType) + ", got " + varTypeToString(actualType));
    }
}

void SemanticAnalyzer::analyze(ASTNode* root){
    if (auto* program = dynamic_cast<Program*>(root)) {
        for (auto* n : program->nodes) {
            analyzeNode(n);
        }
    } else if (auto* declaration = dynamic_cast<Declaration*>(root)) {
        analyzeDeclaration(declaration);
    } else if (auto* statement = dynamic_cast<Statement*>(root)) {
        analyzeStatement(statement);
    } else if (auto* expression = dynamic_cast<Expression*>(root)) {
        analyzeExpression(expression);
    }
}

