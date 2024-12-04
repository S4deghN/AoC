vim9scrip

var lines = readfile('input2')

var hor_match = matchstrlist(lines, 'XMAS') + matchstrlist(lines, 'SAMX')

var ver_lines: list<string>
for i in range(len(lines[0]))
    add(ver_lines, "")
    for line in lines
        ver_lines[i] ..= line[i]
    endfor
endfor

var ver_match = matchstrlist(ver_lines, 'XMAS') + matchstrlist(ver_lines, 'SAMX')

var diag1: list<string>
var diag2: list<string>
var diag3: list<string>
var diag4: list<string>
for i in range(len(lines[0]))
    add(diag1, "")
    add(diag2, "")
    add(diag3, "")
    add(diag4, "")
    for j in range(len(lines))
        diag1[i] ..= (repeat(' ', j) .. lines[j])[i]
        diag2[i] ..= (repeat(' ', j) .. reverse(lines[j]))[i]
        diag3[i] ..= (repeat(' ', len(lines) - 1 - j) .. lines[j])[i]
        diag4[i] ..= (repeat(' ', len(lines) - 1 - j) .. reverse(lines[j]))[i]
    endfor
endfor

diag1 = diag1[0 : -2]
diag2 = diag2[0 : -2]

var diag1_match = matchstrlist(diag1, 'XMAS') + matchstrlist(diag1, 'SAMX')
var diag2_match = matchstrlist(diag2, 'XMAS') + matchstrlist(diag2, 'SAMX')
var diag3_match = matchstrlist(diag3, 'XMAS') + matchstrlist(diag3, 'SAMX')
var diag4_match = matchstrlist(diag4, 'XMAS') + matchstrlist(diag4, 'SAMX')

echo len(hor_match) + len(ver_match) + len(diag1_match) + len(diag2_match) + len(diag3_match)
    + len(diag4_match)
