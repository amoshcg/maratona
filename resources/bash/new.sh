#!/bin/bash

# 1. Define where your template file lives
# Change "template.cpp" to whatever your actual template file is named
TEMPLATE_FILE="$HOME/maratona/resources/bash/template.cpp"

# 2. Check if the user provided a name for the new file
if [ -z "$1" ]; then
  echo "Usage: $0 <new_file_name>"
  exit 1
fi

TARGET_FILE="$1"

# 3. Check if the template actually exists
if [ ! -f "$TEMPLATE_FILE" ]; then
  echo "Error: Template not found at $TEMPLATE_FILE"
  exit 1
fi

# 4. Safety check: Prevent overwriting an existing file
if [ -f "$TARGET_FILE" ]; then
  echo "Error: '$TARGET_FILE' already exists! Aborting."
  exit 1
fi

# 5. Perform the copy operation
cp "$TEMPLATE_FILE" "$TARGET_FILE"

echo "Success! Created '$TARGET_FILE' from template."
