# CS 61C - Number Representation

## 1. Pre-Check

### 1.1. Depending on the context, the same sets of bits may represent different things.

**Ans**: True. One could represent numbers, colors, symbols...

### 1.2. It is possible to get an overflow error in Two’s Complement when adding numbers of opposite signs.

**Ans**: False. Suppose 4 bits, $-8_{10} (1000_2) + 7_{10} (0111_2) = -1_{10} (1111_2)$. 

### 1.3. If you interpret a N bit Two’s complement number as an unsigned number, negative numbers would be smaller than positive numbers.

**Ans**: False. Because of the leading 1, they would be bigger.

### 1.4. If you interpret an N bit Bias notation number as an unsigned number (assume there are negative numbers for the given bias), negative numbers would be smaller than positive numbers.

**Ans:** True. That is basically the purpose of the bias.

## 2. Unsigned Integers

### 2.1. If we have an n-digit unsigned numeral $d_{n-1}d_{n-2}\cdots d_0$ in radix (or base) r, then the value of that numeral is 

$$\sum_{i=0}^{n-1} r^id_i$$

which is just fancy notation to say that instead of a 10’s or 100’s place we have an r’s or $r^2$’s place. For the three radices binary, decimal, and hex, we just let r be 2, 10, and 16, respectively. Let’s try this by hand. Recall that our preferred tool for writing large numbers is the IEC prefixing system:

Ki (Kibi) = $2^{10}$
Mi (Mebi) = $2^{20}$
Gi (Gibi) = $2^{30}$
Ti (Tebi) = $2^{40}$
Pi (Pebi) = $2^{50}$
Ei (Exbi) = $2^{60}$
Zi (Zebi) = $2^{70}$
Yi (Yobi) = $2^{80}$

#### (a) Convert the following numbers from their initial radix into the other two common radices:

1. 0b10010011
2. 63
3. 0b00100100
4. 0
5. 39
6. 437
7. 0x0123

**Ans**: I'll assume the "common radices" are binary, decimal and hexadecimal.

1. 
$$0b\underbrace{1001}_{9}\underbrace{0011}_{3} = 93_{16} = 2^0 + 2^1 + 2^4 + 2^7 = 147_{10}$$

2.
$$63_{10} = 0b\underbrace{11}_3\underbrace{1111}_F = 3F_{16}$$

3.
$$0b\underbrace{0010}_{2}\underbrace{0100}_{4} = 24_{16} = 2^2 + 2^5 = 36_{10}$$

4.
$$0_{10} = 0_{16} = 0_2$$

5.
$$39_{10} = 0b\underbrace{10}_2\underbrace{0111}_7 = 27_{16}$$

6.
$$437_{10} = 0b\underbrace{1}_1\underbrace{1011}_B\underbrace{0101}_5 = 1B5_{16}$$

7.
$$0x0123 = 0b\underbrace{0000}_0\underbrace{0001}_1\underbrace{0010}_2\underbrace{0011}_3 = 0b100100011 = 2^0 + 2^1 + 2^5 + 2^8 = 291_{10}$$

#### (b) Convert the following numbers from hex to binary:
1. 0xD3AD
2. 0xB33F
3. 0x7EC4

**Ans**:

1.
$$0xD3AD = 0b\underbrace{1101}_D\underbrace{0011}_3\underbrace{1010}_A\underbrace{1101}_D = 0b1101001110101101$$

2.
$$0xB33F = 0b\underbrace{1011}_B\underbrace{0011}_3\underbrace{0011}_3\underbrace{1111}_F = 0b1011001100111111$$

3.
$$0x7EC4 = 0b\underbrace{0111}_7\underbrace{1110}_E\underbrace{1100}_C\underbrace{0100}_4 = 0b111111011000100$$

#### (c) Write the following numbers using IEC prefixes:

- $2^{16}$
- $2^{34}$
- $2^{27}$
- $2^{61}$
- $2^{43}$
- $2^{47}$
- $2^{36}$
- $2^{59}$

**Ans**: 

- $2^{16} = 2^6 \times 2^{10} = 64 Ki$
- $2^{34} = 2^4 \times 2^{30} = 16 Gi$
- $2^{27} = 2^7 \times 2^{20} = 128 Mi$
- $2^{61} = 2^1 \times 2^{60} = 2 Ei$
- $2^{43} = 2^3 \times 2^{40} = 8 Ti$
- $2^{47} = 2^7 \times 2^{40} = 128 Ti$
- $2^{36} = 2^6 \times 2^{30} = 64 Gi$
- $2^{59} = 2^9 \times 2^{50} = 512 Pi$

#### (d) Write the following numbers as powers of 2:

- 2 Ki
- 256 Pi
- 512 Ki
- 64 Gi
- 16 Mi
- 128 Ei

**Ans**:

- 2 Ki = $2^{11}$
- 256 Pi = $2^{58}$
- 512 Ki = $2^{19}$
- 64 Gi = $2^{36}$
- 16 Mi = $2^{24}$
- 128 Ei = $2^{67}$

