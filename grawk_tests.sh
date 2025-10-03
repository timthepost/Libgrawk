#!/bin/sh
# test_grawk.sh — TAP tests for the grawk binary

echo "1..4"

# 1. Basic match
echo "foo" | ./ngrawk 'foo' | grep -q foo
[ $? -eq 0 ] && echo "ok 1 - basic match" || echo "not ok 1 - basic match failed"

# 2. Invert match
echo "foo" | ./ngrawk -v 'bar' | grep -q foo
[ $? -eq 0 ] && echo "ok 2 - invert match passed" || echo "not ok 2 - invert match failed"

# 3. Quiet match (should output nothing)
echo "foo" | ./ngrawk -q 'foo' | grep -q foo
[ $? -ne 0 ] && echo "ok 3 - quiet mode suppresses output" || echo "not ok 3 - quiet mode failed"

# 4. Ignore case match
echo "FOO" | ./ngrawk -i 'foo' | grep -q FOO
[ $? -eq 0 ] && echo "ok 4 - ignore case match" || echo "not ok 4 - ignore case failed"
