package com.timmattison.sjmmie.interceptors.packetdelay;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class DelaySendToIntereceptor implements SendToInterceptor {
    private final SjmmieLibrary sjmmieLibrary;
    private final SocketDelayer socketDelayer;

    @Inject
    public DelaySendToIntereceptor(SjmmieLibrary sjmmieLibrary, SocketDelayer socketDelayer) {
        this.sjmmieLibrary = sjmmieLibrary;
        this.socketDelayer = socketDelayer;
    }

    @Override
    public int sendtoInterceptor(int sockfd, byte[] data_to_send, int len, int flags, byte[] sa_data, int addrlen) {
        System.out.println("Delay Sendto: " + sockfd + ", " + len + ", " + flags + ", " + sa_data.length + ", " + addrlen);

        if (socketDelayer != null) {
            socketDelayer.sentDataOnSocket(sockfd);
        }

        return sjmmieLibrary.originalSendTo(sockfd, data_to_send, len, flags, sa_data, addrlen);
    }

    @Override
    public boolean sendToInterceptorIsEnabled() {
        return true;
    }

    @Override
    public void sendToInterceptorSetEnabled(boolean enabled) {
        // Do nothing
    }
}
