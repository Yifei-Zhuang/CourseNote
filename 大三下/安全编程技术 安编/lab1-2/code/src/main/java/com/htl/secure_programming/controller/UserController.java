package com.htl.secure_programming.controller;

import com.htl.secure_programming.dto.UserDTO;
import com.htl.secure_programming.pojo.UserPojo;
import com.htl.secure_programming.service.UserService;
import com.htl.secure_programming.utils.JwtUtil;
import jakarta.servlet.http.HttpServletResponse;
import jakarta.validation.Valid;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.UUID;

@CrossOrigin
@RestController
public class UserController {
    @Autowired
    UserService userService;

    @Autowired
    JwtUtil jwtUtil;

    @PostMapping("/register")
    public String register(@Valid @RequestBody UserDTO userDTO, HttpServletResponse response) {
        UserPojo userPojo = new UserPojo(userDTO);
        try {
            userService.insert(userPojo);
            response.setStatus(200);
            return "success";
        } catch (Exception e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            return e.toString();
        }
    }

    @PostMapping("/login")
    public String login(@Valid @RequestBody UserDTO userDTO, HttpServletResponse response) {
        try {
            if (userService.validate(userDTO.getUsername(), userDTO.getPassword())) {
                response.setStatus(200);
                return JwtUtil.createJWT(UUID.randomUUID().toString(), Math.toIntExact(userService.getUserByUserName(userDTO.getUsername()).getId()), (long) -1);
            }
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            return "";
        } catch (Exception e) {
            e.printStackTrace();
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            return "";
        }
    }
}
