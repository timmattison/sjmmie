package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.RecvFromInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.RecvInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class NopRecvFromIntereceptor implements RecvFromInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopRecvFromIntereceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int recvfromInterceptor(int sockfd, byte[] buf_java, int len, int flags, char sa_family, byte[] sa_data_java, int[] addrlen) {
        System.out.println("RecvFrom: " + sockfd + ", " + len + ", " + flags);
        return sjmmieLibrary.originalRecvFrom(sockfd, buf_java, len, flags, sa_family, sa_data_java, addrlen);
    }

    @Override
    public boolean recvfromInterceptorIsEnabled() {
        return true;
    }

    @Override
    public void recvfromInterceptorSetEnabled(boolean enabled) {
        // Do nothing
    }
}
