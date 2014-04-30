package com.timmattison.sjmmie.interceptors.nop;

import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.CloseInterceptor;

import javax.inject.Inject;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/13/14.
 */
public class NopCloseInterceptor implements CloseInterceptor {
    private final Logger logger;
    private final SjmmieLibrary sjmmieLibrary;

    @Inject
    public NopCloseInterceptor(Logger logger, SjmmieLibrary sjmmieLibrary) {
        this.logger = logger;
        this.sjmmieLibrary = sjmmieLibrary;
    }

    @Override
    public int closeInterceptor(int fildes) {
        logger.info("" + fildes);
        return sjmmieLibrary.originalClose(fildes);
    }
}
