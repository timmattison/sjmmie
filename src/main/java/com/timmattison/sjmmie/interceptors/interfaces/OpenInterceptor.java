package com.timmattison.sjmmie.interceptors.interfaces;

/**
 * Created by timmattison on 2/20/14.
 */
public interface OpenInterceptor {
    /**
     * The open function call interceptor
     * @param filename
     * @param flags
     * @return
     */
    public int openInterceptor(String filename, int flags);
}
