vim9scrip

def FindXmas(diagf_match: list<dict<any>>, diagb_match: list<dict<any>>, line_len: number): number
    var xmas = 0
    for m1 in diagf_match
        for m2 in diagb_match
            if m1.byteidx == m2.byteidx && (m1.idx + m2.idx) == (line_len + (2 * m1.byteidx + 1))
                xmas += 1
            endif
        endfor
    endfor
    return xmas
enddef
defcomp


var lines = readfile('input2')

var diagf1: list<string>
var diagf2: list<string>
var diagb1: list<string>
var diagb2: list<string>

var line_len = len(lines[0])
for i in range(line_len)
    add(diagf1, "")
    add(diagf2, "")
    add(diagb1, "")
    add(diagb2, "")
    for j in range(len(lines))
        diagf1[i] ..= (repeat(' ', j) .. lines[j])[i]
        diagf2[i] ..= (repeat(' ', len(lines) - 1 - j) .. reverse(lines[j]))[i]

        diagb1[i] ..= (repeat(' ', j) .. reverse(lines[j]))[i]
        diagb2[i] ..= (repeat(' ', len(lines) - 1 - j) .. lines[j])[i]
    endfor
endfor

var diagf = diagf1[0 : -2] + reverse(diagf2)
var diagb = diagb1[0 : -2] + reverse(diagb2)

var diagf_match = matchstrlist(diagf, 'MAS') + matchstrlist(diagf, 'SAM')
var diagb_match = matchstrlist(diagb, 'MAS') + matchstrlist(diagb, 'SAM')

echom $'X-MAS: {FindXmas(diagf_match, diagb_match, line_len)}'