## 3. Signed Integers

### 3.1. Unsigned binary numbers work for natural numbers, but many calculations use negative numbers as well. To deal with this, a number of different schemes have been used to represent signed numbers, but we will focus on two’s complement, as it is the standard solution for representing signed integers.

- Most significant bit has a negative value, all others are positive. So the value of
an n-digit two’s complement number can be written as 

$$ \sum_{i=0}^{n-2} 2^id_i - 2^{n-1}d_{n-1}$$

- Otherwise exactly the same as unsigned integers.
- A neat trick for flipping the sign of a two’s complement number: flip all the bits and add 1.
- Addition is exactly the same as with an unsigned number.
- Only one 0, and it’s located at 0b0.

For questions (a) through (c), assume an 8-bit integer and answer each one for the case of an unsigned number, biased number with a bias of -127, and two’s complement number. Indicate if it cannot be answered with a specific representation.

#### (a) What is the largest integer? What is the result of adding one to that number?
1. Unsigned?
2. Biased?
3. Two’s Complement?

**Ans**:

1. 255; Overflow -> 0
2. 128; Overflow -> -127
3. 127; Overflow -> -128

#### (b) How would you represent the numbers 0, 1, and -1?
1. Unsigned?
2. Biased?
3. Two’s Complement?

**Ans**:

1. 0b00000000, 0b00000001, -;
2. 0b01111111, 0b10000000, 0b01111110;
3. 0b00000000, 0b00000001, 0b11111111.

#### (c) How would you represent 17 and -17?
1. Unsigned?
2. Biased?
3. Two’s Complement?

**Ans**:

1. 0b00010001, -;
2. $17 - (-127) = 144 =$ 0b10010000, $-17 - (-127) = 110 =$ 0b01101110;
3. 0b00010001, 0b11101111.

#### (d) What is the largest integer that can be represented by any encoding scheme that only uses 8 bits?

**Ans**: Talking about the schemes studied until now, the largest integer would be 255. But an arbitrary scheme could represent any number.

#### (e) Prove that the two’s complement inversion trick is valid (i.e. that x and $\bar{x}$ + 1 sum to 0)

**Ans**: Given the formula for the two's complement representation, the sum of $x + \bar{x}$ is equal to -1. Thus, $x + \bar{x} + 1 = 0$.

Another way to see this is that $x + \bar{x}$ will always result in 0b111...1, so adding 1 will result in 0b000...0.

#### (f) Explain where each of the three radices shines and why it is preferred over other bases in a given context.

**Ans**: 

- The decimal radix is more familiar to humans, so it is useful to show information and in calculations;
- The hexadecimal basis is useful to transform long binary strings into more readable strings (4 bits into one hexadecimal digit);
- The binary representation is the one the computer will always use, it can describe basically anything (ON, OFF; YES, NO; etc.).

## 4. Arithmetic and Counting

### 4.1. Addition and subtraction of binary/hex numbers can be done in a similar fashion as with decimal digits by working right to left and carrying over extra digits to the next place. However, sometimes this may result in an overflow if the number of bits can no longer represent the true sum. Overflow occurs if and only if two numbers with the same sign are added and the result has the opposite sign.

#### (a) Compute the decimal result of the following arithmetic expressions involving 6-bit Two’s Complement numbers as they would be calculated on a computer.
Do any of these result in an overflow? Are all these operations possible? 

1. 0b011001 − 0b000111
2. 0b100011 + 0b111010
3. 0x3B + 0x06
4. 0xFF − 0xAA

**Ans**: 

1. 0b011001 (25) − 0b000111 (7) = 0b011001 + 0b111001 = 0b1010010 -> (Drop the leading 1) -> 0b010010 = 18. No overflow.
2. 0b100011 (-29) + 0b111010 (-6) = 0b1011101 (OVERFLOW). Using just the 6 bits, we have 0b011101 (29).
3. 0x3B (-5) + 0x06 (6) = 0b111011 + 0b000110 = 0b1000001. After truncating, we have 0b000001 (1), as expected.
4. Neither 0xFF nor 0xAA can be represented with 6 bits.

#### (b) What is the least number of bits needed to represent the following ranges using any number representation scheme.

1. 0 to 256
2. -7 to 56
3. 64 to 127 and -64 to -127
4. Address every byte of a 12 TiB chunk of memory

**Ans**:

1. 256 + 1 = 257 'things'. $\log _2 257 = 8.0056$. Thus, 9 bits;
2. 56 + 7 + 1 = 64 'things'. $\log _2 64 = 6$. Thus, 6 bits;
3. 64 + 64 = 128 'things'. $\log _2 128 = 7$. Thus, 7 bits;
4. 12 TiB = $12 \times 2^{40}$ 'things'. $\log _2 (12 \times 2^{40}) = 43.5849$. Thus, 44 bits;
