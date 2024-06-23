package router

import (
	"bs_backend/database"
	"bs_backend/model"
	"fmt"
	"github.com/gin-gonic/gin"
	"net/http"
)

func AddHouse(c *gin.Context) {
	var house model.House

	if err := c.ShouldBindJSON(&house); err != nil {

		c.JSON(http.StatusBadRequest, gin.H{
			"error": "invalid request",
		})
		return
	}
	house.RoomCount = 0
	// 获取userid
	database.DB.Create(&house)
	c.JSON(http.StatusOK, gin.H{
		"msg": "创建成功",
	})
}
func DeleteHouse(c *gin.Context) {
	var houseid string = c.Query("houseid")
	database.DB.Where("houseid = ? ", houseid).Delete(&model.House{})
	c.JSON(http.StatusOK, gin.H{
		"status": "delete " + houseid + " succeeefully",
	})
}
func GetAllHouse(c *gin.Context) {
	var houses []model.House
	var userid string = c.Query("userid")
	if userid == "" {
		c.JSON(http.StatusBadRequest, gin.H{"error": "missing userid"})
		return
	}
	database.DB.Where("userid = ?", userid).Find(&houses)
	c.JSON(http.StatusOK, gin.H{
		"result": houses,
	})
	fmt.Println(houses)
}
