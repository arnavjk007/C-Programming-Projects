echo 300 > expected.txt

./calc 100 200 > output.txt

diff output.txt expected.txt
if [ $? -ne 0 ]; then 
	echo "Calculates positives incorrectly"
	rm output.txt
	rm expected.txt
	exit 1
fi

echo -10 > expected2.txt

./calc -5 -5 > output2.txt

diff output2.txt expected2.txt
if [ $? -ne 0 ]; then
	echo "Calculates negatives incorrectly"
	rm output2.txt
	rm output.txt
	rm expected2.txt
	rm expected.txt
	exit 1
fi

./calc +100 +200 > output3.txt

diff output3.txt expected.txt
if [ $? -ne 0 ]; then 
	echo "Calculates incorrectly with +"
	rm output3.txt
	rm output2.txt
	rm output.txt
	rm expected.txt
	rm expected2.txt
	exit 1
fi

echo 0 > expected3.txt

./calc +100 -100 > output4.txt
diff output4.txt expected3.txt
if [ $? -ne 0 ];then 
	echo "Calculates pos and neg incorrectly"
	rm output4.txt
	rm output3.txt
	rm output2.txt
	rm output.txt
	rm expected.txt
	rm expected2.txt
	rm expected3.txt
	exit 1
fi

./calc -100 +100 > output5.txt
diff output5.txt expected3.txt
if [ $? -ne 0 ];then
        echo "Calculates pos and neg incorrectly"
	rm output5.txt
        rm output4.txt
        rm output3.txt
        rm output2.txt
        rm output.txt
        rm expected.txt
        rm expected2.txt
        rm expected3.txt
        exit 1
fi


echo "Calculates pos/neg and with + correctly"
rm output5.txt
rm output4.txt
rm output3.txt
rm output2.txt
rm output.txt
rm expected3.txt
rm expected2.txt
rm expected.txt
exit 0

