package com.htl.secure_programming.pojo;


import com.htl.secure_programming.dto.UserDTO;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class UserPojo {
    private Long id;
    private String username;
    private String password;
    private String salt;

    public UserPojo(UserDTO userDTO) {
        this.id = userDTO.getId();
        this.username = userDTO.getUsername();
        this.password = userDTO.getPassword();
    }
}
