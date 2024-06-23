package main

import (
	"bs_backend/database"
	"bs_backend/net"
)

func main() {
	if err := database.DBInit(); err != nil {
		panic(err)
	}
	result, _ := database.DB.DB()
	defer result.Close()
	net.StartWebServer()
}
