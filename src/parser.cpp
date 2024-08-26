#include <iostream>
#include "parser.hpp"
#include <stdexcept>

Parser::Parser(std::vector<Token>& tok) : tokens(tok), current(0) {};

// Return Current Token
Token& Parser::currentToken(){
    if(current>=tokens.size()){
        throw std::runtime_error("No more tokens");
    }
    return tokens[current];
}

// Move to next token
void Parser::consumeToken() {
    if (current < tokens.size()) {
        ++current;
    }
}

bool Parser::check(TokenType type) {
    if(currentToken().type == type){
        return true;
    }
    return false;
}

// Checks if the current token matches specific type
bool Parser::match(TokenType type) {
    std::cout << "matching token " << printTokenType(type) << std::endl;
    if (currentToken().type == type) {
        consumeToken();
        return true;
    }
    // Skip NEWLINE tokens
    while (currentToken().type == TokenType::NEWLINE) {
        consumeToken();
    }
    return currentToken().type == type;
}

// Check if the tokens matches a specific type and consume it. 
void Parser::expect(TokenType type) {
    if (!match(type)) {
        throw std::runtime_error("Unexpected token type: " + printTokenType(type));;
    }
}

ASTNode* Parser::parsePrimaryExpression(){
    if(check(NUMBER)){
        int value = std::stoi(currentToken().value);
        consumeToken();
        return new IntegerLiteral(value);
    } else if (check(STRING)){
        std::string value = currentToken().value;
        consumeToken();
        return new StringLiteral(value);
    } else if (check(ID)){
        std::string name = currentToken().value;
        consumeToken();
        return new Variable(name);
    } else if (check(CHAR)){
        char value = currentToken().value[1];
        consumeToken();
        return new CharacterLiteral(value);
    } else if (check(LPAREN)){
        consumeToken(); // Consume '('
        ASTNode* expression = parseExpression();
        expect(RPAREN);
        return expression;
    } else if (check(TRUE)) {
        consumeToken();
        return new BooleanLiteral(true);
    } else if (check(FALSE)) {
        consumeToken();
        return new BooleanLiteral(false);
    } else{
        throw std::runtime_error("Unexpected token in primary expression.");
    }
    return nullptr;
}

Expression* Parser::parseUnaryExpression(){
    if(match(SUB)|| match(NOT)){
        Token op = currentToken();
        consumeToken();

        Expression* operand = parseUnaryExpression();

        return new UnaryOperation(operand, op.type == SUB ? UnaryOperation::NEG : UnaryOperation::NOT);
    }
    return dynamic_cast<Expression*>(parsePrimaryExpression());
}

int getPrecedence(TokenType type){
    switch (type) {
        case ADD:
        case SUB:
            return 1;
        case MUL:
        case DIV:
        case MOD:
            return 2;
        case EQ:
        case NEQ:
            return 0;
        default:
            return -1;
    }
}

BinaryOperation::OpType getBinaryOpType(TokenType type) {
    switch (type) {
        case ADD: return BinaryOperation::ADD;
        case SUB: return BinaryOperation::SUB;
        case MUL: return BinaryOperation::MUL;
        case DIV: return BinaryOperation::DIV;
        case MOD: return BinaryOperation::MOD;
        case EQ: return BinaryOperation::EQ;
        case NEQ: return BinaryOperation::NEQ;
        default:
            throw std::runtime_error("Unknown binary operator type");
    }
}

Expression* Parser::parseBinaryExpression(int precedence = 0){
    Expression* left = parseUnaryExpression();
    while(true){
        TokenType opType = currentToken().type;

        int currentPrecedence = getPrecedence(opType);

        if(currentPrecedence < precedence)
            break;
        
        consumeToken();

        Expression* right = parseBinaryExpression(currentPrecedence + 1);

        left = new BinaryOperation(left, right, getBinaryOpType(opType));
    }
    return left;
}


// Methods for parsing
ASTNode* Parser::parseExpression(){
    return parseBinaryExpression();
}

