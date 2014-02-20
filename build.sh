#!/usr/bin/env bash

platform='unknown'
unamestr=`uname`
if [[ "$unamestr" == 'Linux' ]]; then
   platform='linux'
elif [[ "$unamestr" == 'Darwin' ]]; then
   platform='macos'
fi

is_macos() {
	[[ "$platform" == "macos" ]] && return $TRUE || return $FALSE
}

is_linux() {
	[[ "$platform" == "linux" ]] && return $TRUE || return $FALSE
}

javah -verbose -jni -classpath target/classes com.timmattison.sjmmie.SjmmieLibrary || exit

if ( is_macos )
then
	gcc -I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include -I. -I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include/darwin -c sjmmie.c -fPIC || exit
	gcc -I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include -I. -I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include/darwin -c functions/open.c -o functions/open.o -fPIC || exit
	gcc -I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include -I. -I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include/darwin -c functions/close.c -o functions/close.o -fPIC || exit
	gcc -dynamiclib -fPIC -ldl -L/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/jre/lib/server -ljvm -o libsjmmie.dylib sjmmie.o functions/open.o functions/close.o
elif ( is_linux )
then
	echo "NOT YET!"
	exit 1
	#gcc -c sjmmie.c -fPIC || exit
	#gcc -shared -fPIC -o libsjmmie.so sjmmie.o
fi
