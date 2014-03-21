package com.timmattison.sjmmie.enums;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by timmattison on 3/21/14.
 */
public enum SocketAddressFamilies {
    AF_UNSPEC(0),
    AF_UNIX(1),
    AF_INET(2),
    AF_INET6(30),
    AF_SYSTEM(32),
    UNKNOWN(Integer.MIN_VALUE);

    private int value;

    private static Map<Integer, SocketAddressFamilies> map = null;

    public static SocketAddressFamilies findByValue(int value) {
        if (map == null) {
            map = new HashMap<Integer, SocketAddressFamilies>();

            for (SocketAddressFamilies socketProtocols : SocketAddressFamilies.values()) {
                map.put(socketProtocols.getValue(), socketProtocols);
            }
        }

        if (map.containsKey(value)) {
            return map.get(value);
        } else {
            return SocketAddressFamilies.UNKNOWN;
        }
    }

    SocketAddressFamilies(int value) {
        this.value = value;
    }

    int getValue() {
        return value;
    }
}
