* 编译选项
** 动态库
   gcc trans_lb.c -shared -fPIC -o libtranslib.so
   gcc main.c -ltranslib
