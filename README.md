Custom Compiler Documentation
Overview
This document provides an overview of the grammar used in the custom compiler. The grammar is designed to define the structure and syntax of a programming language that is being developed.

Grammar Structure
Program Structure
Program: The starting point of the code is a <program>, which consists of a list of statements.

php
Copy code
<program> ::= <statement_list>
Statement List: A <statement_list> can be one or more statements separated by semicolons (;).

php
Copy code
<statement_list> ::= <statement> ";" <statement_list> | <statement> ";"
Statements
A statement in the program can be one of several types:

Print Statement: Outputs the value of an expression.

go
Copy code
<print_statement> ::= "bhana" "(" <expression> ")"
Input Statement: Takes input and assigns it to an identifier.

go
Copy code
<input_statement> ::= "suna" "(" <identifier> ")"
Declaration Statement: Declares a variable with a specific type and optionally assigns a value to it.

php
Copy code
<declaration_statement> ::= <type> <identifier> "=" <expression> | <type> <identifier>
Assignment Statement: Assigns the value of an expression to an identifier.

php
Copy code
<assignment_statement> ::= <identifier> "=" <expression>
If Statement: A conditional statement that executes a block of code if the condition is true. It can also have an else block.

wasm
Copy code
<if_statement> ::= "yadi" "(" <expression> ")" <block> | "yadi" "(" <expression> ")" <block> "anyatha" <block>
While Statement: A loop that continues to execute as long as the condition is true.

go
Copy code
<while_statement> ::= "jabasamma" "(" <expression> ")" <block>
For Statement: A loop that iterates a specific number of times, with initialization, condition, and iteration steps.

go
Copy code
<for_statement> ::= "lagi" "(" <declaration_statement> ";" <expression> ";" <assignment_statement> ")" <block>
Function Definition: Defines a function with a return type, name, parameters, and a block of code.

go
Copy code
<function_definition> ::= <type> "kaam" <identifier> "(" <parameter_list> ")" <block>
Return Statement: Returns a value from a function.

go
Copy code
<return_statement> ::= "firta" <expression>
Blocks and Expressions
Block: A block of code enclosed in curly braces {}, which can contain multiple statements.

go
Copy code
<block> ::= "{" <statement_list> "}"
Expression: Represents a value or a calculation, which can involve terms and operators.

go
Copy code
<expression> ::= <term> { ("+" | "-" | "*" | "/") <term> }
               | "thik"
               | "bethik"
               | <identifier>
               | <number>
               | <string>
               | <character>
Term: A component of an expression, which can be a factor or involve multiplication/division.

bash
Copy code
<term> ::= <factor> { ("*" | "/") <factor> }
Factor: The most basic unit in an expression, which can be an identifier, number, string, character, or another expression in parentheses.

php
Copy code
<factor> ::= <identifier>
           | <number>
           | <string>
           | <character>
           | "(" <expression> ")"
Identifiers and Literals
Identifier: A name for a variable, function, or other entities in the program.

less
Copy code
<identifier> ::= [a-zA-Z_][a-zA-Z0-9_]*
Number: A numeric literal, which can be an integer or a floating-point number.

less
Copy code
<number> ::= [0-9]+ | [0-9]*\.[0-9]+
String: A sequence of characters enclosed in double quotes.

go
Copy code
<string> ::= '"' [^"]* '"'
Character: A single character enclosed in single quotes.

go
Copy code
<character> ::= "'" [^'] "'"
Data Types
Types: The language supports several data types:
purna: Integer type
dasa: Floating-point type
akshar: String type
paath: Character type
khali: Void type
go
Copy code
<type> ::= "purna" | "dasa" | "akshar" | "paath" | "khali"
Copy and paste this into your README.md file, and it will serve as the documentation for your custom compiler.