const fs = require('fs');

const data = fs.readFileSync('testInput', 'utf8').trim().split('\n');

const numbers = data.map(Number);

const sums = numbers.map((number, index) => {
    if (index < numbers.length - 2) {
        return numbers[index] + numbers[index + 1] + numbers[index + 2];
    } else {
        return 0;
    }
})

let ans = 0;
sums.forEach((num, idx)=> {
    console.log(num, idx);
    if (idx < sums.length - 1 && sums[idx + 1] > num ) {
        ans += 1;
    }
});

console.log(data);
console.log(numbers);
console.log(sums);
console.log(ans);
