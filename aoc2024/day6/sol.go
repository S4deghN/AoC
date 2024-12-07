package main

import "fmt"
import "os"
import "strings"

const x = 0
const y = 0

var up    = [2]int{0, -1}
var down  = [2]int{0,  1}
var right = [2]int{1,  0}
var left  = [2]int{-1, 0}

var dir_list = [4][2]int{
    up,
    right,
    down,
    left,
}

func walk(table [][]rune, guard [2]int, dir_index int, recur bool)  {
    sx := guard[0]
    sy := guard[1]
    if !recur {
        if table[sy][sx] == '@' || table[sy][sx] == 'X' || table[sy][sx] == '^' {
            return
        }
        table[sy][sx] = '#'
    }

    table_x := len(table[0])
    table_y := len(table)
    dir     := dir_list[dir_index]

    visits  := map[[3]int]bool{}

    for guard[0] > -1 && guard[0] < table_x && guard[1] > -1 && guard[1] < table_y {

        if table[guard[1]][guard[0]] == '#' {
            // if looped!
            if !recur && visits[[3]int{guard[0], guard[1], dir_index}] {
                table[sy][sx] = '@'
                return
            } else {
                visits[[3]int{guard[0], guard[1], dir_index}] = true
            }

            guard[0] -= dir[0]
            guard[1] -= dir[1]
            dir_index = (dir_index + 1) % 4
            dir = dir_list[dir_index]
        } else {
            if recur {
                walk(table, guard, dir_index, false)
            }
        }
        guard[0] += dir[0]
        guard[1] += dir[1]
    }

    if !recur {
        table[sy][sx] = 'X'
    }
}

func main() {
    buf, _ := os.ReadFile("input2")
    lines := strings.Fields(string(buf))
    table := [][]rune{}

    for _, line := range lines {
        row := []rune(line)
        table = append(table, row)
    }

    guard := [2]int{}
    dir_index := 0

    for i, row := range table {
        for j, char := range row {
            if char == '^' {
                guard[0] = j
                guard[1] = i
                dir_index = 0
            }
        }
    }

    walk(table, guard, dir_index, true)

    sum := 1 // 1 for start postion
    opts := 0
    for _, row := range table {
        for _, char := range row {
            if char == 'X' {
                sum += 1
            }
            if char == '@' {
                sum += 1
                opts +=1
            }
        }
    }

    // fmt.Printf("    0 1 2 3 4 5 6 7 8 9\n")
    for i, row := range table {
        fmt.Printf("%d: %c\n", i, row)
    }
    fmt.Printf("guard: %d\n", guard)
    fmt.Printf("Sum: %d\n", sum)
    fmt.Printf("Opts: %d\n", opts)
}

