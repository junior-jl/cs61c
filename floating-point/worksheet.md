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

### 2.5. Cover the following single-precision floating point numbers from binary to decimal or from decimal to binary. You may leave your answer as an expression.

- 0x00000000;
- 8.25;
- 0x00000F00;
- 39.5625;
- 0xFF94BEEF;
- $-\infty$;

**Ans**: 

0x00000000 = $0_{10}$;

$8.25$ = 0x41040000;

![image](https://user-images.githubusercontent.com/69206952/210023057-c6a26bf3-5737-4c4c-971f-db5d30cc79f9.png)


0x00000F00 $\approx 5.38 \times 10^{-38}$;


![image](https://user-images.githubusercontent.com/69206952/210022964-359ee2c9-af6f-4ba8-9418-036d4fc35f00.png)

$39.5625$ = 0x421E4000; 

![image](https://user-images.githubusercontent.com/69206952/210023481-967d4d23-b4fc-44c2-9b86-f0a1e42cfa05.png)

0xFF94BEEF = NaN;

![image](https://user-images.githubusercontent.com/69206952/210023703-37d28584-1fd7-4bb5-8bfc-a93bfe6bf4f9.png)

$-\infty$ = Sign: 1; Exponent: 255; Significand: 0; 0xFF800000;

## 3. More Floating Point Representation

Not every number can be represented perfectly using floating point. For example, $1/3$ can only be approximated and thus must be rounded in any attempt to represent it. For this question, we will only look at positive numbers.

### 3.1. What is the next smallest number larger than 2 that can be represented completely?

**Ans**: ![image](https://user-images.githubusercontent.com/69206952/210080051-324f0ab5-78a2-4a98-af5e-2ca75ba54c66.png)

$2 \times (1 + 2^{-23}) \approx 2.0000002384185791015625$

### 3.2. What is the next smallest number larger than 4 that can be represented completely?

**Ans**: Following the same thought of the last question, the next number is $2^2 \times (1 + 2^{-23}) \approx 4.000000476837158203125$.

### 3.3. Define stepsize to be the distance between some value x and the smallest value larger than x that can be completely represented. What is the step size for 2? 4?

**Ans**: The stepsize depends on the exponent value. So $step = 2^{exp + bias} \times 2^{-23}$. Hence, for 2, we have

$$ step = 2 \times 2^{-23} = 2^{-22}$$

And for 4,

$$ step = 2^2 \times 2^{-23} = 2^{-21}$$

### 3.4. Now let’s see if we can generalize the stepsize for normalized numbers (we can do so for denorms as well, but we won’t in this question). If we are given a normalized number that is not the largest representable normalized number with exponent value x and with significand value y, what is the stepsize at that value? Hint: There are 23 significand bits.

**Ans**: 

![image](https://user-images.githubusercontent.com/69206952/210081938-c5f26a95-3e3e-4153-b420-734bfa4c6ec7.png)

$$ step = 2^{x - 150} $$

### 3.5. Now let’s apply this technique. What is the largest odd number that we can represent? Part 4 should be very useful in finding this answer.

**Ans**: 

![image](https://user-images.githubusercontent.com/69206952/210083286-b3c4232e-31ff-41f6-a32c-4af2db9e7d5e.png)

$$ 2^{-24} - 1$$
