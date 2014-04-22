CC=gcc
INCLUDE=-I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include -I. -I/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/include/darwin
OPTIONS=-dynamiclib -fPIC -ldl -L/Library/Java/JavaVirtualMachines/jdk1.7.0_45.jdk/Contents/Home/jre/lib/server -ljvm

libsjmmie.dylib: sjmmie.c functions/*.[ch] objects/*.[ch]
	javah -verbose -jni -classpath target/classes com.timmattison.sjmmie.SjmmieLibrary
	$(CC) $(INCLUDE) $(OPTIONS) -o $@ sjmmie.c functions/*.c objects/*.c

clean:
	rm -f libsjmmie.dylib
