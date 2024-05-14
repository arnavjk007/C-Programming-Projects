bash delayinput.sh delayed.txt | ./calc_arm  > expected.txt
bash delayinput.sh delayed.txt | ./calc > output.txt
diff output.txt expected.txt
if [ $? -ne 0 ]; then
        echo "Delayed tests failed"
        rm expected.txt output.txt
        exit 1
fi

echo "Delayed tests passed"
rm output.txt expected.txt
exit 0
