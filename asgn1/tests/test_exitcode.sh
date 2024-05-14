echo "BAD INPUT" > expected.txt

./calc 1 abc > output.txt

if [ $? -eq 0 ]; then
	echo "Wrong exit code for BAD INPUT"
	rm output.txt
	rm expected.txt
	exit 1
fi

./calc abc 1 > output.txt

if [ $? -eq 0 ]; then
        echo "Wrong exit code for BAD INPUT"
        rm output.txt
        rm expected.txt
        exit 1
fi

./calc abc abc > output.txt

if [ $? -eq 0 ]; then
        echo "Wrong exit code for BAD INPUT"
        rm output.txt
        rm expected.txt
        exit 1
fi

echo "Correct exit code"
rm output.txt
rm expected.txt
exit 0
