package com.timmattison.sjmmie.interceptors.streamdump;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.CloseInterceptor;

import javax.inject.Inject;
import java.io.IOException;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/13/14.
 */
public class StreamDumpCloseInterceptor implements CloseInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;
    private final StreamDumpManager streamDumpManager;

    @Inject
    public StreamDumpCloseInterceptor(Logger logger, SjmmieLibrary sjmmieLibrary, StreamDumpManager streamDumpManager) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
        this.streamDumpManager = streamDumpManager;
    }

    @Override
    public int closeInterceptor(int fildes) {
        logger.info("" + fildes);

        try {
            streamDumpManager.closeStream(fildes);
        } catch (IOException e) {
            e.printStackTrace();
        }

        return sjmmieLibrary.originalClose(fildes);
    }
}
