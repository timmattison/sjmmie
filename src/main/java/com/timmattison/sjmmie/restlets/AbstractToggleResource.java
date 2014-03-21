package com.timmattison.sjmmie.restlets;

/**
 * Created by timmattison on 3/21/14.
 */

import com.timmattison.sjmmie.controls.Toggle;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 11/1/13
 * Time: 10:55 AM
 * To change this template use File | Settings | File Templates.
 */
public abstract class AbstractToggleResource extends AbstractResource {
    public Toggle getToggle() {
        return getToggleMap().get(getPath());
    }
}
