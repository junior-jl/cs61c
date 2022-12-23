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

