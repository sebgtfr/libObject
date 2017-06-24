#!/bin/sh

cd ..
./compile_libobject.sh && clear
cd -

rm -f a.out

#gcc main.c -I../release/include -lobjects -L../release -Wall -Wextra -Werror -g -g3 -ggdb
gcc number_main.c -o number -I../release/include -lobjects -L../release -Wall -Wextra -Werror -g -g3 -ggdb
#gcc ini_main.c -o ini -I../release/include -lobjects -L../release -Wall -Wextra -Werror -g -g3 -ggdb
#gcc timer_main.c -o timer -I../release/include -lobjects -L../release -Wall -Wextra -Werror -g -g3 -ggdb
#gcc server_main.c -o server -I../release/include -lobjects -L../release -Wall -Wextra -Werror -g -g3 -ggdb
#gcc client_main.c -o client -I../release/include -lobjects -L../release -Wall -Wextra -Werror -g -g3 -ggdb

if [ -e "a.out" ]
then
       clear
#       valgrind ./a.out
fi
