use sec;
create table user
(
    id       int auto_increment
        primary key,
    userName varchar(50) not null,
    password varchar(50) not null,
    salt     text        not null comment '密码加密使用的盐，增加安全性。',
    constraint user_userName_uindex
        unique (userName)
);

create table todoList
(
    id      int auto_increment
        primary key,
    finish  tinyint(1) default 0 not null,
    userId  int                  not null,
    content text                 null,
    constraint todoList_user_id_fk
        foreign key (userId) references user (id)
);

