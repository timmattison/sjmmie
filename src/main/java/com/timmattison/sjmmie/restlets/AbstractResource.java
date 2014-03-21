package com.timmattison.sjmmie.restlets;

/**
 * Created by timmattison on 3/21/14.
 */

import com.timmattison.sjmmie.controls.Toggle;
import org.restlet.resource.ServerResource;

import java.util.Collection;
import java.util.Map;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 11/1/13
 * Time: 10:55 AM
 * To change this template use File | Settings | File Templates.
 */
public abstract class AbstractResource extends ServerResource {
    protected Collection<Toggle> getCommands() {
        return getToggleMap().values();
    }

    protected Map<String, Toggle> getToggleMap() {
        return (Map<String, Toggle>) getContext().getAttributes().get(RestletApplication.ToggleMapAttribute);
    }

    protected String getPath() {
        String fullPath = String.valueOf(getRequest().getResourceRef());
        int afterLastForwardSlash = fullPath.lastIndexOf('/') + 1;
        int beforeQueryString = fullPath.lastIndexOf('?');

        String returnValue;

        if (beforeQueryString == -1) {
            returnValue = fullPath.substring(afterLastForwardSlash);
        } else {
            returnValue = fullPath.substring(afterLastForwardSlash, beforeQueryString);
        }

        return returnValue;
    }

    /*
    protected BasicHistogram getHistogram() {
        return ((DSHistCommand) getContext().getAttributes().get(RedMonitor.DSHistAttribute)).getValue();
    }
    */
}
