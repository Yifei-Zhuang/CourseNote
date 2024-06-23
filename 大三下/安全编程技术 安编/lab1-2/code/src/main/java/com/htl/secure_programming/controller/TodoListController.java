package com.htl.secure_programming.controller;

import com.htl.secure_programming.pojo.TodoListPojo;
import com.htl.secure_programming.service.TodoListService;
import com.htl.secure_programming.utils.JwtUtil;
import jakarta.servlet.http.HttpServletResponse;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.context.request.RequestContextHolder;
import org.springframework.web.context.request.ServletRequestAttributes;

import javax.naming.AuthenticationException;
import java.io.IOException;
import java.util.List;

@CrossOrigin
@RestController
@RequestMapping("/todo")
public class TodoListController {
    public static int getUserId() throws AuthenticationException, IOException {
        String token = ((ServletRequestAttributes) RequestContextHolder.getRequestAttributes()).getRequest().getHeader("Authorization");
        if (token == null) {
            throw new AuthenticationException("missing token");
        }
//        System.out.println(token);
        return JwtUtil.validateJWT(token);
    }

    @Autowired
    TodoListService todoListService;

    @PostMapping("/all")
    public List<TodoListPojo> getAll(HttpServletResponse response) {
        try {
            int userId = getUserId();
            return todoListService.getAllTodo(userId);
        } catch (Exception e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            return null;
        }
    }

    @PostMapping("/insert")
    public String add(@RequestBody TodoListPojo todoListPojo, HttpServletResponse response) {
        try {
            int userId = getUserId();
            todoListPojo.setUserId(userId);
            response.setStatus(HttpServletResponse.SC_OK);
            todoListService.insert(todoListPojo);
            return "success";
        } catch (Exception e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return e.toString();
        }
    }

    @PostMapping("/delete")
    public String delete(@RequestBody TodoListPojo todoListPojo, HttpServletResponse response) {
        try {
            int userId = getUserId();
            if (userId != todoListService.getTodo(todoListPojo.getId()).getUserId()) {
                response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
                return "unauthorized";
            }
            todoListPojo.setUserId(userId);
            response.setStatus(HttpServletResponse.SC_OK);
            todoListService.delete(todoListPojo.getId());
            return "success";
        } catch (Exception e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return e.toString();
        }
    }

    @PostMapping("/update")
    public String update(@RequestBody TodoListPojo todoListPojo, HttpServletResponse response) {
        try {
            int userId = getUserId();
            todoListPojo.setUserId(userId);
            response.setStatus(HttpServletResponse.SC_OK);
            todoListService.update(todoListPojo);
            return "success";
        } catch (Exception e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return e.toString();
        }
    }

}
