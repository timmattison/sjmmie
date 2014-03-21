package com.timmattison.sjmmie.interceptors;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class FixedPacketLossSendToInterceptor implements SendToInterceptor {
    private final SjmmieLibrary sjmmieLibrary;
    private int counter = 0;
    private boolean enabled = true;

    @Inject
    public FixedPacketLossSendToInterceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int sendtoInterceptor(int sockfd, byte[] data_to_send, int len, int flags, char dest_addr_sa_family, byte[] sa_data, int addrlen) {
        if (sendToInterceptorIsEnabled()) {
            counter++;

            if ((counter % 1000) == 0) {
                System.out.println("[" + counter + "] Dropping " + len + " byte(s)");
                return len;
            }
        }

        return sjmmieLibrary.originalSendTo(sockfd, data_to_send, len, flags, dest_addr_sa_family, sa_data, addrlen);
    }

    @Override
    public boolean sendToInterceptorIsEnabled() {
        return enabled;
    }

    @Override
    public void sendToInterceptorSetEnabled(boolean enabled) {
        System.out.println("Fixed packet loss is now " + (enabled ? "enabled" : "disabled"));
        this.enabled = enabled;
    }
}
