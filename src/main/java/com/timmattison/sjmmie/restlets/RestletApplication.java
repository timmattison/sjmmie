package com.timmattison.sjmmie.restlets;

/**
 * Created by timmattison on 3/21/14.
 */

import com.google.inject.assistedinject.Assisted;
import com.timmattison.sjmmie.control.Toggle;
import org.restlet.Application;
import org.restlet.Restlet;
import org.restlet.routing.Router;

import javax.inject.Inject;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 10/24/13
 * Time: 6:15 PM
 * To change this template use File | Settings | File Templates.
 */
public class RestletApplication extends Application {
    public static final String ToggleMapAttribute = "ToggleMapAttribute";
    private final List<Toggle> toggles;

    @Inject
    public RestletApplication(@Assisted("toggles") List<Toggle> toggles) {
        this.toggles = toggles;
    }

    /**
     * Creates a root Restlet that will receive all incoming calls.
     */
    @Override
    public Restlet createInboundRoot() {
        // Create a router Restlet that routes each call
        Router router = new Router(getContext());

        Map<String, Toggle> toggleMap = new HashMap<String, Toggle>();

        for (Toggle toggle : toggles) {
            toggleMap.put(toggle.getName(), toggle);
        }

        router.getContext().getAttributes().put(ToggleMapAttribute, toggleMap);

        for (Toggle toggle : toggles) {
            router.attach("/toggle/" + toggle.getName(), ToggleResource.class);
        }

        // A simple default path that doesn't do much
        router.attachDefault(DefaultResource.class);

        // Serve jQuery from a local copy
        router.attach("/jquery-1.10.2.min.js", JQueryResource.class);

        return router;
    }
}
