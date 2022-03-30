#!/bin/sh

SCRIPT_DIRECTORY=$(dirname $0)

rm -rf "$SCRIPT_DIRECTORY/xcode"
mkdir "$SCRIPT_DIRECTORY/xcode"

MACOSX_DEPLOYMENT_TARGET=10.10 cmake -S "$SCRIPT_DIRECTORY" -B "$SCRIPT_DIRECTORY/xcode" -G "Xcode"

# We should copy a features.h file
# from ./xcode/src/git2/sys/features.h
# to ./git2/sys/features.h

mv "$SCRIPT_DIRECTORY/xcode/src/git2/sys/features.h" "$SCRIPT_DIRECTORY/include/git2/sys/features.h"

# And also add GIT_SSH and GIT_SSH_MEMORY_CREDENTIALS
# We should add them via Package.swift, but let's do it after SPM adds plugin support.
file="$SCRIPT_DIRECTORY/include/git2/sys/features.h"

if ! grep -q "#define GIT_SSH_MEMORY_CREDENTIALS\b" "$file" ; then
    echo "#define GIT_SSH_MEMORY_CREDENTIALS 1" >> "$file"
fi

if ! grep -q "#define GIT_SSH\b" "$file" ; then
    echo "#define GIT_SSH 1" >> "$file"
fi
