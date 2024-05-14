echo "0.04104 -0.1231231 -" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Valid Input tests failed: large decimals"
        rm input.txt expected.txt output.txt
        exit 1
fi

echo "10 10 +" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Valid Input tests failed: 10 10 +"
        rm input.txt expected.txt output.txt
        exit 1
fi

echo "20 20 - 10 10 + 3030 100000000 / 100 9 * 50 5 %" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Valid Input tests failed: each op"
        rm input.txt expected.txt output.txt
        exit 1
fi

echo "5 s 5 c 5 t 5 a 4 r" > input.txt
./calc_arm < input.txt > expected.txt
./calc < input.txt > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Valid Input tests failed: each trig"
        rm input.txt expected.txt output.txt
        exit 1
fi

echo "Valid input tests passed"
rm input.txt expected.txt output.txt
exit 0
