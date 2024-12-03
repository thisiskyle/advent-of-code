package main

import day "2024/days/day2"
import "2024/utils"
import "fmt"


func main() {
    var input = utils.GetInput(day.Day)
    //var input = utils.GetTestInput(day.Day)

    fmt.Println(fmt.Sprintf("Day %d Part %d: %d", day.Day, 1, day.Run(input[:], 1)))
    fmt.Println(fmt.Sprintf("Day %d Part %d: %d", day.Day, 2, day.Run(input[:], 2)))
}
