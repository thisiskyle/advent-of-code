package utils

import (
    "bufio"
    "fmt"
    "os"
)

func GetInput(day int) []string {
    var input []string

    file, err := os.Open(fmt.Sprintf("./inputs/%d.input", day))
    if(err != nil) {
        fmt.Println("something went wrong reading input")
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        input = append(input, scanner.Text())
    }
    return input
}

func GetTestInput(day int) []string {
    var input []string

    file, err := os.Open(fmt.Sprintf("./inputs/%d.test", day))
    if(err != nil) {
        fmt.Println("something went wrong reading input")
    }
    defer file.Close()

    scanner := bufio.NewScanner(file)
    for scanner.Scan() {
        input = append(input, scanner.Text())
    }
    return input
}


func Abs(n int) int {
    if(n < 0) {
        return n * -1
    }
    return n
}
