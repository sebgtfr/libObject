#!/bin/sh

cd ../script_compile/
./compile_libobject.sh && clear
cd -

rm -f a.out

#g++ main.cpp -o test -I../release/include -lobjects -L../release -w -Wall -Wextra -Werror -g -g3 -ggdb -ggdb3
#g++ buffer_main.cpp -o buffer -I../release/include -lobjects -L../release -w -Wall -Wextra -Werror -g -g3 -ggdb -ggdb3
g++ string_main.cpp -o string -I../release/include -lobjects -L../release -w -Wall -Wextra -Werror -g -g3 -ggdb -ggdb3
