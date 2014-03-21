package com.timmattison.sjmmie;

import com.timmattison.sjmmie.interceptors.interfaces.CloseInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.ConnectInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.OpenInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;

/**
 * Created by timmattison on 2/20/14.
 */
public abstract class AbstractSjmmie implements OpenInterceptor, CloseInterceptor, ConnectInterceptor, SendToInterceptor {
    private static SjmmieLibrary sjmmieLibrary = new SjmmieLibrary();

    protected OpenInterceptor openInterceptor;
    protected CloseInterceptor closeInterceptor;
    protected ConnectInterceptor connectInterceptor;
    public SendToInterceptor sendToInterceptor;

    @Override
    public int openInterceptor(String filename, int flags) {
        if (openInterceptor != null) {
            return openInterceptor.openInterceptor(filename, flags);
        } else {
            return sjmmieLibrary.originalOpen(filename, flags);
        }
    }

    @Override
    public int closeInterceptor(int fildes) {
        if (closeInterceptor != null) {
            return closeInterceptor.closeInterceptor(fildes);
        } else {
            return sjmmieLibrary.originalClose(fildes);
        }
    }

    @Override
    public int connectInterceptor(int s, char sa_family, byte[] sa_data, int namelen) {
        if (connectInterceptor != null) {
            return connectInterceptor.connectInterceptor(s, sa_family, sa_data, namelen);
        } else {
            return sjmmieLibrary.originalConnect(s, sa_family, sa_data, namelen);
        }
    }

    @Override
    public int sendtoInterceptor(int sockfd, byte[] data_to_send, int len, int flags, char dest_addr_sa_family, byte[] sa_data, int addrlen) {
        if (sendToInterceptor != null) {
            return sendToInterceptor.sendtoInterceptor(sockfd, data_to_send, len, flags, dest_addr_sa_family, sa_data, addrlen);
        } else {
            return sjmmieLibrary.originalSendTo(sockfd, data_to_send, len, flags, dest_addr_sa_family, sa_data, addrlen);
        }
    }
}
