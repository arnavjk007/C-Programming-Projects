
xxd input_expected.txt input_expected.txt > expected.txt

./xd input_expected.txt input_expected.txt > output.txt

diff expected.txt output.txt

if [ $? -eq 0 ]; then
	echo "Invalid arguments test passed"
	rm output.txt
	rm expected.txt
	exit 0
fi

echo "Invalid arguments test failed"
rm output.txt
rm expected.txt
exit 1
