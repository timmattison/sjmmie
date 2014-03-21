package com.timmattison.sjmmie.interceptors;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.OpenInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/13/14.
 */
public class BasicOpenInterceptor implements OpenInterceptor {
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public BasicOpenInterceptor(SjmmieLibrary sjmmieLibrary) {
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int openInterceptor(String filename, int flags) {
        return sjmmieLibrary.originalOpen(filename, flags);
    }
}
