# CPU
Soft processor on Visual C++
Uses your asm code and generate C++ instructions + disassembler
# Examples
+ Input code (square solution)
```
begin VS 6
pop
pop
pop
push 1
push 2
add
push 1
add
sub
popr cx
pop
popr ax
popr ax
add
add
mul
: 65
back
back
back
jxx 65
back
back
back
size
clear
resize 12
resize 19
size
div
mul
: 97
div
mul
div
mul
sub
sub
popr cx
popr ax
pop
pop
jxx 97
mul
pop
popr ax
popr bx
pop
pop
mul
add
add
pop
popr bx
pop
pop
pop
popr dx
popr bx
add
add
popr cx
popr ax
pop
popr ax
popr ax
popr cx
popr ax
end
```
+ "light" ASM output
```
3	39	5
4
4
4
1 	1
1   2
14
1 	1
14
18
5 	2
4
5 	0
5 	0
14
14
17
26 	65
6
6
6
11 	65
6
6
6
7
9
8 	12
8 	19
7
19
17
26 	97
19
17
19
17
18
18
5 	2
5 	0
4
4
11 	97
17
4
5 	0
5 	1
4
4
17
14
14
4
5 	1
4
4
4
5 	3
5 	1
14
14
5 	2
5 	0
4
5 	0
5 	0
5 	2
5 	0
13
```
+ ASM output is a byte sequence
+ CPU output
-1 -1
