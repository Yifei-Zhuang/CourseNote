package com.htl.secure_programming.service;

import com.htl.secure_programming.dao.UserMapper;
import com.htl.secure_programming.pojo.UserPojo;
import com.htl.secure_programming.utils.encryptUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class UserService {
    @Autowired
    private UserMapper userMapper;

    public UserPojo getUserById(int id) {
        return userMapper.getUserById(id);
    }

    public UserPojo getUserByUserName(String name) {
        return userMapper.getUserByUserName(name);
    }

    public int insert(UserPojo userPojo) {
        // generate salt
        String salt = encryptUtils.getSalt();
        String password = encryptUtils.getMd5Hex(userPojo.getPassword(), salt);
        userPojo.setPassword(password);
        userPojo.setSalt(salt);
        return userMapper.insert(userPojo);
    }

    public boolean validate(String username, String password) {
        UserPojo userPojo = userMapper.getUserByUserName(username);
        if (userPojo == null) {
            return false;
        }
        String salt = userPojo.getSalt();
        String md5PasswordInDB = userPojo.getPassword();
        return encryptUtils.validate(password, salt, md5PasswordInDB);
    }

}
