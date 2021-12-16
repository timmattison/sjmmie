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

javah -verbose -jni -classpath src/main/java com.timmattison.sjmmie.SjmmieLibrary || exit

if ( is_macos )
then
  JAVA_HOME=$(java -XshowSettings:properties -version 2>&1 > /dev/null | grep 'java.home' | awk '{print $3}')
	gcc -I$JAVA_HOME/include -I. -I$JAVA_HOME/include/darwin -c sjmmie.c -fPIC || exit
	gcc -I$JAVA_HOME/include -I. -I$JAVA_HOME/include/darwin -c functions/open.c -o functions/open.o -fPIC || exit
	gcc -I$JAVA_HOME/include -I. -I$JAVA_HOME/include/darwin -c functions/close.c -o functions/close.o -fPIC || exit
	gcc -dynamiclib -fPIC -ldl -L$JAVA_HOME/lib/server -ljvm -o libsjmmie.dylib sjmmie.o functions/open.o functions/close.o
elif ( is_linux )
then
	echo "NOT YET!"
	exit 1
	#gcc -c sjmmie.c -fPIC || exit
	#gcc -shared -fPIC -o libsjmmie.so sjmmie.o
fi
