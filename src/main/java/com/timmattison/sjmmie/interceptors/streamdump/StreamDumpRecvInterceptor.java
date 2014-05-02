package com.timmattison.sjmmie.interceptors.streamdump;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.RecvInterceptor;

import javax.inject.Inject;
import java.io.IOException;
import java.util.Arrays;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/21/14.
 */
public class StreamDumpRecvInterceptor implements RecvInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;
    private final StreamDumpManager streamDumpManager;

    @Inject
    public StreamDumpRecvInterceptor(Logger logger, SjmmieLibrary sjmmieLibrary, StreamDumpManager streamDumpManager) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
        this.streamDumpManager = streamDumpManager;
    }

    @Override
    public int recvInterceptor(int socket, byte[] buffer, int length, int flags) {
        logger.info("RECV: " + socket + ", " + length + ", " + flags);
        int lengthReceived = sjmmieLibrary.originalRecv(socket, buffer, length, flags);

        if (lengthReceived == -1) {
            return lengthReceived;
        }

        try {
            streamDumpManager.writeInputStream(socket, Arrays.copyOf(buffer, lengthReceived));
        } catch (IOException e) {
            e.printStackTrace();
        }

        return length;
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
