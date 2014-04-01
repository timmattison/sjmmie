package com.timmattison.sjmmie.restlets;

import com.google.inject.assistedinject.Assisted;
import com.timmattison.sjmmie.controls.Toggle;

import java.util.List;

/**
 * Created by timmattison on 4/1/14.
 */
public class BasicRestletApplicationFactory implements RestletApplicationFactory {
    private RestletApplication restletApplication;

    @Override
    public RestletApplication create(@Assisted("toggles") List<Toggle> toggles) {
        System.out.println("RAF 1");
        if (restletApplication == null) {
            System.out.println("RAF 2");
            restletApplication = new RestletApplication(toggles);
        }

        System.out.println("RAF 3");
        return restletApplication;
    }
}
