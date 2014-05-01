package com.timmattison.sjmmie.interceptors.streamdump;

import com.timmattison.sjmmie.objects.ReferenceSockaddr;

/**
 * Created by timmattison on 5/1/14.
 */
public interface SockAddrTranslator {
    public String translateSockAddr(ReferenceSockaddr referenceSockaddr);
}
