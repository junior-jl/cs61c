# Worksheet - RISC-V Single Cycle Datapath Fall 2020 CS61C

## 1. Pre-Check

### 1.1. The single cycle datapath makes use of all hardware units for each instruction.

**Ans**: False. Even though all units are avaliable for the single instruction, parts of the datapath not needed for the instruction do not need to work (can be ignored with signals from control unit).

### 1.2. It is possible to execute the stages of the single cycle datapath in parallel to speed up execution of a single instruction.

**Ans**: False. The stages are designed in a way that the 'input' depends on the 'output' from the last stage. For example, you cannot execute a shift on the ALU without decoding the instruction before.

### 1.3. Combinational logic is only used in the instruction decode stage.

**Ans**: False. There are multiplexers in other stages, like ALU operations.

## 2. Single-Cycle CPU

### 2.1. For this worksheet, we will be working with the single-cycle CPU datapath below.

![image](https://user-images.githubusercontent.com/69206952/218565086-0cec9eb0-ed07-4107-b5aa-6d4b84496260.png)

#### a) On the datapath, fill in each **round** box with the name of the datapath component, and each **square** box with the name of the control signal.

**Ans**:

![Datapath filled](https://user-images.githubusercontent.com/69206952/218567689-c486b2cd-be38-4d32-8d55-e11425962be1.png)

#### b) Explain what happens in each dapatath stage.

**Ans**:

- **IF** (Instruction Fetch): the current instruction is fetched. The instruction pointed by the Program Counter is the output of the Instruction Memory.
- **ID** (Instruction Decode): the instruction fetched is decoded. Based on the opcode, it is possible to know the instruction type. With the type, the rest of the information needed to execute the instruction can be extracted. Here the control signals and immediates are generated and the registers are read.
- **EX** (Execute): the operation of the instruction is done (arithmetic operation between registers/immediates, comparison...).
- **MEM** (Memory): if the instruction requires access to memory, it is done in this step. Writing in or reading from it.
- **WB** (Writeback): the result of the operations, data from the memory or the new value of PC is written back in a register or in PC.

### 2.2. Fill out the following table with the control signals for each instruction based on the datapath on the previous page. Wherever possible, use * to indicate that what this signal is does not matter (as in, letting the value be whatever it wants won't affect the execution of the instruction). If the value of the signal does matter for correct execution, but can vary, list all of the values (for example, for a signal that matters with possible values of 0 and 1, write 0/1).

**Ans**:

Meaning of signals:
- BrEq - 1 if register values are equal, else 0.
- BrLT - 1 if register value 1 is less than register value 2, else 0.
- PCSel - PC = PC + 4 if 0, PC = ALU_OUT if 1.
- ImmSel - mode of operation of the generator (type of the instruction).
- BrUn - 0 if comparison between signed numbers, 1 to compare number as unsigned.
- ASel - First input of the ALU (0 - rs1, 1 - pc).
- BSel - Second input of the ALU (0 - rs2, 1 - immediate).
- ALUSel - operation to be performed by the ALU.
- MemRW - 0 if read from the memory, 1 if write into memory.
- RegWEn - 0 if not writing into registers, 1 if need to write.
- WBSel - Decides what to write into register, 0 - mem_out, 1 - alu_out, 2 - pc + 4.

|      | BrEq | BrLT | PCSel | ImmSel | BrUN | ASel | BSel | ALUSel | MemRW | RegWEn | WBSel |
|:----:|:----:|:----:|:-----:|:------:|:----:|:----:|:----:|:------:|:-----:|:------:|:-----:|
|  add |   *  |   *  |   0   |    *   |   *  |   0  |   0  |   add  |   *   |    1   |   1   |
|  ori |   *  |   *  |   0   |    I   |   *  |   0  |   1  |   or   |   *   |    1   |   1   |
|  lw  |   *  |   *  |   0   |    I   |   *  |   0  |   1  |   add  |   0   |    1   |   2   |
|  sw  |   *  |   *  |   0   |    S   |   *  |   0  |   1  |   add  |   1   |    0   |   *   |
|  beq |  0/1 |   *  |  0/1  |   SB   |   *  |   1  |   1  |   add  |   0   |    0   |   *   |
|  jal |   *  |   *  |   1   |   UJ   |   *  |   1  |   1  |   add  |   0   |    1   |   0   |
| bltu |   *  |  0/1 |  0/1  |   SB   |   1  |   1  |   1  |   add  |   0   |    0   |   *   |

### 2.3. Clocking methodology

- A **state element** is an element connected to the clock (denoted by a triangle at the bottom). The **input signal** to each state element must stabilize before each **rising edge**.
- The **critical path** is the longest delay path between state elements in the circuit. The circuit cannot be clocked faster than this, since anything faster would mean that the correct value is not guaranteed to reach the state element in the alloted time. If we place registers in the critical path, we can shorten the period by **reducing the amount of logic between registers**.

For this exercise, assume the delay for each stage in the datapath is as follows:

IF: 200ps     ID: 100ps     EX: 200ps     MEM: 200ps      WB: 100ps

#### a) Mark the stages of the datapath that the following instructions use and calculate the total time needed to execute the instruction.

**Ans**:

|      | IF | ID | EX | MEM | WB | Total Time |
|:----:|:--:|:--:|:--:|:---:|:--:|:----------:|
|  add |  x |  x |  x |     |  x |    600ps   |
|  ori |  x |  x |  x |     |  x |    600ps   |
|  lw  |  x |  x |  x |  x  |  x |    800ps   |
|  sw  |  x |  x |  x |  x  |    |    700ps   |
|  beq |  x |  x |  x |     |    |    500ps   |
|  jal |  x |  x |  x |     |  x |    600ps   |
| bltu |  x |  x |  x |     |    |    500ps   |

#### b) Which instruction(s) exercise the critical path?

**Ans**: The load instruction.

#### c) What is the fastest you could clock this single cycle datapath?

**Ans**: Based on the critical path, it takes 800ps. So the maximum clock frequency is $\frac{1}{800ps} = 1.25GHz$.

#### d) Why is the single cycle datapath inneficient?

**Ans**: Because there are a lot of idle time for every component. For example, while the instruction is fetched, the ALU is idle, it could have been used.

#### e) How can you improve its performance? What is the purpose of pipelining?

**Ans**: As said on the question above, one can improve the performance of a processor with pipelining, making use of all the components in the datapath without letting them go idle.
