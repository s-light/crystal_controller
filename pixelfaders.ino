
const slight_FaderLin pixelfaders_faders[leds_count] = {
    slight_FaderLin(
        // byte cbID_New
        0,
        // byte cbChannelCount_New
        colors_per_led,
        // tCbfuncValuesChanged cbfuncValuesChanged_New
        pixelFader_callback_OutputChanged,
        // tCbfuncStateChanged cbfuncStateChanged_New
        pixelFader_callback_onEvent),
    slight_FaderLin(
        1,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        2,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        3,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        4,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        5,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        6,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        7,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        8,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        9,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        10,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        11,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        12,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        13,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        14,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
    slight_FaderLin(
        15,
        colors_per_led,
        pixelFader_callback_OutputChanged,
        pixelFader_callback_onEvent),
};


void pixelFader_callback_OutputChanged(uint8_t id, uint16_t *values, uint8_t count) {
    // if (bDebugOut_myFaderRGB_Output_Enable) {
    //     Serial.print(F("OutputValue: "));
    //     printArray_uint16(Serial, wValues, bCount);
    //     Serial.println();
    // }

    // for (size_t channel_index = 0; channel_index < count; channel_index++) {
    //     tlc.setChannel(channel_index, values[channel_index]);
    // }

    if (output_enabled) {
        tlc.setRGB(values[0], values[1], values[2]);
        tlc.write();
    }
}


void pixelFader_callback_onEvent(slight_FaderLin *pInstance, byte event) {
    // Serial.print(F("Instance ID:"));
    // Serial.println((*pInstance).getID());
    //
    // Serial.print(F("Event: "));
    // (*pInstance).printEvent(Serial, event);
    // Serial.println();

    // react on events:
    switch (event) {
        case slight_FaderLin::event_StateChanged : {
            // Serial.print(F("slight_FaderLin "));
            // Serial.print((*pInstance).getID());
            // Serial.println(F(" : "));
            // Serial.print(F("\t state: "));
            // (*pInstance).printState(Serial);
            // Serial.println();

            // switch (state) {
            //     case slight_FaderLin::state_Standby : {
            //             //
            //         } break;
            //     case slight_FaderLin::state_Fading : {
            //             //
            //         } break;
            //     case slight_FaderLin::state_Finished : {
            //             //
            //         } break;
            // }  // end switch
        } break;
        case slight_FaderLin::event_fading_Finished : {
            // Serial.print(F("\t fading Finished."));
        } break;
    }  // end switch
}




void pixelfaders_fadeTo(
    uint8_t pixelid, uint16_t duration, uint16_t r, uint16_t g, uint16_t b
) {
    uint16_t values[colors_per_led];
    // init array with 0
    values[0] = r;
    values[1] = g;
    values[2] = b;
    pixelfaders_faders[pixelid].startFadeTo(duration, values);
}

void pixelfaders_wait_for_fade() {
    bool fading_all_done = false;
    while (!fading_all_done) {
        fading_all_done = true;
        for (size_t i = 0; i < leds_count; i++) {
            if (
                pixelfaders_faders[i].update() == slight_FaderLin::state_Fading
                // pixelfaders_faders[i].update() == slight_FaderLin::state_Standby
            ) {
                fading_all_done = false;
            }
        }
    }
    for (size_t i = 0; i < leds_count; i++) {
        pixelfaders_faders[i].update();
    }
}

void pixelfaders_init(Print &out) {
    out.println(F("setup pixelFaders:"));

    out.println(F("\t begin();"));
    for (size_t i = 0; i < leds_count; i++) {
        pixelfaders_faders[i].begin();
    }

    out.println(F("\t welcome fade"));
    pixelfaders_welcome_fade();

    out.println(F("\t finished."));
}

void pixelfaders_welcome_fade() {
    for (size_t i = 0; i < leds_count; i++) {
        pixelfaders_fadeTo(i , 1000, 60000, 60000, 0);
    }
    pixelfaders_wait_for_fade();

    for (size_t i = 0; i < leds_count; i++) {
        pixelfaders_fadeTo(i , 1000, 1000, 500, 1);
    }
    pixelfaders_wait_for_fade();

    for (size_t i = 0; i < leds_count; i++) {
        pixelfaders_fadeTo(i , 1000, 0, 0, 1);
    }
    pixelfaders_wait_for_fade();
}
