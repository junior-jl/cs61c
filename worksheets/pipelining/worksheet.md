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
