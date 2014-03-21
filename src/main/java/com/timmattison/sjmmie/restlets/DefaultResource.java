package com.timmattison.sjmmie.restlets;

/**
 * Created by timmattison on 3/21/14.
 */

import com.timmattison.sjmmie.control.Toggle;
import org.restlet.data.MediaType;
import org.restlet.representation.Representation;
import org.restlet.representation.StringRepresentation;
import org.restlet.resource.Get;

/**
 * Created with IntelliJ IDEA.
 * User: timmattison
 * Date: 10/25/13
 * Time: 11:14 AM
 * To change this template use File | Settings | File Templates.
 */
public class DefaultResource extends AbstractResource {
    private String content;

    @Get
    public Representation represent() {
        if (content == null) {
            StringBuilder stringBuilder = new StringBuilder();
            stringBuilder.append("<html>");
            stringBuilder.append("<head>");
            stringBuilder.append("<script type=\"text/javascript\">document.write(\"\\<script src='/jquery-1.10.2.min.js' type='text/javascript'>\\<\\/script>\");</script>");
            stringBuilder.append("</head>");
            stringBuilder.append("<body><html><body><title>Sjmmie RESTlet server</title>\n");
            stringBuilder.append("<ul>\n");

            for (Toggle toggle : getToggleMap().values()) {
                stringBuilder.append(generateToggleLink(toggle));
            }

            content = stringBuilder.toString();
        }

        Representation representation = new StringRepresentation(content, MediaType.TEXT_HTML);
        return representation;
    }

    private String generateNormalLink(String url, String value, String text) {
        StringBuilder stringBuilder = new StringBuilder();

        stringBuilder.append("<a href=\"/");
        stringBuilder.append(url);

        if (value != null) {
            stringBuilder.append("?value=");
            stringBuilder.append(value);
        }

        stringBuilder.append("\">");
        stringBuilder.append(text);
        stringBuilder.append("</a><br/>\n");

        return stringBuilder.toString();
    }

    private String generateToggleLink(Toggle toggle) {
        StringBuilder stringBuilder = new StringBuilder();

        String toggleName = toggle.getName();

        stringBuilder.append("<a href=\"javascript:{}\" onclick=\"jQuery.post('/toggle/");
        stringBuilder.append(toggleName);
        stringBuilder.append("');\">");
        stringBuilder.append(toggleName);
        stringBuilder.append("</a>\n");

        return stringBuilder.toString();
    }
}
