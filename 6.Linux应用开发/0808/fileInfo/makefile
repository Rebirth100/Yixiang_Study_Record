build_app:
	cc file_info.h file_info.c main.c -o  app

build_app_debug:
	cc file_info.h file_info.c main.c -o  app -D DEBUG

test_app:
	./app 
	./app .
	./app -d
	./app /dev
	./app /home/hgg/ptest
	./app .  -d
	./app  -d -d -d -d
	./app /media/  /home/
	./app /media/  /home/  -d
	./app /media/  /home/hgg/ptest  /home
	./app /media/  /home/hgg/ptest  /home -d
	./app /media/ -d /home/hgg/ptest -d /home -d
	./app /home/hgg/i.c