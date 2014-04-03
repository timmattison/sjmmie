package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.RecvFromInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class NopRecvFromInterceptor implements RecvFromInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopRecvFromInterceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int recvfromInterceptor(int sockfd, byte[] receive_buffer, int len, int flags, char address_family, byte[] address_data, int addrlen) {
        System.out.println("Recvfrom: " + sockfd + ", " + len + ", " + flags + ", " + addrlen);
        return sjmmieLibrary.originalRecvFrom(sockfd, receive_buffer, len, flags, address_family, address_data, addrlen);
    }

    @Override
    public boolean recvFromInterceptorIsEnabled() {
        return true;
    }

    @Override
    public void recvFromInterceptorSetEnabled(boolean enabled) {
        // Do nothing
    }
}
