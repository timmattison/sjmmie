package com.timmattison.sjmmie.restlets;

import org.apache.commons.io.IOUtils;

import java.io.IOException;
import java.io.InputStream;
import java.net.URL;

/**
 * Created by timmattison on 3/21/14.
 */
public class InternalResourceLoader {
    public static String getInternalResource(Class caller, String name) throws IOException {
        URL url = caller.getResource("/" + name);
        InputStream inputStream = url.openStream();
        return IOUtils.toString(inputStream);
    }
}
