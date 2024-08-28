#include <iostream>
#include "parser.hpp"
#include <stdexcept>

Parser::Parser(std::vector<Token>& tok) : tokens(tok), current(0) {};

// Return Current Token
Token& Parser::currentToken(){
    if(current>=tokens.size()){
        throw std::runtime_error("SyntaxError: aru TOKEN baaki chhainan");
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
    while (currentToken().type == TokenType::NEWLINE) {
        consumeToken();
    }
    if(currentToken().type == type){
        return true;
    }
    return false;
}

// Checks if the current token matches specific type
bool Parser::match(TokenType type) {
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
    TokenType currType = currentToken().type;
    if (!match(type)) {
        throw std::runtime_error("SyntaxError:\nAasa garieko TOKEN type: " + printTokenType(type) + "\nPaieko TOKEN: " + printTokenType(currType));
    }
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
        throw std::runtime_error("SyntaxError: VARIABLE DECLARATION ma aasa nagarieko TYPE bhettiyo");
    }
}


ASTNode* Parser::parsePrimaryExpression(){
    if(check(NUMBER)){
        int in = std::stoi(currentToken().value);
        float fp = std::stof(currentToken().value);
        consumeToken();
        if(fp == static_cast<float>(in)){
            return new IntegerLiteral(in);
        } else {
            return new FloatLiteral(fp);
        }
    } else if (check(STRING)){
        std::string value = currentToken().value;
        consumeToken();
        return new StringLiteral(value);
    } else if (check(ID)){
        std::string name = currentToken().value;
        consumeToken();

        if (match(LPAREN)) { // If followed by '(', it's a function call
            std::vector<ASTNode*> args;

            if (!match(RPAREN)) { // Check if there are arguments
                do {
                    args.push_back(parseExpression());
                } while (match(COMMA));
            }
            expect(RPAREN); // Expect closing ')'
            return new FunctionCall(name, args);
            
        }
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
        throw std::runtime_error("SyntaxError: PRIMARY EXPRESSION ma aasa nagarieko TOKEN bhetiyo");
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
        case OR:         
            return 0;
        case AND:        
            return 1;
        case EQ:         
        case NEQ:        
            return 2;
        case LT:         
        case GT:         
        case LE:         
        case GE:         
            return 3;
        case ADD:        
        case SUB:        
            return 4;
        case MUL:        
        case DIV:        
        case MOD:        
            return 5;
        default:
            return -1;  // unknown operator
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
        case LT: return BinaryOperation::LT;
        case GT: return BinaryOperation::GT;
        case LE: return BinaryOperation::LE;
        case GE: return BinaryOperation::GE;
        case AND: return BinaryOperation::AND;
        case OR: return BinaryOperation::OR;
        default:
            throw std::runtime_error("SyntaxError: nachineko BINARY OPERATOR TYPE");
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

ASTNode* Parser::parseStatement(bool isFun){
    if(match(PRINT)){ // Print Statement
        if(check(PRINT)){
            consumeToken();
        }
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
    else if (check(ID)) { // Assignment statement for predeclared variables
        std::string varName = currentToken().value;
        expect(ID);

        // Check for function call and take it on
        if (match(LPAREN)) {  // Function call detected
            std::vector<ASTNode*> args;

            if (!match(RPAREN)) { // Check if there are arguments
                do {
                    args.push_back(parseExpression());
                    args.back()->print();
                } while (match(COMMA));
            }
            if(!check(END))
                expect(RPAREN);
            
            expect(END); // Expect a semicolon at the end of the statement
            return new FunctionCallStatement(varName, args);
        }

        expect(ASSIGN);
        Expression* expr = dynamic_cast<Expression *>(parseExpression());
        expect(END);
        return new AssignmentStatement(varName, expr);
    } 
    else if (check(TYPE)) { // Assignment statement
        std::string varTypeToken = currentToken().value;
        consumeToken();
        std::string varName = currentToken().value;
        expect(ID);
        expect(END);
        VariableDeclaration::Type varType = mapTokenTypeToVarType(varTypeToken);
        return new VariableDeclaration(varType, varName);
    } 
    else if (match(IF)){
        expect(LPAREN);

        Expression* condition = dynamic_cast<Expression*>(parseExpression());
        
        expect(RPAREN);
        Statement* thenBranch = dynamic_cast<Statement*>(parseStatement());
        Statement* elseBranch = nullptr;
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
        expect(LPAREN);
        Statement* initializer = dynamic_cast<Statement *>(parseStatement());
        Expression* condition = dynamic_cast<Expression *>(parseExpression());
        expect(END);
        Statement* increment = dynamic_cast<Statement *>(parseStatement());
        expect(RPAREN);
        Statement* body = dynamic_cast<Statement *>(parseStatement());
        return new ForStatement(initializer, condition, increment, body);
    }
    else if (match(TokenType::LBRACE)) {  // Block Statement
        std::vector<ASTNode*> statements;
        while (!check(TokenType::RBRACE)) {
            // if (auto stmt = dynamic_cast<Statement*>(parseStatement())) {
            //     statements.push_back(stmt);
            // } else if (auto decl = dynamic_cast<Declaration*>(parseStatement())) {
            //     statements.push_back(decl);
            // }
            statements.push_back(parseStatement());
            if(match(RBRACE)){
                break;
            }
        }
        expect(TokenType::RBRACE);  // Ensure the closing brace is consumed
        return new BlockStatement(statements);
    }
    else if (match(TokenType::RETURN)){
        if(isFun){
            throw std::runtime_error("SyntaxError: FUNCTION bahira bata FIRTA garna mildaina");
        }
        Expression* expr = dynamic_cast<Expression*>(parseExpression());
        expect(END);

        return new ReturnStatement(expr);
    }
    else if (match(NEWLINE)){
        consumeToken();
        return nullptr;
    }
    else {
        if(match(END_OF_FILE)){
            return nullptr;
        }
        Token currToken = currentToken();
        throw std::runtime_error("SyntaxError: STATEMENTS PARSE garna asafal, bhetieyo nachaheko token: " + printTokenType(currToken.type));
    }
}

// Parse Function Decalartion
ASTNode* Parser::parseFunctionDeclaration() {
    expect(FUNC_DEF);

    Token returnTypeToken = currentToken();
    expect(TYPE);
    
    std::string functionName = currentToken().value;
    expect(ID);

    expect(LPAREN);

    std::vector<VariableDeclaration*> parameters;

    while (!match(RPAREN)) {
        Token typeToken = currentToken();
        expect(TYPE);
        std::string paramName = currentToken().value;
        expect(ID);
        parameters.push_back(new VariableDeclaration(mapTokenTypeToVarType(typeToken.value), paramName));

        if (match(COMMA)) {
            continue;
        } else {
            break;
        }
    }
    if(!check(LBRACE)){
        expect(RPAREN);
    }

    Statement* body = dynamic_cast<Statement*>(parseStatement(true));
    
    if (!body) {
        throw std::runtime_error("SyntaxError: avaid FUNCTION BODY");
    }

    VariableDeclaration* returnType = new VariableDeclaration(mapTokenTypeToVarType(returnTypeToken.value), "");

    return new FunctionDeclaration(functionName, parameters, returnType, body);
}

ASTNode* Parser::parseDeclaration(){
    TokenType typeT = currentToken().type;

    if(typeT == TYPE){
        std::string varTypeToken = currentToken().value;
        consumeToken();
        std::string varName = currentToken().value;
        expect(ID);
        expect(END);
        VariableDeclaration::Type varType = mapTokenTypeToVarType(varTypeToken);
        return new VariableDeclaration(varType, varName);
    } else if(typeT == FUNC_DEF){
        return parseFunctionDeclaration();
    } else {
        throw std::runtime_error("SyntaxError: DECLARATION ma aasa nagareko TOKEN bhettiyo: " + printTokenType(typeT));
    }
}

ASTNode* Parser::parse(){
    std::vector<ASTNode*> nodes;

    while(!check(END_OF_FILE)){
        if(check(TokenType::FUNC_DEF)){
            nodes.push_back(parseFunctionDeclaration());
        } else if (check(TYPE)){
            nodes.push_back(parseDeclaration());
        } else {
            nodes.push_back(parseStatement());
        }
    }

    return new Program(nodes);
}