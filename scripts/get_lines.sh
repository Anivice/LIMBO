#!/usr/bin/env bash

project_dir="$(git rev-parse --show-toplevel)"
project_lines="$(git ls-files "$project_dir" | grep -E '\.c|\.h|\.sh|\.cmake|\.asm|\.xml|\.gdb|\.ld' | xargs cat | wc -l)"
project_size=0
for file in $(git ls-files "$project_dir" | grep -E '\.c|\.h|\.sh|\.cmake|\.asm|\.xml|\.gdb|\.ld');
do
    ((project_size += $(stat "$file" --printf="%s")))
done

((project_size /= 1024))

sed --in-place -E 's/(\!\[Lines of Code\]\(https\:\/\/img\.shields\.io\/badge\/ProjectLines\-)(.*)(\-cyan\))/\1'"$project_lines"'\3/g' "$project_dir/README.md"
sed --in-place -E 's/(\!\[Size of Code\]\(https\:\/\/img\.shields\.io\/badge\/ProjectSize\-)(.*)(\%20K\-yellow\))/\1'"$project_size"'\3/g' "$project_dir/README.md"
