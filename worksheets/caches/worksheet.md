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
