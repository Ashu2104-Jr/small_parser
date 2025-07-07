This project is a lightweight parser and compiler for a custom-designed programming language with a syntax close to low-level languages. It performs the following:

Lexical Analysis: Reads and tokenizes the input source code.
Syntax Checking: Validates the custom language syntax and identifies any errors.
Error Reporting: Displays clear error messages with line numbers and descriptions of what went wrong.
Code Generation: Converts error-free source code into equivalent low-level assembly-like instructions.
Execution: Produces the final output based on the generated low-level code.

Language Features
Looping Constructs: Supports loop structures for repeated execution.
Conditional Logic: Implements if, else, and related conditional expressions.
Function Calls: Enables definition and invocation of user-defined functions.
This tool is ideal for exploring how compilers work, experimenting with custom syntax design, and translating structured logic into low-level instruction sequences.

Instructions to use this code 
  1.Prepare an ARM Environment
  This compiler generates ARM assembly code. To assemble and execute it, you need an ARM environment such as:
    An ARM-based development board (e.g., Raspberry Pi)
    An ARM emulator (e.g., QEMU)
    A cross-compilation toolchain for ARM on your system
  2.Use the run.sh Script (linux bash file)
    After setting up the environment, simply run the provided script to compile your code and generate the output files automatically:
    The run.sh script will:
      Compile your C code and provide output file as a assembly file (.s)
      execute the ARM assembly output file
      and provide output like "output='your output'"
  
