package main

import (
	"fmt"
	"regexp"
	"strconv"
    "2024/utils"
)

func main() {
    var input = utils.GetInput("./day3/input")
    fmt.Println(fmt.Sprintf("Day 3 Part 1: %d", part1(input)))
    fmt.Println(fmt.Sprintf("Day 3 Part 2: %d", part2(input)))
}

func part1(input []string) int {
    ans := 0
    instructions := sanatize(input)
    var r = regexp.MustCompile(`(mul)\((\d{1,3}),(\d{1,3})\)`)

    for i := range instructions {
        matches := r.FindStringSubmatch(instructions[i])
        if(len(matches) > 0) {
            fmt.Println("mul found")
            a, _ := strconv.Atoi(matches[2])
            b, _ := strconv.Atoi(matches[3])
            ans = ans + (a * b)
        }
    }
    return ans
}

func part2(input []string) int {
    ans := 0
    instructions := sanatize(input)
    exec := true

    fmt.Println(instructions)

    var mul = regexp.MustCompile(`(mul)\((\d{1,3}),(\d{1,3})\)`)
    var do = regexp.MustCompile(`do\(\)`)
    var dont = regexp.MustCompile(`don't\(\)`)

    for i := range instructions {

        if(exec) {
            fmt.Println("executing")
            matches := mul.FindStringSubmatch(instructions[i])
            if(len(matches) > 0) {
                fmt.Println("mul found")
                a, _ := strconv.Atoi(matches[2])
                b, _ := strconv.Atoi(matches[3])
                ans = ans + (a * b)
            }
        }

        if(do.MatchString(instructions[i])) {
            fmt.Println("do")
            exec = true
        } else if(dont.MatchString(instructions[i])) {
            fmt.Println("dont")
            exec = false
        }
    }
    return ans
}


func sanatize(input []string) []string {
    returnThis := make([]string, 0)

    r := regexp.MustCompile(`(mul\(\d{1,3},\d{1,3}\)|do\(\)|don't\(\))`)

    for i := range input {
        matches := r.FindAllString(input[i], -1)
        returnThis = append(returnThis, matches...)
    }
    return returnThis
}
