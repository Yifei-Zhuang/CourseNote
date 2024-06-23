package router

import (
	"bs_backend/database"
	"bs_backend/model"
	"github.com/gin-gonic/gin"
	"net/http"
)

func GetAllLog(c *gin.Context) {
	deviceId := c.Query("deviceId")
	if deviceId == "" {
		c.JSON(http.StatusBadRequest, gin.H{
			"err": "missing deviceId param",
		})
		return
	}
	var logs model.Log
	database.DB.Where("deviceid = ?", deviceId).Find(&logs)
	c.JSON(http.StatusOK, gin.H{
		"logs": logs,
	})
}
