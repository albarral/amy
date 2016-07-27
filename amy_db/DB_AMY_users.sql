
-- Users creation for DB_AMY database 
-- execute this script with root user
-- execute this script before the schema script


CREATE USER 'amy'@'localhost' IDENTIFIED BY 'amypwd';

GRANT SELECT, INSERT, UPDATE, DELETE, DROP, ALTER, CREATE on DB_AMY.* TO amy@localhost;
