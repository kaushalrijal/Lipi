

# Documentation

## Table of Contents 
- [Preface](#preface)
- [Program Structure](#program-structure)
- [Comments](#comments)
	- [Single Line Comments](#single-line-comments) 
	- [Multi Line Comments](#multi-line-comments)
- [Keywords](#keywords)
- [Identifiers and Literals](#identifiers-and-literals)
- [Data Types](#data-types)
- [Variables](#variables)
- [Statements](#statements)
	- [Print Statement](#print-statement)
	- [Input Statement](#input-statement)
	- [Assignment Statement](#assignment-statement)
	- [If Statement](#if-statement)
	-  [While Statement](#while-statement)
	- [For Statement](#for-statement)
	- [Function Definition](#function-definition)
	- [Return Statement](#return-statement)
- [Expressions](#expressions)
	- [Basic Expressions](#basic-expressions)
	- [Logical Expressions](#logical-expressions)
	- [Comparison](#comparison)
	- [Modulo Expression](#modulo-expression)
- [Examples](#examples)
##  Preface
In Lipi, the syntax is intentionally designed to be familiar to speakers of Nepali language, making it easier to learn and use for those with a background in the Nepali, Hindi, or other Sanskrit based languages. It provides a straightforward set of constructs for defining variables, creating functions, and managing control flow, all while using Nepali keywords and expressions.

This guide assumes you have the following basic background:

- **A General Understanding of Programming Concepts**: Familiarity with fundamental programming concepts such as variables, control structures, and functions will be beneficial.
- **Basic Knowledge of Nepali Language**: Since Lipi uses
Nepali-inspired syntax, having a general understanding of Nepali
grammar and expressions will help in grasping the language’s unique constructs.
- **Some Experience with Programming**: If you are new to programming, it’s advisable to explore introductory programming tutorials or resources. While Lipi is designed to be accessible, having a foundational understanding of programming principles will make learning the language smoother.

If you’re new to programming or want to get a quick start, consider exploring introductory programming resources and tutorials. This will
help you build a solid foundation before diving into Lipi’s specific features and syntax.
  
## Program Structure
A program is a sequence of statements, each ending with a semicolon `;`.
```sh
statement1;
statement2;
```
## Comments
Comments are annotations in your code that are ignored by the compiler or interpreter. They are used for documentation, to explain, clarify, or temporarily disable parts of the code without affecting its execution. Comments are essential for documenting your code and making it easier for others (or yourself) to understand its purpose and functionality.
1. Single Line comments:
	*Syntax:*
	```
	:) This is a single line comment
	```
2. Multi Line comments:
	*Syntax:*
	```
	(: This is a
	multiline
	comment :)
	```
*Example:*
```
:) A program to demonstrate comments
(: Comments are great.
I love comments. You love comments.
Everyone loves comments. :)
```

## Keywords
The following keywords are reserved and cannot be used as identifiers:
`bhana`  `suna`  `purna`  `dasa`  `akshar`  `paath`  `khali`  `yadi`  `anyatha`  `jabasamma`  `lagi`  `kaam`  `firta`  `thik`  `bethik`

## Identifiers and Literals
-  *Identifier:* A name for a variable or function, starting with a letter or underscore, followed by letters, numbers, or underscores (e.g., _progamer, i_am_ironman33).
-  *Number:* An integer or decimal value (e.g., 42, 3.14).
-  *String:* A sequence of characters enclosed in double quotes (e.g., "Sample text").
-  *Character:* A single character enclosed in single quotes (e.g., 'A').

## Data Types
-  `purna`: Integer
-  `dasa`: Decimal
-  `akshar`: Character
-  `paath`: String
-  `khali`: Void

*Examples:*
```sh
purna  count; //  Declare  an  integer  variable
dasa  price; //  Declare  a  decimal  variable
akshar  ch; //  Declare  a  character  variable
paath  name; //  Declare  a  string  variable
khali  nothing; //  Invalid, khali is only for functions
```
## Variables
You use variables as symbolic names for values in your application. The names of variables, called identifiers, and must conform to the rules of identifiers. A variable can be declared in Lipi as:
*Syntax:*
```
type identifier;
```
Only one variable can be declared at a time and each variable must have unique identifier. Also values cannot be assigned to variables at the time of declaration.
*Example:*
```
purna x; :) Valid
purna x, y, z; :) Invalid
purna x = 5; :) Invalid
```
## Statements
### Print Statement
Use `bhana` to print a value or expression to the output.
*Syntax:*
```sh
bhana(expression);
```
*Example:*
```sh
bhana(5  +  3); //  Output:  8
bhana("Hello, World!"); //  Output:  Hello,  World!
```
### Input Statement
Use `suna` to read a value from the user and store it in a variable.
*Syntax:*
```sh
suna(variable_name);
```
*Example:*
```sh
purna  name; //  Declares  an  purna  variable  `name`
suna(name); //  Reads  input  into  the  variable  `name`
bhana(name); //  Prints  the  value  of  the  variable  `name`
```
### Assignment Statement
A value can be assigned to an existing variable. Make sure you don't assign a value at the time of declaration!
*Syntax:*
```sh
variable_name  =  expression;
```
*Examples:*
```sh
purna age;
age  =  31; //  Assigns  the  value  31  to  the  variable  `age`
```
### If Statement
Use `yadi` to execute a block of code conditionally. You can include an `anyatha` block for the else condition.
*Syntax:*
```sh
yadi(expression) {
//if  block  of  code
}anyatha {
//  else  block  of  code
}
```
*Examples:*
```sh
yadi(age  >  18) {
bhana("Adult");
}anyatha {
bhana("Minor");
}
```
### While Statement
Use `jabasamma` to repeat a block of code while a condition is true.
*Syntax:*
```sh
jabasamma(expression) {
//  block  of  code
}
```
*Examples:*
```sh
jabasamma(age  <  30) {
age  =  age  +  1;
}
```
### For Statement
Use `lagi` to loop through a range of values, specifying initialization, condition, and update.
*Syntax:*
```sh
lagi(initialization; condition; update;) {
//  block  of  code
}
```
*Examples:*
```sh
purna i;
lagi(i  =  0; i  <  10; i  =  i  +  1;) {
bhana(i);
}
```
### Function Definition
Use `kaam` to define a new function.
*Syntax:*
```sh
kaam  return_type  function_name(parameter_list) {
//  block  of  code
}
```
*Examples:*
```sh
kaam  purna  add(purna  a,  purna  b) {
firta  a  +  b;
}
```
#### Return Statement
Use `firta` to return a value from a function.
*Syntax:*
```sh
firta expression;
```
*Examples:*
```sh
firta  result;
```
## Expressions
### Basic Expressions
You can perform operations with numbers, strings, and other values.
*Syntax:*
```sh
term  { (`+`  |  `-`  |  `*`  |  `/`) term }
```
*Examples:*
```sh
5  +  3  *  2
```
### Logical Expressions
Combine logical terms using `&&`, `||`, or `!` to form complex conditions.
*Syntax:*
```sh
logical_term  { ("&&"  |  "||"  |  "!") logical_term }
```
*Examples:*
```sh
age  >  18 && age  <  65
```
### Comparison
Compare values using operators like `==`, `!=`, `<`, `<=`, `>`, and `>=`.
*Syntax:*
```sh
expression (== |  !=  |  <  |  <=  |  >  |  >=) expression
```
*Examples:*
```sh
age  ==  30
```
### Modulo Expression
Calculate the remainder of a division using `%`.
*Syntax:*
```sh
expression  %  expression
```
*Examples:*
```sh
10  %  3  //  Results  to 1
```

## Examples
For additional examples and sample programs, please refer to the [examples folder](../examples/). 
The `examples` folder contains various scripts and example programs written in Lipi that demonstrate different features and functionalities of the language. You can explore these examples to see how Lipi can be applied in real-world scenarios.