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

func Register(c *gin.Context) {
	var user model.User
	if err := c.ShouldBindJSON(&user); err != nil {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "invalid request",
		})
		return
	}
	fmt.Println(c)
	fmt.Println(user)

	if user.UserName == "" || user.PassWord == "" || user.PhoneNumber == "" {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "缺少用户名或者密码或者手机号，请检查后重新提交",
		})
		return
	}
	if len(user.UserName) < 6 {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "用户名至少6位",
		})
	}
	if len(user.PassWord) < 6 {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "密码至少6位",
		})
	}
	var userInDB model.User
	if err := database.DB.Where("username = ?", user.UserName).First(&userInDB).Error; err != gorm.ErrRecordNotFound {
		c.JSON(http.StatusUnauthorized, gin.H{
			"error": "用户已存在",
		})
		return
	}
	if err := database.DB.Where("phonenumber = ?", user.PhoneNumber).First(&userInDB).Error; err != gorm.ErrRecordNotFound {
		c.JSON(http.StatusUnauthorized, gin.H{
			"error": "手机号已存在",
		})
		return
	}

	database.DB.Create(&user)
	c.JSON(http.StatusOK, gin.H{})
}
func ChangePassword(c *gin.Context) {
	userid := c.Query("userid")
	password := c.Query("password")
	if userid == "" || password == "" {
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "缺少字段",
		})
		return
	}
	var user model.User
	if err := database.DB.Where("userid = ?", userid).First(&user).Error; err == gorm.ErrRecordNotFound {
		c.JSON(http.StatusBadRequest, gin.H{
			"err": "userid non exist",
		})
	}
	user.PassWord = password
	database.DB.Save(&user)

	c.JSON(http.StatusOK, gin.H{})
}
func Login(c *gin.Context) {
	var login model.Login
	if err := c.ShouldBindJSON(&login); err != nil {
		fmt.Println("[error] login fail; ")
		fmt.Println("[info]  post msg is", c)
		c.JSON(http.StatusBadRequest, gin.H{
			"error": "请求无效，请检查输入参数",
		})
		return
	}
	//fmt.Println(c)
	var user model.User
	if err := database.DB.Where("username = ?", login.UserName).First(&user).Error; err == gorm.ErrRecordNotFound {
		c.JSON(http.StatusUnauthorized, gin.H{
			"error": "用户不存在",
		})
		//fmt.Println(user)
		return
	}
	if login.PassWord != user.PassWord {
		c.JSON(http.StatusUnauthorized, gin.H{
			"error": "密码错误",
		})
		return
	}
	c.JSON(http.StatusOK, gin.H{
		"msg":    "登陆成功",
		"userid": strconv.Itoa(user.Id),
	})
}
