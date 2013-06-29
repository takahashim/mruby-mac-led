LED class for Mac
=================

This is an LED class for Mac OS X.
It is a wrapper of keyboard LED manipulation libarary.
(http://osxbook.com/book/bonus/chapter10/kbdleds/)


## Usage

```ruby
led = LED.new
led.on? #=> false
led.on
led.on? #=> true
led.off
led.on? #=> false
led.toggle
led.on? #=> true
led.toggle
led.on? #=> false
```

## Reference

### Class Methods

* `LED.new`

Create new instance of LED.

### Instance Methods

* `LED#on`

Turn on.

* `LED#off`

Turn off.

* `LED#on?`

Return the status of LED.

* `LED#toggle`

Change the status of LED.


## License

BSD license.

## Author

The author of this mrbgem is Masayoshi Takahashi.
The author of keyboard LED manipulation library is Amit Singh.


