#!/bin/sh

export MACOSX_DEPLOYMENT_TARGET=10.10  # Must match GitUp

rm -rf "xcode"
mkdir "xcode"
cd "xcode"
cmake -G "Xcode" ..
open "libgit2.xcodeproj"
