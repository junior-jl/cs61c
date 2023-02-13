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
