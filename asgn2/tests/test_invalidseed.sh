# Create a file with test input.
echo 8 > /tmp/lcr_input
echo -1000 >> /tmp/lcr_input

# Select the right binary to use as a reference.
lcr_ref=lcr_arm
if [ $(uname -m) = "x86_64" ]; then
    lcr_ref=lcr_x86
fi

# Run the reference binary with the test input and redirect the output and
# errors to separate files.
./$lcr_ref < /tmp/lcr_input > /tmp/ref_out 2> /tmp/ref_err
ref_returncode=$?

# Run your binary with the test input and redirect the output and errors to
# a separate file.
./lcr < /tmp/lcr_input > /tmp/my_out 2> /tmp/my_err
my_returncode=$?

diff /tmp/ref_out /tmp/my_out
if [ $? -ne 0 ]; then
    echo "Failed invalid seed test."
    exit 1
fi

diff /tmp/ref_err /tmp/my_err
if [ $?  -ne 0 ]; then
    echo "Error output is wrong."
    exit 1
fi

if [ $ref_returncode -ne $my_returncode ] ; then
    echo "Exit codes are differnt."
    exit 1
fi

echo "Invalid seeds test passed"
exit 0
