#!/usr/bin/env bash
# cp_run.sh - Optimized for MSYS2 on Windows

# 1. Convert Windows paths to Unix paths (Critical for MSYS2)
CPP_FILE=$(cygpath -u "$1")

if [ -z "$CPP_FILE" ]; then
    echo "Error: No file provided."
    exit 1
fi

# 2. Setup Directories relative to the script location
# This ensures it works regardless of where you call it from
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
BUILD_DIR="$SCRIPT_DIR/../build"
mkdir -p "$BUILD_DIR"

# 3. Extract names
FILE_NAME=$(basename "$CPP_FILE")
BASE_NAME="${FILE_NAME%.*}"
# Update the EXE path to be Unix-friendly
EXE=$(cygpath -u "$BUILD_DIR/$BASE_NAME.exe")
INPUT_FILE="$BUILD_DIR/input.txt"
OUTPUT_FILE="$BUILD_DIR/output.txt"

# 4. Compile
echo "Compiling: $FILE_NAME"
g++ -std=c++17 -O2 -Wall "$CPP_FILE" -o "$EXE"

if [ $? -ne 0 ]; then
    echo "--------------------------"
    echo "Compilation Failed!"
    exit 1
fi

# 5. Run with Input/Output
if [ -f "$INPUT_FILE" ]; then
    echo "Running with input.txt..."
    # Using 'time' to see how fast your code is
    time "$EXE" < "$INPUT_FILE" > "$OUTPUT_FILE"
    echo "--------------------------"
    echo "Success! Output: build/output.txt"
else
    echo "Input file not found. Running in terminal..."
    "$EXE"
fi