
DROP DATABASE IF EXISTS DB_AMY;
CREATE DATABASE IF NOT EXISTS DB_AMY;
USE DB_AMY;

-- -----------------------------------------------------
-- Table TAB_JOINTS
-- -----------------------------------------------------
DROP TABLE IF EXISTS TAB_JOINTS;

CREATE TABLE TAB_JOINTS 
(
  arm INT not NULL DEFAULT 0,
  info INT not NULL DEFAULT 0,
  joint1 FLOAT not NULL DEFAULT '0.00',
  joint2 FLOAT not NULL DEFAULT '0.00',
  joint3 FLOAT not NULL DEFAULT '0.00',
  joint4 FLOAT not NULL DEFAULT '0.00',
  joint5 FLOAT not NULL DEFAULT '0.00'
);

ALTER TABLE TAB_JOINTS
ADD CONSTRAINT PK_JOINTS PRIMARY KEY (arm, info);


insert into TAB_JOINTS (arm, info) VALUES (0,0);
insert into TAB_JOINTS (arm, info) VALUES (0,1);
