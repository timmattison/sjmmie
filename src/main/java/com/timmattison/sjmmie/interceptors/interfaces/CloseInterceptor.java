package com.timmattison.sjmmie.interceptors.interfaces;

/**
 * Created by timmattison on 2/20/14.
 */
public interface CloseInterceptor {
    /**
     * The close function call interceptor
     * @param fildes
     * @return
     */
    public int closeInterceptor(int fildes);
}
