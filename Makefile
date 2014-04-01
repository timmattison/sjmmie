CC=gcc
INCLUDE=-I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include -I. -I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include/darwin
OPTIONS=-dynamiclib -fPIC -ldl -L/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/jre/lib/server -ljvm
DEPS=sjmmie.h

libsjmmie.dylib: sjmmie.c marshalling.c jvm_init.c
	javah -verbose -jni -classpath target/classes com.timmattison.sjmmie.SjmmieLibrary
	$(CC) $(INCLUDE) $(OPTIONS) -o $@ $^ functions/*.c

clean:
	rm -f libsjmmie.dylib
