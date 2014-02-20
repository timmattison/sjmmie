package com.timmattison.sjmmie;

import com.google.inject.Guice;
import com.google.inject.Injector;
import com.timmattison.sjmmie.interceptors.interfaces.CloseInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.ConnectInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.OpenInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 2/20/14.
 */
public class Sjmmie extends AbstractSjmmie {
    private static Sjmmie INSTANCE = null;

    public static Sjmmie getInstance() {
        if (INSTANCE == null) {
            Injector injector = Guice.createInjector(new SjmmieModule());

            // Get an instance of the Sjmmie object
            INSTANCE = injector.getInstance(Sjmmie.class);
        }

        return INSTANCE;
    }

    @Inject
    public Sjmmie(OpenInterceptor openInterceptor, CloseInterceptor closeInterceptor, ConnectInterceptor connectInterceptor) {
        this.openInterceptor = openInterceptor;
        this.closeInterceptor = closeInterceptor;
        this.connectInterceptor = connectInterceptor;
    }
}
