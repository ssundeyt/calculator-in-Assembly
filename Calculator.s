.text
.globl _add, _subtract, _multiply, _divide # xcode uses GAS prefix: .globl instead of global

# xmm registers instead of int's, information stored in xmm0

# add xmm1 and xmm0
_add:
    addsd %xmm1, %xmm0
    ret

# xmm1 - xmm0
_subtract:
    subsd %xmm1, %xmm0
    ret

# multiply xmm 1 and 0
_multiply:
    mulsd %xmm1, %xmm0
    ret

# rax quotient, divide xmm1 by xmm0
_divide:
    divsd %xmm1, %xmm0    # rdx
    ret
