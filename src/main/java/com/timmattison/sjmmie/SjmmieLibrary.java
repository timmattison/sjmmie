package com.timmattison.sjmmie;

import com.timmattison.sjmmie.objects.ReferenceSockaddr;

/**
 * Created by timmattison on 2/20/14.
 */
public class SjmmieLibrary {
    static {
        System.loadLibrary("sjmmie");
    }

    public native int originalOpen(byte[] filename, int flags);

    public native int originalClose(int fildes);

    public native int originalConnect(int s, ReferenceSockaddr referenceSockaddr);

    public native int originalSendTo(int sockfd, byte[] data_to_send, int len, int flags, byte[] sa_data, int addrlen);

    public native int originalRecvFrom(int sockfd, byte[] receive_buffer, int len, int flags, byte[] address_data, int addrlen);

    public native int originalSocket(int domain, int type, int protocol);

    public native int originalSend(int socket, byte[] buffer, int length, int flags);

    public native int originalRecv(int socket, byte[] buffer, int size, int flags);
}
