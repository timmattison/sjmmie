package com.timmattison.sjmmie.interceptors.interfaces;

/**
 * Created by timmattison on 2/20/14.
 */
public interface SocketInterceptor {
    /**
     * The socket function call interceptor
     * @param domain
     * @param type
     * @param protocol
     * @return
     */
    public int socketInterceptor(int domain, int type, int protocol);

    public boolean socketInterceptorIsEnabled();

    public void socketInterceptorSetEnabled(boolean enabled);
}
