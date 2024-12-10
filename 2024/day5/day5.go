package main

import (
	"fmt"
    "strings"
    "strconv"
    "2024/utils"
)

func main() {
    var input = utils.GetInput("./day5/input")
    fmt.Println(fmt.Sprintf("Day 5 Part 1: %d", part1(input)))
    fmt.Println(fmt.Sprintf("Day 5 Part 2: %d", part2(input)))
}

func mapRules(list []string) map[int][]int {
    returnMe := make(map[int][]int)
    for i := range list {
        // split by |
        split := strings.Split(list[i], "|")
        l, _ := strconv.Atoi(split[0])
        r, _ := strconv.Atoi(split[1])
        // check the map for split[0]
        _, ok := returnMe[l]
        if(ok) {
            returnMe[l] = append(returnMe[l], r)
        } else {
            returnMe[l] = make([]int, 0)
            returnMe[l] = append(returnMe[l], r)
        }
    }
    return returnMe
}

func formatInput(input []string) [][]int {
    var returnMe = make([][]int, 0)
    for i := range input {
        returnMe = append(returnMe, make([]int, 0))
        str := strings.Split(input[i], ",")
        for j := range str {
            v, _ := strconv.Atoi(str[j])
            returnMe[i] = append(returnMe[i], v)
        }
    }
    return returnMe
}

func splitInput(input []string) ([]string, []string) {
    returnMeA := []string{}
    returnMeB := []string{}
    secondPart := false
    for i := range input {
        if(secondPart) {
            returnMeB = append(returnMeB, input[i])
        } else {
            if(input[i] == "") {
                secondPart = true
            } else {
                returnMeA = append(returnMeA, input[i])
            }
        }
    }
    return returnMeA, returnMeB
}

func checkTheRules(input []int, rules map[int][]int) bool {
    for i, k := range input {
        for j := range rules[k] {
            n := rules[k][j]
            idx := utils.IndexOf(len(input), func(i int) bool { return input[i] == n })
            if(idx != -1 && i > idx) {
                return false
            }
        }
    }
    return true
}


func calculateAnswer(input [][]int) int {
    ans := 0
    for i := range input {
        index := (len(input[i]) / 2)
        ans += input[i][index]
    }
    return ans
}

func fixIncorrect(incorrect [][]int, rules map[int][]int) [][]int {
    var returnMe = make([][]int, 0)

    for i := range incorrect {
        weights := make(map[int]int)

        for _, k := range incorrect[i] {
            weights[k] = 0
        }

        for _, k := range incorrect[i] {
            for _, r := range rules[k] {
                _, ok := weights[r]
                if(ok) {
                    weights[r]++
                }
            }
        }

        returnMe = append(returnMe, make([]int, len(weights)))

        for k, v := range weights {
            returnMe[i][v] = k
        }

        fmt.Println(weights)
    }
    return returnMe
}


func part1(rawInput []string) int {
    a, b := splitInput(rawInput)
    rules := mapRules(a)
    input := formatInput(b)

    var correct [][]int
    for i := range input {
        if(checkTheRules(input[i], rules)) {
            correct = append(correct, input[i])
        }
    }
    return calculateAnswer(correct)
}

func part2(rawInput []string) int {
    a, b := splitInput(rawInput)
    rules := mapRules(a)
    input := formatInput(b)

    var incorrect [][]int
    for i := range input {
        if(!checkTheRules(input[i], rules)) {
            incorrect = append(incorrect, input[i])
        }
    }

    fmt.Println(incorrect)
    fixed := fixIncorrect(incorrect, rules)
    fmt.Println(fixed)
    return calculateAnswer(fixed)
}
