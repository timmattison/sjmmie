package com.timmattison.sjmmie.interceptors.streamdump;

import java.io.FileNotFoundException;
import java.io.IOException;

/**
 * Created by timmattison on 5/1/14.
 */
public interface StreamDumpManager {
    public void openStream(int descriptor, String description) throws FileNotFoundException;

    public void closeStream(int descriptor) throws IOException;

    public void writeOutputStream(int descriptor, byte[] data) throws IOException;

    public void writeInputStream(int descriptor, byte[] data) throws IOException;
}
