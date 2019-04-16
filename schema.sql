CREATE TABLE `user` (
    `id` int(11) unsigned NOT NULL AUTO_INCREMENT,
    `name` varchar(64) NOT NULL DEFAULT '',
    `password` varchar(128) NOT NULL DEFAULT '',
    `salt` varchar(32) NOT NULL DEFAULT '',
    PRIMARY KEY (`id`),
    UNIQUE KEY `name` (`name`)
  );

--  create table syncdir(
--       name varchar(64) NOT NULL DEFAULT '',
--       device_mac varchar(18) not null default '',
--       client_path text ,
--       primary key (name,device_mac),
--       foreign key fk_username(name) references user(name)
--   );

create table device(
    dev_id int(11) unsigned NOT NULL AUTO_INCREMENT,
    name varchar(64) NOT NULL DEFAULT '',
    dev_mac varchar(18) not null default '',
    primary key(dev_id),
    foreign key fk_username(name) references user(name)
);

create table devicefile(
    dev_id int(11) unsigned NOT NULL,
    type int(1) unsigned NOT NULL default 0,
    path varchar(255) not null default '',
    last_modified_time int(12) unsigned,
    md5 varchar (18) default '',
    foreign key fk_devid(dev_id) references device(dev_id)
);

create table userfile(
    owner varchar(64) NOT NULL DEFAULT '',
    type int(1) unsigned NOT NULL default 0,
    last_modified_time int(12) unsigned,
    path varchar(255) not null default '',
    md5 varchar (18) default '',
    foreign key fk_owner(owner) references user(name)
)

create table transferingFile(
    owner varchar(64) NOT NULL DEFAULT '',
    type int(1) unsigned NOT NULL default 0,
    last_modified_time int(12) unsigned,
    path varchar(255) not null default '',
    md5 varchar (18) default '',
    foreign key fk_owner(owner) references user(name)
)