package com.timmattison.sjmmie.restlets;

/**
 * Created by timmattison on 3/21/14.
 */

import org.restlet.data.MediaType;
import org.restlet.representation.Representation;
import org.restlet.representation.StringRepresentation;
import org.restlet.resource.Post;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 11/1/13
 * Time: 11:15 AM
 * To change this template use File | Settings | File Templates.
 */
public class ToggleResource extends AbstractToggleResource {
    @Post
    public Representation acceptItem(Representation entity) {
        try {
            getToggle().toggle();

            return new StringRepresentation("SUCCESS", MediaType.TEXT_PLAIN);
        } catch (Exception ex) {
            return new StringRepresentation("FAILURE", MediaType.TEXT_PLAIN);
        }
    }
}
