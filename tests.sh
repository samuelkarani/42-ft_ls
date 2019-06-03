# no std args
./ft_ls > out
ls -1 > test
diff out test

./ft_ls -R > out
ls -1 -R > test
diff out test

# std args
./ft_ls . > out
ls -1 . > test
diff out test

./ft_ls .. > out
ls -1 .. > test
diff out test

./ft_ls tests > out
ls -1 tests > test
diff out test

./ft_ls tests/ Makefile ./libft main.c > out
ls -1 tests/ Makefile ./libft main.c > test
diff out test

./ft_ls Makefile main.c > out
ls -1 Makefile main.c > test
diff out test

./ft_ls tests libft > out
ls -1 tests libft > test
diff out test
./ft_ls -R tests > out
ls -1 -R tests > test
diff out test

./ft_ls -R tests/ Makefile ./libft main.c > out
ls -1 -R tests/ Makefile ./libft main.c > test
diff out test

./ft_ls -R Makefile main.c > out
ls -1 -R Makefile main.c > test
diff out test

./ft_ls -R tests libft > out
ls -1 -R tests libft > test
diff out test

./ft_ls tests/empty > out
ls -1 tests/empty > test
diff out test

./ft_ls -R tests/empty > out
ls -1 -R tests/empty > test
diff out test

./ft_ls tests/ Makefile tests/empty ./libft main.c > out
ls -1 tests/ Makefile tests/empty ./libft main.c > test
diff out test

# multi-level
./ft_ls . ../ ~ tests/one  ./tests/two > out
ls -1 . ../ ~ tests/one ./tests/two > test
diff out test

# flags
./ft_ls -l main.c Makefile utils.c > out
ls -l main.c Makefile utils.c > test
diff out test

./ft_ls -a -r -l -t libft main.c Makefile utils.c > out
ls -1 -a -r -l -t libft main.c Makefile utils.c > test
diff out test

./ft_ls -a -t -l -r libft main.c Makefile utils.c > out
ls -1 -a -t -l -r libft main.c Makefile utils.c > test
diff out test

./ft_ls -ar -tl -R  libft main.c Makefile utils.c > out
ls -1 -ar -tl -R  libft main.c Makefile utils.c > test
diff out test

./ft_ls -artRl libft main.c Makefile utils.c > out
ls -1 -artRl libft main.c Makefile utils.c > test
diff out test

# special folders without -l
./ft_ls -art ~ > /tmp/out
ls -1 -art ~ > /tmp/test
diff /tmp/out /tmp/test

./ft_ls -art / > out
ls -1 -art / > test
diff out test

./ft_ls -art /etc > out
ls -1 -art /etc > test
diff out test

./ft_ls -art /usr > out
ls -1 -art /usr > test
diff out test

./ft_ls -art /tmp > out
ls -1 -art /tmp > test
diff out test

./ft_ls -art /var > out
ls -1 -art /var > test
diff out test

./ft_ls -art /dev > out
ls -1 -art /dev > test
diff out test

# special folders with -l
./ft_ls -alrt ~ > /tmp/out
ls -1 -alrt ~ > /tmp/test
diff out test

./ft_ls -alrt / > out
ls -1 -alrt / > test
diff out test

./ft_ls -alrt /usr > out
ls -1 -alrt /usr > test
diff out test

./ft_ls -alrt /etc > out
ls -1 -alrt /etc > test
diff out test

./ft_ls -alrt /tmp > out
ls -1 -alrt /tmp > test
diff out test

./ft_ls -alrt /var > out
ls -1 -alrt /var > test
diff out test

./ft_ls -alrt /tmp /var /etc Makefile  > out
ls -alrt /tmp /var /etc Makefile  > test
diff out test

# error handling
./ft_ls -Z > out 2>&1
ls -1 -Z > test 2>&1
diff out test

./ft_ls tests o > out 2>&1
ls -1 tests o > test 2>&1
diff out test

./ft_ls -a -t -Z -r > out 2>&1
ls -1 -a -t -Z -r > test 2>&1
diff out test

./ft_ls -artZRl > out 2>&1
ls -1artZRl > test 2>&1
diff out test

./ft_ls - l ~/ > out 2>&1
ls -1 - l ~/ > test 2>&1
diff out test

# number changes
./ft_ls -alRrt /dev > out
ls -1 -alRrt /dev > test
diff out test

# special folders HARD -R  without l
./ft_ls -aRt /usr > out1
ls -1 -aRt /usr > test1
diff out1 test1

./ft_ls -aRt /var > out2
ls -1 -aRt /var > test2
diff out2 test2

# special folders HARD -R with l
./ft_ls -alRt /usr > out4
ls -1 -alRt /usr > test4
diff out4 test4

exit 0

./ft_ls -aRrt ~ > /tmp/out3
ls -1 -aRrt ~ > /tmp/test3
diff /tmp/out3 /tmp/test3

./ft_ls -alRrt ~ > /tmp/out
ls -1 -alRrt ~ > /tmp/test
diff /tmp/out /tmp/test