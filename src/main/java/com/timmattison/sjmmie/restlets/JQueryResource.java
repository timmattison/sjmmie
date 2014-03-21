package com.timmattison.sjmmie.restlets;

/**
 * Created by timmattison on 3/21/14.
 */

import org.restlet.representation.Representation;
import org.restlet.representation.StringRepresentation;
import org.restlet.resource.Get;
import org.restlet.resource.ServerResource;

import java.io.IOException;

/**
 * Created by timmattison on 12/30/13.
 */
public class JQueryResource extends ServerResource {
    @Get
    public Representation represent() throws IOException {
        return new StringRepresentation(InternalResourceLoader.getInternalResource(this.getClass(), "jquery-1.10.2.min.js"));
    }
}

