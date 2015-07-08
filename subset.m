#subset:

import module2

function f(a, b, c)
    d = a+b-c
    return d
end

function g(a, b)
    return f(a, b, 3)
end


-- sample translation
module2.h(2)
g(1, 2) == f(1, 2, 3)

push 2

push 2
push 1
call g
push 1
push 2
push 3
call f
cmp

if 2+4*alpha-2 == 0
    print('hello')
end

push alpha
push 4
mult
push 2
add
push 2
sub
push 0
cmp
jnz label
push 'hello'
call print
label:
