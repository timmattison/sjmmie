package com.timmattison.sjmmie.interceptors.interfaces;

import com.timmattison.sjmmie.objects.ReferenceSockaddr;

/**
 * Created by timmattison on 2/20/14.
 */
public interface ConnectInterceptor {
    /**
     * The connect function call interceptor
     * @param socketDescriptor
     * @param referenceSockaddr
     * @return
     */
    public int connectInterceptor(int socketDescriptor, ReferenceSockaddr referenceSockaddr);
}
