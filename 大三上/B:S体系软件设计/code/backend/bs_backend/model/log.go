package model

type Log struct {
	Logid    int `json:"deviceId" gorm:"column:deviceid;primaryKey;autoIncrement"`
	DeviceID int `json:"deviceid" gorm:"references:Id;column:deviceid;not null"`
	Device
	Status      bool   `json:"status" gorm:"column:status"`
	SensorValue int    `json:"sensorValue" gorm:"column:sensorvalue;"`
	Brightness  int    `json:"brightness" gorm:"column:brightness"`
	UpInfo      string `json:"upinfo" gorm:"column:upInfo;"`
}
