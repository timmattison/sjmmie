package com.timmattison.sjmmie.interceptors.packetdelay;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendInterceptor;

import javax.inject.Inject;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/21/14.
 */
public class DelaySendIntereceptor implements SendInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;
    private final SocketDelayer socketDelayer;

    @Inject
    public DelaySendIntereceptor(Logger logger, SjmmieLibrary sjmmieLibrary, SocketDelayer socketDelayer) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
        this.socketDelayer = socketDelayer;
    }

    @Override
    public int sendInterceptor(int socket, byte[] buffer, int length, int flags) {
        logger.info("Delay Send: " + socket + ", " + length + ", " + flags);

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
