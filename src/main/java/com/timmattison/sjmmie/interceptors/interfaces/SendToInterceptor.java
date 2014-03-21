package com.timmattison.sjmmie.interceptors.interfaces;

/**
 * Created by timmattison on 2/20/14.
 */
public interface SendToInterceptor {
    /**
     * The connect function call interceptor
     * @param sockfd
     * @param data_to_send
     * @param len
     * @param flags
     * @param dest_addr_sa_family
     * @param sa_data
     * @param addrlen
     * @return
     */
    public int sendtoInterceptor(int sockfd, byte[] data_to_send, int len, int flags, char dest_addr_sa_family, byte[] sa_data, int addrlen);

    public boolean sendToInterceptorIsEnabled();

    public void sendToInterceptorSetEnabled(boolean enabled);
}
