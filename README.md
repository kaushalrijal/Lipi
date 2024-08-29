# LIPI Documentation

Welcome to the LIPI documentation! This guide will help you understand how to write and execute code in LIPI language.

## Basic Syntax

### Program Structure

A program is a sequence of statements, each ending with a semicolon `;`.

```sh
statement1;
statement2;
```

## Keywords

The following keywords are reserved and cannot be used as identifiers:

  `bhana` `suna` `purna` `dasa` `akshar` `paath` `khali` `yadi` `anyatha` `jabasamma` `lagi` `kaam` `firta` `thik` `bethik`

## Statements

### Print Statement

1. Use `bhana` to print a value or expression to the output.

*Syntax:*

```sh
bhana(expression);
```

*Example:*

```sh
bhana(5 + 3);  // Output: 8
bhana("Hello, World!");  // Output: Hello, World!
```

### Input Statement

2. Use `suna` to read a value from the user and store it in a variable.

*Syntax:*

```sh
suna(variable_name);
```

*Example:*

```sh
purna name; // Declares an purna variable `name`
suna(name);  // Reads input into the variable `name`
bhana(name);  // Prints the value of the variable `name`
```

### Declaration Statement

3. Use `purna` or `dasa` for your specific identifier. You cannot initialize a variable at the time of declaration.

*Syntax:*

```sh
//Syntax Error - Not Working 
type variable_name = value;

//Working
type variable_name;
vaiable_name = value;
```

*Examples:*

```sh
purna age;  // Declares an integer variable `age`
dasa salary;  // Declares a decimal variable `salary`
```

### Assignment Statement

4. Use your own `Identifier` to assign a value to an existing variable.

*Syntax:*

```sh
variable_name = expression;
```

*Examples:*

```sh
age = 31;  // Assigns the value 31 to the variable `age`
```

### If Statement

5. Use `yadi` to execute a block of code conditionally. You can include an `anyatha` block for the else condition.

*Syntax:*

```sh
yadi(expression) {
    //if block of code
}anyatha {
    // else block of code
}
```

*Examples:*

```sh
yadi(age > 18) {
    bhana("Adult");
}anyatha {
    bhana("Minor");
}
```

### While Statement

6. Use `jabasamma` to repeat a block of code while a condition is true.

*Syntax:*

```sh
jabasamma(expression) {
    // block of code
}
```

*Examples:*

```sh
jabasamma(age < 30) {
    age = age + 1;
}
```

### For Statement

7. Use `lagi` to loop through a range of values, specifying initialization, condition, and update.

*Syntax:*

```sh
lagi(initialization; condition; update) {
    // block of code
}
```

*Examples:*

```sh
lagi(i = 0; i < 10; i = i + 1) {
    bhana(i);
}
```

### Function Definition

8. Use `kaam` to define a new function.

*Syntax:*

```sh
kaam return_type function_name(parameter_list) {
    // block of code
}
```

*Examples:*

```sh
kaam purna add(purna a, purna b) {
    firta a + b;
}
```

### Return Statement

9. Use `firta` to return a value from a function.

*Syntax:*

```sh
firta(expression);
```

*Examples:*

```sh
firta result;
```

## Expressions

### Basic Expressions

10. You can perform operations with numbers, strings, and other values.

*Syntax:*

```sh
term { (`+` | `-` | `*` | `/`) term }
```

*Examples:*

```sh
5 + 3 * 2
```

### Logical Expressions

11. Combine logical terms using `&&`, `||`, or `!` to form complex conditions.

*Syntax:*

```sh
logical_term { ("&&" | "||" | "!") logical_term }
```

*Examples:*

```sh
age > 18 && age < 65
```

### Comparison

12. Compare values using operators like `==`, `!=`, `<`, `<=`, `>`, and `>=`.

*Syntax:*

```sh
expression (== | != | < | <= | > | >=) expression
```

*Examples:*

```sh
age == 30
```

### Modulo Expression

13. Calculate the remainder of a division using `%`.

*Syntax:*

```sh
expression % expression
```

*Examples:*

```sh
10 % 3  // Results in 1
```

## Data Types

- `purna`: Integer
- `dasa`: Decimal
- `akshar`: Character
- `paath`: String
- `khali`: Void

*Examples:*

```sh
purna count;  // Declare an integer variable
dasa price;   // Declare a decimal variable
akshar ch;  // Declare a character variable
paath name;  // Declare a string variable
khali nothing;  // Declare a void variable
```

## Identifiers and Literals

- *Identifier:* A name for a variable or function, starting with a letter or underscore, followed by letters, numbers, or underscores (e.g., variable1, _temp).
- *Number:* An integer or decimal value (e.g., 42, 3.14).
- *String:* A sequence of characters enclosed in double quotes (e.g., "Sample text").
- *Character:* A single character enclosed in single quotes (e.g., 'A').


### Code to take input and display the output

*Examples:*

```sh
purna age;
paath name;
akshar gender;

bhana("Enter your name : ");
suna(name);

bhana("Enter your age : ");
suna(age);

bhana("Enter f or m for gender : ");
suna(gender);
bhana("\n");

bhana("Your name is ");
bhana(name);

bhana("\nYour age is ");
bhana(age);

bhana("\n");

yadi(gender == 'f'){
    bhana("You are Female");
}anyatha{
    bhana("You are Male");
}

```
*OUTPUT:*
```sh
Enter your name : hari
Enter your age : 19
Enter f or m for gender : m

Your name is hari
Your age is 19
You are Male
```

---

## Building the Project

### Prerequisites

- CMake 3.10 or higher
- A C++ compiler (e.g., g++, clang++)

### Steps

1. **Clone the Repository**:

    ```sh
    git clone https://github.com/yourusername/lipi.git
    cd lipi
    ```

2. **Create a Build Directory**:

    ```sh
    mkdir build
    cd build
    ```

3. **Run CMake**:

    ```sh
    cmake ..
    ```
    or if this doesn't work then
    ```sh
    cmake -G "MinGW Makefiles" ..
    ```

5. **Build the Project**:

    ```sh
    make
    ```

## Running the Compiler

To run the compiler on a source file:

```sh
./lipi path/to/your/source_file.lipi
```
---

### Team Members Names
---
1. Kaushal Rijal
2. Hariom Raj Chauhan
3. Prasant Roy
4. Guru Prakash Gupta
---
##### Copyrights 2024


