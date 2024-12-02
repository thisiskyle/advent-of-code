package day02

import (
    "fmt"
    "strings"
    "strconv"
)

var Day int = 2

func Run(input []string, part int) int {
    if(part == 1) {
        return part1(input)
    } else if(part == 2) {
        return part2(input)
    }
    return 0
}

func part1(input []string) int {
    safeCount := 0

    for i := range input {

        var report = strings.Split(input[i], " ")
        dir := 0
        safe := true

        out:
        for j := range report {

            if(j < len(report) - 1) {
                c, _ := strconv.Atoi(report[j])
                n, _ := strconv.Atoi(report[j + 1])
                diff := c - n
                fmt.Println(fmt.Sprintf("%d - %d = %d", c, n, diff))
                if(j == 0) {
                    if(diff < 0) {
                        dir = -1
                    }
                    if(diff > 0) {
                        dir = 1
                    }
                }

                if(diff == 0 || diff > 3 || diff < -3 || diff * dir < 0) {
                    fmt.Println("setting false")
                    safe = false
                    break out
                }
            }
        }

        if(safe == true) {
            fmt.Println("add to safe")
            safeCount++
        }
    }

    return safeCount
}

func part2(input []string) int {
    ans := 0
    return ans
}
