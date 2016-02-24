# SpektrumRX
A library for reading Spektrum sattellite receivers.

# In a Nutshell
I wrote this library to solve a specific problem: how to read a Spektrum sattellite receiver bound to a DX9 with a Teensy 3.2. If that's what you're doing, it will work awesome for you. If you're doing something slightly different, this code will require a certain amount of modification.

# Notes
- It uses two serial ports, because I'm lazy and run only Teensy and better microcontrollers, so I always have multiple serial ports available. If you want to make this work with an UNO or a Trinket, you're going to have to write some code.
- Binding is fiddly and wierd and requires extra discrete components, and was not one of my design goals. Sorry.

# Requirements
Uses, but doesn't really require, my handy-dandy debugprint library:
https://github.com/TimTheTerrible/debugprint
