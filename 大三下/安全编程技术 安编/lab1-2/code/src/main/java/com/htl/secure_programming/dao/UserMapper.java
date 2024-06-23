package com.htl.secure_programming.dao;

import com.htl.secure_programming.pojo.UserPojo;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Options;
import org.apache.ibatis.annotations.Select;

@Mapper
public interface UserMapper {
    @Insert({
            "insert into user (username, password, salt)",
            "values (#{username}, #{password}, #{salt})"
    })
    @Options(useGeneratedKeys = true, keyProperty = "id")
    public int insert(UserPojo userPojo);

    @Select({
            "select * from user where id = #{id}"
    })
    public UserPojo getUserById(int id);

    @Select({
            "select * from user where username = #{name}"
    })
    public UserPojo getUserByUserName(String name);

}
