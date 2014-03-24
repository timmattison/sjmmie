package com.timmattison.sjmmie.interceptors.packetdelay;

import java.util.HashSet;
import java.util.Set;

/**
 * Created by timmattison on 3/24/14.
 */
public class BasicSocketDelayer implements SocketDelayer {
    private Set<Integer> socketDescriptorSet = new HashSet<Integer>();

    private int delay = 2500;

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
        System.out.println("Adding socket descriptor " + socketDescriptor);
        socketDescriptorSet.add(socketDescriptor);
    }

    @Override
    public void receivedDataOnSocket(int socketDescriptor) {
        boolean shouldDelay = socketDescriptorSet.contains(socketDescriptor);

        // Do we need to delay?
        if (shouldDelay == true) {
            // Yes, remove the socket descriptor from the set so we know we delayed already
            socketDescriptorSet.remove(socketDescriptor);

            System.out.println("DELAYING...");

            try {
                // Sleep for the specified delay
                Thread.sleep(delay);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
