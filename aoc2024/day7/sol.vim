vim9script

var part_two = true

def FindCombs(eqs: list<list<number>>): number
    var sum = 0
    for eq in eqs
        var combs = (1 << (len(eq) - 2))
        echo $"{eq}: {combs}"
        var was_true = false
        for comb in range(combs)
            var acc = eq[1]
            var sub_eq = eq[2 : ]
            for i in range(len(sub_eq))
                if !!and(1 << i, comb)
                    acc *= sub_eq[i]
                else
                    acc += sub_eq[i]
                endif
            endfor
            if acc == eq[0] && !was_true
                echo $'acc: {acc}'
                was_true = true
                sum += acc
                break
            endif
        endfor
        if !was_true && part_two
            echo "second"
            combs = str2nr(string(pow(3, len(eq) - 2)))
            for it in range(combs)
                var comb = it
                var acc = eq[1]
                var sub_eq = eq[2 : ]
                for i in range(len(sub_eq))
                    var p = str2nr(string(pow(3, len(sub_eq) - 1 - i)))
                    var whole = comb / p
                    var remain = whole == 0 && p < comb ? 0 : comb % p
                    comb = remain

                    if whole == 0
                        acc *= sub_eq[i]
                    elseif whole == 1
                        acc += sub_eq[i]
                    else
                        acc = str2nr(acc .. sub_eq[i])
                    endif
                endfor
                if acc == eq[0] && !was_true
                    echo $'acc: {acc}'
                    was_true = true
                    sum += acc
                    break
                endif
            endfor
        endif
    endfor
    return sum
enddef

defcomp

var lines = readfile('input')

var eqs: list<list<number>>
for line in lines
    var row = split(line)->map((_, val) => str2nr(val))
    add(eqs, row)
endfor

var sum = FindCombs(eqs)

echo $'sum: {sum}'
