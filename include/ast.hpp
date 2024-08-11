#ifndef AST_HPP
#define AST_HPP

#include <iostream>
#include <vector>

enum class ASTNodeType {
    PROGRAM,
    STATEMENT_LIST,
    BHANA_STMT,
    SUNA_STMT,
    JABASAMMA_LOOP,
    LAGI_LOOP,
    YADI_STMT,
    ANYATHA_STMT,
    KAAM_DECL,
    FIRTA_STMT,
    PURNADATA_TYPE,
    DASADATA_TYPE,
    AKSHAR_DATA_TYPE,
    PAATH_DATA_TYPE,
    VARIABLE,
    EXPRESSION,
    TERM,
    FACTOR,
    NUMBER,
    STRING,
    UNKNOWN
};

class ASTNode {
public:
    ASTNode(ASTNodeType type, std::string value);
    virtual ~ASTNode();

    void addChild(ASTNode* child);
    void print(int indent);

    ASTNodeType getType() { return type; }
    std::string getValue() { return value; }

private:
    ASTNodeType type;
    std::string value;
    std::vector<ASTNode*> children;
};

#endif  // AST_HPP