vim9scrip

var lines = readfile('input2')
var matches = matchstrlist(lines, 'mul(\d\{1,3},\d\{1,3})\|do()\|don''t()')

var skip = false
var sum = 0
for m in matches
    if m.text == 'do()'
        skip = false
    elseif m.text == 'don''t()'
        skip = true
    else
        if skip == true | continue | endif
        var [_, a, b; _] = matchlist(m.text,  'mul(\(\d\{1,3}\),\(\d\{1,3}\))')
        sum += str2nr(a) * str2nr(b)
    endif
endfor

setreg('+', sum)
echo sum

# echo lines
# echo matches
