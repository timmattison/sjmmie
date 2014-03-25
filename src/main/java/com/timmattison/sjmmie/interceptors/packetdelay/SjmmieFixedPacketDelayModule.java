package com.timmattison.sjmmie.interceptors.packetdelay;

import com.google.inject.AbstractModule;
import com.google.inject.assistedinject.FactoryModuleBuilder;
import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.*;
import com.timmattison.sjmmie.interceptors.nop.NopCloseInterceptor;
import com.timmattison.sjmmie.interceptors.nop.NopConnectInterceptor;
import com.timmattison.sjmmie.interceptors.nop.NopOpenInterceptor;
import com.timmattison.sjmmie.interceptors.nop.NopSocketInterceptor;
import com.timmattison.sjmmie.restlets.RestletApplication;
import com.timmattison.sjmmie.restlets.RestletApplicationFactory;
import org.restlet.Application;

/**
 * Created by timmattison on 3/13/14.
 */
public class SjmmieFixedPacketDelayModule extends AbstractModule {
    @Override
    protected void configure() {
        bind(SjmmieLibrary.class).toInstance(new SjmmieLibrary());

        // Normal implementations
        bind(OpenInterceptor.class).to(NopOpenInterceptor.class).asEagerSingleton();
        bind(CloseInterceptor.class).to(NopCloseInterceptor.class).asEagerSingleton();
        bind(ConnectInterceptor.class).to(NopConnectInterceptor.class).asEagerSingleton();
        bind(SocketInterceptor.class).to(NopSocketInterceptor.class).asEagerSingleton();

        // Delay implementations
        bind(SendToInterceptor.class).to(DelaySendToIntereceptor.class).asEagerSingleton();
        bind(SendInterceptor.class).to(DelaySendIntereceptor.class).asEagerSingleton();
        bind(RecvInterceptor.class).to(DelayRecvIntereceptor.class).asEagerSingleton();
        bind(RecvFromInterceptor.class).to(DelayRecvFromIntereceptor.class).asEagerSingleton();

        // Delayer
        bind(SocketDelayer.class).to(BasicSocketDelayer.class).asEagerSingleton();

        // Use the RESTlet system
        install(new FactoryModuleBuilder().implement(Application.class, RestletApplication.class).build(RestletApplicationFactory.class));
    }
}
