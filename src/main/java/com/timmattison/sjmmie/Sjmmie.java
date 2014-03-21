package com.timmattison.sjmmie;

import com.google.inject.Guice;
import com.google.inject.Injector;
import com.timmattison.sjmmie.control.SendToInterceptorToggle;
import com.timmattison.sjmmie.control.Toggle;
import com.timmattison.sjmmie.interceptors.interfaces.CloseInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.ConnectInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.OpenInterceptor;
import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;
import com.timmattison.sjmmie.restlets.RestletApplicationFactory;
import org.restlet.Component;
import org.restlet.data.Protocol;

import javax.inject.Inject;
import java.util.ArrayList;
import java.util.List;

/**
 * Created by timmattison on 2/20/14.
 */
public class Sjmmie extends AbstractSjmmie {
    private static Sjmmie INSTANCE = null;
    private static final int listeningPort = 64000;
    private final RestletApplicationFactory restletApplicationFactory;
    private final SendToInterceptorToggle sendToInterceptorToggle;

    public static Sjmmie getInstance() {
        if (INSTANCE == null) {
            Injector injector = Guice.createInjector(new SjmmieModule());

            // Get an instance of the Sjmmie object
            INSTANCE = injector.getInstance(Sjmmie.class);
        }

        return INSTANCE;
    }

    @Inject
    public Sjmmie(RestletApplicationFactory restletApplicationFactory, OpenInterceptor openInterceptor, CloseInterceptor closeInterceptor, ConnectInterceptor connectInterceptor, SendToInterceptor sendToInterceptor, SendToInterceptorToggle sendToInterceptorToggle) {
        this.restletApplicationFactory = restletApplicationFactory;
        this.openInterceptor = openInterceptor;
        this.closeInterceptor = closeInterceptor;
        this.connectInterceptor = connectInterceptor;
        this.sendToInterceptor = sendToInterceptor;
        this.sendToInterceptorToggle = sendToInterceptorToggle;

        startRestlets();
    }

    private void startRestlets() {
        try {
            // Create a new Component.
            Component component = new Component();

            // Add a new HTTP server listening on the specified port
            component.getServers().add(Protocol.HTTP, listeningPort);

            // Attach the sample application.
            component.getDefaultHost().attach(restletApplicationFactory.create(getToggles()));

            // Start the component.
            component.start();
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

    @Override
    public boolean isEnabled() {
        // TODO FIXME XXX - UGLY AND BAD, FIX ME
        return sendToInterceptor.isEnabled();
    }

    @Override
    public void setEnabled(boolean enabled) {
        // TODO FIXME XXX - UGLY AND BAD, FIX ME
        sendToInterceptor.setEnabled(enabled);
    }
}
