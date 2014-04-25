package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.OpenInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/13/14.
 */
public class NopOpenInterceptor implements OpenInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopOpenInterceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int openInterceptor(byte[] filename, int flags) {
        System.out.println("Open: " + new String(filename) + ", " + flags);
        return sjmmieLibrary.originalOpen(filename, flags);
    }
}
