echo "3 +" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: 3 +"
	rm input.txt expected.txt output.txt
	exit 1
fi

echo "3 -" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: 3 -"
	rm input.txt expected.txt output.txt
	exit 1
fi

echo "3 *" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: 3 *"
	rm input.txt expected.txt output.txt
	exit 1
fi


echo "3 /" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: 3 /"
	rm input.txt expected.txt output.txt
	exit 1
fi


echo "3 %" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: 3 %"
	rm input.txt expected.txt output.txt
	exit 1
fi


echo "s" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: s"
	rm input.txt expected.txt output.txt
	exit 1
fi


echo "c" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: c"
	rm input.txt expected.txt output.txt
	exit 1
fi


echo "t" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: t"
	rm input.txt expected.txt output.txt
	exit 1
fi


echo "a" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: a"
	rm input.txt expected.txt output.txt
	exit 1
fi


echo "r" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: r"
	rm input.txt expected.txt output.txt
	exit 1
fi

echo "2 2 2 2 + + + dhsalh" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: string"
	rm input.txt expected.txt output.txt
	exit 1
fi

echo "\n" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
	echo "Invalid Input tests failed: 3 +"
	rm input.txt expected.txt output.txt
	exit 1
fi

echo "Invalid input tests passed"
rm input.txt expected.txt output.txt
exit 0
