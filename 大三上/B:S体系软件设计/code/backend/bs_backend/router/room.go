package router

import (
	"bs_backend/database"
	"bs_backend/model"
	"github.com/gin-gonic/gin"
	"net/http"
)

func GetSingleRoom(c *gin.Context) {
	var room []model.Room
	var roomid string = c.Query("roomid")
	if roomid == "" {
		c.JSON(http.StatusBadRequest, gin.H{"error": "missing userid"})
		return
	}
	database.DB.Where("roomid = ?", roomid).Find(&room)
	c.JSON(http.StatusOK, gin.H{
		"result": room,
	})
}
func GetAllRoom(c *gin.Context) {
	var rooms []model.Room
	var houseid string = c.Query("houseid")
	if houseid == "" {
		c.JSON(http.StatusBadRequest, gin.H{"error": "missing userid"})
		return
	}
	database.DB.Where("houseid = ?", houseid).Find(&rooms)
	c.JSON(http.StatusOK, gin.H{
		"result": rooms,
	})
}
func AddRoom(c *gin.Context) {
	var room model.Room
	if err := c.ShouldBindJSON(&room); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "invalid request",
		})
		return
	}
	// 添加房间
	database.DB.Create(&room)
	// 修改对应的场所的房间数
	var house model.House
	database.DB.Where("houseid=?", room.HouseHouseId).First(&house)
	house.RoomCount += 1
	database.DB.Save(&house)
	c.JSON(http.StatusOK, gin.H{
		"msg": "创建成功",
	})
}
func DeleteRoom(c *gin.Context) {
	var roomid string = c.Query("roomid")
	var room model.Room
	var house model.House
	database.DB.Where("roomid=?", roomid).First(&room)
	database.DB.Where("houseid=?", room.HouseHouseId).First(&house)
	house.RoomCount -= 1
	database.DB.Save(&house)
	database.DB.Where("roomid = ? ", roomid).Delete(&model.Room{})

	c.JSON(http.StatusOK, gin.H{
		"status": "delete " + roomid + " succeeefully",
	})
}
