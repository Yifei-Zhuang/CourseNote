package model

type Image struct {
	RoomId   int    `json:"roomId" gorm:"column:roomid;not null"`
	ImageUrl string `json:"image" gorm:"column:image;not null"`
}
