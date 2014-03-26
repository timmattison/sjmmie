package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class NopSendInterceptor implements SendInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopSendInterceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int sendInterceptor(int socket, byte[] buffer, int length, int flags) {
        System.out.println("Send: " + socket + ", " + length + ", " + flags);
        return sjmmieLibrary.originalSend(socket, buffer, length, flags);
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
