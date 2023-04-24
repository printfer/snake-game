#!/bin/sh

# Find the project root directory
project_root=$(git rev-parse --show-toplevel)

# Call lint_staged.sh using the absolute path
"$project_root/scripts/lint_staged.sh"
