package com.timmattison.sjmmie.interceptors.streamdump;

import com.google.inject.AbstractModule;
import com.timmattison.sjmmie.SjmmieLibrary;
import com.timmattison.sjmmie.interceptors.interfaces.*;
import com.timmattison.sjmmie.interceptors.nop.NopOpenInterceptor;
import com.timmattison.sjmmie.interceptors.nop.NopRecvFromInterceptor;
import com.timmattison.sjmmie.interceptors.nop.NopSendToInterceptor;
import com.timmattison.sjmmie.restlets.BasicRestletApplicationFactory;
import com.timmattison.sjmmie.restlets.RestletApplicationFactory;

import java.util.logging.ConsoleHandler;
import java.util.logging.Level;
import java.util.logging.LogManager;
import java.util.logging.Logger;

/**
 * Created by timmattison on 3/13/14.
 */
public class SjmmieStreamDumpModule extends AbstractModule {
    @Override
    protected void configure() {
        // Set up the logger
        LogManager logManager = LogManager.getLogManager();
        Logger rootLogger = logManager.getLogger("");
        rootLogger.setLevel(Level.ALL);
        rootLogger.addHandler(new ConsoleHandler());

        bind(SjmmieLibrary.class).toInstance(new SjmmieLibrary());

        bind(OpenInterceptor.class).to(NopOpenInterceptor.class).asEagerSingleton();
        bind(CloseInterceptor.class).to(StreamDumpCloseInterceptor.class).asEagerSingleton();
        bind(ConnectInterceptor.class).to(StreamDumpConnectInterceptor.class).asEagerSingleton();
        bind(SendToInterceptor.class).to(NopSendToInterceptor.class).asEagerSingleton();
        bind(RecvFromInterceptor.class).to(NopRecvFromInterceptor.class).asEagerSingleton();
        bind(SocketInterceptor.class).to(StreamDumpSocketInterceptor.class).asEagerSingleton();
        bind(SendInterceptor.class).to(StreamDumpSendInterceptor.class).asEagerSingleton();
        bind(RecvInterceptor.class).to(StreamDumpRecvInterceptor.class).asEagerSingleton();

        bind(SockAddrTranslator.class).to(BasicSockAddrTranslator.class);
        bind(StreamDumpManager.class).to(BasicStreamDumpManager.class).asEagerSingleton();

        // Use the RESTlet system
        bind(RestletApplicationFactory.class).to(BasicRestletApplicationFactory.class).asEagerSingleton();
    }
}