ASTNode* Parser::parseStatement(){
    printToken(currentToken());
    if(match(PRINT)){ // Print Statement
        expect(LPAREN);
        Expression* expr = dynamic_cast<Expression*>(parseExpression());
        expect(RPAREN);
        expect(END);
        return new PrintStatement(expr);
    } 
    else if(match(INPUT)){ // Input Statement
        expect(LPAREN);
        std::string vName = currentToken().value;
        expect(ID);
        expect(RPAREN);
        expect(END);
        return new InputStatement(vName);
    } 
    else if (match(TYPE)) { // Assignment statement
        Token typeToken = currentToken();  
        expect(ID);  
        std::string varName = currentToken().value; 
        expect(ASSIGN); 
        Expression* expr = dynamic_cast<Expression*>(parseExpression()); 
        expect(END); 
        return new AssignmentStatement(varName, expr); 
    } 
    else if (check(ID)) { // Assignment statement for predeclared variables
        std::string varName = currentToken().value;
        consumeToken();
        expect(ASSIGN);
        Expression* expr = dynamic_cast<Expression *>(parseExpression());
        expect(END);
        return new AssignmentStatement(varName, expr);
    } 
    else if (match(IF)){
        expect(LPAREN);

        Expression* condition = dynamic_cast<Expression*>(parseExpression());
        
        expect(RPAREN);
        Statement* thenBranch = dynamic_cast<Statement*>(parseStatement());
        std::cout << "then block executed succesfully" << std::endl;
        Statement* elseBranch = nullptr;
        printToken(currentToken());
        if(match(ELSE)){
            elseBranch = dynamic_cast<Statement*>(parseStatement());
        }

        return new IfStatement(condition, thenBranch, elseBranch);
    }
    else if(match(WHILE)){
        expect(LPAREN);

        Expression* condition = dynamic_cast<Expression *>(parseExpression());

        expect(RPAREN);

        Statement * body = dynamic_cast<Statement*>(parseStatement());

        return new WhileStatement(condition, body);
    }
    else if(match(FOR)){
        consumeToken();
        expect(LPAREN);

        Statement* initializer = dynamic_cast<Statement *>(parseStatement());
        Expression* condition = dynamic_cast<Expression *>(parseExpression());
        expect(END);
        Expression* increment = dynamic_cast<Expression *>(parseExpression());
        expect(RPAREN);
        Statement* body = dynamic_cast<Statement *>(parseStatement());

        return new ForStatement(initializer, condition, increment, body);
    } 
    else if (match(TokenType::LBRACE)) {  // Block Statement
        std::vector<Statement*> statements;
        while (!match(TokenType::RBRACE) && !match(TokenType::END_OF_FILE)) {
            statements.push_back(dynamic_cast<Statement*>(parseStatement()));
        }
        if (!match(TokenType::RBRACE)) {
            throw std::runtime_error("Expected '}' at end of block");
        }
        return new BlockStatement(statements);
    }
    else {
        throw std::runtime_error("Unexpected Error Occured");
    }
}

// Parse Function Decalartion
ASTNode* Parser::parseFunctionDeclaration(){
    expect(FUNC_DEF);
    expect(ID);

    std::string functionName = currentToken().value;

    expect(LPAREN);

    std::vector<VariableDeclaration*> parameters;

    while(!match(RPAREN)){
        Token typeToken = currentToken();
        expect(TYPE);
        expect(ID);
        std::string paramName = currentToken().value;
        parameters.push_back(new VariableDeclaration(static_cast<VariableDeclaration::Type>(typeToken.type), paramName));

        if(match(COMMA)){
            continue;
        } else {
            break;
        }
    }

    // Parse return type
    Declaration* returnType = nullptr;
    if(match(TYPE)){
        Token typeToken = currentToken();
        returnType = new VariableDeclaration(static_cast<VariableDeclaration::Type>(typeToken.type), "");
    }

    Statement* body = dynamic_cast<Statement *>(parseStatement());

    return new FunctionDeclaration(functionName, parameters, returnType);
}

VariableDeclaration::Type mapTokenTypeToVarType(const std::string tokenType) {
    if (tokenType == "purna") {
        return VariableDeclaration::INT;
    } else if (tokenType == "dasa") {
        return VariableDeclaration::FLOAT;
    } else if (tokenType == "akshar") {
        return VariableDeclaration::CHAR;
    } else if (tokenType == "paath") {
        return VariableDeclaration::STRING;
    } else if (tokenType == "khali") {
        return VariableDeclaration::VOID;
    } else {
        throw std::runtime_error("Unknown token type for variable declaration");
    }
}

ASTNode* Parser::parseDeclaration(){
    std::cout << "this is inside the declaration function---------" << std::endl;
    TokenType typeT = currentToken().type;
    printToken(currentToken());

    if(typeT == TYPE){
        std::string varTypeToken = currentToken().value;
        consumeToken();
        std::string varName = currentToken().value;
        expect(ID);
        expect(END);
        std::cout << "variable declaration complete:::::::::::::::::::" << std::endl;
        VariableDeclaration::Type varType = mapTokenTypeToVarType(varTypeToken);
        return new VariableDeclaration(varType, varName);
    } else if(typeT == FUNC_DEF){
        return parseFunctionDeclaration();
    } else {
        throw std::runtime_error("Unexpected token for declaration");
    }
}

ASTNode* Parser::parse(){
    std::vector<ASTNode*> nodes;

    while(!check(END_OF_FILE)){
        if(check(TokenType::FUNC_DEF)){
            nodes.push_back(parseFunctionDeclaration());
        } else if (check(TYPE) || check(ID)){
            nodes.push_back(parseDeclaration());
        } else {
            nodes.push_back(parseStatement());
        }
    }

    return new Program(nodes);
}