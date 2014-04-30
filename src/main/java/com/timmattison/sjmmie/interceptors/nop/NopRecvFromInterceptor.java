package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.RecvFromInterceptor;

import javax.inject.Inject;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/21/14.
 */
public class NopRecvFromInterceptor implements RecvFromInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopRecvFromInterceptor(Logger logger, SjmmieLibrary sjmmieLibrary) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int recvfromInterceptor(int sockfd, byte[] receive_buffer, int len, int flags, byte[] address_data, int addrlen) {
        logger.info(sockfd + ", " + len + ", " + flags + ", " + addrlen);
        return sjmmieLibrary.originalRecvFrom(sockfd, receive_buffer, len, flags, address_data, addrlen);
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
