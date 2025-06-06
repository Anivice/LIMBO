#!/usr/bin/sh
"$1" --version 2>&1 | head -n 1 | sed -E 's/.*\s([0-9]+\.[0-9]+\.[0-9]+).*/\1/g' 2>/dev/null
exit $?
