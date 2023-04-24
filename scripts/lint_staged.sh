#!/bin/sh

# Get a list of staged files
staged_files=$(git diff --cached --name-only --diff-filter=ACM)

# Set the exit code to 0 (success) initially
exit_code=0

# Check if there are any staged files
if [ -z "$staged_files" ]; then
    echo "No staged files found. Skipping linting and formatting."
    exit 0
fi

echo "Running linting and formatting on staged files..."

# Loop through staged files
for file in $staged_files; do
    if [[ $file == *.c ]] || [[ $file == *.h ]]; then
        echo "Processing $file"

        # Format the file
        echo "  Formatting with clang-format..."
        clang-format -i "$file"

        # Lint the file
        echo "  Linting with clang-tidy..."
        lint_output=$(clang-tidy "$file" -- -I/usr/include)

        # If linting has warnings or errors, print the output and update the exit code
        if [ ! -z "$lint_output" ]; then
            echo "  Linting issues found in $file:"
            echo "$lint_output"
            exit_code=1
        else
            echo "  No linting issues found in $file"
        fi

        # Stage the file (if it was modified by clang-format)
        git add "$file"
    fi
done

# If any linting issues were found, exit with a non-zero code to abort the commit
if [ $exit_code -ne 0 ]; then
    echo "Linting failed. Commit aborted."
else
    echo "Linting and formatting completed successfully. Proceeding with the commit."
fi

exit $exit_code
