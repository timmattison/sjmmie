package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.ConnectInterceptor;

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
    public int connectInterceptor(int s, char sa_family, byte[] sa_data, int namelen) {
        System.out.println("Connect: " + s + ", " + namelen);
        return sjmmieLibrary.originalConnect(s, sa_family, sa_data, namelen);
    }
}
