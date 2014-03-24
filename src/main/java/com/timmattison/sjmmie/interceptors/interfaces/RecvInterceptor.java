package com.timmattison.sjmmie.interceptors.interfaces;

/**
 * Created by timmattison on 2/20/14.
 */
public interface RecvInterceptor {
    /**
     * The recv function call interceptor
     * @param socket
     * @param buffer
     * @param length
     * @param flags
     * @return
     */
    public int recvInterceptor(int socket, byte[] buffer, int length, int flags);

    public boolean recvInterceptorIsEnabled();

    public void recvInterceptorSetEnabled(boolean enabled);
}
