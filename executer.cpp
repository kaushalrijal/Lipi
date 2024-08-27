
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <string>

void generateCppFile(const std::string &code, const std::string &filename)
{
    std::ofstream outFile(filename);
    if (outFile.is_open())
    {
        outFile << code;
        outFile.close();
    }
    else
    {
        std::cerr << "Failed to open file for writing C++ code." << std::endl;
    }
}

bool compileCppFile(const std::string &filename, const std::string &outputBinary)
{
    std::string command = "g++ " + filename + " -o " + outputBinary;
    int result = std::system(command.c_str());
    return result == 0; // Return true if compilation was successful.
}

std::string runBinary(const std::string &binaryName)
{
    std::string outputFileName = "output.txt";
    std::string command;

#ifdef _WIN32
    // Windows
    command = binaryName + ".exe";
#else
    // Unix-like systems (Linux, macOS, etc.)
    command = "./" + binaryName;
#endif

    std::system(command.c_str());

    // Read the output from the file.
    std::ifstream inFile(outputFileName);
    std::string output((std::istreambuf_iterator<char>(inFile)), std::istreambuf_iterator<char>());
    inFile.close();

    // Remove the output file after reading.
    std::remove(outputFileName.c_str());

    return output;
}

int main()
{   
    // 1. Read the generated code from the file.
    std::string generatedCode;
    std::ifstream tempFile("temp.txt");

    if (tempFile.is_open())
    {
        generatedCode.assign((std::istreambuf_iterator<char>(tempFile)),
                             std::istreambuf_iterator<char>());
        tempFile.close();
    }
    else
    {
        std::cerr << "Failed to open test.txt file for reading." << std::endl;
        return 1;
    }

    // 2. Define file names for the temp C++ file and binary.
    std::string cppFilename = "temp_program.cpp";
    std::string binaryFilename = "temp_program";

    // 3. Write the generated code to a file.
    generateCppFile(generatedCode, cppFilename);

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

    return 0;
}
