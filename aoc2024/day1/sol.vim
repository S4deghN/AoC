vim9scrip

var lines = readfile('input2')
var list1: list<number>
var list2: list<number>
var dist: list<number>
for line in lines
    var [_, item1, item2; _] = matchlist(line, '\v(\d+)\s+(\d+)')
    add(list1, str2nr(item1))
    add(list2, str2nr(item2))
endfor
sort(list1)
sort(list2)

foreach(list1, (i, val) => {
    # part 1
    # add(dist, abs(list2[i] - val))
    # part 2
    add(dist, count(list2, val) * val)
})

# echo lines
# echo list1
# echo list2
# echo dist
echo reduce(dist, (acc, val) => acc + val, 0)
