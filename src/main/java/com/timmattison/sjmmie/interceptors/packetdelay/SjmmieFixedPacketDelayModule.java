package com.timmattison.sjmmie.interceptors.packetdelay;

import com.google.inject.AbstractModule;
import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.*;
import com.timmattison.sjmmie.interceptors.nop.*;
import com.timmattison.sjmmie.restlets.BasicRestletApplicationFactory;
import com.timmattison.sjmmie.restlets.RestletApplicationFactory;

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
        bind(RecvFromInterceptor.class).to(DelayRecvFromIntereceptor.class).asEagerSingleton();
        bind(SendInterceptor.class).to(DelaySendIntereceptor.class).asEagerSingleton();
        bind(RecvInterceptor.class).to(DelayRecvIntereceptor.class).asEagerSingleton();

        // Delayer
        bind(SocketDelayer.class).to(BasicSocketDelayer.class).asEagerSingleton();

        // Use the RESTlet system
        bind(RestletApplicationFactory.class).to(BasicRestletApplicationFactory.class).asEagerSingleton();
    }
}
