package com.timmattison.sjmmie.enums;

import java.util.HashMap;
import java.util.Map;

/**
 * Created by timmattison on 3/21/14.
 */
public enum SocketProtocols {
    IPPROTO_IP(0),
    IPPROTO_ICMP(1),
    IPPROTO_IGMP(2),
    IPPROTO_IPV4(4),
    IPPROTO_TCP(6),
    IPPROTO_UDP(17),
    IPPROTO_IPV6(41),
    UNKNOWN(Integer.MIN_VALUE);

    private int value;

    private static Map<Integer, SocketProtocols> map = null;

    public static SocketProtocols findByValue(int value) {
        if (map == null) {
            map = new HashMap<Integer, SocketProtocols>();

            for (SocketProtocols socketProtocols : SocketProtocols.values()) {
                map.put(socketProtocols.getValue(), socketProtocols);
            }
        }

        if (map.containsKey(value)) {
            return map.get(value);
        } else {
            return SocketProtocols.UNKNOWN;
        }
    }

    SocketProtocols(int value) {
        this.value = value;
    }

    int getValue() {
        return value;
    }
}
