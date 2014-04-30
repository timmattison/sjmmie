package com.timmattison.sjmmie.restlets;

import com.google.inject.assistedinject.Assisted;
import com.timmattison.sjmmie.controls.Toggle;

import javax.inject.Inject;
import java.util.List;
import java.util.logging.Logger;

/**
 * Created by timmattison on 4/1/14.
 */
public class BasicRestletApplicationFactory implements RestletApplicationFactory {
    private final Logger logger;
    private RestletApplication restletApplication;

    @Inject
    public BasicRestletApplicationFactory(Logger logger) {
        this.logger = logger;
    }

    @Override
    public RestletApplication create(@Assisted("toggles") List<Toggle> toggles) {
        if (restletApplication == null) {
            restletApplication = new RestletApplication(toggles);
        }

        return restletApplication;
    }
}
