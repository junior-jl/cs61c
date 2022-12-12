## 1. Pre-Check

1.1. Depending on the context, the same sets of bits may represent different things.

**Ans**: True. One could represent numbers, colors, symbols...

1.2. It is possible to get an overflow error in Two’s Complement when adding numbers of opposite signs.

**Ans**: False. Suppose 4 bits, $-8_{10} (1001_2) + 7_{10} (0111_2) = -1_{10} (1111_2)$. 

1.3. If you interpret a N bit Two’s complement number as an unsigned number, negative numbers would be smaller than positive numbers.

**Ans**: False. Because of the leading 1, they would be bigger.

1.4. If you interpret an N bit Bias notation number as an unsigned number (assume there are negative numbers for the given bias), negative numbers would be smaller than positive numbers.

**Ans:** True. That is basically the purpose of the bias.

## 2. Unsigned Integers

2.1. If we have an n-digit unsigned numeral $d_{n-1}d_{n-2}\cdots d_0$ in radix (or base) r, then the value of that numeral is 

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

(a) Convert the following numbers from their initial radix into the other two common radices:

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
