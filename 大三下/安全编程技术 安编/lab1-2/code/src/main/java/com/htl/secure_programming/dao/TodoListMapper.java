package com.htl.secure_programming.dao;

import com.htl.secure_programming.pojo.TodoListPojo;
import org.apache.ibatis.annotations.*;

import java.util.List;

@Mapper
public interface TodoListMapper {
    @Insert({
            "insert into todolist (id, finish, userId, content) ",
            "values (#{id}, #{finish}, #{userId}, #{content})"
    })
    public boolean insert(TodoListPojo todoListPojo);

    @Delete({
            "delete from todolist where id = #{id}"
    })
    public boolean delete(int id);

    @Update({
            "update todolist set finish = #{finish},  userId = #{userId}, content = #{content} where id = #{id}"
    })
    public boolean update(TodoListPojo todoListPojo);

    @Select({
            "select * from todolist where userId = #{userId}"
    })
    public List<TodoListPojo> getAllTodoByUserId(int userId);

    @Select({
            "select * from todolist where id = #{id}"
    })
    public TodoListPojo getbyId(int id);
}
