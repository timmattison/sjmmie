package com.timmattison.sjmmie.interceptors.interfaces;

/**
 * Created by timmattison on 2/20/14.
 */
public interface RecvFromInterceptor {
    /**
     * The recvfrom function call interceptor
     * @param sockfd
     * @param buf_java
     * @param len
     * @param flags
     * @param sa_family
     * @param sa_data_java
     * @param addrlen
     * @return
     */
    public int recvfromInterceptor(int sockfd, byte[] buf_java, int len, int flags, char sa_family, byte[] sa_data_java, int[] addrlen);

    public boolean recvfromInterceptorIsEnabled();

    public void recvfromInterceptorSetEnabled(boolean enabled);
}
