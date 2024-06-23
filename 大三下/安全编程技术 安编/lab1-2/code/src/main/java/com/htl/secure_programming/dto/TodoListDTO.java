package com.htl.secure_programming.dto;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class TodoListDTO {
    private int id;
    private boolean finish;
    private int userId;
    private String content;
}
