package com.timmattison.sjmmie.interceptors.packetdelay;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class DelaySendIntereceptor implements SendInterceptor {
    private final SjmmieLibrary sjmmieLibrary;
    private final SocketDelayer socketDelayer;

    @Inject
    public DelaySendIntereceptor(SjmmieLibrary sjmmieLibrary, SocketDelayer socketDelayer) {
        this.sjmmieLibrary = sjmmieLibrary;
        this.socketDelayer = socketDelayer;
    }

    @Override
    public int sendInterceptor(int socket, byte[] buffer, int length, int flags) {
        System.out.println("Delay Send: " + socket + ", " + length + ", " + flags);

        if (socketDelayer != null) {
            socketDelayer.sentDataOnSocket(socket);
        }

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
