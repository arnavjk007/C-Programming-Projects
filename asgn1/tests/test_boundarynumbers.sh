echo 1024 > POSexpected.txt

./calc 512 512 > output.txt

diff output.txt POSexpected.txt
if [ $? -ne 0 ]; then
	echo "Boundary tests failed, 512 512"
	rm output1.txt
	rm POSexpected.txt
	exit 1
fi

echo -1024 > NEGexpected.txt

./calc -512 -512 > output2.txt

diff output2.txt NEGexpected.txt
if [ $? -ne 0 ]; then
	echo "Boundary tests failed, -512 -512"
        rm output2.txt
        rm output1.txt
        rm POSexpected.txt
        rm NEGexpected.txt
	exit 1
fi

#type 2 error
echo 1025 > type2.txt

./calc 512 513 > type2output.txt
diff type2output.txt type2.txt
if [ $? -eq 0 ]; then
	echo "Type 2 large number error"
	rm type2.txt
        rm type2output.txt
        rm output2.txt
        rm output1.txt
        rm POSexpected.txt
        rm NEGexpected.txt
	exit 1
fi

echo "Boundary tests passed"
rm POSexpected.txt
rm output1.txt
rm NEGexpected.txt
rm output2.txt
rm type2.txt
rm type2output.txt
exit 0
