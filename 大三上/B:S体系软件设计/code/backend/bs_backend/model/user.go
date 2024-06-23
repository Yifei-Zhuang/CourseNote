package model

type Login struct {
	UserName string `json:"userName" gorm:"column:username;primaryKey;uniqueIndex;size:100"`
	PassWord string `json:"password" gorm:"column: password;not null"`
}

type User struct {
	Id          int    `json:"id" gorm:"column:userid;primaryKey;autoIncrement"`
	PhoneNumber string `json:"phoneNumber" gorm:"column:phonenumber;primaryKey;uniqueIndex;size:100"`
	Login
}
