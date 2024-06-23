package net

import (
	"bs_backend/middleware"
	"bs_backend/router"
	"github.com/gin-gonic/gin"
	"log"
)

func StartWebServer() {
	gin.SetMode(gin.ReleaseMode)
	r := gin.Default()
	r.Use(middleware.Cors())
	userRouter := r.Group("/user")
	userRouter.POST("/register", router.Register)
	userRouter.POST("/login", router.Login)
	userRouter.GET("/changePassword", router.ChangePassword)

	houseRouter := r.Group("/house")
	//houseRouter.Use(middleware.Auth())
	houseRouter.POST("/add", router.AddHouse)
	houseRouter.GET("/all", router.GetAllHouse)
	houseRouter.GET("/delete", router.DeleteHouse)
	//

	roomRouter := r.Group("/room")
	roomRouter.GET("/all", router.GetAllRoom)
	roomRouter.POST("/add", router.AddRoom)
	roomRouter.GET("/delete", router.DeleteRoom)
	roomRouter.GET("/get", router.GetSingleRoom)

	deviceRouter := r.Group("/device")
	deviceRouter.POST("/add", router.AddDevice)
	deviceRouter.GET("/get", router.GetRoomDevice)
	deviceRouter.GET("/delete", router.DeleteDevice)
	deviceRouter.GET("/getSingle", router.GetSingleDevice)
	deviceRouter.GET("/change", router.ChangeDevice)

	imageRouter := r.Group("/image")
	imageRouter.POST("/upload", router.UploadImage)
	imageRouter.GET("/get", router.GetImage)

	log.Println("start web server successfully")
	log.Println("listening on port 9000")
	log.Fatal(r.Run(":9000"))
}
