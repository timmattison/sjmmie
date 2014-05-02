package com.timmattison.sjmmie.interceptors.streamdump;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendInterceptor;

import javax.inject.Inject;
import java.io.IOException;
import java.util.Arrays;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/21/14.
 */
public class StreamDumpSendInterceptor implements SendInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;
    private final StreamDumpManager streamDumpManager;

    @Inject
    public StreamDumpSendInterceptor(Logger logger, SjmmieLibrary sjmmieLibrary, StreamDumpManager streamDumpManager) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
        this.streamDumpManager = streamDumpManager;
    }

    @Override
    public int sendInterceptor(int socket, byte[] buffer, int length, int flags) {
        logger.info("SEND: " + socket + ", " + length + ", " + flags);
        int lengthSent = sjmmieLibrary.originalSend(socket, buffer, length, flags);

        if(lengthSent == -1) {
            return lengthSent;
        }

        try {
            streamDumpManager.writeOutputStream(socket, Arrays.copyOf(buffer, lengthSent));
        } catch (IOException e) {
            e.printStackTrace();
        }

        return lengthSent;
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
