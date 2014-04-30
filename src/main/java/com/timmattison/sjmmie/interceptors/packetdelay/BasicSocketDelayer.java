package com.timmattison.sjmmie.interceptors.packetdelay;

import javax.inject.Inject;
import java.util.HashSet;
import java.util.Set;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/24/14.
 */
public class BasicSocketDelayer implements SocketDelayer {
    private final Logger logger;
    private Set<Integer> socketDescriptorSet = new HashSet<Integer>();

    private int delay = 50;

    @Inject
    public BasicSocketDelayer(Logger logger) {
        this.logger = logger;
    }

    @Override
    public int getDelay() {
        return delay;
    }

    @Override
    public void setDelay(int delayInMilliseconds) {
        delay = delayInMilliseconds;
    }

    public void sentDataOnSocket(int socketDescriptor) {
        // Indicate that we want to delay next time
        logger.info("Adding socket descriptor " + socketDescriptor);
        socketDescriptorSet.add(socketDescriptor);
    }

    @Override
    public void receivedDataOnSocket(int socketDescriptor) {
        boolean shouldDelay = socketDescriptorSet.contains(socketDescriptor);

        // Do we need to delay?
        if (shouldDelay == true) {
            // Yes, remove the socket descriptor from the set so we know we delayed already
            socketDescriptorSet.remove(socketDescriptor);

            logger.info("DELAYING...");

            try {
                // Sleep for the specified delay
                Thread.sleep(delay);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
