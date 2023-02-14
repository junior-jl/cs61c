# Worksheet RISC-V Pipelining and Hazards CS61C FA20

## 1. Pre-Check

### 1.1. Pipelining the CPU datapath results in instructions being executed with higher latency and throughput.

**Ans**: True. The latency (time to perform one instruction) can change to a higher number because the cycle time has do be adjusted to the longest one, but it also can stay the same, however, the throughput is highly better, because there are more instructions running at once.

### 1.2. Without forwarding, data hazards will usually result in 3 stalls.

**Ans**: True. Depending on the instruction, the next one needs to wait the previous one finish the last three steps of the instruction in order to execute itself.

### 1.3. All data hazards can be resolved with forwarding.

**Ans**: False. If you have a load instruction causing a hazard (load some data from memory and put in register x, and then need the value of x in the next instruction), forwarding cannot resolve the issue and stalling is the only option.

### 1.4. Stalling is the only way to resolve control hazards.

**Ans**: False. It is not the only way, altough it can be used, but there are ways like branch prediction to resolve those.

## 2. Pipelining Registers

In order to pipeline, we add registers between the five datapath stages. Label each of the five stages (IF, ID, EX, MEM, and WB) on the diagram attached at the end of the worksheet.

### 2.1. What is the purpose of the new registers?

**Ans**: Pipelining makes possible for various instructions occur at the same time. So the new registers are needed because every instruction needs to be executed as if it is the only one being executed, so those registers contain all the values necessary for them (control signals, registers read, etc.).

### 2.2. Why do we add +4 to the PC again in the memory stage?

**Ans**: To avoid passing PC and PC+4 through the whole cycle.

### 2.3. Why do we need to save the instruction in a register multiple times?

**Ans**: In order to update the control signals every cycle. For example, the ALU has different signals on an `add` and on a `jal` instruction, and the signals must be updated to get the instruction that is on a determined stage work properly.

## 3. Performance Analysis

- Register clk-to-q 30ps
- Register setup 20ps
- Mux 25ps
- Branch comp. 75ps
- ALU 200ps
- Memory read 250ps
- Memory write 200ps
- RegFile read 150ps
- RegFile write 20ps

### 3.1. With the delays provided above for each of the datapath components, what would be the fastest possible clock time for a single cycle datapath?

**Ans**: The critical path would be:

1. Register clk-to-q (PC) 30ps
2. Memory Read (IMEM) 250ps
3. RegFile read 150ps
4. Mux + ALU 225ps
5. Memory Read (DMEM) 250ps
6. Mux + RegFile setup (Writeback) + Register setup (?) 45ps (65ps?) --- Not sure
---------------------------------------------------------------------------
950ps (970ps?)

So the maximum clock frequency would be $\frac{1}{950ps} = 1.053 GHz$ or $\frac{1}{970ps} = 1.031 GHz$.

### 3.2. What is the fastest possible clock time for a pipelined datapath?

Not sure how to interpret the delays. # TODO!!

### 3.3. What is the speedup from the single cycle datapath to the pipelined datapath? Why is the speedup less than 5?

TODO when complete question 3.2. But the speedup is less than 5 probably because of the need of pipeline registers and to adapt the stage time to the slowest one.

## 4. Hazards

One of the costs of pipelining is that it introduces three types of pipeline hazards: structural hazards, data hazards, and control hazards.

### Structural Hazards

Structural hazards occur when more than one instruction needs to use the same datapath resource at the same time. There are two main causes of structural hazards:

1. Register File - the register file is accessed both during ID, when it is read, and during WB, when it is written to. We can solve this by having separate read and write ports. To account for reads and writes to the same register, processors usually write to the register during the first half of the clock cycle, and read from it during the second half. This is also known as double pumping.
2. Memory - Memory is accessed for both instructions and data. Having a separate instruction memory (abbreviated IMEM) and data memory (abbreviated DMEM) solves this hazard.

Something to remember about structural hazards is that they can always be resolved by adding more hardware.

### Data Hazards

