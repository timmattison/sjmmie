package com.timmattison.sjmmie.interceptors.packetloss;

import com.google.inject.AbstractModule;
import com.google.inject.assistedinject.FactoryModuleBuilder;
import com.google.inject.name.Names;
import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.*;
import com.timmattison.sjmmie.interceptors.nop.NopCloseInterceptor;
import com.timmattison.sjmmie.interceptors.nop.NopConnectInterceptor;
import com.timmattison.sjmmie.interceptors.nop.NopOpenInterceptor;
import com.timmattison.sjmmie.interceptors.nop.NopSocketInterceptor;
import com.timmattison.sjmmie.interceptors.packetloss.FixedPacketLossSendToInterceptor;
import com.timmattison.sjmmie.restlets.BasicRestletApplicationFactory;
import com.timmattison.sjmmie.restlets.RestletApplication;
import com.timmattison.sjmmie.restlets.RestletApplicationFactory;
import org.restlet.Application;

/**
 * Created by timmattison on 3/13/14.
 */
public class SjmmieFixedPacketLossModule extends AbstractModule {
    private final int modulus;

    public SjmmieFixedPacketLossModule(int modulus) {
        this.modulus = modulus;
    }

    @Override
    protected void configure() {
        bind(SjmmieLibrary.class).toInstance(new SjmmieLibrary());

        bind(OpenInterceptor.class).to(NopOpenInterceptor.class).asEagerSingleton();
        bind(CloseInterceptor.class).to(NopCloseInterceptor.class).asEagerSingleton();
        bind(ConnectInterceptor.class).to(NopConnectInterceptor.class).asEagerSingleton();
        bind(SocketInterceptor.class).to(NopSocketInterceptor.class).asEagerSingleton();

        bindConstant().annotatedWith(Names.named("Modulus")).to(modulus);
        bind(SendToInterceptor.class).to(FixedPacketLossSendToInterceptor.class).asEagerSingleton();

        // Use the RESTlet system
        bind(RestletApplicationFactory.class).to(BasicRestletApplicationFactory.class).asEagerSingleton();
    }
}
