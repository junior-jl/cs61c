# CALL, RISC-V Procedures

## 1. Pre-Check

This section is designed as a conceptual check for you to determine if you conceptually understand and have any misconceptions about this topic. Please answer true/false to the following questions, and include an explanation:

### 1.1. The compiler may output pseudoinstructions.

**Ans**: True. The assembler is responsible for changing the pseudoinstructions for the real ones.

### 1.2. The main job of the assembler is to generate optimized machine code.

**Ans**: False. It is to replace pseudoinstructions.

### 1.3. The object files produced by the assembler are only moved, not edited, by the linker.

**Ans**: False. The linker will fill the blanks on some references.

### 1.4. The destination of all jump instructions is completely determined after linking.

**Ans**: False. Some references from jumps are only known at run-time.

### 2. CALL

The following is a diagram of the CALL stack detailing how C programs are built and executed by machines:

![image](https://user-images.githubusercontent.com/69206952/213331708-17723d0a-6497-456d-84ad-6c1d81834014.png)

### 2.1. What is the Stored Program concept and what does it enable us to do?

**Ans**: The store program concept is the idea that a program can be represented in the same way as data, because the instructions executed by the computer are just bytes, words, etc, just like the data that it stores. So, this allows the computer to execute more programs by just adding them to the memory, giving it the ability to perform different actions and tasks without changing the hardware.

### 2.2. How many passes through the code does the Assembler have to make? Why?

**Ans**: Two. Because in the first one, it needs to keep track of all the labels that can be referenced in the code to avoid the 'forward reference' problem. On the second one converts all instructions and replace pseudoinstructions.

### 2.3. Describe the six main parts of the object files outputted by the Assembler (Header, Text, Data, Relocation Table, Symbol Table, Debugging Information).

**Ans**: 

1. The header contains the metadata of all the other parts.
2. The text is basically the machine code itself.
3. The data is any data (byte, word, etc.) that is declared or used by the program.
4. The relocation table contains the references that will be filled by the linker.
5. The symbol table keeps track of all the labels.
6. Debugging information is some additional information that is only used for these purposes.


### 2.4. Which step in CALL resolves relative addressing? Absolute addressing?

**Ans**: The assembler converts the instructions to machine code, including the relative addresses. The linker will be responsible for combining multiple files into an executable, calculating the absolute addresses. It also updates the machine code to use absolute addresses.
