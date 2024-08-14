#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

#include<string>
#include<unordered_map>

class SymbolTable{
    std::unordered_map<std::string, std::string> table;

    public:
        void declareVariable(const std::string& name, const std::string& type);
        std::string lookupVariable(const std::string& name);
};

#endif SYMBOL_TABLE_H