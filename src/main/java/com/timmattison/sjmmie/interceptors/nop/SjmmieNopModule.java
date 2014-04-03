package com.timmattison.sjmmie.interceptors.nop;

import com.google.inject.AbstractModule;
import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.*;
import com.timmattison.sjmmie.restlets.BasicRestletApplicationFactory;
import com.timmattison.sjmmie.restlets.RestletApplicationFactory;

/**
 * Created by timmattison on 3/13/14.
 */
public class SjmmieNopModule extends AbstractModule {
    @Override
    protected void configure() {
        bind(SjmmieLibrary.class).toInstance(new SjmmieLibrary());

        bind(OpenInterceptor.class).to(NopOpenInterceptor.class).asEagerSingleton();
        bind(CloseInterceptor.class).to(NopCloseInterceptor.class).asEagerSingleton();
        bind(ConnectInterceptor.class).to(NopConnectInterceptor.class).asEagerSingleton();
        bind(SendToInterceptor.class).to(NopSendToInterceptor.class).asEagerSingleton();
        bind(RecvFromInterceptor.class).to(NopRecvFromInterceptor.class).asEagerSingleton();
        bind(SocketInterceptor.class).to(NopSocketInterceptor.class).asEagerSingleton();
        bind(SendInterceptor.class).to(NopSendInterceptor.class).asEagerSingleton();
        bind(RecvInterceptor.class).to(NopRecvInterceptor.class).asEagerSingleton();

        // Use the RESTlet system
        bind(RestletApplicationFactory.class).to(BasicRestletApplicationFactory.class).asEagerSingleton();
    }
}
