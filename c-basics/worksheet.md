# C Basics

## 1. Pre-Check

### 1.1. True or False: C is a pass-by-value language.

**Ans**: True.

### 1.2. What is a pointer? What does it have in common to an array variable?

**Ans**: A pointer is a special variable that stores a memory address. The name of an array is a pointer to a memory location with the size of the array.

### 1.3. If you try to dereference a variable that is not a pointer, what will happen? What about when you free one?

**Ans**: It would cause an error because the value in a variable would probably not be a valid address. Free expects a pointer as argument, so the compiler would throw an error as well.

### 1.4. When should you use the heap over the stack? Do they grow?

**Ans**: The stack is used to store local (temporary) variables, while the heap is used to store global variables. They grow, but the allocation of stack memory is controlled by the compiler while the heap is controlled by the programmer.

## 2. C

### 2.1. Let’s assume that int\* p is located at 0xF9320904 and int x is located at
0xF93209B0. As we can observe:

- \*p evaluates to 0x2A ( $42_{10}$ ).
- p evaluates to 0xF93209AC.
- x evaluates to 0x61C.
- &x evaluates to 0xF93209B0.

Let’s say we have an int \*\*pp that is located at 0xF9320900.

What does pp evaluate to? How about \*pp? What about \*\*pp?

**Ans**: 

- pp -> 0xF9320904.
- \*pp -> 0xF93209AC.
- \*\*pp -> 0x2A.

### 2.2. The following functions are syntactically-correct C, but written in an incomprehensible style. Describe the behavior of each function in plain English.

#### (a) Recall that the ternary operator evaluates the condition before the ? and returns the value before the colon (:) if true, or the value after it if false.

```c
1 int foo(int *arr, size_t n) {
2 return n ? arr[0] + foo(arr + 1, n - 1) : 0;
3 }
```

**Ans**: It basically sums **n** integers in an array **arr**. It works in a way that "while" **n** is not equal to zero, it sums the first integer in the array with the recursive call to the function pointing to the next number and with **n** decreased in 1.

#### (b) Recall that the negation operator, !, returns 0 if the value is non-zero, and 1 if the value is 0. The ˜ operator performs a bitwise not (NOT) operation.

```c
1 int bar(int *arr, size_t n) {
2 int sum = 0, i;
3 for (i = n; i > 0; i--)
4 sum += !arr[i - 1];
5 return ˜sum + 1;
6 }
```

**Ans**: It counts the occurrences of 0s in the array and returns it as a negative number. The expression `!arr[i - 1]` will return 1 (increasing `sum`) when the digit is zero and will return 0 (not increasing `sum`) when the digit is non-zero. `~sum + 1` is the two's complement representation of `sum`. Hence, if the array contains three zeroes, the function will return -3.

#### (c) Recall that ˆ is the bitwise exclusive-or (XOR) operator.

```c
1 void baz(int x, int y) {
2 x = x ˆ y;
3 y = x ˆ y;
4 x = x ˆ y;
5 }
```

**Ans**: Locally, it swaps **x** and **y**, but in the caller function nothing happens, since just the values are being passed.

#### (d) Bonus: How do you write the bitwise exclusive-nor (XNOR) operator in C?

The XNOR operator between x and y could be written as `!(x^y)`. But looking at the truth table of a XNOR gate.

| x | y | x XNOR y |
|:-:|:-:|:--------:|
| 0 | 0 |     1    |
| 0 | 1 |     0    |
| 1 | 0 |     0    |
| 1 | 1 |     1    |

We could just write `x == y` to get the result of a XNOR, since the bits must match.
