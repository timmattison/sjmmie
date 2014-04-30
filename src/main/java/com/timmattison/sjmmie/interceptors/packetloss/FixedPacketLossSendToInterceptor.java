package com.timmattison.sjmmie.interceptors.packetloss;

import com.google.inject.assistedinject.Assisted;
import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;

import javax.inject.Inject;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/21/14.
 */
public class FixedPacketLossSendToInterceptor implements SendToInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;
    private final int modulus;
    private int counter = 0;
    private boolean enabled = true;

    @Inject
    public FixedPacketLossSendToInterceptor(Logger logger, @Assisted("Modulus") int modulus, SjmmieLibrary sjmmieLibrary) {
        this.logger = logger;
        this.modulus = modulus;
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int sendtoInterceptor(int sockfd, byte[] data_to_send, int len, int flags, byte[] sa_data, int addrlen) {
        if (sendToInterceptorIsEnabled()) {
            counter++;

            if ((counter % modulus) == 0) {
                logger.info("[" + sockfd + ", " + counter + "] Dropping " + len + " byte(s)");
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
        logger.info("Fixed packet loss is now " + (enabled ? "enabled" : "disabled"));
        this.enabled = enabled;
    }
}
