package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class NopSendToInterceptor implements SendToInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopSendToInterceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int sendtoInterceptor(int sockfd, byte[] data_to_send, int len, int flags, char dest_addr_sa_family, byte[] sa_data, int addrlen) {
        System.out.println("Sendto: " + sockfd + ", " + len + ", " + flags + ", " + addrlen);
        return sjmmieLibrary.originalSendTo(sockfd, data_to_send, len, flags, dest_addr_sa_family, sa_data, addrlen);
    }

    @Override
    public boolean sendToInterceptorIsEnabled() {
        return true;
    }

    @Override
    public void sendToInterceptorSetEnabled(boolean enabled) {
        // Do nothing
    }
}
