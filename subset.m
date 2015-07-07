#subset:

import module2

function f(a, b, c)
    d = a+b-c
    return d
end

function g(a, b)
    return f(a, b, 3)
end

module2.h(2)
g(1, 2) == f(1, 2, 3)


