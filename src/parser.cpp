#include "parser.hpp"
#include <stdexcept>

Parser::Parser(std::vector<Token>& tok) : tokens(tok), current(0) {};

// Return Current Token
Token& Parser::currentToken(){
    if(current>=tokens.size()){
        throw std::runtime_error("No more tokens");
    }
    return tokens[current+1];
}

// Move to next token
void Parser::consumeToken() {
    if (current < tokens.size()) {
        ++current;
    }
}

// Checks if the current token matches specific type
bool Parser::match(TokenType type) {
    if (currentToken().type == type) {
        consumeToken();
        return true;
    }
    return false;
}

// Check if the tokens matches a specific type and consume it. 
void Parser::expect(TokenType type) {
    if (!match(type)) {
        throw std::runtime_error("Unexpected token type");
    }
}

ASTNode* Parser::parsePrimaryExpression(){
    if(match(NUMBER)){
        int value = std::stoi(currentToken().value);
        consumeToken();
        return new IntegerLiteral(value);
    } else if (match(STRING)){
        std::string value = currentToken().value;
        consumeToken();
        return new StringLiteral(value);
    } else if (match(ID)){
        std::string name = currentToken().value;
        consumeToken();
        return new Variable(name);
    } else if (match(CHAR)){
        char value = currentToken().value[1];
        consumeToken();
        return new CharacterLiteral(value);
    } else if (match(LPAREN)){
        consumeToken(); // Consume '('
        ASTNode* expression = parseExpression();
        expect(RPAREN);
        return expression;
    }
    throw std::runtime_error("Unexpected token in primary expression.");
}

Expression* Parser::parseUnaryExpression(){
    if(match(SUB)|| match(NOT)){
        Token op = currentToken();
        consumeToken();

        Expression* operand = parseUnaryExpression();

        return new UnaryOperation(operand, op.type == SUB ? UnaryOperation::NEG : UnaryOperation::NOT);
    }
    parsePrimaryExpression();
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
    parseBinaryExpression();
}

ASTNode* Parser::parseStatement(){
    if(match(PRINT)){ // Print Statement
        expect(LPAREN);
        Expression* expr = dynamic_cast<Expression*>(parseExpression());
        expect(LPAREN);
        expect(END);
        return new PrintStatement(expr);
    } 
    else if(match(INPUT)){ // Input Statement
        expect(LPAREN);
        expect(ID);
        std::string vName = currentToken().value;
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
    else if (match(ID)) { // Assignment statement for predeclared variables
        std::string varName = currentToken().value;
        consumeToken();
        expect(ASSIGN);
        Expression* expr = dynamic_cast<Expression *>(parseExpression());
        expect(END);
        return new AssignmentStatement(varName, expr);
    } 
    else if (match(IF)){
        consumeToken();
        expect(LPAREN);

        Expression* condition = dynamic_cast<Expression*>(parseExpression());
        
        expect(RPAREN);
        
        Statement* thenBranch = dynamic_cast<Statement*>(parseStatement());
        Statement* elseBranch = nullptr;

        if(match(ELSE)){
            consumeToken();
            elseBranch = dynamic_cast<Statement*>(parseStatement());
        }

        return new IfStatement(condition, thenBranch, elseBranch);
    }
    else if(match(WHILE)){
        consumeToken();
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


ASTNode* Parser::parseDeclaration(){
    TokenType typeT = currentToken().type;

    if(typeT == TYPE){
        expect(TYPE);
        TokenType varType = currentToken().type;
        expect(ID);
        std::string varName = currentToken().value;
        expect(END);

        return new VariableDeclaration(static_cast<VariableDeclaration::Type>(varType), varName);
    } else if(typeT == FUNC_DEF){
        return parseFunctionDeclaration();
    } else {
        throw std::runtime_error("Unexpected token for declaration");
    }
}
