package utils

import (
    "bufio"
    "fmt"
    "os"
)

func GetInput(path string) []string {
    var input []string

    file, err := os.Open(path)
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

func IndexOf(limit int, predicate func(i int) bool) int {
    for i := range limit {
        if(predicate(i)) {
            return i
        }
    }
    return -1
}
