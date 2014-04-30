package com.timmattison.sjmmie.interceptors.packetdelay;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.RecvFromInterceptor;

import javax.inject.Inject;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/21/14.
 */
public class DelayRecvFromIntereceptor implements RecvFromInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;
    private final SocketDelayer socketDelayer;

    @Inject
    public DelayRecvFromIntereceptor(Logger logger, SjmmieLibrary sjmmieLibrary, SocketDelayer socketDelayer) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
        this.socketDelayer = socketDelayer;
    }

    @Override
    public int recvfromInterceptor(int sockfd, byte[] receive_buffer, int len, int flags, byte[] address_data, int addrlen) {
        logger.info(sockfd + ", " + len + ", " + flags + ", " + addrlen);

        if (socketDelayer != null) {
            socketDelayer.sentDataOnSocket(sockfd);
        }

        return sjmmieLibrary.originalSendTo(sockfd, receive_buffer, len, flags, address_data, addrlen);
    }

    @Override
    public boolean recvFromInterceptorIsEnabled() {
        return true;
    }

    @Override
    public void recvFromInterceptorSetEnabled(boolean enabled) {
        // Do nothing
    }
}
