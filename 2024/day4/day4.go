package main

import (
    "strings"
	"fmt"
    "2024/utils"
)

func main() {
    var input = utils.GetInput("./day4/input")
    fmt.Println(fmt.Sprintf("Day 4 Part 1: %d", part1(input)))
    fmt.Println(fmt.Sprintf("Day 4 Part 2: %d", part2(input)))
}

type Point struct {
    X int
    Y int
}

var directions = map[int]Point {
    0: {1, 0}, //east
    1: {1, -1}, 
    2: {0, -1}, //south
    3: {-1, -1},
    4: {-1, 0}, //west
    5: {-1, 1},
    6: {0, 1}, // north
    7: {1, 1},
}



func part1(input []string) int {
    ans := 0
    maxY := len(input)

    for y := range input {
        maxX := len(input[y])
            for x := range input[y] {
                if(string(input[y][x]) == "X") {
                // for each direction
                for i := range 8 {
                    var sb strings.Builder
                    // for each letter of MAS
                    for j := range 3 {
                        dir := directions[i]
                        dx := x + (dir.X * (j + 1))
                        dy := y + (dir.Y * (j + 1))

                        if(dx > -1 && dx < maxX && dy > -1 && dy < maxY) {
                            sb.WriteString(string(input[dy][dx]))
                        }
                    }
                    if(sb.String() == "MAS") {
                        ans++
                    }
                }
            }
        }
    }
    return ans
}

func part2(input []string) int {
    ans := 0

    maxY := len(input)

    for y := range input {
        maxX := len(input[y])

        for x := range input[y] {

            if(string(input[y][x]) == "A") {
                    // 1, 5
                    dx1 := x + (directions[1].X)
                    dy1 := y + (directions[1].Y)
                    dx5 := x + (directions[5].X)
                    dy5 := y + (directions[5].Y)
                    // 3, 7
                    dx3 := x + (directions[3].X)
                    dy3 := y + (directions[3].Y)
                    dx7 := x + (directions[7].X)
                    dy7 := y + (directions[7].Y)

                    if((dx1 > -1 && dx1 < maxX && dy1 > -1 && dy1 < maxY) &&
                        (dx5 > -1 && dx5 < maxX && dy5 > -1 && dy5 < maxY) &&
                        (dx3 > -1 && dx3 < maxX && dy3 > -1 && dy3 < maxY) &&
                        (dx7 > -1 && dx7 < maxX && dy7 > -1 && dy7 < maxY)) {
                        var sb1 strings.Builder
                        sb1.WriteString(string(input[dy1][dx1]))
                        sb1.WriteString(string(input[dy5][dx5]))

                        var sb2 strings.Builder
                        sb2.WriteString(string(input[dy3][dx3]))
                        sb2.WriteString(string(input[dy7][dx7]))

                        if((sb1.String() == "MS" || sb1.String() == "SM") && 
                            (sb2.String() == "MS" || sb2.String() == "SM")) {
                            ans++
                        }
                    }
                }
            }
        }
    return ans
}
