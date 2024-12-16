package main

import (
    "fmt"
    "2024/utils"
)

type Point struct {
    x int
    y int
}

var guardCharDirMap = map[string]int {
    "^": 0, // north
    ">": 1, // east
    "v": 2, // south
    "<": 3, // west
}

var directions = []Point {
    {0, -1}, // north
    {1, 0}, //east
    {0, 1}, //south
    {-1, 0}, //west
}

func main() {
    var input = utils.GetInput("./day6/input")
    fmt.Println(fmt.Sprintf("Day 6 Part 1: %d", part1(input)))
    fmt.Println(fmt.Sprintf("Day 6 Part 2: %d", part2(input)))
}

func wrap(n int, mn int, mx int) int {
    if(n < mn) {
        return mx
    }
    if(n > mx) {
        return mn
    }
    return n
}

func turnRight(index int) int {
    return wrap(index + 1, 0, 3) 
}

func createGrid(rawInput []string) [][]string {
    returnMe := make([][]string, 0)
    for i := range rawInput {
        returnMe = append(returnMe, make([]string, len(rawInput[i])))

        for j := range rawInput[i] {
            returnMe[i][j] = string(rawInput[i][j])
        }
    }
    return returnMe
}

func part1(rawInput []string) int {
    ans := 1
    grid := createGrid(rawInput)
    maxx := len(grid[0])
    maxy := len(grid)

    gPos := Point{ x: 0, y: 0}
    var gDir int

    // get the guard's initial position and direction
    for y := range grid {
        for x := range grid[y] {
            dir, ok := guardCharDirMap[grid[y][x]]
            if(ok) {
                gPos.x = x
                gPos.y = y
                gDir = dir
            }
        }
    }

    grid[gPos.y][gPos.x] = "x"

    // TODO: walk the guard and count the steps
    for {
        // check the next spot
        next := Point{
            x: gPos.x + directions[gDir].x,
            y: gPos.y + directions[gDir].y,
        }

        // if out of bounds, we are done
        if(next.x >= maxx || next.x < 0 ||
        next.y >= maxy || next.y < 0) {
            break
        }

        // if blocked, turn right
        if(grid[next.y][next.x] == "#") {
            gDir = turnRight(gDir)
        } else {
            // if empty, move gPos, ans++
            gPos = next

            if(grid[gPos.y][gPos.x] != "x") {
                ans++
                grid[gPos.y][gPos.x] = "x"
            } 
        }
    }

    return ans
}

func part2(rawInput []string) int {
    ans := 0
    return ans
}
