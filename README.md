sjmmie
======

SJMMIE (AKA Sjmmie) is the Simple Java Method Modification and Interception Engine.  It exposes the Mac OS interposition functionality (and eventually Linux's dynamic loader preloading functionality) to the JVM.  To put it simply you can now write Java code that intercepts calls to the operating system and modify their behavior.

=======
WARNING
=======

WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING

Do not check out the tim-work-branch branch.  I do a lot of rebasing and use Github as a backup.  You have been warned!  If you do this things will break, OFTEN, for you!

WARNING WARNING WARNING WARNING WARNING WARNING WARNING WARNING

Why?
----

Intercepting operating system calls lets you do lots of fun and useful things.  The original reason I started going down this road was to try to write an application or library that would let me simulate varying network conditions like packet loss and delay.  An application called "Trickle" was written to do this a long time ago but it hasn't been updated in over 10 years.  So I set out to create something new and better.

How to add a new function
=========================

If you want to intercept/interpose a new function you must follow the pattern below.  We will use C's send function as the example for these steps

Step 1: Get the declaration for the function you want to intercept and add the necessary interposer to sjmmie.c
----------------------------------------------------------------------------------------------------------------

To intercept the send function the signature would be:
```C
ssize_t send(int socket, const void *buffer, size_t length, int flags);
```

Add a Sjmmie version of this above the interposer typedef that is the same as the original function with "SJMMIE_" prepended to its name like this:
```C
ssize_t SJMMIE_send(int socket, const void *buffer, size_t length, int flags);
```

Then add a new interposer where the "SJMMIE_" version is the replacement and the function to intercept is the original like this:
```C
{ .replacement = SJMMIE_send, .original = send },
```

Step 2: Add the externs required for interception into sjmmie.h
---------------------------------------------------------------

There are four required externs for each intercepted function.  They are the name of the interceptor in Java, its arguments in JNI type signature format (http://docs.oracle.com/javase/1.5.0/docs/guide/jni/spec/types.html#wp276), a JNI methodID reference to the interceptor, XXX and another random variable that I don't get XXX.  For send it looks like this:

// For intercepting "send"
extern const char *send_interceptor_name;
extern const char *send_interceptor_arguments;
extern jmethodID java_send_method;
extern jmethodID send_interceptor;

Step 3: Unroll the C parameters if necessary
--------------------------------------------

If the function you want to intercept requires passing types other than primitives you'll need to unroll them and set them up in such a way that they can be passed as types JNI understands.  The original send function contains only primitive types so we'll use the sendto function as an example here instead.  It's signature in C is:

```
ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
```

The type we can't convert immediately to a primitive type is "const struct sockaddr".  Its structure looks like this:

```
struct sockaddr {
    unsigned short sa_family;   // address family, AF_xxx
    char           sa_data[14]; // 14 bytes of protocol address
};
```

These are two types we can handle.  So in this case our Java method takes sa_family and sa_data instead of sockaddr.  However, our interposition function always must have the exact same signature as our original function.

Step 4: Create an interface for your interceptor
------------------------------------------------

This interface defines a method that takes the parameters from the C call.  For send:

```Java
package com.timmattison.sjmmie.interceptors.interfaces;

/**
 * Created by timmattison on 2/20/14.
 */
public interface SendInterceptor {
    /**
     * The send function call interceptor
     * @param socket
     * @param buffer
     * @param length
     * @param flags
     * @return
     */
    public int sendInterceptor(int socket, byte[] buffer, int length, int flags);

    public boolean sendInterceptorIsEnabled();

    public void sendInterceptorSetEnabled(boolean enabled);
```

The sendInterceptorIsEnabled and sendInterceptorSetEnabled lets us selectively enable and disable our interceptor later.  You do not need this to perform simple interception.

Step 5: Create a file in the functions directory that contains the C glue code and add the function to the SjmmieLibrary.java file
----------------------------------------------------------------------------------------------------------------------------------

This file contains your interceptor function (SJMMIE_send for us) and a function that allows the JVM to call back to C to use the original function.  This function is a JNIEXPORTed function that contains all of the parameters needed to call the original function with the parameters unrolled as necessary.

Here is where you also define the XXX four XXX externs from step 2.

Our signature for the JNI function looks like this:

```C
JNIEXPORT int JNICALL Java_com_timmattison_sjmmie_SjmmieLibrary_originalSend(JNIEnv *env, jobject obj, jint socket, jbyteArray buf_java, jint length, jint flags)
```

Our signature for the interceptor looks like this:

```C
ssize_t SJMMIE_send(int socket, const void *buffer, size_t length, int flags)
```

NOTE: You will have to do some work to move byte arrays back and forth between C and Java.  See functions/send.c for an example.

Now add your JNIEXPORTed function as a native method in the SjmmieLibrary class like this:

```Java
public native int originalSend(int socket, byte[] buffer, int length, int flags);
```

Step 6: Populate the jmethodID reference to your interceptor
------------------------------------------------------------

In sjmmie.c for send we did this:

```C
       // send
       java_send_method = (*env)->GetMethodID(env, sjmmie_class, send_interceptor_name, send_interceptor_arguments);
```

Step 7: Add your interceptor to the Sjmmie object's parameter list
------------------------------------------------------------------

Just add the interface as a parameter to the @Inject annotated constructor, create an instance variable that has the same name as the interface but with the first character lowercase, and assign that variable the value that comes in from the interface.  For send it looks like this:

```Java
    @Inject
    public Sjmmie(OpenInterceptor openInterceptor, CloseInterceptor closeInterceptor, ConnectInterceptor connectInterceptor, SendInterceptor sendInterceptor) {
        this.openInterceptor = openInterceptor;
        this.closeInterceptor = closeInterceptor;
        this.connectInterceptor = connectInterceptor;
        this.sendInterceptor = sendInterceptor;
    }
```

NOTE: There may be other interceptors in this constructor and they should be left alone.


Step 8: Have the AbstractSjmmie Java class implement your interceptor's interface
---------------------------------------------------------------------------------

This makes sure there are no name collisions and lets the abstract class check to see if your interceptor is available.  For send we implemented the SendInterceptor interface and added these methods keeping in mind to use the name that we used in step 7:

```Java
    @Override
    public int sendInterceptor(int socket, byte[] buffer, int length, int flags) {
        if (sendInterceptor != null) {
            return sendInterceptor.sendInterceptor(socket, buffer, length, flags);
        } else {
            return sjmmieLibrary.originalSend(socket, buffer, length, flags);
        }
    }

    @Override
    public boolean sendInterceptorIsEnabled() {
        return sendInterceptor.sendInterceptorIsEnabled();
    }

    @Override
    public void sendInterceptorSetEnabled(boolean enabled) {
        sendInterceptor.sendInterceptorSetEnabled(enabled);
    }
```

This code passes through all calls to the sendInterceptor or passes them right back to the original send function if no sendInterceptor exits.  Because the behavior for checking if it is enabled or changing its enabled state is undefined if the object isn't instantiated those methods don't have a NULL check and are expected to crash if called without a valid sendInterceptor object.

Step 9: Create a NOP (No OPeration) implementation of your interceptor
----------------------------------------------------------------------

Create an implementation of your interceptor that does nothing other than print out that it was called.  For send this looks like this:

```Java

package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class NopSendIntereceptor implements SendInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopSendIntereceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int sendInterceptor(int socket, byte[] buffer, int length, int flags) {
        System.out.println("Send: " + socket + ", " + length + ", " + flags);
        return sjmmieLibrary.originalSend(socket, buffer, length, flags);
    }

    @Override
    public boolean sendInterceptorIsEnabled() {
        return true;
    }

    @Override
    public void sendInterceptorSetEnabled(boolean enabled) {
        // Do nothing
    }
}
```

Make sure you put it in the com.timmattison.sjmmie.interceptors.nop package.

Step 10: Wire up your NOP interceptor with Guice
------------------------------------------------

NOTE: We use Guice for dependency injection

Wire up your new NOP interceptor to your interceptor's interface as an eager singleton in SjmmieNopModule.java.  This makes sure you have one global instance across all threads.  For send this looks like this:

```Java
bind(SendInterceptor.class).to(NopSendIntereceptor.class).asEagerSingleton();
```
