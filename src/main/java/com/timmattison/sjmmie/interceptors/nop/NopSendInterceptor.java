package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendInterceptor;

import javax.inject.Inject;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/21/14.
 */
public class NopSendInterceptor implements SendInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopSendInterceptor(Logger logger, SjmmieLibrary sjmmieLibrary) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int sendInterceptor(int socket, byte[] buffer, int length, int flags) {
        logger.info(socket + ", " + length + ", " + flags);
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
