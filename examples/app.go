package main

import (
    "fmt"
    "log"
    "net/http"
)

func main() {

    http.HandleFunc("/", func(w http.ResponseWriter, r *http.Request) {
        w.Header().Add("etag", "\"asdf\"")
        fmt.Fprintf(w, "Hello\n")
    })

    log.Fatal(http.ListenAndServe(":8080", nil))

}