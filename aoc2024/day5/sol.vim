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

var lines = readfile('input2')
var split_point = 0
for i in range(len(lines))
    if lines[i] == ''
        split_point = i
        break
    endif
endfor

var rules_str = lines[0 : split_point - 1]
var updates = lines[split_point + 1 : ]

var rules: dict<any>
for line in rules_str
    var match_list = matchlist(line, '\(\d\+\)|\(\d\+\)')
    var left = str2nr(match_list[1])
    var right = str2nr(match_list[2])

    if !has_key(rules, left) | rules[left] = [] | endif
    add(rules[left], right)
endfor

for [k, v] in items(rules)
    echo $'{k}: {v}'
endfor

echo '--------'

var error = false
var good_updates = []
for i in range(len(updates))
    var update_str = split(updates[i], ',')
    var update = mapnew(update_str, (_, v) => str2nr(v))
    for j in range(len(update))
        var key = update[j]
        if !has_key(rules, key) || j == 0 | continue | endif
        for pre in update[0 : j - 1]
            if Find(rules[key], pre) != -1
                # this is error
                error = true
            endif
        endfor
    endfor

    if error == false
        add(good_updates, update)
    endif

    error = false
endfor

echo good_updates

echo '--------'

var sum = 0
for i in good_updates
    sum += i[len(i) / 2]
endfor

echo sum
