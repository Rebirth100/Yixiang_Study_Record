CREATE TABLE employee 
(
    e_id INTEGER PRIMARY KEY AUTOINCREMENT,
    e_name TEXT NOT NULL UNIQUE,
    e_email TEXT CHECK(e_email LIKE '%@%.%'),
    e_in_date date
);

INSERT INTO employee(e_id,e_name,e_email,e_in_date) 
VALUES(1,'张学友','zhang.xueyou@qq.com','2024-12-10'),
(2,'刘德华','liu.dehua@163.com','2022-04-10'),
(4,'陈奕迅','chen.yixun@qq.com','2025-10-12');

int main()
{	
	const char *db="xxxxxx";//自定义数据库文件路径 
	char jsonArray[4096]="\0";
	init(db);
	print(db);
	data2json(db,jsonArray);
	printf("%s",jsonArray);
}