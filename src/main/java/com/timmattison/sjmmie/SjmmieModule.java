package com.timmattison.sjmmie;

import com.google.inject.AbstractModule;
import com.google.inject.assistedinject.FactoryModuleBuilder;
import com.timmattison.sjmmie.interceptors.interfaces.*;
import com.timmattison.sjmmie.interceptors.nop.*;
import com.timmattison.sjmmie.restlets.RestletApplication;
import com.timmattison.sjmmie.restlets.RestletApplicationFactory;
import org.restlet.Application;

/**
 * Created by timmattison on 3/13/14.
 */
public class SjmmieModule extends AbstractModule {
    @Override
    protected void configure() {
        bind(SjmmieLibrary.class).toInstance(new SjmmieLibrary());

        bind(OpenInterceptor.class).to(NopOpenInterceptor.class).asEagerSingleton();
        bind(CloseInterceptor.class).to(NopCloseInterceptor.class).asEagerSingleton();
        bind(ConnectInterceptor.class).to(NopConnectInterceptor.class).asEagerSingleton();
        bind(SendToInterceptor.class).to(NopSendToIntereceptor.class).asEagerSingleton();
        bind(SocketInterceptor.class).to(NopSocketInterceptor.class).asEagerSingleton();

        // Use the RESTlet system
        install(new FactoryModuleBuilder().implement(Application.class, RestletApplication.class).build(RestletApplicationFactory.class));
    }
}
