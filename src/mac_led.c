/*
 * mac_led.c
 * manipulate keyboard LED (capslock) on Mac OS X
 *
 * Copyright (c) 2013 Masayoshi Takahashi
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <mruby.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/hid/IOHIDLib.h>
#include <IOKit/hid/IOHIDUsageTables.h>

int          manipulate_led(UInt32 whichLED, UInt32 value);
int          get_led_value(UInt32 whichLED);

const int LED_ON  = 1;
const int LED_OFF = 0;

static mrb_value
mrb_mac_led_init(mrb_state *mrb, mrb_value self)
{
  return self;
}

static mrb_value
mrb_mac_led_on_p(mrb_state *mrb, mrb_value self)
{
  UInt32 whichLED = kHIDUsage_LED_CapsLock;
  mrb_bool led_value = get_led_value(whichLED);
  return mrb_bool_value(led_value);
}

static mrb_value
mrb_mac_led_on(mrb_state *mrb, mrb_value self)
{
  UInt32 whichLED = kHIDUsage_LED_CapsLock;
  manipulate_led(whichLED, LED_ON);
  return self;
}

static mrb_value
mrb_mac_led_off(mrb_state *mrb, mrb_value self)
{
  UInt32 whichLED = kHIDUsage_LED_CapsLock;
  manipulate_led(whichLED, LED_OFF);
  return self;
}

static mrb_value
mrb_mac_led_toggle(mrb_state *mrb, mrb_value self)
{
  UInt32 whichLED = kHIDUsage_LED_CapsLock;
  mrb_bool led_value = get_led_value(whichLED);
  if (led_value) {
    manipulate_led(whichLED, LED_OFF);
  } else {
    manipulate_led(whichLED, LED_ON);
  }
  return self;
}

void
mrb_mruby_mac_led_gem_init(mrb_state* mrb) {
  struct RClass *led = mrb_define_class(mrb, "LED", mrb->object_class);
  mrb_define_method(mrb, led, "initialize", mrb_mac_led_init, MRB_ARGS_OPT(1));
  mrb_define_method(mrb, led, "on", mrb_mac_led_on, MRB_ARGS_NONE());
  mrb_define_method(mrb, led, "off", mrb_mac_led_off, MRB_ARGS_NONE());
  mrb_define_method(mrb, led, "on?", mrb_mac_led_on_p, MRB_ARGS_NONE());
  mrb_define_method(mrb, led, "toggle", mrb_mac_led_toggle, MRB_ARGS_NONE());
}

void
mrb_mruby_mac_led_gem_final(mrb_state* mrb) {
  // finalizer
}


