#!/usr/bin/env bash

platform='unknown'
unamestr=`uname`
if [[ "$unamestr" == 'Linux' ]]; then
   platform='linux'
elif [[ "$unamestr" == 'FreeBSD' ]]; then
   platform='freebsd'
elif [[ "$unamestr" == 'Darwin' ]]; then
   platform='macos'
fi

is_macos() {
	[[ "$platform" == "macos" ]] && return $TRUE || return $FALSE
}

is_linux() {
	[[ "$platform" == "linux" ]] && return $TRUE || return $FALSE
}

if [[ -z "$SJMMIE_JVM_OPTS" ]]; then SJMMIE_JVM_OPTS="-Djava.class.path=out/artifacts/sjmmie_jar/sjmmie.jar"; fi
if [[ -z "$SJMMIE_CLASS" ]];    then SJMMIE_CLASS="com/timmattison/sjmmie/Sjmmie"; fi

if [[ -z "$PROGRAM_TO_SJMMIE" ]]; then
	echo "You must populate the PROGRAM_TO_SJMMIE variable with the program you want to use Sjmmie on"
	exit 1
fi

if ( is_macos )
then
	DYLD_INSERT_LIBRARIES=libsjmmie.dylib \
	LD_LIBRARY_PATH=/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/jre/lib/server \
	SJMMIE_JVM_OPTS=$SJMMIE_JVM_OPTS \
	SJMMIE_CLASS=$SJMMIE_CLASS \
		$PROGRAM_TO_SJMMIE
elif ( is_linux )
then
	echo "Not yet"
fi


