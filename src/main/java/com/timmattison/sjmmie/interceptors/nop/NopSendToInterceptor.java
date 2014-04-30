package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;

import javax.inject.Inject;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/21/14.
 */
public class NopSendToInterceptor implements SendToInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopSendToInterceptor(Logger logger, SjmmieLibrary sjmmieLibrary) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int sendtoInterceptor(int sockfd, byte[] data_to_send, int len, int flags, byte[] sa_data, int addrlen) {
        logger.info(sockfd + ", " + len + ", " + flags + ", " + addrlen);
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
