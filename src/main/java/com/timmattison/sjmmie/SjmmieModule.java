package com.timmattison.sjmmie;

import com.google.inject.AbstractModule;
import com.timmattison.sjmmie.interceptors.*;
import com.timmattison.sjmmie.interceptors.interfaces.CloseInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.ConnectInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.OpenInterceptor;

/**
 * Created by timmattison on 3/13/14.
 */
public class SjmmieModule extends AbstractModule {
    @Override
    protected void configure() {
        bind(SjmmieLibrary.class).toInstance(new SjmmieLibrary());

        bind(OpenInterceptor.class).to(BasicOpenInterceptor.class).asEagerSingleton();
        bind(CloseInterceptor.class).to(BasicCloseInterceptor.class).asEagerSingleton();
        bind(ConnectInterceptor.class).to(BasicConnectInterceptor.class).asEagerSingleton();
    }
}
