package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.CloseInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/13/14.
 */
public class NopCloseInterceptor implements CloseInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopCloseInterceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int closeInterceptor(int fildes) {
        System.out.println("Close: " + fildes);
        return sjmmieLibrary.originalClose(fildes);
    }
}
