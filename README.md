# cm2b
cm2b is a basic knockoff for cm2 CPUs.

# TODO
- [ ] Finish parser
- [ ] Design an IR
- [ ] Make IR generation
- [x] Finish syntax design
- [ ] Make a primitive scope  
- [ ] Add preprocessing (e.g., #include)

# Syntax
cm2b syntax is simple and minimalistic. Some basics include:

## Variables
set x = 5;      // declaration
x = x + 2;      // assignment
// Variables are dynamically typed (numbers only). Variables in scopes are accessed as scope.variable

## Labels
label start
...
goto start;     // jump to a label
// label defines a position, goto jumps to it

## Control Flow
if x > 25 then label_true else label_false
// jumps to label_true if condition true, else label_false

## Scope
scope math
set pi = 3141;  // becomes math.pi
scioe main
math.pi = 3; // acceses math.pi instead of main.pi

## Comments
// This is a single-line comment

## Arithmetic & Logic
x = x + 1;
y = x * 2;
z = x > y;   // result 0 (false) or 1 (true)
// Supports +, -, *, /, comparisons >, <, >=, <=, ==, !=. Logical operations return 0 or 1

## Example Program
scope cpu_test
set counter = 0;

label loop_start
counter = counter + 1;

if counter < 100 then loop_start else end_test

label end_test
// Finished counting
