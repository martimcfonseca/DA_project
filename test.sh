#!/bin/bash

PROGRAM="./src/myProg"
INPUT_DIR="./Project1SampleDatasets/input"
EXPECTED_DIR="./Project1SampleDatasets/output"
TEMP_OUTPUT="./tmp_output.csv"

PASSED=0
FAILED=0

for input in $INPUT_DIR/*.csv; do
    filename=$(basename "$input")
    expected="$EXPECTED_DIR/$filename"

    $PROGRAM -b "$input" "$TEMP_OUTPUT" 2>/dev/null

    if diff -q "$TEMP_OUTPUT" "$expected" > /dev/null; then
        echo "$filename: PASSED"
        PASSED=$((PASSED+1))
    else
        echo "$filename: FAILED"
        FAILED=$((FAILED+1))
        diff "$TEMP_OUTPUT" "$expected"
    fi
done

rm -f "$TEMP_OUTPUT"

echo ""
echo "Results: $PASSED passed, $FAILED failed"