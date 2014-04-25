package com.timmattison.sjmmie;

import com.timmattison.sjmmie.interceptors.interfaces.*;
import com.timmattison.sjmmie.objects.ReferenceSockaddr;

/**
 * Created by timmattison on 2/20/14.
 */
public abstract class AbstractSjmmie implements OpenInterceptor, CloseInterceptor, ConnectInterceptor, SendToInterceptor, RecvFromInterceptor, SocketInterceptor, SendInterceptor, RecvInterceptor {
    private static SjmmieLibrary sjmmieLibrary = new SjmmieLibrary();

    protected OpenInterceptor openInterceptor;
    protected CloseInterceptor closeInterceptor;
    protected ConnectInterceptor connectInterceptor;
    protected SendToInterceptor sendToInterceptor;
    protected RecvFromInterceptor recvFromInterceptor;
    protected SocketInterceptor socketInterceptor;
    protected SendInterceptor sendInterceptor;
    protected RecvInterceptor recvInterceptor;

    @Override
    public int openInterceptor(byte[] filename, int flags) {
        if (openInterceptor != null) {
            return openInterceptor.openInterceptor(filename, flags);
        } else {
            return sjmmieLibrary.originalOpen(filename, flags);
        }
    }

    @Override
    public int closeInterceptor(int fildes) {
        if (closeInterceptor != null) {
            return closeInterceptor.closeInterceptor(fildes);
        } else {
            return sjmmieLibrary.originalClose(fildes);
        }
    }

    @Override
    public int connectInterceptor(int s, ReferenceSockaddr referenceSockaddr) {
        if (connectInterceptor != null) {
            return connectInterceptor.connectInterceptor(s, referenceSockaddr);
        } else {
            return sjmmieLibrary.originalConnect(s, referenceSockaddr);
        }
    }

    @Override
    public int sendtoInterceptor(int sockfd, byte[] data_to_send, int len, int flags, byte[] sa_data, int addrlen) {
        if (sendToInterceptor != null) {
            return sendToInterceptor.sendtoInterceptor(sockfd, data_to_send, len, flags, sa_data, addrlen);
        } else {
            return sjmmieLibrary.originalSendTo(sockfd, data_to_send, len, flags, sa_data, addrlen);
        }
    }

    @Override
    public boolean sendToInterceptorIsEnabled() {
        return sendToInterceptor.sendToInterceptorIsEnabled();
    }

    @Override
    public void sendToInterceptorSetEnabled(boolean enabled) {
        sendToInterceptor.sendToInterceptorSetEnabled(enabled);
    }

    @Override
    public int socketInterceptor(int domain, int type, int protocol) {
        if (socketInterceptor != null) {
            return socketInterceptor.socketInterceptor(domain, type, protocol);
        } else {
            return sjmmieLibrary.originalSocket(domain, type, protocol);
        }
    }

    @Override
    public boolean socketInterceptorIsEnabled() {
        return socketInterceptor.socketInterceptorIsEnabled();
    }

    @Override
    public void socketInterceptorSetEnabled(boolean enabled) {
        socketInterceptor.socketInterceptorSetEnabled(enabled);
    }

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

    @Override
    public int recvInterceptor(int socket, byte[] buffer, int length, int flags) {
        if (recvInterceptor != null) {
            return recvInterceptor.recvInterceptor(socket, buffer, length, flags);
        } else {
            return sjmmieLibrary.originalRecv(socket, buffer, length, flags);
        }
    }

    @Override
    public boolean recvInterceptorIsEnabled() {
        return recvInterceptor.recvInterceptorIsEnabled();
    }

    @Override
    public void recvInterceptorSetEnabled(boolean enabled) {
        recvInterceptor.recvInterceptorSetEnabled(enabled);
    }

    @Override
    public int recvfromInterceptor(int sockfd, byte[] receive_buffer, int len, int flags, byte[] address_data, int addrlen) {
        if (recvFromInterceptor != null) {
            return recvFromInterceptor.recvfromInterceptor(sockfd, receive_buffer, len, flags, address_data, addrlen);
        } else {
            return sjmmieLibrary.originalRecvFrom(sockfd, receive_buffer, len, flags, address_data, addrlen);
        }
    }

    @Override
    public boolean recvFromInterceptorIsEnabled() {
        return recvFromInterceptor.recvFromInterceptorIsEnabled();
    }

    @Override
    public void recvFromInterceptorSetEnabled(boolean enabled) {
        recvFromInterceptor.recvFromInterceptorSetEnabled(enabled);
    }
}