Data hazards are caused by data dependencies between instructions. In CS 61C, where we will always assume that instructions are always going through the processor in order, we see data hazards when an instruction **reads** a register before a previous instruction has finished **writing** to that register.

#### Forwarding

Most data hazards can be resolved by forwarding, which is when the result of the EX or MEM stage is sent to the EX stage for a following instruction to use.

### 4.1. Look for data hazards in the code below, and figure out how forwarding could be used to solve them.

![image](https://user-images.githubusercontent.com/69206952/218600214-9326ef03-ce65-4f5d-bd6c-830d9179f372.png)

**Ans**: Two data hazards. Cycles C4 and C5 need the value of `t0`, but it is only updated after C5, so this can be solved by forwarding the output of C3 EX to C4 EX and C5 EX.

### 4.2. Imagine you are a hardware designer working on a CPU's forwarding control logic. How many instructions after the addi instruction could be affected by data hazards created by this addi instruction.

**Ans**: At most, three instructions. If the next three instructions use the value of `t0`, their instruction decode phase would be performed before the writeback phase for the addi instruction.

### Stalls

### 4.3. Look for data hazards in the code below. One of them cannot be solved with forwarding - why? What can we do to solve this hazard?

![image](https://user-images.githubusercontent.com/69206952/218601320-4331bb51-212d-4681-98b0-6d370fd3949e.png)

**Ans**: The data hazard between the instruction 2 and 3 is similar to the ones above, it can be solved with forwarding. But there's also a data hazard between 3 and 4. The data address value can only be used at the and of the MEM stage in C6, but that value is need at the begining at the EX phase for instruction 4 (C6), so it's needed before, this can only be solved stalling, adding a `nop` instruction.

### 4.4. Say you are the compiler and can re-order instructions to minimize data hazards while guaranteeing the same output. How can you fix the code above?

**Ans**: The order 2-1-3-4 would solve the first data hazard, but there would still be the second one. 2-3-1-4 would solve the second one and maintain the first. The best order would be 2-3-1-4.

### Detecting Data Hazards

Say we have the rs1, rs2, RegWEn, and rd signals for two instructions (instruction n and instruction n + 1) and we wish to determine if a data hazard exists across the instructions. We can simply check to see if the rd for instruction n matches either rs1 or rs2 of instruction n + 1, indicating that such a hazard exists (think, why does this make sense?).

We could then use our hazard detection to determine which forwarding paths/number of stalls (if any) are necessary to take to ensure proper instruction execution. In pseudo-code, this could look something like the following:

```
if (rs1(n + 1) == rd(n) || rs2(n + 1) == rd(n) && RegWen(n) == 1) {
  forward ALU output of instruction n
}

```

### Control Hazards

Control hazards are caused by **jump and branch instructions**, because for all jumps and some branches, the next PC is not PC + 4, but the result of the computation completed in the EX stage. We could stall the pipeline for control hazards, but this decreases performance.

### 4.5. Besides stalling, what can we do to resolve control hazards?

There is the method of branch prediction, in which we try to predict if the branch is going to be taken or not, and if our guess is wrong, just 'throw away' what was going to be done and update PC properly.

### Extra for Experience

### 4.6. Given the RISC-V code below and a pipelined CPU with no forwarding, how many hazards would there be? What types are each hazard? Consider all possible hazards from all pairs of instructions.

**Ans**: How many stalls would there need to be in order to fix the data hazard(s)? What about the control hazard(s)?

![image](https://user-images.githubusercontent.com/69206952/218605522-6ab46cc7-ea5f-4a12-9290-8c3f5b9761c1.png)

**Ans**: 

1. Between 1 and 2 (data hazard) because of `t1`. Solved with 2 stalls.
2. Between 2 and 3 (data hazard) because of `s0`. Solved with 2 stalls.
3. Between 2 and 4 (data hazard) because of `s0`. Would already be solved with the stalls from the previous error.
4. Between 4 and 5 (control hazard). Two stalls needed or branch prediction.

![image](https://user-images.githubusercontent.com/69206952/218606170-66e723dc-75d6-4135-b57f-11bfae7e1732.png)
