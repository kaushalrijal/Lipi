#include "code_generator.hpp"

std::string CodeGenerator::generate(ASTNode* root){
    Program* program= dynamic_cast<Program*>(root);
    std::string code = "#include <iostream>\n\nint main(){\n";

    for(auto node : program->nodes){
        if (auto stmt = dynamic_cast<Statement*>(node)) {
            code += generateStatement(stmt);
        } else if (auto funcDecl = dynamic_cast<FunctionDeclaration*>(node)){
            code += generateFunctionDeclaration(funcDecl);
        } else if (auto decl = dynamic_cast<Declaration*>(node)) {
            code += generateDeclaration(decl); 
        }
    }

    code += "return 0;\n}";
    return code;
}

std::string CodeGenerator::generateStatement(Statement *stmt){
    if(auto printStmt = dynamic_cast<PrintStatement*>(stmt)){   // Generate print statement
        return "std::cout << " + generateExpression(printStmt->expr) + ";\n";
    } else if (auto assignStmt = dynamic_cast<AssignmentStatement* >(stmt)){ // assignment statement
        return assignStmt->varName + "=" + generateExpression(assignStmt->expr) + ";\n";
    } else if (auto inputStmt = dynamic_cast<InputStatement* >(stmt)){  // imput statement
        return "std::cin >> " + inputStmt->varName + ";\n";
    } else if (auto ifStmt = dynamic_cast<IfStatement* >(stmt)){
        std::string code = "if (";
        code += generateExpression(ifStmt->condition);
        code += ")\n";
        code += generateStatement(ifStmt->thenBranch);
        code += "\n";
        if(ifStmt->elseBranch){
            code += "else\n";
            code += generateStatement(ifStmt->elseBranch);
            code += "\n";
        }

        return code;
    } else if (auto whileStmt = dynamic_cast<WhileStatement* >(stmt)){
        std::string code;
        code += "while (";
        code += generateExpression(whileStmt->condition);  // Generate the condition expression
        code += ")\n";
        code += generateStatement(whileStmt->body);  // Generate the body of the loop
        code += "\n";

        return code;
    } else if (auto blockStmt = dynamic_cast<BlockStatement*>(stmt)) {
        std::string code = "{\n";
        for (auto& s : blockStmt->nodes) {
            if(auto decl = dynamic_cast<Declaration*>(s)){
                code += generateDeclaration(decl);
            } else {
                code += generateStatement(dynamic_cast<Statement*>(s));  // Generate all statements inside the block
            }
        }
        code += "}\n";
        return code;
    } else if (auto declStmt = dynamic_cast<Declaration *>(stmt)){
        return generateDeclaration(declStmt);
    } else if (auto returnStmt = dynamic_cast<ReturnStatement*>(stmt)) { // Return statement
        return "return " + generateExpression(returnStmt->ret_expr) + ";\n";
    } else if (auto functionCallStmt = dynamic_cast<FunctionCallStatement*>(stmt)) {
        std::string code = functionCallStmt->functionName + "(";
        for (size_t i = 0; i < functionCallStmt->args.size(); ++i) {
            code += generateExpression(dynamic_cast<Expression*>(functionCallStmt->args[i]));
            if (i < functionCallStmt->args.size() - 1) {
                code += ", ";
            }
        }
        code += ");\n";
        return code;
    } else if (auto forStmt = dynamic_cast<ForStatement*>(stmt)) {
        std::string code = "for (";

        // Generate initialization code
        if (forStmt->initializer) {
            code += generateStatement(forStmt->initializer);
            code = code.substr(0, code.size() - 2); // Remove the trailing newline and semicolon
        }
        code += "; ";

        // Generate condition code
        if (forStmt->condition) {
            code += generateExpression(forStmt->condition);
        }
        code += "; ";

        // Generate increment code
        if (forStmt->increment) {
            code += generateStatement(forStmt->increment);
            code = code.substr(0, code.size() - 2); // Remove the trailing newline and semicolon
        }
        code += ")";

        // Generate body code
        if (forStmt->body) {
            code += generateStatement(forStmt->body);
        }
        code += "\n";

        return code;
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
        return stringLiteral->value;
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
    } else if (auto funcCall = dynamic_cast<FunctionCall*>(expr)) {
        std::string code = funcCall->functionName + "(";
        for (size_t i = 0; i < funcCall->arguments.size(); ++i) {
            code += generateExpression(dynamic_cast<Expression*>(funcCall->arguments[i]));
            if (i < funcCall->arguments.size() - 1) {
                code += ", ";
            }
        }
        code += ")";
        return code;
    }
    return "";
}

std::string CodeGenerator::generateDeclaration(Declaration *decl){
    if(auto varDecl = dynamic_cast<VariableDeclaration *>(decl)){
        switch(varDecl->type){
            case VariableDeclaration::INT:
                return "int " + varDecl->varName + ";\n";
            case VariableDeclaration::FLOAT:
                return "float " + varDecl->varName + ";\n";
            case VariableDeclaration::CHAR:
                return "char " + varDecl->varName + ";\n";
            case VariableDeclaration::STRING:
                return "std::string " + varDecl->varName + ";\n";
            case VariableDeclaration::VOID:
                break;
            default:
                break;
        }
    }
    return "";
}

std::string CodeGenerator::generateFunctionDeclaration(FunctionDeclaration* funcDecl) {
    std::string code;

    // Function return type
    std::string returnType;
    if (funcDecl->returnType) {
        switch (funcDecl->returnType->type) {
            case VariableDeclaration::INT:
                returnType = "int";
                break;
            case VariableDeclaration::FLOAT:
                returnType = "float";
                break;
            case VariableDeclaration::CHAR:
                returnType = "char";
                break;
            case VariableDeclaration::STRING:
                returnType = "std::string";
                break;
            case VariableDeclaration::VOID:
                returnType = "void";
                break;
            default:
                returnType = "void"; // Default to void if unknown
                break;
        }
    } else {
        returnType = "void"; // Default return type if not specified
    }

    // Function signature
    code += returnType + " " + funcDecl->name + "(";
    for (size_t i = 0; i < funcDecl->parameters.size(); ++i) {
        auto param = funcDecl->parameters[i];
        std::string paramType;
        switch (param->type) {
            case VariableDeclaration::INT:
                paramType = "int";
                break;
            case VariableDeclaration::FLOAT:
                paramType = "float";
                break;
            case VariableDeclaration::CHAR:
                paramType = "char";
                break;
            case VariableDeclaration::STRING:
                paramType = "std::string";
                break;
            case VariableDeclaration::VOID:
                paramType = "void";
                break;
            default:
                paramType = "int"; // Default to int if unknown
                break;
        }
        code += paramType + " " + param->varName;
        if (i < funcDecl->parameters.size() - 1) {
            code += ", ";
        }
    }
    code += ")\n";

    // Function body
    if (funcDecl->body) {
        code += generateStatement(funcDecl->body);
    }

    code += "\n";

    return code;
}
