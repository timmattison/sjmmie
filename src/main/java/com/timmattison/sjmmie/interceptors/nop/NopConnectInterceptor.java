package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.ConnectInterceptor;
import com.timmattison.sjmmie.objects.ReferenceSockaddr;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/13/14.
 */
public class NopConnectInterceptor implements ConnectInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopConnectInterceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int connectInterceptor(int s, ReferenceSockaddr referenceSockaddr) {
        System.out.println("Connect: " + s + ", " + referenceSockaddr.sa_data.length + ", " + referenceSockaddr.sa_len);
        return sjmmieLibrary.originalConnect(s, referenceSockaddr);
    }
}
