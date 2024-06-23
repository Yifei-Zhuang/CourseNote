package model

type Device struct {
	Id          int    `json:"deviceId" gorm:"column:deviceid;primaryKey;autoIncrement"`
	Name        string `json:"deviceName" gorm:"column:devicename;not null'"`
	Type        string `json:"type" gorm:"column:type;not null"`
	RoomId      int    `json:"roomid" gorm:"references:Id;column:roomid;"`
	Description string `json:"description" gorm:"column:description;"`
	// 描述灯的开闭，以及门的开关
	Status bool `json:"status" gorm:"column:status"`
	// 描述传感器的值
	SensorValue int `json:"sensorValue" gorm:"column:sensorvalue;"`
	// 描述亮度值
	Brightness int `json:"brightness" gorm:"column:brightness"`
	Position   int `json:"position" gorm:"column:position;not null"`
	//

}
