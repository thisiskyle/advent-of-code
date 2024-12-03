package day2

import (
	"strconv"
	"strings"
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
    var reports = convertReportsToInt(input)

    for i := range reports {
        if(isReportSafe(reports[i])) {
            safeCount++
        }
    }

    return safeCount
}

func part2(input []string) int {
    safeCount := 0
    var reports = convertReportsToInt(input)

    for i := range reports {
        if(isReportSafe(reports[i])) {
            safeCount++
        } else {

            out:
            for j := range reports[i] {
                temp := make([]int, len(reports[i]))
                copy(temp, reports[i])

                temp = append(temp[:j], temp[j+1:]...)
                if(isReportSafe(temp)) {
                    safeCount++
                    break out
                }
            }
        }
    }

    return safeCount
}

func convertReportsToInt(report []string) [][]int{
    returnThis := make([][]int, 0)

    for i := range report {
        var reportString = strings.Split(report[i], " ")
        returnThis = append(returnThis, make([]int, 0))
        for j := range reportString {
            level, _ := strconv.Atoi(reportString[j])
            returnThis[i] = append(returnThis[i], level)
        }
    }
    return returnThis
}

func isReportSafe(report []int) bool {
    dir := 0
    safe := true

    out:
    for l := range report {
        if(l == len(report) - 1) {
            break out
        }
        currentLevel := report[l]
        nextLevel := report[l + 1]
        diff := currentLevel - nextLevel

        if(l == 0) {
            if(diff < 0) { dir = -1 }
            if(diff > 0) { dir = 1 }
        }

        //   duplicate        gap too big         wrong direction
        if (diff == 0 || diff > 3 || diff < -3 || diff * dir < 0) {
            safe = false
            break out
        }
    }
    return safe
}
