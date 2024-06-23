package com.htl.secure_programming.service;

import com.htl.secure_programming.dao.TodoListMapper;
import com.htl.secure_programming.pojo.TodoListPojo;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class TodoListService {
    @Autowired
    TodoListMapper todoListMapper;

    public boolean insert(TodoListPojo todoListPojo) {
        return todoListMapper.insert(todoListPojo);
    }

    public boolean delete(int id) {
        return todoListMapper.delete(id);
    }

    public boolean delete(TodoListPojo todoListPojo) {
        return todoListMapper.delete(todoListPojo.getId());
    }

    public boolean update(TodoListPojo todoListPojo) {
//        System.out.println(todoListPojo);
        return todoListMapper.update(todoListPojo);
    }

    public List<TodoListPojo> getAllTodo(int userId) {
        return todoListMapper.getAllTodoByUserId(userId);
    }

    public TodoListPojo getTodo(int id) {
        return todoListMapper.getbyId(id);
    }
}
