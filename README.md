![Logo](./images/logo.png)
# cm2b

cm2b is a basic knockoff for CM2 CPUs. It is simple and minimalistic.

---

## TODO
- [ ] Finish parser  
- [x] Design an IR  
- [ ] Make IR generation  
- [x] Finish syntax design  
- [ ] Add preprocessing (e.g., `#include`)  

---

## Syntax

### Variables
```cm2b
set x = 5;      // declaration
x = x + 2;      // assignment
```
- Variables are dynamically typed (numbers only).  
- All variables share the same global scope.

---

### Labels
```cm2b
label start;
...
goto start;     // jump to a label
```
- `label` defines a position, `goto` jumps to it.  
- Use `gosub` to call it and `ret` to return from a `gosub`.

---

### Control Flow
```cm2b
if x > 25 then label_true else label_false;
```
- Jumps to `label_true` if condition is true, otherwise to `label_false`.

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
set counter = 0;

label loop_start;
counter = counter + 1;

if counter < 100 then loop_start else end_test;

label end_test;
// Finished counting
```

---

## Intermediate Representation
- [cm2 universal isa](https://docs.google.com/spreadsheets/d/13bLfUIbausaWUBpG9-wlf7qLv_2vzgzIvoaG8cppK4g)
