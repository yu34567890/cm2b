
![Logo](./images/logo.png)
# cm2b

cm2b is a basic knockoff for CM2 CPUs. It is simple and minimalistic.

---

## TODO
- [ ] Finish parser
- [ ] Design an IR
- [ ] Make IR generation
- [x] Finish syntax design
- [ ] Make a primitive scope  
- [ ] Add preprocessing (e.g., `#include`)

---

## Syntax

### Variables
```cm2b
set x = 5;      // declaration
x = x + 2;      // assignment
```
- Variables are dynamically typed (numbers only).  
- Variables in scopes are accessed as `scope.variable`.

---

### Labels
```cm2b
label start
...
goto start;     // jump to a label
```
- `label` defines a position, `goto` jumps to it also use `gosub` to call it and use `ret` to return to gosub.

---

### Control Flow
```cm2b
if x > 25 then label_true else label_false
```
- Jumps to `label_true` if condition is true, otherwise to `label_false`.

---

### Scope
```cm2b
scope math
set pi = 3141;  // becomes math.pi

scope main
math.pi = 3;     // accesses math.pi instead of main.pi
```

---

### Comments
```cm2b
// This is a single-line comment
```

---

### Arithmetic & Logic
```cm2b
x = x + 1;
y = x * 2;
z = x > y;   // result 0 (false) or 1 (true)
```
- Supports `+`, `-`, `*`, `/`, comparisons `>`, `<`, `>=`, `<=`, `==`, `!=`.  
- Logical operations return `0` or `1`.

---

### Example Program
```cm2b
scope cpu_test
set counter = 0;

label loop_start
counter = counter + 1;

if counter < 100 then loop_start else end_test

label end_test
// Finished counting
```
