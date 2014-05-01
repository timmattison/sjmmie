package com.timmattison.sjmmie;

import com.google.inject.Guice;
import com.google.inject.Injector;
import com.timmattison.sjmmie.controls.SendToInterceptorToggle;
import com.timmattison.sjmmie.controls.Toggle;
import com.timmattison.sjmmie.interceptors.interfaces.*;
import com.timmattison.sjmmie.interceptors.streamdump.SjmmieStreamDumpModule;
import com.timmattison.sjmmie.restlets.RestletApplicationFactory;
import org.restlet.Component;
import org.restlet.data.Protocol;

import javax.inject.Inject;
import java.util.ArrayList;
import java.util.List;
import java.util.logging.ConsoleHandler;
import java.util.logging.Level;
import java.util.logging.LogManager;
import java.util.logging.Logger;

/**
 * Created by timmattison on 2/20/14.
 */
public class Sjmmie extends AbstractSjmmie {
    private final Logger logger;
    private static Sjmmie INSTANCE = null;
    private static final int listeningPort = 64000;
    private final RestletApplicationFactory restletApplicationFactory;
    private final SendToInterceptorToggle sendToInterceptorToggle;
    private static boolean restletsStarted = false;

    public static Sjmmie getInstance() {
        synchronized (Sjmmie.class) {
            if (INSTANCE == null) {
                LogManager logManager = LogManager.getLogManager();
                Logger rootLogger = logManager.getLogger("");
                rootLogger.setLevel(Level.ALL);
                rootLogger.addHandler(new ConsoleHandler());

                Injector injector = Guice.createInjector(new SjmmieStreamDumpModule());

                // Get an instance of the Sjmmie object
                INSTANCE = injector.getInstance(Sjmmie.class);
            }

            return INSTANCE;
        }
    }

    @Inject
    public Sjmmie(RestletApplicationFactory restletApplicationFactory, OpenInterceptor openInterceptor, CloseInterceptor closeInterceptor, ConnectInterceptor connectInterceptor, SendToInterceptor sendToInterceptor, SendToInterceptorToggle sendToInterceptorToggle, RecvFromInterceptor recvFromInterceptor, SocketInterceptor socketInterceptor, SendInterceptor sendInterceptor, Logger logger, RecvInterceptor recvInterceptor) {
        this.logger = logger;
        this.restletApplicationFactory = restletApplicationFactory;
        this.openInterceptor = openInterceptor;
        this.closeInterceptor = closeInterceptor;
        this.connectInterceptor = connectInterceptor;
        this.sendToInterceptor = sendToInterceptor;
        this.sendToInterceptorToggle = sendToInterceptorToggle;
        this.recvFromInterceptor = recvFromInterceptor;
        this.socketInterceptor = socketInterceptor;
        this.sendInterceptor = sendInterceptor;
        this.sendInterceptor = null;
        this.recvInterceptor = null;

        logger.info("Interceptors wired up");

        /*
        if (!restletsStarted) {
            startRestlets();
        }
        */
    }

    private void startRestlets() {
        try {
            // Create a new Component.
            Component component = new Component();

            // Add a new HTTP server listening on the specified port
            component.getServers().add(Protocol.HTTP, listeningPort);

            // Attach the sample application.
            component.getDefaultHost().attach(restletApplicationFactory.create(getToggles()));

            logger.info("Starting RESTlets");

            // Start the component.
            component.start();

            // Indicate that the RESTlets were started
            restletsStarted = true;
        } catch (Exception e) {
            // Something is wrong.
            e.printStackTrace();
        }
    }

    private List<Toggle> getToggles() {
        List<Toggle> returnValue = new ArrayList<Toggle>();
        returnValue.add(sendToInterceptorToggle);
        return returnValue;
    }
}
