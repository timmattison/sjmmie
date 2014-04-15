package com.timmattison.sjmmie.interceptors.interfaces;

/**
 * Created by timmattison on 2/20/14.
 */
public interface RecvFromInterceptor {
    /**
     * The recvfrom function call interceptor
     * @param sockfd
     * @param receive_buffer
     * @param len
     * @param flags
     * @param address_data
     * @param addrlen
     * @return
     */
    public int recvfromInterceptor(int sockfd, byte[] receive_buffer, int len, int flags, byte[] address_data, int addrlen);

    public boolean recvFromInterceptorIsEnabled();

    public void recvFromInterceptorSetEnabled(boolean enabled);
}
