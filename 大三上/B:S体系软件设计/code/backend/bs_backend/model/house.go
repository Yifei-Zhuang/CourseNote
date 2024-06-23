package model

type House struct {
	HouseId     int    `json:"houseId" gorm:"column:houseid;primaryKey;autoIncrement"`
	UserId      int    `json:"userId" gorm:"references:Id;column:userid;not null"`
	HouseName   string `json:"houseName" gorm:"column:housename;not null"`
	Description string `json:"description" gorm:"column:description;not null"`
	RoomCount   int    `json:"roomcount" gorm:"column:roomcount;not null"`
	User        User
}
