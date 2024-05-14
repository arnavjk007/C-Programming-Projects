echo "TOO BIG" > expected.txt

./calc 513 8 > output1.txt


diff output1.txt expected.txt
if [ $? -ne 0 ]; then 
	echo "Error, not detecting large numbers"
	rm output1.txt
	rm expected.txt
	exit 1
fi 

./calc 8 513 > output2.txt

diff output2.txt expected.txt
if [ $? -ne 0 ]; then 
	echo "Error, not detecting large numbers"
	rm output2.txt
	rm output1.txt
	rm expected.txt
	exit 1
fi

./calc -513 8 > output3.txt

diff output3.txt expected.txt
if [ $? -ne 0]; then 
	echo "Error, not detcting large numbers"
	rm output3.txt
	rm output2.txt
        rm output1.txt
	rm expected.txt
	exit 1
fi

./calc 8 -513 > output4.txt

diff output4.txt expected.txt
if [ $? -ne 0 ]; then 
	echo "Error, not detecting large numbers"
	rm output3.txt
        rm output2.txt
        rm output1.txt
	rm output4.txt
	rm expected.txt
	exit 1
fi

./calc -513 -8 > output5.txt

diff output5.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Error, not detecting large numbers"
        rm output3.txt
        rm output2.txt
        rm output1.txt
        rm output4.txt
	rm output5.txt
        rm expected.txt
        exit 1
fi

./calc -8 -513 > output6.txt

diff output6.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Error, not detecting large numbers"
        rm output3.txt
        rm output2.txt
        rm output1.txt
        rm output4.txt
        rm output5.txt
	rm output6.txt
        rm expected.txt
        exit 1
fi

echo "Large Tests Passed"
rm expected.txt
rm output1.txt
rm output2.txt
rm output3.txt
rm output4.txt
rm output5.txt
rm output6.txt
exit 0

