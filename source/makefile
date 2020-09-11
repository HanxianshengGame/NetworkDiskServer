src_files:=$(wildcard *.c)
obj_files:=$(patsubst %.c, %.o, $(src_files))
CXX:=g++
final_file:= Server
$(final_file):$(obj_files)
	$(CXX) $^ -o $@ -lpthread -lmysqlclient -lcrypt
%.o:%.c
	$(CXX) -c $^ -o $@ -Wall -D DEBUG
.PHONY: rebuild clean
rebuild: clean $(final_file)
clean: 
	rm -rf $(obj_files) $(final_file)
