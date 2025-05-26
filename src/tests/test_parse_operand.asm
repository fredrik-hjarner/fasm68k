include 'helpers.inc'

iterate <operand,    type_str>, \
        d1,          'dn', \
        a1,          'an', \
        (a1),        '(an)', \
        -(a1),       '-(an)', \
        (a1)+,       '(an)+', \
        #1,          'imm', \
        1,           'abs.l', \
        1.w,         'abs.w', \
        1.l,         'abs.l', \
        1(pc),       '(d,pc)', \
        <(1,pc)>,    '(d,pc)', \
        1(a1),       '(d,an)', \
        <(1,a1)>,    '(d,an)', \
        <1(pc,a1)>,  '(d,pc,xn)', \
        <(1,pc,a1)>, '(d,pc,xn)', \
        <1(a1,a1)>,  '(d,an,xn)', \
        <(1,a1,a1)>, '(d,an,xn)', \
        <(a1,a1)>,   '(d,an,xn)'

    parse_operand <operand>
    if @op1.type <> type_str
        err 10, 9, `operand, ' <> ', type_str
    end if

end iterate