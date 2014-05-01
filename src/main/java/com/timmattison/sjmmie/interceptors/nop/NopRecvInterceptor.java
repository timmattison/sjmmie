package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.RecvInterceptor;

import javax.inject.Inject;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/21/14.
 */
public class NopRecvInterceptor implements RecvInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopRecvInterceptor(Logger logger, SjmmieLibrary sjmmieLibrary) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int recvInterceptor(int socket, byte[] buffer, int length, int flags) {
        logger.info(socket + ", " + length + ", " + flags);
        int returnValue = sjmmieLibrary.originalRecv(socket, buffer, length, flags);
        logger.info("RECV[" + length + "]: " + new String(buffer));
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
