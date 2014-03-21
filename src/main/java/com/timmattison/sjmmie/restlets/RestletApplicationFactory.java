package com.timmattison.sjmmie.restlets;

/**
 * Created by timmattison on 3/21/14.
 */

import com.google.inject.Inject;
import com.google.inject.assistedinject.Assisted;
import com.timmattison.sjmmie.control.Toggle;

import java.util.List;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 10/25/13
 * Time: 12:21 PM
 * To change this template use File | Settings | File Templates.
 */
public interface RestletApplicationFactory {
    @Inject
    RestletApplication create(@Assisted("toggles") List<Toggle> toggles);
}
