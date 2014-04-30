package com.timmattison.sjmmie.interceptors.packetdelay;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.RecvInterceptor;

import javax.inject.Inject;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/21/14.
 */
public class DelayRecvIntereceptor implements RecvInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;
    private final SocketDelayer socketDelayer;

    @Inject
    public DelayRecvIntereceptor(Logger logger, SjmmieLibrary sjmmieLibrary, SocketDelayer socketDelayer) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
        this.socketDelayer = socketDelayer;
    }

    @Override
    public int recvInterceptor(int socket, byte[] buffer, int length, int flags) {
        logger.info(socket + ", " + length + ", " + flags);

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
