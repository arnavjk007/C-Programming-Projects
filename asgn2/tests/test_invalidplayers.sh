
echo 1 > /tmp/lcr_input
echo 4823 >> /tmp/lcr_input

lcr_ref=lcr_arm
if [ $(uname -m) = "x86_64" ]; then
    lcr_ref=lcr_x86
fi

./$lcr_ref < /tmp/lcr_input > /tmp/ref_out 2> /tmp/ref_err
ref_returncode=$?

./lcr < /tmp/lcr_input > /tmp/my_out 2> /tmp/my_err
my_returncode=$?

diff /tmp/ref_out /tmp/my_out
if [ $? -ne 0 ]; then
    echo "Failed invalid player test."
    exit 1
fi

diff /tmp/ref_err /tmp/my_err
if [ $?  -ne 0 ]; then
    echo "Error output doesn't match for invalid player test."
    exit 1
fi

echo "Passed invalid player test."
exit 0
