package com.timmattison.sjmmie.interceptors.streamdump;

import com.timmattison.sjmmie.objects.ReferenceSockaddr;

/**
 * Created by timmattison on 5/1/14.
 */
public class BasicSockAddrTranslator implements SockAddrTranslator {
    @Override
    public String translateSockAddr(ReferenceSockaddr referenceSockaddr) {
        if (referenceSockaddr.sa_data == null) {
            return "NULL";
        }

        StringBuilder stringBuilder = new StringBuilder();

        int loopLength = (4 > referenceSockaddr.sa_data.length) ? 4 : referenceSockaddr.sa_data.length;

        for (int loop = 0; loop < loopLength; loop++) {
            int current_byte = referenceSockaddr.sa_data[loop];

            if (current_byte < 0) {
                current_byte = ~current_byte + 1;
            }

            stringBuilder.append(String.valueOf(current_byte));
        }

        return stringBuilder.toString();
    }
}
