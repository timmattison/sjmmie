package com.timmattison.sjmmie.interceptors.packetdelay;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.RecvFromInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.RecvInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class DelayRecvFromIntereceptor implements RecvFromInterceptor {
    private final SjmmieLibrary sjmmieLibrary;
    private final SocketDelayer socketDelayer;

    @Inject
    public DelayRecvFromIntereceptor(SjmmieLibrary sjmmieLibrary, SocketDelayer socketDelayer) {
        this.sjmmieLibrary = sjmmieLibrary;
        this.socketDelayer = socketDelayer;
    }

    @Override
    public int recvfromInterceptor(int sockfd, byte[] buf_java, int len, int flags, char sa_family, byte[] sa_data_java, int[] addrlen) {
        System.out.println("Delay RecvFrom: " + sockfd + ", " + len + ", " + flags);

        if (socketDelayer != null) {
            socketDelayer.receivedDataOnSocket(sockfd);
        }

        int returnValue = sjmmieLibrary.originalRecvFrom(sockfd, buf_java, len, flags, sa_family, sa_data_java, addrlen);
        return returnValue;
    }

    @Override
    public boolean recvfromInterceptorIsEnabled() {
        return false;
    }

    @Override
    public void recvfromInterceptorSetEnabled(boolean enabled) {

    }
}
