echo "BAD INPUT" > expected.txt

./calc 4.5 5 > output.txt

diff output.txt  expected.txt
if [ $? -eq 0 ]; then
	echo "No decimal found, test passed"
	rm output.txt
	rm expected.txt
	exit 0
fi

./calc 5 4.5 > output2.txt

diff output2.txt expected.txt
if [ $? -eq 0 ]; then
	echo "No decimal found, test passed"
	rm output2.txt
	rm output.txt
	rm expected.txt
	exit 0
fi

#type 2 error 
echo 1.1 > expected2.txt

./calc 0.1 1 > output3.txt
diff output3.txt expected2.txt
if [ $? -eq 0 ]; then
	echo "Decimal type 2 tests failed"
	rm output3.txt
	rm output2.txt
	rm output.txt
	rm expected2.txt
	rm expected.txt
	exit 1
fi

echo "Decimal tests failed"
rm output.txt
rm output2.txt
rm output3.txt
rm expected2.txt
rm expected.txt
exit 1
