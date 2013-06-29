/*
 * mac_led.c
 * manipulate keyboard LED (capslock)
 *
 * Copyright (c) 2013 Masayoshi Takahashi. All Rights Reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 *  ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *  ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 *  OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 *  HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 *  OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 *  SUCH DAMAGE.
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


