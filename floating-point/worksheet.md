# Worksheet 3 - Floating Point

## 1. Pre-Check

This section is designed as a conceptual check for you to determine if you conceptually understand and have any misconceptions about this topic. Please answer true/false to the following questions, and include an explanation:

### 1.1. True or False. The goals of floating point are to have a large range of values, a low amount of precision, and real arithmetic results

**Ans**: False. The goal is to have a large range of values, with high precision and approximate results.

### 1.2. True or False. The distance between floating point numbers increase as the absolute value of the numbers increase.

**Ans**: True. The exponent part of the number helps to represent a large range of numbers, but it also dictates by how much they are separated.

### 1.3. True or False. Floating Point addition is associative.

**Ans**: False. The approximations make the addition a non-associative operation.

## 2. Floating Point

The IEEE 754 standard defines a binary representation for floating point values using three fields.
- The sign determines the sign of the number (0 for positive, 1 for negative).
- The exponent is in **biased notation**. For instance, the bias is -127 which comes from $-(2^{8−1} − 1)$ for single-precision floating point numbers.
- The significand or mantissa is akin to unsigned integers, but used to store a fraction instead of an integer.

The below table shows the bit breakdown for the single precision (32-bit) representation. The leftmost bit is the MSB and the rightmost bit is the LSB.

|   1  |     8    |               23              |
|:----:|:--------:|:-----------------------------:|
| Sign | Exponent | Mantissa/Significand/Fraction |

For normalized floats:
Value = $(-1)^{sign} \times 2^{exponent + bias} \times 1.significand_2$
For denormalized floats:
Value = $(-1)^{sign} \times 2^{exponent + bias + 1} \times 0.significand_2$

| Exponent | Significand |  Meaning |
|:--------:|:-----------:|:--------:|
|     0    |   Anything  |  Denorm  |
|   1-254  |   Anything  |  Normal  |
|    255   |      0      | Infinity |
|    255   |   Nonzero   |    NaN   |

Note that in the above table, our exponent has values from 0 to 255. When translating between binary and decimal floating point values, we must remember that there is a bias for the exponent.

### 2.1. How many zeroes can be represented using a float?

**Ans**: Two. -0 and +0, because of the sign bit.

### 2.2. What is the largest finite positive value that can be stored using a single-precision float?

**Ans**: The largest positive number would have a sign bit 0, an exponent 1111 1110 (254) and a mantissa of 111 1111 1111 1111 1111 1111. The mantissa being all 1s means $1 - 2^{-23}$. So the number is $[1 + (1 - 2^{-23})] \times 2^{127} \approx 3.4 \times 10^{38}$.

### 2.3. What is the smallest positive value that can be stored using a single precision float?

**Ans**: The smallest positive number also has a sign bit 0, an exponent 0000 0000 and a mantissa of 000 0000 0000 0000 0000 0001, because all zeroes is reserved to represent 0. Since it is a denormalized number, it is $(2^{-23}) \times 2^{-126} \approx 1.4 \times 10^{-45}$.

### 2.4. What is the smallest positive normalized value that can be stored using a single precision float?

**Ans**: Sign: 0; Exponent: 0000 0001; Mantissa: 000 0000 0000 0000 0000 0000. $2^{-126} =  \approx 1.18 \times 10^{-38}$.
