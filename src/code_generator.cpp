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

std::string CodeGenerator::generateExpression(Expression *){

}

std::string CodeGenerator::generateDeclaration(Declaration *){

}