package com.timmattison.sjmmie.interceptors.interfaces;

/**
 * Created by timmattison on 2/20/14.
 */
public interface ConnectInterceptor {
    /**
     * The connect function call interceptor
     * @param s
     * @param sa_family
     * @param sa_data
     * @param namelen
     * @return
     */
    public int connectInterceptor(int s, char sa_family, byte[] sa_data, int namelen);
}
