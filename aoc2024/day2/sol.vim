vim9scrip

var lines = readfile('input2')

var safe_count: number = 0

def CountMistakes(list: list<number>): number
    var diff: list<number>
    for i in range(len(list) - 1)
        add(diff, list[i + 1] - list[i])
    endfor

    var mistakes = 0
    var sum = reduce(diff, (acc, val) => acc + val, 0)
    if sum > 0
        for d in diff
            if d > 3 || d < 1
                mistakes += 1
            endif
        endfor
    elseif sum < 0
        for d in diff
            if d < -3 || d > -1
                mistakes += 1
            endif
        endfor
    else
        mistakes = v:numbermax
    endif

    return mistakes
enddef

for line in lines
    var level = mapnew(split(line), (_, val) => str2nr(val))

    var mistakes = CountMistakes(level)

    if mistakes == 0
        safe_count += 1
    elseif mistakes < 3
        for i in range(len(level))
            var test = deepcopy(level)
            remove(test, i)
            mistakes = CountMistakes(test)
            if mistakes == 0
                safe_count += 1
                break
            endif
        endfor
    endif

endfor

echo $'safes: {safe_count}'
# echo lines

# 1   2   3   4   5   6
#   i   i   i   i   i
