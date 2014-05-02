package com.timmattison.sjmmie.interceptors.streamdump;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.enums.SocketAddressFamilies;
import com.timmattison.sjmmie.enums.SocketProtocols;
import com.timmattison.sjmmie.enums.SocketTypes;
import com.timmattison.sjmmie.interceptors.interfaces.SocketInterceptor;

import javax.inject.Inject;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/13/14.
 */
public class StreamDumpSocketInterceptor implements SocketInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public StreamDumpSocketInterceptor(Logger logger, SjmmieLibrary sjmmieLibrary) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int socketInterceptor(int domain, int type, int protocol) {
        int socketDescriptor = sjmmieLibrary.originalSocket(domain, type, protocol);
        logger.info("Socket: Descriptor -> " + socketDescriptor + ", Domain -> " + SocketAddressFamilies.findByValue(domain) + "[" + domain + "], type -> " + SocketTypes.findByValue(type) + "[" + type + "], protocol -> " + SocketProtocols.findByValue(protocol) + "[" + protocol + "]");

        return socketDescriptor;
    }

    @Override
    public boolean socketInterceptorIsEnabled() {
        return true;
    }

    @Override
    public void socketInterceptorSetEnabled(boolean enabled) {
        // Do nothing
    }
}