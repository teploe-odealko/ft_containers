c++ main.cpp -Wall -Wextra -Werror -o std.out
c++ main.cpp -Wall -Wextra -Werror -DFT -o ft.out
./std.out > std
./ft.out > ft
diff std ft