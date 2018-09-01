#ifndef LEDBOARD_H_
#define LEDBOARD_H_

#include <Arduino.h>

#include <Tlc59711.h>

bool output_enabled = true;

const uint8_t boards_count = 1;

const uint8_t chips_per_board = 4;

const uint8_t colors_per_led = 3;
const uint8_t leds_per_chip = 4;

const uint8_t colorchannels_per_board = (
    colors_per_led * leds_per_chip * chips_per_board
);

const uint8_t leds_per_row = 4;
const uint8_t leds_per_column = 4;
const uint8_t leds_count = leds_per_row * leds_per_column;

const uint8_t channel_position_map[leds_per_column][leds_per_row] = {
    { 0,  1,  4,  5},
    { 2,  3,  6,  7},
    { 8,  9, 12, 13},
    {10, 11, 14, 15},
};

// tlc info
const uint8_t tlc_channels = colors_per_led * leds_per_chip;
const uint8_t tlc_channels_per_board = tlc_channels * chips_per_board;
const uint8_t tlc_chips = boards_count * chips_per_board;
const uint8_t tlc_channels_total = (uint8_t)(tlc_chips * tlc_channels);

Tlc59711 tlc(tlc_chips);

#endif  // LEDBOARD_H_
