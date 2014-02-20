package com.timmattison.sjmmie;

/**
 * Created by timmattison on 2/20/14.
 */
public class SjmmieLibrary {
    static {
        System.loadLibrary("sjmmie");
    }

    public native int originalOpen(String filename, int flags);

    public native int originalClose(int fildes);

    public native int originalConnect(int s, char sa_family, byte[] sa_data, int namelen);
}
