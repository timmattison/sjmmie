package com.timmattison.sjmmie;

import com.google.inject.AbstractModule;
import com.google.inject.assistedinject.FactoryModuleBuilder;
import com.timmattison.sjmmie.interceptors.BasicCloseInterceptor;
import com.timmattison.sjmmie.interceptors.BasicConnectInterceptor;
import com.timmattison.sjmmie.interceptors.BasicOpenInterceptor;
import com.timmattison.sjmmie.interceptors.FixedPacketLossSendToInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.CloseInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.ConnectInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.OpenInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;
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

        bind(OpenInterceptor.class).to(BasicOpenInterceptor.class).asEagerSingleton();
        bind(CloseInterceptor.class).to(BasicCloseInterceptor.class).asEagerSingleton();
        bind(ConnectInterceptor.class).to(BasicConnectInterceptor.class).asEagerSingleton();
        bind(SendToInterceptor.class).to(FixedPacketLossSendToInterceptor.class).asEagerSingleton();

        // Use the RESTlet system
        install(new FactoryModuleBuilder().implement(Application.class, RestletApplication.class).build(RestletApplicationFactory.class));
    }
}
