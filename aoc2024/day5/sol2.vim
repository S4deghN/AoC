vim9scrip

def Find(list: list<number>, num: number): number
    var ret = -1
    for i in range(len(list))
        if list[i] == num
            ret = i
        endif
    endfor
    return ret
enddef

# a >  b ->  1
# a == b ->  0
# a <  b -> -1
def Compare(rules: dict<any>, a: number, b: number): number
    var a_has_rule = has_key(rules, a)
    var b_has_rule = has_key(rules, b)

    if a_has_rule
        if Find(rules[a], b) != -1
            return 1
        endif
    endif

    if b_has_rule
        if Find(rules[b], a) != -1
            return -1
        endif
    endif

    return 0
enddef

# Desending sort
def Sort(rules: dict<any>, A: list<number>): list<number>
    var n = len(A)
    var swapped = true
    while swapped
        swapped = false
        for i in range(n - 1)
            # A[i] < A[i + 1]
            if Compare(rules, A[i], A[i + 1]) == -1
                var temp = A[i]
                A[i] = A[i + 1]
                A[i + 1] = temp
                swapped = true
            endif
        endfor
    endwhile
    return A
enddef

defcomp

var lines = readfile('input2')
var split_point = 0
for i in range(len(lines))
    if lines[i] == ''
        split_point = i
        break
    endif
endfor

var updates: list<list<number>>
for line in lines[split_point + 1 : ]
    var list_str = split(line, ',')
    var list: list<number>
    for str in list_str
        add(list, str2nr(str))
    endfor
    add(updates, list)
endfor

var rules_str = lines[0 : split_point - 1]
var rules: dict<any>
for line in rules_str
    var match_list = matchlist(line, '\(\d\+\)|\(\d\+\)')
    var left = str2nr(match_list[1])
    var right = str2nr(match_list[2])

    if !has_key(rules, left) | rules[left] = [] | endif
    add(rules[left], right)
endfor

# for [k, v] in items(rules)
#     echo $'{k}: {v}'
# endfor
# echo '--------'

var order: list<number>
for k in keys(rules)
    add(order, str2nr(k))
endfor

Sort(rules, order)
echo order
echo '--------'

var reordered: list<list<number>>
for update in updates
    var error = false
    for i in range(len(update) - 1)
        # if a < b
        if Compare(rules, update[i], update[i + 1]) == -1
            error = true
            break
        endif
    endfor
    if error
        add(reordered, Sort(rules, update))
    endif
endfor

var sum = 0
for list in reordered
    sum += list[len(list) / 2]
endfor

echo sum
