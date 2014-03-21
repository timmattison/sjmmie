package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SocketInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/13/14.
 */
public class NopSocketInterceptor implements SocketInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopSocketInterceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int socketInterceptor(int domain, int type, int protocol) {
        System.out.println("Socket: " + domain + ", " + type + " " + protocol);
        return sjmmieLibrary.originalSocket(domain, type, protocol);
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
