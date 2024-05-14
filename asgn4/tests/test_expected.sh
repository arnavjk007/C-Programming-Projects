
xxd input_expected.txt > expected.txt

./xd input_expected.txt > output.txt

diff expected.txt output.txt

if [ $? -ne 0 ]; then 
	echo "Output doesn't match expected output, failed expected test."
	rm output.txt
	rm expected.txt
	exit 1
fi

echo "Expected test passed"
rm output.txt
rm expected.txt
exit 0
