package com.timmattison.sjmmie.interceptors.streamdump;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.ConnectInterceptor;
import com.timmattison.sjmmie.objects.ReferenceSockaddr;

import javax.inject.Inject;
import java.io.FileNotFoundException;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/13/14.
 */
public class StreamDumpConnectInterceptor implements ConnectInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;
    private final StreamDumpManager streamDumpManager;
    private final SockAddrTranslator sockAddrTranslator;

    @Inject
    public StreamDumpConnectInterceptor(Logger logger, SjmmieLibrary sjmmieLibrary, StreamDumpManager streamDumpManager, SockAddrTranslator sockAddrTranslator) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
        this.streamDumpManager = streamDumpManager;
        this.sockAddrTranslator = sockAddrTranslator;
    }

    @Override
    public int connectInterceptor(int socketDescriptor, ReferenceSockaddr referenceSockaddr) {
        logger.info(socketDescriptor + ", " + referenceSockaddr.sa_data.length + ", " + referenceSockaddr.sa_len);
        int result = sjmmieLibrary.originalConnect(socketDescriptor, referenceSockaddr);

        if(result != 0) {
            return result;
        }

        try {
            streamDumpManager.openStream(socketDescriptor, sockAddrTranslator.translateSockAddr(referenceSockaddr));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }

        return result;
    }
}
