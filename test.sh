
if ! diff -u tests/33_output <(./bin/particles < tests/33_input) &>/dev/null; then
 >&2 echo "3x3 test failed"
else
 >&2 echo "3x3 test passed"
fi

if ! diff -u tests/74_output <(./bin/particles < tests/74_input) &>/dev/null; then
 >&2 echo "7x4 test failed"
else
 >&2 echo "7x4 test passed"
fi

if ! diff -u tests/95_output <(./bin/particles < tests/95_input) &>/dev/null; then
 >&2 echo "9x5 test failed"
else
 >&2 echo "9x5 test passed"
fi