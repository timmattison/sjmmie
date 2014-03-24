package com.timmattison.sjmmie.interceptors.packetdelay;

/**
 * Created by timmattison on 3/24/14.
 */
public interface SocketDelayer {
    int getDelay();
    void setDelay(int delayInMilliseconds);
    void sentDataOnSocket(int socketDescriptor);
    void receivedDataOnSocket(int socketDescriptor);
}
