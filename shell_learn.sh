#!/bin/bash

my_array=(A B "C" D)


echo "array: ${my_array[*]}"
echo "数组元素个数为: ${#my_array[@]}"

echo "第一个元素为: ${my_array[0]}"
echo "第二个元素为: ${my_array[1]}"
echo "第三个元素为: ${my_array[2]}"
echo "第四个元素为: ${my_array[3]}"


for i in {0..10}; do
	#表达式和运算符之间要有空格，例如 2+2 是不对的，必须写成 2 + 2。
	#完整的表达式要被反引号`` 包含。
	#乘号(*)前边必须加反斜杠(\)才能实现乘法运算；
    my_array[i]=`expr $i + 1` 
done

echo "array: ${my_array[*]}"
echo "数组元素个数为: ${#my_array[@]}"

a=2
b=3
echo $[$a == $b]
echo $[$a != $b]

if [ $a -eq $b ]
then
   echo "$a -eq $b : a is equal to b"
else
   echo "$a -eq $b: a is not equal to b"
fi

if [ $a -gt $b ]
then
   echo "$a -gt $b: a is greater than b"
else
   echo "$a -gt $b: a is not greater than b"
fi

if [ $a -lt $b ]
then
   echo "$a -lt $b: a is less than b"
else
   echo "$a -lt $b: a is not less than b"
fi

if [ $a -ge $b ]
then
   echo "$a -ge $b: a is greater or  equal to b"
else
   echo "$a -ge $b: a is not greater or equal to b"
fi

if [ $a -le $b ]
then
   echo "$a -le $b: a is less or  equal to b"
else
   echo "$a -le $b: a is not less or equal to b"
fi


string="alibaba is a great company"
echo `expr index "$string" is`


