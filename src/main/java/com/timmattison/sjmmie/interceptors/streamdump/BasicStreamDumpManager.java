package com.timmattison.sjmmie.interceptors.streamdump;

import javax.inject.Inject;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;
import java.util.logging.Logger;

/**
 * Created by timmattison on 5/1/14.
 */
public class BasicStreamDumpManager implements StreamDumpManager {
    private final Logger logger;
    private Map<Integer, FileOutputStream> streams = new HashMap<Integer, FileOutputStream>();

    @Inject
    public BasicStreamDumpManager(Logger logger) {
        this.logger = logger;
    }

    @Override
    public synchronized void openStream(int descriptor, String description) throws FileNotFoundException {
        logger.info("A opening " + descriptor);
        streams.put(descriptor, new FileOutputStream(description + "." + new Date().getTime() + ".stream", true));
        logger.info("B " + streams.keySet());
    }

    @Override
    public synchronized void closeStream(int descriptor) throws IOException {
        logger.info("C1 closing " + descriptor);
        FileOutputStream stream = streams.get(descriptor);
        logger.info("C2");
        if(stream == null) {
            logger.info("C3");
            return;
        }
        logger.info("D");
        stream.close();

        logger.info("E");
        streams.remove(descriptor);
        logger.info("F");
    }

    @Override
    public void writeOutputStream(int descriptor, byte[] data) throws IOException {
        logger.info("G");
        writeStream(descriptor, data);
        logger.info("H");
    }

    @Override
    public void writeInputStream(int descriptor, byte[] data) throws IOException {
        logger.info("I");
        writeStream(descriptor, data);
        logger.info("J");
    }

    private void writeStream(int descriptor, byte[] data) throws IOException {
        logger.info("K writing to " + descriptor);
        FileOutputStream stream = streams.get(descriptor);
        logger.info("L");
        stream.write(data);
        logger.info("M");
    }
}
