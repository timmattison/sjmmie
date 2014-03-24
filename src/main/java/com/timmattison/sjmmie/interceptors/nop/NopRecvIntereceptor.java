package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.RecvInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class NopRecvIntereceptor implements RecvInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopRecvIntereceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int recvInterceptor(int socket, byte[] buffer, int length, int flags) {
        System.out.println("Recv: " + socket + ", " + length + ", " + flags);
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
