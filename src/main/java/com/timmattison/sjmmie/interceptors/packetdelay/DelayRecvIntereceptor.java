package com.timmattison.sjmmie.interceptors.packetdelay;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.RecvInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class DelayRecvIntereceptor implements RecvInterceptor {
    private final SjmmieLibrary sjmmieLibrary;
    private final SocketDelayer socketDelayer;

    @Inject
    public DelayRecvIntereceptor(SjmmieLibrary sjmmieLibrary, SocketDelayer socketDelayer) {
        this.sjmmieLibrary = sjmmieLibrary;
        this.socketDelayer = socketDelayer;
    }

    @Override
    public int recvInterceptor(int socket, byte[] buffer, int length, int flags) {
        System.out.println("Delay Recv: " + socket + ", " + length + ", " + flags);

        if (socketDelayer != null) {
            socketDelayer.receivedDataOnSocket(socket);
        }

        int returnValue = sjmmieLibrary.originalRecv(socket, buffer, length, flags);
        return returnValue;
    }

    @Override
    public boolean recvInterceptorIsEnabled() {
        return true;
    }

    @Override
    public void recvInterceptorSetEnabled(boolean enabled) {
        // Do nothing
    }
}
