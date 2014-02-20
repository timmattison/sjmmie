package com.timmattison.sjmmie.interceptors;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.ConnectInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/13/14.
 */
public class BasicConnectInterceptor implements ConnectInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public BasicConnectInterceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int connectInterceptor(int s, char sa_family, byte[] sa_data, int namelen) {
        System.out.println("In Java's connect interceptor");
        return sjmmieLibrary.originalConnect(s, sa_family, sa_data, namelen);
    }
}
