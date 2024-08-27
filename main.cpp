#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

#include "lexer.hpp"
#include "parser.hpp"
#include "semantic_analyzer.hpp"
#include "code_generator.hpp"
#include "executer.hpp"
// #include "executer.cpp"

int main(int argc, char** argv){
    if(argc<2){
        std::cerr << "Arguments list cannot be empty.";
    }
    
    std::ifstream inf(argv[1]);

    if(inf.fail()){
        std::cerr << "Failed to open file " << argv[1];
    }

    std::stringstream buffer;
    buffer << inf.rdbuf();
    std::string code = buffer.str();

    // std::cout << code << std::endl;

    try{

    Lexer lexer(code);
    std::vector<Token> tokens = lexer.tokenize();

    // for(auto token : tokens){
    //     printToken(token);
    // }
    
    Parser parser(tokens);

    // std::cout << "This should print before parse function is called\n";
    ASTNode* root = parser.parse();

    // std::cout << "This should print after the parse function!";
    // root->print();

    SemanticAnalyzer semanticAnalyzer;
    semanticAnalyzer.analyze(root);

    CodeGenerator codeGenerator;
    std::string gen = codeGenerator.generate(root);

    std::cout << "Generated Code:\n" << gen << std::endl;

    std::string cppFilename = "temp_program.cpp";
    std::string binaryFilename = "temp_program";

    // 3. Write the generated code to a file.
    generateCppFile(gen, cppFilename);

    // 4. Compile the generated C++ code.
    if (compileCppFile(cppFilename, binaryFilename))
    {
        // 5. Run the compiled binary and get the output.
        std::string output = runBinary(binaryFilename);

        // Optionally, remove the binary after execution.
        std::remove(binaryFilename.c_str());
        std::remove(cppFilename.c_str());
    }
    else
    {
        std::cerr << "Compilation failed." << std::endl;
    }


    } catch(std::exception &e){
        std::cout << e.what();
    }
    
    return 0;
}