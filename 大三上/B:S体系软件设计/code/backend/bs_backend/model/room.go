package model

type Room struct {
	Id           int    `json:"roomId" gorm:"column:roomid;primaryKey;autoIncrement"`
	RoomName     string `json:"name" gorm:"column:name;"`
	RoomDesc     string `json:"description" gorm:"column:description;"`
	HouseHouseId int    `json:"houseid" gorm:"references:HouseId;column:houseid;not null"`
	UserId       int    `json:"userid" gorm:"references:Id;column:userid;not null"`
	User         User
	House        House
}
