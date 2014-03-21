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
        System.out.println("Configuring");
        bind(SjmmieLibrary.class).toInstance(new SjmmieLibrary());

        System.out.println("Configuring 1");
        bind(OpenInterceptor.class).to(BasicOpenInterceptor.class).asEagerSingleton();
        System.out.println("Configuring 2");
        bind(CloseInterceptor.class).to(BasicCloseInterceptor.class).asEagerSingleton();
        System.out.println("Configuring 3");
        bind(ConnectInterceptor.class).to(BasicConnectInterceptor.class).asEagerSingleton();
        System.out.println("Configuring 4");
        bind(SendToInterceptor.class).to(FixedPacketLossSendToInterceptor.class).asEagerSingleton();
        System.out.println("Configuring 5");

        // Use the RESTlet system
        try {
        install(new FactoryModuleBuilder().implement(Application.class, RestletApplication.class).build(RestletApplicationFactory.class));
        } catch (Throwable t) {
            t.printStackTrace();
            System.exit(1);
        }
        System.out.println("Configured 1");
    }
}
