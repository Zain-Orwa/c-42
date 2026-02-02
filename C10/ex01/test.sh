#!bin/bash


./ft_cat file1 file2 > a.out
cat file1 file2 > b.out
diff a.out b.out

./ft_cat nonexistent_file
echo "exit status:" $?

echo "hello" | ./ft_cat
echo "hello" | ./ft_cat - file1

