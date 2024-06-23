package router

import (
	"bs_backend/database"
	"bs_backend/model"
	"fmt"
	"github.com/gin-gonic/gin"
	"gorm.io/gorm"
	"net/http"
	"strconv"
)

func AddDevice(c *gin.Context) {
	var device model.Device
	//前端发送的值
	//{
	//	type:'door',
	//  name:'133'
	//	roomid:'132',
	//	description:'123',
	//	position:'12'
	//}
	// 需要针对类型初始化value
	if err := c.ShouldBindJSON(&device); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "invalid request",
		})
		return
	}
	//log.Println("device", device)
	if device.Type == "" {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "缺少字段，提交失败",
		})
		return
	}
	if device.Type == "door" {
		// 初始化门关闭
		device.Status = false
	} else if device.Type == "light_bulb" {
		device.Status = true
		device.Brightness = 100
	} else if device.Type == "wet" || device.Type == "temperature" {
		device.SensorValue = 10
	} else if device.Type == "switch" {
		device.Status = false
	}
	database.DB.Create(&device)
	c.JSON(http.StatusOK, gin.H{
		"msg": "创建成功",
	})
}
func GetRoomDevice(c *gin.Context) {
	//前端需要传输的值
	//{
	//	roomid: "123"
	//}
	var devices []model.Device
	var roomid string = c.Query("roomid")
	//log.Println("roomid", roomid)
	if roomid == "" {
		c.JSON(http.StatusBadRequest, gin.H{"error": "missing roomid"})
		return
	}
	database.DB.Where("roomid = ?", roomid).Find(&devices)
	c.JSON(http.StatusOK, gin.H{
		"result": devices,
	})
}
func GetSingleDevice(c *gin.Context) {
	//前端需要传输的值
	//{
	//	roomid: "123"
	//}
	var device model.Device
	var deviceid string = c.Query("deviceid")
	//log.Println("roomid", roomid)
	if deviceid == "" {
		c.JSON(http.StatusBadRequest, gin.H{"error": "missing roomid"})
		return
	}
	database.DB.Where("deviceid = ?", deviceid).Find(&device)
	c.JSON(http.StatusOK, gin.H{
		"result": device,
	})
}
func DeleteDevice(c *gin.Context) {
	var deviceid string = c.Query("deviceId")
	database.DB.Where("deviceid = ? ", deviceid).Delete(&model.Device{})
	c.JSON(http.StatusOK, gin.H{
		"status": "delete " + deviceid + " succeeefully",
	})
}
func ChangeDevice(c *gin.Context) {
	DeviceType := c.Query("type")
	deviceId, _ := strconv.Atoi(c.Query("deviceId"))
	//if DeviceType != "light_bulb" && DeviceType != "door" && DeviceType != "switch" {
	//	c.JSON(http.StatusBadRequest, gin.H{
	//		"err": "wrong type",
	//	})
	//}
	var device model.Device

	if err := database.DB.Where("deviceId = ?", deviceId).First(&device).Error; err == gorm.ErrRecordNotFound {
		c.JSON(http.StatusBadRequest, gin.H{
			"err": "deviceid non exist",
		})
	}

	if DeviceType == "light_bulb" {
		lightness, _ := strconv.Atoi(c.Query("lightness"))
		device.Brightness = lightness
		if lightness == 0 {
			device.Status = false
		} else {
			device.Status = true
		}
		database.DB.Save(&device)
	} else if DeviceType == "sensor" {
		value, _ := strconv.Atoi(c.Query("value"))
		device.SensorValue = value
		database.DB.Save(&device)
	} else {
		target := c.Query("target")
		fmt.Println("target is ", target)
		if target == "false" {
			device.Status = false
		} else {
			device.Status = true
		}
		fmt.Println(device)
		database.DB.Save(&device)
	}
	c.JSON(http.StatusOK, gin.H{})
}
