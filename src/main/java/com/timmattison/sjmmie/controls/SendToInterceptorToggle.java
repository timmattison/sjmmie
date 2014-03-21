package com.timmattison.sjmmie.controls;

import com.timmattison.sjmmie.interceptors.interfaces.SendToInterceptor;

import javax.inject.Inject;

/**
 * Created by timmattison on 3/21/14.
 */
public class SendToInterceptorToggle implements Toggle {
    private final SendToInterceptor sendToInterceptor;

    @Inject
    SendToInterceptorToggle(SendToInterceptor sendToInterceptor) {
        this.sendToInterceptor = sendToInterceptor;
    }

    @Override
    public void toggle() {
        sendToInterceptor.sendToInterceptorSetEnabled(!sendToInterceptor.sendToInterceptorIsEnabled());
    }

    @Override
    public String getName() {
        return "sendTo";
    }
}
