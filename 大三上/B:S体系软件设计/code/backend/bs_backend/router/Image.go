package router

import (
	"bs_backend/model"
	"bufio"
	"errors"
	"github.com/gin-gonic/gin"
	"io/ioutil"
	"net/http"
	"os"
	"path/filepath"
	"strconv"
	"strings"
)

func UploadImage(c *gin.Context) {
	var image model.Image
	if err := c.ShouldBindJSON(&image); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "请求无效",
		})
		return
	}
	dir, _ := os.Getwd()
	path := filepath.Join(dir, "images", strconv.Itoa(image.RoomId))
	newFilePath := filepath.FromSlash(path)
	file, _ := os.Create(newFilePath)
	defer file.Close()
	// 切除第一个逗号之前的文本
	commaPos := strings.Index(image.ImageUrl, ",")
	w := bufio.NewWriter(file)
	if _, err := w.WriteString(image.ImageUrl[commaPos+1:]); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "图片存储失败",
		})
	}
	c.JSON(http.StatusOK, gin.H{
		"msg": "图片存储成功！",
	})
}

func GetImage(c *gin.Context) {
	roomid := c.Query("roomid")
	if roomid == "" {
		roomid = "-1"
	}
	dir, _ := os.Getwd()
	path := filepath.Join(dir, "images", roomid)
	//fmt.Println(path)
	// 检查文件是否存在
	if _, err := os.Stat(path); errors.Is(err, os.ErrNotExist) {
		c.JSON(http.StatusOK, gin.H{
			"status": false,
		})
		return
	}
	file, _ := os.Open(path)
	defer file.Close()
	content, _ := ioutil.ReadAll(file)
	c.JSON(http.StatusOK, gin.H{
		"status": true,
		"image":  string(content),
	})

}
