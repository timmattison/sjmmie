package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.ConnectInterceptor;
import com.timmattison.sjmmie.objects.ReferenceSockaddr;

import javax.inject.Inject;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/13/14.
 */
public class NopConnectInterceptor implements ConnectInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopConnectInterceptor(Logger logger, SjmmieLibrary sjmmieLibrary) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int connectInterceptor(int socketDescriptor, ReferenceSockaddr referenceSockaddr) {
        logger.info(socketDescriptor + ", " + referenceSockaddr.sa_data.length + ", " + referenceSockaddr.sa_len);
        return sjmmieLibrary.originalConnect(socketDescriptor, referenceSockaddr);
    }
}
