#!/bin/sh

# Copy the pre-commit hook to the .git/hooks/ directory
cp scripts/pre-commit.sh .git/hooks/pre-commit

# Make the pre-commit hook and lint_staged.sh script executable
chmod +x .git/hooks/pre-commit scripts/lint_staged.sh

# Display a success message
echo "Project setup complete. Pre-commit hook installed."
