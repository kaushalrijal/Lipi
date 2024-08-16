Here's the documentation formatted for a README file:

---

# Custom Compiler Documentation

## Overview

This document provides an overview of the grammar used in the custom compiler. The grammar is designed to define the structure and syntax of a programming language that is being developed.

## Grammar Structure

### Program Structure

- **Program**: The starting point of the code is a `<program>`, which consists of a list of statements.
  ```
  <program> ::= <statement_list>
  ```

- **Statement List**: A `<statement_list>` can be one or more statements separated by semicolons (`;`).
  ```
  <statement_list> ::= <statement> ";" <statement_list> | <statement> ";"
  ```

### Statements

A statement in the program can be one of several types:

- **Print Statement**: Outputs the value of an expression.
  ```
  <print_statement> ::= "bhana" "(" <expression> ")"
  ```

- **Input Statement**: Takes input and assigns it to an identifier.
  ```
  <input_statement> ::= "suna" "(" <identifier> ")"
  ```

- **Declaration Statement**: Declares a variable with a specific type and optionally assigns a value to it.
  ```
  <declaration_statement> ::= <type> <identifier> "=" <expression> | <type> <identifier>
  ```

- **Assignment Statement**: Assigns the value of an expression to an identifier.
  ```
  <assignment_statement> ::= <identifier> "=" <expression>
  ```

- **If Statement**: A conditional statement that executes a block of code if the condition is true. It can also have an `else` block.
  ```
  <if_statement> ::= "yadi" "(" <expression> ")" <block> | "yadi" "(" <expression> ")" <block> "anyatha" <block>
  ```

- **While Statement**: A loop that continues to execute as long as the condition is true.
  ```
  <while_statement> ::= "jabasamma" "(" <expression> ")" <block>
  ```

- **For Statement**: A loop that iterates a specific number of times, with initialization, condition, and iteration steps.
  ```
  <for_statement> ::= "lagi" "(" <declaration_statement> ";" <expression> ";" <assignment_statement> ")" <block>
  ```

- **Function Definition**: Defines a function with a return type, name, parameters, and a block of code.
  ```
  <function_definition> ::= <type> "kaam" <identifier> "(" <parameter_list> ")" <block>
  ```

- **Return Statement**: Returns a value from a function.
  ```
  <return_statement> ::= "firta" <expression>
  ```

### Blocks and Expressions

- **Block**: A block of code enclosed in curly braces `{}`, which can contain multiple statements.
  ```
  <block> ::= "{" <statement_list> "}"
  ```

- **Expression**: Represents a value or a calculation, which can involve terms and operators.
  ```
  <expression> ::= <term> { ("+" | "-" | "*" | "/") <term> }
                 | "thik"
                 | "bethik"
                 | <identifier>
                 | <number>
                 | <string>
                 | <character>
  ```

- **Term**: A component of an expression, which can be a factor or involve multiplication/division.
  ```
  <term> ::= <factor> { ("*" | "/") <factor> }
  ```

- **Factor**: The most basic unit in an expression, which can be an identifier, number, string, character, or another expression in parentheses.
  ```
  <factor> ::= <identifier>
             | <number>
             | <string>
             | <character>
             | "(" <expression> ")"
  ```

### Identifiers and Literals

- **Identifier**: A name for a variable, function, or other entities in the program.
  ```
  <identifier> ::= [a-zA-Z_][a-zA-Z0-9_]*
  ```

- **Number**: A numeric literal, which can be an integer or a floating-point number.
  ```
  <number> ::= [0-9]+ | [0-9]*\.[0-9]+
  ```

- **String**: A sequence of characters enclosed in double quotes.
  ```
  <string> ::= '"' [^"]* '"'
  ```

- **Character**: A single character enclosed in single quotes.
  ```
  <character> ::= "'" [^'] "'"
  ```

### Data Types

- **Types**: The language supports several data types:
  - `purna`: Integer type
  - `dasa`: Floating-point type
  - `akshar`: String type
  - `paath`: Character type
  - `khali`: Void type
  ```
  <type> ::= "purna" | "dasa" | "akshar" | "paath" | "khali"
  ```

---

Copy and paste this into your `README.md` file, and it will serve as the documentation for your custom compiler.

Let me know if you need any further adjustments!