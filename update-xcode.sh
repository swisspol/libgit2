#!/bin/sh

SCRIPT_DIRECTORY=$(dirname $0)
echo "Traveling to $SCRIPT_DIRECTORY"
cd $SCRIPT_DIRECTORY

SHOULD_OPEN_XCODE=$1

export MACOSX_DEPLOYMENT_TARGET=10.10  # Must match GitUp

rm -rf "xcode"
mkdir "xcode"
cd "xcode"
cmake -G "Xcode" ..

# We should copy a features.h file 
# from ./xcode/src/git2/sys/features.h
# to ./git2/sys/features.h

cd ../
mv "./xcode/src/git2/sys/features.h" "./include/git2/sys/features.h"

# And also add GIT_SSH and GIT_SSH_MEMORY_CREDENTIALS
# We should add them via Package.swift, but let's do it after SPM adds plugin support.
file="./include/git2/sys/features.h"

if ! grep -q "#define GIT_SSH_MEMORY_CREDENTIALS\b" "$file" ; then
    echo "#define GIT_SSH_MEMORY_CREDENTIALS 1" >> "$file"
fi

if ! grep -q "#define GIT_SSH\b" "$file" ; then
    echo "#define GIT_SSH 1" >> "$file"
fi

# And open Xcode if needed.
if [ -z "$SHOULD_OPEN_XCODE" ]
then
    echo "Run Xcode if you need 'xed $SCRIPT_DIRECTORY/xcode/libgit2.xcodeproj'"
else
    open "./xcode/libgit2.xcodeproj"
fi
