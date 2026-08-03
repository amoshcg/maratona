#!/bin/bash

# 1. Check if a file was provided
if [ -z "$1" ]; then
  echo "Usage: $0 <source_file.cpp>"
  exit 1
fi

SOURCE_FILE="$1"

# 2. Extract the filename without the extension and append .out
# Adding a distinct extension separates it from the source file in terminal autocomplete
OUTPUT_BINARY="${SOURCE_FILE%.*}.out"

# 3. Check if the executable exists and is up-to-date
# -nt checks if a file is strictly newer. Negating it skips compilation 
# if the binary is newer than or the exact same age as the source.
if [ -f "$OUTPUT_BINARY" ] && [ ! "$SOURCE_FILE" -nt "$OUTPUT_BINARY" ]; then
  echo "Already updated. Run it with: ./$OUTPUT_BINARY"
  exit 0
fi

# 4. Define your compiler and flags
CXX="g++"
CXXFLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -Wshadow -std=c++23 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts"

echo "Compiling $SOURCE_FILE..."

# 5. Execute the compile command
$CXX $CXXFLAGS "$SOURCE_FILE" -o "$OUTPUT_BINARY"

# 6. Check if compilation was successful
if [ $? -eq 0 ]; then
  echo "Success! Run it with: ./$OUTPUT_BINARY"
else
  echo "Compilation failed."
fi