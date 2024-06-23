package database

import (
	"fmt"
	"github.com/spf13/viper"
)

type databaseConfig struct {
	userName string
	password string
	port     string
	dbName   string
}

func readInConfig() *databaseConfig {
	config := databaseConfig{}
	viper.AddConfigPath(".")
	viper.AddConfigPath("./conf")
	viper.SetConfigName("config")
	viper.SetConfigType("yaml")
	if err := viper.ReadInConfig(); err != nil {
		fmt.Println("cannot read config file ", err)
	}
	config.userName = viper.GetString("database.user")
	config.password = viper.GetString("database.password")
	config.dbName = viper.GetString("database.dbName")
	config.port = viper.GetString("database.port")
	return &config
}
