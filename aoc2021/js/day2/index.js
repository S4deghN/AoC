const fs = require('fs')
const data = fs.readFileSync('input', 'utf8').trim().split('\n')

let hor = 0
let ver = 0
let aim = 0

data.forEach((item) => {
    [dir, val] = item.split(' ')
    val = Number(val)

    if (dir === "forward") {
        hor += val
        ver += aim * val
    } else if (dir === "down") {
        aim += val
    } else if (dir === "up") {
        aim -= val
    }
})

console.log(data)
console.log("hor: %d, ver: %d, ans: %d", hor, ver, hor * ver)
