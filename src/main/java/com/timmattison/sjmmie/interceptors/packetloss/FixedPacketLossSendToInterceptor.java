package com.timmattison.sjmmie.interceptors.packetloss;

import com.google.inject.assistedinject.Assisted;
import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class FixedPacketLossSendToInterceptor implements SendToInterceptor {
    private final SjmmieLibrary sjmmieLibrary;
    private final int modulus;
    private int counter = 0;
    private boolean enabled = true;

    @Inject
    public FixedPacketLossSendToInterceptor(@Assisted("Modulus") int modulus, SjmmieLibrary sjmmieLibrary) {
        this.modulus = modulus;
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int sendtoInterceptor(int sockfd, byte[] data_to_send, int len, int flags, byte[] sa_data, int addrlen) {
        if (sendToInterceptorIsEnabled()) {
            counter++;

            if ((counter % modulus) == 0) {
                System.out.println("[" + sockfd + ", " + counter + "] Dropping " + len + " byte(s)");
                return len;
            }
        }

        return sjmmieLibrary.originalSendTo(sockfd, data_to_send, len, flags, sa_data, addrlen);
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
