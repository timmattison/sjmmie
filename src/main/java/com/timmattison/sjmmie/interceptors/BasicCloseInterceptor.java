package com.timmattison.sjmmie.interceptors;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.CloseInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/13/14.
 */
public class BasicCloseInterceptor implements CloseInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public BasicCloseInterceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int closeInterceptor(int fildes) {
        return sjmmieLibrary.originalClose(fildes);
    }
}
