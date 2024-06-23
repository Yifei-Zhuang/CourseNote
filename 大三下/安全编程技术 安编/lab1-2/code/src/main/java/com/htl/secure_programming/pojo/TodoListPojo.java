package com.htl.secure_programming.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class TodoListPojo {
    private int id;
    private boolean finish;
    private int userId;
    private String content;
}
