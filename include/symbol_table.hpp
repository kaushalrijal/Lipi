#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include<string>
#include<unordered_map>

enum class VarType {
    Purna,  // Integer
    Dasa,   // Float
    Akshar, // Character
    Paath,  // String
    Khali,  // Void for functions
    Thik_Bethik // Boolean
};



class SymbolTable{
    std::unordered_map<std::string, VarType> table;

    public:
        void declareVariable(const std::string& name, VarType type);
        VarType lookupVariable(const std::string& name);
};

#endif