package day02

import (
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
        for level := range report {

            if(level < len(report) - 1) {
                c, _ := strconv.Atoi(report[level])
                n, _ := strconv.Atoi(report[level + 1])
                diff := c - n
                if(level == 0) {
                    dir = getDirection(diff)
                }

                if(failsRuleCheck(diff, dir)) {
                    safe = false
                    break out
                }
            }
        }

        if(safe == true) {
            safeCount++
        }
    }

    return safeCount
}

func part2(input []string) int {
    safeCount := 0

    for i := range input {

        var report = strings.Split(input[i], " ")
        dir := 0
        safe := true

        index := 0
        maxLevel := len(report)

        out:
        for index < maxLevel - 1 {
            currentLevel, _ := strconv.Atoi(report[index])
            nextLevel, _ := strconv.Atoi(report[index + 1])
            diff := currentLevel - nextLevel

            if(index == 0) {
                dir = getDirection(diff)
            }

            if(failsRuleCheck(diff, dir)) {
                    safe = false
                    break out
            }
            index++
        }

        if(safe == true) {
            safeCount++
        }
    }

    return safeCount
}


func getDirection(diff int) int {
    if(diff < 0) { return -1 }
    if(diff > 0) { return 1 }
    return 0
}


func failsRuleCheck(diff int, dir int) bool {
    return (diff == 0 || diff > 3 || diff < -3 || diff * dir < 0)
}
