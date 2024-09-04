# LIPI: Aba Code Nepali Ma

## Table of Contents
- [Introduction](#introduction)
- [Team Members](#team-members)
- [Building the Project](#building-the-project)
	- [Prerequisites](#prerequisites)
	- [Steps](#steps)
- [Running the Compiler](#running-the-compiler)
- [Documentation](#documentation)
- [Contributions and Discussion](#contributions-and-discussion)

## Introduction
Lipi is a high-level, Nepali-inspired programming language designed to be both expressive and accessible. It combines the simplicity of Nepali syntax with the power of modern programming concepts. Lipi is a versatile language that can be used for a variety of applications, from basic scripts to complex programs.

Lipi includes a core set of language elements:

-   Lipi supports fundamental constructs like variable declarations, assignments, and a range of expressions including arithmetic and logical operations.
-   It offers control structures such as if-statements, loops, and function definitions, enabling users to write both simple and complex logic.
-   Functions in Lipi are defined using Nepali terms, allowing for reusable code blocks and modular programming

Lipi can be utilised for various programming tasks:

-   **Script Writing**: Ideal for writing simple scripts and automating tasks, Lipi’s clear syntax helps users quickly implement solutions without unnecessary complexity.
-   **Application Development**: With its support for functions, control flow, and modular design, Lipi is suited for developing more intricate applications where readability and maintainability are crucial.

This project was developed for the ACES C++ Project Demonstration.

## Team Members 
1. [Kaushal Rijal](https://github.com/kaushalrijal)
2. [Hariom Raj Chauhan](https://github.com/HariomRajChauhan)
3. [Prasant Roy](https://github.com/Prashantt6)
4. [Guru Prakash Gupta](https://github.com/guptaguruprakash)

## Building the Project 
### Prerequisites
- CMake 3.10 or higher
- A C++ compiler (e.g., g++, clang++)
### Steps
1.  **Clone the Repository**:
	```sh
	git clone https://github.com/yourusername/lipi.git
	cd lipi
	```
2.  **Create a Build Directory**:
	```sh
	mkdir build
	cd build
	```
3.  **Run CMake**:
	```sh
	cmake ..
	```
	if you don't have nmake then
	```sh
	cmake -G "MinGW Makefiles" ..
	```
4.  **Build the Project**:
	```sh
	make
	```
## Running the Compiler
Once the build process is complete, an executable named Lipi.exe is formed inside the build directory. You can execute it from there, or copy it to desired location and use it as per needs. While in the same directory as the executable in the terminal:
```sh
.\lipi  path/to/your/source_file.lipi
```
## Documentation
For detailed documentation, please refer to [docs/README.md](docs/README.md).

## Contributions and Discussion

We welcome contributions and feedback from the community. If you encounter any issues or have suggestions for improvements, please open an issue on our GitHub repository or submit a pull request. We appreciate your support and look forward to collaborating with you!