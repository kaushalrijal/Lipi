#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <filesystem>

#include "lexer.hpp"
#include "parser.hpp"
#include "semantic_analyzer.hpp"
#include "code_generator.hpp"
#include "executer.hpp"

int main(int argc, char** argv){
    if(argc<2){
        std::cerr << "ARGUMENTS khali huna paudaina!";
    }
    
    std::ifstream inf(argv[1]);

    if(inf.fail()){
        std::cerr << "FILE kholna asafal" << argv[1];
    }

    std::stringstream buffer;
    buffer << inf.rdbuf();
    std::string code = buffer.str();

    try{

    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();
    
    Parser parser(tokens);

    ASTNode* root = parser.parse();

    SemanticAnalyzer semanticAnalyzer;
    semanticAnalyzer.analyze(root);

    CodeGenerator codeGenerator;
    std::string gen = codeGenerator.generate(root);

    std::filesystem::path inputPath(argv[1]);
    std::string filenameWithoutExtension = inputPath.stem().string();

    std::string cppFilename = filenameWithoutExtension + ".cpp";
    std::string binaryFilename = filenameWithoutExtension;

    generateCppFile(gen, cppFilename);

    if (compileCppFile(cppFilename, binaryFilename))
    {
        std::string output = runBinary(binaryFilename);

        
        std::remove(binaryFilename.c_str());
        std::remove(cppFilename.c_str());
    }
    else
    {
        std::cerr << "Compilation asafal." << std::endl;
    }


    } catch(std::exception &e){
        std::cout << e.what();
    }
    
    return 0;
}