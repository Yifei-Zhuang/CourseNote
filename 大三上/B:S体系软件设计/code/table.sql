create table devices
(
    deviceid    bigint auto_increment
        primary key,
    devicename  longtext   null,
    type        longtext   not null,
    roomid      bigint     null,
    description longtext   null,
    status      tinyint(1) null,
    sensorvalue bigint     null,
    brightness  bigint     null,
    position    bigint     not null
);

create table images
(
    roomid bigint   not null,
    image  longtext not null
);

create table logs
(
    deviceid    bigint auto_increment
        primary key,
    devicename  longtext   null,
    type        longtext   not null,
    roomid      bigint     null,
    description longtext   null,
    status      tinyint(1) null,
    sensorvalue bigint     null,
    brightness  bigint     null,
    position    bigint     not null,
    upInfo      longtext   null
);

create table users
(
    userid      bigint auto_increment,
    phonenumber varchar(100) not null,
    username    varchar(100) not null,
    ` password` longtext     not null,
    primary key (userid, phonenumber, username),
    constraint idx_users_phone_number
        unique (phonenumber),
    constraint idx_users_user_name
        unique (username)
);

create table houses
(
    houseid     bigint auto_increment
        primary key,
    userid      bigint   not null,
    housename   longtext not null,
    description longtext not null,
    roomcount   bigint   not null,
    constraint fk_houses_user
        foreign key (userid) references users (userid)
);

create table rooms
(
    roomid      bigint auto_increment
        primary key,
    name        longtext null,
    description longtext null,
    houseid     bigint   not null,
    userid      bigint   not null,
    constraint fk_rooms_house
        foreign key (houseid) references houses (houseid),
    constraint fk_rooms_user
        foreign key (userid) references users (userid)
);


