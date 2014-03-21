package com.timmattison.sjmmie.enums;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by timmattison on 3/21/14.
 */
public enum SocketTypes {
    SOCK_STREAM(1),
    SOCK_DGRAM(2),
    SOCK_RAW(3),
    SOCK_RDM(4),
    SOCK_SEQPACKET(5),
    UNKNOWN(Integer.MIN_VALUE);

    private int value;

    private static Map<Integer, SocketTypes> map = null;

    public static SocketTypes findByValue(int value) {
        if (map == null) {
            map = new HashMap<Integer, SocketTypes>();

            for (SocketTypes protocolEnum : SocketTypes.values()) {
                map.put(protocolEnum.getValue(), protocolEnum);
            }
        }

        if (map.containsKey(value)) {
            return map.get(value);
        } else {
            return SocketTypes.UNKNOWN;
        }
    }

    SocketTypes(int value) {
        this.value = value;
    }

    int getValue() {
        return value;
    }
}
