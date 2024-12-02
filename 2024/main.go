package main

import day "2024/days/day02"
import "2024/utils"
import "fmt"


func main() {
    // test input
    //var input = [...]string { "7 6 4 2 1", "1 2 7 8 9", "9 7 6 2 1", "1 3 2 4 5", "8 6 4 4 1", "1 3 6 7 9", }
    var input = utils.GetInput(day.Day)

    part := 1
    fmt.Println(fmt.Sprintf("Day %d Part %d: %d", day.Day, part, day.Run(input[:], part)))
}
