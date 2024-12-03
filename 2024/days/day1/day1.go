package day1

import (
    "sort"
    "strings"
    "strconv"
    "2024/utils"
)


var Day int = 1

func Run(input []string, part int) int {
    if(part == 1) {
        return part1(input)
    } else if(part == 2) {
        return part2(input)
    }
    return 0
}

func formatInput(input []string) ([]int, []int) {
    var left []int
    var right []int

    for _, v := range input  {
        s := strings.Split(v, "   ")
        a, errA := strconv.Atoi(s[0])
        b, errB := strconv.Atoi(s[1])

        if(errA != nil) {
            panic(errA)
        }
        if(errB != nil) {
            panic(errB)
        }

        left = append(left, a)
        right = append(right, b)

    }
    return left, right
}


func part1(input []string) int {

    distance := 0

    left, right := formatInput(input)
    sort.Ints(left)
    sort.Ints(right)

    for i := range left  {
        distance = distance + utils.Abs(left[i] - right[i])
    }

    return distance
}

func part2(input []string) int {
    similarity := 0

    left, right := formatInput(input)
    sort.Ints(left)
    sort.Ints(right)

    var m = make(map[int]int)

    for i := range left  {
        l := left[i]
        n := 0
        x, ok := m[l]
        if(ok) {
            similarity = similarity + x
        } else {
            for j := range right  {
                if(right[j] == l) {
                    n = n + 1
                }
            }
            m[l] = n * l
            similarity = similarity + m[l]
        }
        
    }
    return similarity
}
