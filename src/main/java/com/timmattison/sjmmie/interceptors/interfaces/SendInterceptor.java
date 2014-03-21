package com.timmattison.sjmmie.interceptors.interfaces;

/**
 * Created by timmattison on 2/20/14.
 */
public interface SendInterceptor {
    /**
     * The send function call interceptor
     * @param socket
     * @param buffer
     * @param length
     * @param flags
     * @return
     */
    public int sendInterceptor(int socket, byte[] buffer, int length, int flags);

    public boolean sendInterceptorIsEnabled();

    public void sendInterceptorSetEnabled(boolean enabled);
}
