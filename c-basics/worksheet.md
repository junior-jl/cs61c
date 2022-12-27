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
2   return n ? arr[0] + foo(arr + 1, n - 1) : 0;
3 }
```

**Ans**: It basically sums **n** integers in an array **arr**. It works in a way that "while" **n** is not equal to zero, it sums the first integer in the array with the recursive call to the function pointing to the next number and with **n** decreased in 1.

#### (b) Recall that the negation operator, !, returns 0 if the value is non-zero, and 1 if the value is 0. The ˜ operator performs a bitwise not (NOT) operation.

```c
1 int bar(int *arr, size_t n) {
2   int sum = 0, i;
3   for (i = n; i > 0; i--)
4     sum += !arr[i - 1];
5   return ˜sum + 1;
6 }
```

**Ans**: It counts the occurrences of 0s in the array and returns it as a negative number. The expression `!arr[i - 1]` will return 1 (increasing `sum`) when the digit is zero and will return 0 (not increasing `sum`) when the digit is non-zero. `~sum + 1` is the two's complement representation of `sum`. Hence, if the array contains three zeroes, the function will return -3.

#### (c) Recall that ˆ is the bitwise exclusive-or (XOR) operator.

```c
1 void baz(int x, int y) {
2   x = x ˆ y;
3   y = x ˆ y;
4   x = x ˆ y;
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

## 3. Programming with Pointers

### 3.1. Implement the following functions so that they work as described.

#### (a) Swap the value of two ints. Remain swapped after returning from this function.

**Ans**:

```c
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}
```

#### (b) Return the number of bytes in a string. Do not use strlen.

**Ans**:

```c
int mystrlen(char *mystr)
{
	int count = 0;
	while ((*mystr++) != '\0')
	{
		count += (int) sizeof(char);
	}
	return count;
}
```

### 3.2. The following functions may contain logic or syntax errors. Find and correct them.

#### (a) Returns the sum of all the elements in summands.

```c
1 int sum(int* summands) {
2   int sum = 0;
3   for (int i = 0; i < sizeof(summands); i++)
4     sum += *(summands + i);
5   return sum;
6 }
```

**Ans**: The function doesn't know the size of the array because it is being treated as a pointer.

```c
int sum(int* summands, size_t arr_size)
{
	int sum = 0;
	for (int i = 0; i < arr_size; i++)
		sum += *(summands + i);
	return sum;
}
```

#### (b) Increments all of the letters in the string which is stored at the front of an array of arbitrary length, `n >= strlen(string)`. Does not modify any other parts of the array’s memory.

```c
1 void increment(char* string, int n) {
2   for (int i = 0; i < n; i++)
3     *(string + i)++;
4 }
```

**Ans**:

#### (c) Copies the string `src` to `dst`.

```c
1 void copy(char* src, char* dst) {
2   while (*dst++ = *src++);
3 }
```

**Ans**: It looks like it works fine, but the `dst` string should be initialized before being passed, or at least malloc'ed.

#### (d) Overwrites an input string src with "61C is awesome!" if there’s room. Does nothing if there is not. Assume that `length` correctly represents the length of `src`.

```c
1 void cs61c(char* src, size_t length) {
2   char *srcptr, replaceptr;
3   char replacement[16] = "61C is awesome!";
4   srcptr = src;
5   replaceptr = replacement;
6   if (length >= 16) {
7     for (int i = 0; i < 16; i++)
8       *srcptr++ = *replaceptr++;
9   }
10 }
```

**Ans**: Line 2 has a mistake. It looks like `replaceptr` is supposed to be a pointer to char, but it is not being declared as a pointer, just as a char. So the line 2 should be `char *srcptr, *replaceptr`.

## 4. Memory Management

### 4.1. For each part, choose one or more of the following memory segments where the data could be located: code, static, heap, stack.

(a) Static variables
(b) Local variables
(c) Global variables
(d) Constants
(e) Machine Instructions
(f) Result of malloc
(g) String Literals

**Ans**:

(a) Static variables -> STATIC
(b) Local variables -> STACK
(c) Global variables -> STATIC
(d) Constants -> STATIC ?
(e) Machine Instructions -> CODE
(f) Result of malloc -> HEAP
(g) String Literals -> STATIC ?

### 4.2. Write the code necessary to allocate memory on the heap in the following scenarios.

#### (a) An array **arr** of _k_ integers.

**Ans**: `arr = (int *) malloc(k * sizeof(int));`.

#### (b) A string **str** containing _p_ characters.

**Ans**: `str = (char *) malloc(p + 1);`.

#### (c) An _n x m_ matriz **mat** of integers initialized to zero.

**Ans**: One could do `mat = (int *) malloc(n * m * sizeof(int));` and initialize to zero using a loop. But it is better to use `calloc` (allocate and initialize to zero) `mat = (int *) calloc(n * m, sizeof(int);`. Check https://devdocs.io/c/memory/calloc.

