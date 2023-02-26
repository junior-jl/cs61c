# Worksheet Caches - CS61C Fall 2020

## 1. Pre-Check

This section is designed as a conceptual check for you to determine if you conceptually understand and have any misconceptions about this topic. Please answer true/false to the following questions, and include an explanation:

### 1.1. For the same cache size and block size, a 4-way set associative cache will have fewer index bits than a direct-mapped cache.

**Ans**: True. The direct mapped cache will have 4 times more addresses to index, so it needs to more bits.

### 1.2. Any cache miss that occurs when the cache is full is a capacity miss.

**Ans**: False. There can still be conflict misses.

### 1.3. Increasing cache size by adding more blocks always improves (increases) hit rate.

**Ans**: False. That depends on the application, but for example, this can lead to more compulsory misses.

## 2. Understanding T/I/O

When working with caches, we have to be able to break down the memory addresses we work with to understand where they fit into our caches. There are three fields:

- **T**ag - Used to distinguish different blocks that use the same index. Number of bits: (# of bits in memory address) - Index bits - offset bits
- **I**ndex - The set that this piece of memory will be placed in. Number of bits: $log_2$(# of indices)
- **O**ffset - The location of the byte in the block. Number of bits: $log_2$(size of block)

Given these definitions, the following is true:

$log_2$(memory size) = address bit-width = # tag bits + # index bits + # offset bits

Another useful equality to remember is:

$$cache \ size = block \ size * num \ blocks$$


### 2.1. Assume we have a direct-mapped byte-addressed cache with capacity 32B and block size of 8B. Of the 32 bits in each address, which bits do we use to find the index of the cache to use?

**Ans**: Since we have 8 bytes in a block, we need 3 bits for the offset. A 32B cache divided by 8B blocks gives 4 blocks in the cache, so we need 2 bits for the index. Hence, the 3 LSB are for the offset and the 2 bits after that are the index. $ADDRESS[3:4]$.

### 2.2. Which bits are our tag bits? What about our offset?

**Ans**: In the previous answer we saw that the offset is $ADDRESS[0:2]$ and tag bits are the remaining bits, so $ADDRESS[5:31]$.

### 2.3. Classify each of the following byte memory accesses as a cache hit (H), cache miss (M), or cache miss with replacement (R). Tip: Drawing out the cache can help you see the replacements more clearly.

**Ans**:

| **Address** | **T/I/O** | **Hit, Miss, Replace** |
|:-----------:|:---------:|:----------------------:|
|  0x00000004 |   0/0/4   |      M, compulsory     |
|  0x00000005 |   0/0/5   |            H           |
|  0x00000068 |   3/1/0   |      M, compulsory     |
|  0x000000C8 |   6/1/0   |       R, conflict      |
|  0x00000068 |   3/1/0   |       R, conflict      |
|  0x000000DD |   6/3/5   |      M, compulsory     |
|  0x00000045 |   2/0/5   |       R, conflict      |
|  0x00000004 |   0/0/4   |       R, capacity      |
|  0x000000C8 |   6/1/0   |       R, capacity      |

## 3. Cache Associativity

In the previous problem, we had a Direct-Mapped cache, in which blocks map to specifically one slot in our cache. This is good for quick replacement and finding out block, but not good for efficiency of space!

This is where we bring associativity into the matter. We define associativity as the number of slots a block can potentially map to in our cache. Thus, a Fully-Associative cache has the most associativity, meaning every block can go anywhere in the cache.

For an N-way associative cache, the following is true:

$$N * num \ sets = num \ blocks$$

### 3.1. Here's some practice involving a 2-way set associative cache. This time we have an 8-bit address space, 8 B blocks, and a cache size of 32 B. Classify each of the following accesses as a cache hit (H), cache miss (M) or cache miss with replacement (R). For any misses, list out which type of miss it is. Assume that we have an LRU replacement policy (in general, this is not the case).

**Ans**: The offset bits are the same, but the index only needs one bit.

| **Address** | **T/I/O** | **Hit, Miss, Replace** |
|:-----------:|:---------:|:----------------------:|
| 0b0000 0100 |   0/0/4   |      M, compulsory     |
| 0b0000 0101 |   0/0/5   |            H           |
| 0b0110 1000 |   6/1/0   |      M, compulsory     |
| 0b1100 1000 |   12/1/0  |      M, compulsory     |
| 0b0110 1000 |   6/1/0   |            H           |
| 0b1101 1101 |   13/1/5  |       R, conflict      |
| 0b0100 0101 |   4/0/5   |      M, compulsory     |
| 0b0000 0100 |   0/0/4   |            H           |
| 0b1100 1000 |   12/1/0  |       R, capacity      |

### 3.2. What is the rate of our above accesses?

**Ans**: 1/3.

## 4. The 3 C's of Cache Misses

### 4.1. Go back to questions 2 and 3 and classify each M and R as one of the 3 types of misses described below:

1. Compulsory: First time you ask the cache for a certain block. A miss that must occur when you first bring in a block. Reduce compulsory misses by having longer cache lines (bigger blocks), which bring in the surrounding addresses along with our requested data. Can also pre-fetch blocks beforehand using a hardware prefetcher (a special circuit that tries to guess the next few blocks that you will want).
2. Conflict: Occurs if, hypothetically, you went through the ENTIRE string of accesses with a fully associative cache (with an LRU replacement policy) and wouldn't have missed for that specific access. Increasing the associativity or improving the replacement policy would remove the miss.
3. Capacity: Capacity misses are independent of the associativity of your cache. If you hypothetically ran the ENTIRE string of memory accesses with a fully associative cache (with an LRU replacement policy) of the same size as your cache, and it was a miss for that specific access, then this miss is a capacity miss. The only way to remove the miss is to increase the cache capacity.

Note: The test you can use to see if a miss is a conflict miss is the same as the test you can use to see if a miss is a capacity miss.

Note: There are many different ways of fixing misses. The name of the miss doesn't necessarily tell us the best way to reduce the number of misses.

### 5. Code Analysis

Given the follow chunk of code, analyze the hit rate given that we have a byte-addressed computer with a total memory of 1 MiB. It also features a 16 KiB Direct-Mapped cache with 1 KiB blocks. Assume that your cache begins cold.

```c
# define NUM_INTS 8192  // 2^13
int A[NUM_INTS];        // A lives at 0x10000
int i, total = 0;
for (i = 0; i < NUM_INTS; i += 128) {
    A[i] = i;           // Line 1
}
for (i = 0; i < NUM_INTS; i += 128) {
    total += A[i];      // Line 2
}

```

### 5.1. How many bits make up a memory address on this computer?

**Ans**: $log_2(1MiB) = log_2(2^20) = 20$.

### 5.2. What is the T:I:O breakdown?

**Ans**: We have 16KiB/1KiB (16) blocks, so the index needs 4 bits. To address 1KiB (2^10), we need 10 bits on the offset. So, the 6 MSB are for the tag.

### 5.3. Calculate the cache hit rate for the line marked Line 1:

**Ans**: Supposing a 4-bit integer, we would have the address being added to 512 bytes each iteration, since the block is 1024 bytes wide, it would have 2 accesses per block. The first one is always a compulsory miss and the second would be a hit, so 50\%.

### 5.4. Calculate the cache hit rate for the line marked Line 2:

**Ans**: Same as before. (? not sure)

## 6. AMAT

Recall that AMAT stands for Average Memory Access Time. The main formula for it is:

$$AMAT = Hit \ Time + Miss \ Rate * Miss \ Penalty$$

In a multi-level cache, there are two types of miss rates that we consider for each level.

**Global**: Calculated as the number of accesses that missed at that level divided by the total number of accesses to the cache system.
**Local**: Calculated as the number of accesses that missed at that level divided by the total number of accesses to that cache level.

### 6.1. An L2$, out of 100 total accesses to the cache system, missed 20 times. What is the global miss rate of L2$?

**Ans**: 20\%.

### 6.2. If L1$ had a miss rate of 50\%, what is the local miss rate of L2$?

Suppose your system consists of:

1. An L1$ that has a hit time of 2 cycles and has a local miss rate of 20\%.
2. An L2$ that has a hit time of 15 cycles and has a global miss rate of 5\%.
3. Main memory where accesses take 100 cycles.

**Ans**: Question looks inconsistent because of global miss rate given to L2, but... using the data from 6.1. we have 40\%.

$$ LMR = \frac{L2 \ misses}{L2 \ accesses} = \frac{20}{L1 \ misses} = \frac{20}{0.5 \times accesses} = \frac{20}{50} = 0.4 $$

### 6.3. What is the local miss rate of L2$?

**Ans**: 

$$LMR = \frac{0.05}{0.2} = 0.25$$

### 6.4. What is the AMAT of the system?

**Ans**:

$$AMAT = 2 + 0.2 \times (15 + 0.25 \times 100) = 10 \ cycles$$

### 6.5. Suppose we want to reduce the AMAT of the system to 8 cycles or lower by adding in a L3$. If the L3$ has a local miss rate of 30\%, what is the largest hit time that the L3$ can have?

$$8 = 2 + 0.2 \times (15 + 0.25 \times (HIT \ TIME \ L3 + 0.3 \times 100)) $$

$$HIT \ TIME \ L3 = 30 \ cycles$$
