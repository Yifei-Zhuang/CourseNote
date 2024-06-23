package database

import (
	"bs_backend/model"
	"errors"
	"fmt"
	"gorm.io/driver/mysql"
	"gorm.io/gorm"
	"gorm.io/gorm/logger"
)

var DB *gorm.DB
var err error

func ConnectToDB() {
	config := readInConfig()
	dsn := fmt.Sprintf("%s:%s@tcp(127.0.0.1:%s)/%s?charset=utf8mb4&parseTime=True&loc=Local", config.userName, config.password, config.port, config.dbName)
	if DB, err = gorm.Open(mysql.Open(dsn), &gorm.Config{
		Logger: logger.Default.LogMode(logger.Info),
	}); err != nil {
		panic(fmt.Errorf("database connection failed: %s \n", err))
	}
	fmt.Println("database connect successfully")
}

func DBInit() error {
	ConnectToDB()
	if err := DB.AutoMigrate(&model.User{}); err != nil {
		return errors.New("cannot migrate User table")
	}
	if err := DB.AutoMigrate(&model.House{}); err != nil {
		return errors.New("cannot migrate House table")
	}
	if err := DB.AutoMigrate(&model.Room{}); err != nil {
		return errors.New("cannot migrate Room table")
	}
	if err := DB.AutoMigrate(&model.Device{}); err != nil {
		return errors.New("cannot migrate Device table")
	}
	if err := DB.AutoMigrate(&model.Log{}); err != nil {
		return errors.New("cannot import Log table")
	}
	if err := DB.AutoMigrate(&model.Image{}); err != nil {
		return errors.New("cannot import Log table")
	}

	return nil
}

//func AddCard(card *model.Card) error {
//	if card.Cno == "" || card.Name == "" || card.Type == "" || card.Department == "" {
//		return errors.New("缺少table表所需字段")
//	}
//	if card.Type != "T" && card.Type != "S" {
//		return errors.New("无效的card类型（只能是T或者是S）")
//	}
//	if err := DB.Where("cno=?", card.Cno).First(&model.Card{}).Error; err != gorm.ErrRecordNotFound {
//		return errors.New("cno重复，违反主键约束")
//	}
//	DB.Create(card)
//	return nil
//}
//func AddBook(book *model.Book) error {
//	if book.Category == "" || book.Title == "" || book.Press == "" || book.Author == "" {
//		return errors.New("缺少Book表所需字段")
//	}
//	if err := DB.Where("bno=?", book.Bno).First(&model.Book{}).Error; err != gorm.ErrRecordNotFound {
//		return errors.New("bno重复，违反主键约束")
//	}
//	DB.Create(book)
//	return nil
//}
//
//func AddBorrow(borrow *model.Borrow) error {
//	fmt.Println("borrow", borrow)
//	if borrow.BookBno == "" || borrow.CardCno == "" {
//		return errors.New("传入的borrow元组缺少字段bno或cno")
//	}
//	if err := DB.Where("cno=?", string(borrow.CardCno)).First(&model.Card{}).Error; err == gorm.ErrRecordNotFound {
//		return errors.New("插入的borrow的cno性在Card表中不存在，违背外键约束")
//	}
//	var book model.Book
//
//	if err := DB.Where("bno=?", borrow.BookBno).First(&book).Error; err == gorm.ErrRecordNotFound {
//		return errors.New("插入的borrow的cno性在Card表中不存在，违背外键约束")
//	}
//
//	if book.Stock == 0 {
//		return errors.New("书籍已经被借阅完，请等待他人归还")
//	}
//
//	book.Stock -= 1
//	DB.Create(borrow)
//	DB.Save(&book)
//	return nil
//}
//
//func ReturnBorrow(borrow *model.Borrow) error {
//	if borrow.BookBno == "" || borrow.CardCno == "" {
//		return errors.New("传入的borrow元组缺少字段bno或cno")
//	}
//	if err := DB.Where("cno=?", string(borrow.CardCno)).First(&model.Card{}).Error; err == gorm.ErrRecordNotFound {
//		return errors.New("归还者的借书证号cno不存在")
//	}
//	fmt.Println("cno", borrow.CardCno, "bno", borrow.BookBno)
//
//	var book model.Book
//	if err := DB.Where("bno=?", borrow.BookBno).First(&book).Error; err == gorm.ErrRecordNotFound {
//		return errors.New("书籍的bno不存在")
//	}
//	tempDB := DB.Where("cno = ? and bno=?", borrow.CardCno, borrow.BookBno).First(&model.Borrow{})
//	if err := tempDB.Error; err == gorm.ErrRecordNotFound {
//		return errors.New("不存在该借阅记录或持卡人已经归还书籍")
//	}
//	tempDB.Updates(model.Borrow{
//		Return_date: time.Now().Format("2006-01-02"),
//	})
//	book.Stock += 1
//	DB.Save(&book)
//	return nil
//}
