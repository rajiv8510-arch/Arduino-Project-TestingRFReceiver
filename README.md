# RF Receiver Testing Tools

Development and testing sketches for 433MHz RF wireless receivers.

## Overview

This repository contains **development and testing tools** for working with RF wireless receivers. These sketches were used to learn, test, and develop RF receiver protocols before implementing production code.

**⚠️ Note**: These are TESTING/DEVELOPMENT tools, not production code. For production-ready RF receiver implementation, see the [CoolerRemoteControl](../CoolerRemoteControl/) repository (v1.0 RF Basic).

## Purpose

- Learn how RF receivers work
- Test different RF receiver modules
- Decode RF signals from remotes
- Develop and debug RF protocols
- Understand 4-channel RF receiver operation
- Experiment with different RF libraries

## Contents

### Test Sketches

Located in `test-sketches/`:

#### 1. RFTest_RCSwitch.ino
**Library**: RCSwitch  
**Purpose**: Test RF signal reception and decoding

**Features**:
- Receives RF signals via RCSwitch library
- Reads 4-channel receiver data pins (D0-D3, Vt)
- Decodes RF codes from remotes
- LED feedback for received signals
- Switch-case for specific RF code actions
- Serial output for debugging

**Hardware**:
- Arduino Uno/Nano
- RCSwitch-compatible RF receiver
- 4-channel RF receiver module
- LED on pin 13

**Use Case**: General RF signal testing and code identification

#### 2. RFTest_RM4.ino
**Library**: RM4  
**Purpose**: Test 4-channel RF receiver modules

**Features**:
- Uses RM4 library for clean 4-channel interface
- Reads button codes from 4-button RF remotes
- Commented relay control code (template)
- Simple button code output
- Minimal overhead

**Hardware**:
- Arduino Uno/Nano
- 4-channel RF receiver (RM4SG-M or similar)
- 4-button RF remote

**Use Case**: Testing 4-channel RF receivers specifically

### Libraries

Located in `libraries/`:

#### 1. RM4 Library
**Version**: arduino-rm4-master  
**Author**: Matt Sparks  
**License**: BSD

**Purpose**: Interface with 4-channel RF receiver modules

**Features**:
- Clean API for 4-channel receivers
- Button code translation
- Multiple button press detection
- Bitwise OR for simultaneous buttons

**Compatible Hardware**:
- RM4SG-M RF receiver modules
- Similar 4-channel receivers
- 4-button keyfobs

**Installation**:
```
Arduino IDE → Sketch → Include Library → Add .ZIP Library
Select: libraries/RM4
```

#### 2. RadioHead Library
**Version**: 1.102  
**Author**: Mike McCauley  
**License**: GPL

**Purpose**: General-purpose RF communication library

**Features**:
- Supports many RF modules
- Reliable datagram delivery
- Addressing and routing
- Error detection
- Works with many RF chipsets

**Supported Modules**:
- 433MHz ASK/OOK modules
- nRF24L01+
- RFM69
- LoRa modules
- And many more

**Installation**:
```
Arduino IDE → Sketch → Include Library → Add .ZIP Library
Select: libraries/RadioHead
```

**Note**: RadioHead is included for completeness but not used in current test sketches

## Hardware Setup

### For RFTest_RCSwitch.ino

```
RF Receiver (RCSwitch)    Arduino
----------------------    -------
VCC                   →   5V
GND                   →   GND
DATA                  →   Pin 2 (interrupt 0)

4-Channel Receiver        Arduino
------------------        -------
D0                    →   Pin 8
D1                    →   Pin 9
D2                    →   Pin 10
D3                    →   Pin 11
Vt                    →   Pin 12
VCC                   →   5V
GND                   →   GND

LED                       Arduino
---                       -------
Anode (+)             →   Pin 13 (via 330Ω)
Cathode (-)           →   GND
```

### For RFTest_RM4.ino

```
4-Channel Receiver        Arduino
------------------        -------
D0                    →   Pin 2
D1                    →   Pin 10
D2                    →   Pin 11
D3                    →   Pin 12
VCC                   →   Pin 13 (enable)
GND                   →   GND
```

## Usage

### Testing RF Signals with RCSwitch

1. **Install RCSwitch Library**
   - Download from https://github.com/sui77/rc-switch
   - Or use Arduino Library Manager

2. **Upload RFTest_RCSwitch.ino**

3. **Open Serial Monitor** (9600 baud)

4. **Press RF Remote Buttons**
   - View received RF codes
   - LED blinks to indicate reception

5. **Note RF Codes**
   - Record codes for each button
   - Use in production code

### Testing 4-Channel Receiver with RM4

1. **Install RM4 Library**
   - Use included library folder
   - Copy to Arduino/libraries/

2. **Upload RFTest_RM4.ino**

3. **Open Serial Monitor** (9600 baud)

4. **Press Buttons on 4-Button Remote**
   - Button A: Code 1
   - Button B: Code 2
   - Button C: Code 4
   - Button D: Code 8

5. **Test Simultaneous Buttons**
   - Multiple buttons = OR of codes
   - A+C = 1|4 = 5

## Development Workflow

These tools are used in the following development workflow:

```
1. Test RF Receiver
   ↓ (Use RFTest sketches)
   
2. Learn RF Codes
   ↓ (Record codes from Serial Monitor)
   
3. Develop Protocol
   ↓ (Design button functions)
   
4. Prototype Code
   ↓ (Test with relay control)
   
5. Create Production Code
   ↓ (Implement in final project)
   
6. Deploy
   ↓ (CoolerRemoteControl v1.0)
```

## Typical Output

### RFTest_RCSwitch.ino

```
Serial Monitor:
	5592332	5592332
	5592515	5592515
	5592522	5592522
	16777215	16777215 (Special code triggers LED sequence)
```

### RFTest_RM4.ino

```
Serial Monitor:
1  (Button A pressed)
2  (Button B pressed)
4  (Button C pressed)
8  (Button D pressed)
5  (Button A+C pressed simultaneously)
```

## Modifications

### Adding Relay Control

In `RFTest_RM4.ino`, uncomment the relay control sections:

```cpp
const int relay1 = 14;
const int relay2 = 15;
const int relay3 = 16;
const int relay4 = 17;

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
}

void loop() {
  const int button_code = remote.buttonCode();
  
  if (button_code == 8) {
    digitalWrite(relay1, LOW);  // Relay ON
    delay(2000);
  } else {
    digitalWrite(relay1, HIGH); // Relay OFF
  }
  // Repeat for other buttons...
}
```

### Changing RF Codes

In `RFTest_RCSwitch.ino`, modify the switch-case:

```cpp
switch(num) {
  case YOUR_CODE:  // Replace with your RF code
    // Your action here
    break;
}
```

## Troubleshooting

### No RF Codes Received
- Check RF receiver wiring
- Verify receiver power (should get warm)
- Check antenna connection
- Try different remote
- Verify interrupt pin (pin 2 for RCSwitch)

### Wrong Codes Displayed
- Different remotes send different codes
- Each remote has unique ID
- Record codes for your specific remote

### Relay Not Working
- Check relay module connections
- Verify relay logic (active HIGH or LOW)
- Test relay separately with digitalWrite
- Check power supply (relays need adequate current)

### Library Not Found
- Install library in Arduino/libraries/
- Restart Arduino IDE
- Check library path

## Relationship to Other Projects

### Connection to CoolerRemoteControl

These testing tools were used to develop:
- **CoolerRemoteControl v1.0** (RF Basic)
  - Production RF receiver code
  - 4-channel relay control
  - Stable and tested
  - Ready for deployment

**Development Path**:
```
RFTest sketches → Learn & Test → Develop → CoolerRemoteControl v1.0
```

### Not Related To
- CoolerRemoteControl v2.0 (uses IR, not RF)
- CoolerWaterLevelControl (no remote control)

## Use Cases

### 1. Learning RF Communication
- Understand how RF receivers work
- See RF codes in real-time
- Experiment with different remotes

### 2. Protocol Development
- Test different RF code schemes
- Develop button mapping
- Debug RF reception issues

### 3. Hardware Testing
- Verify RF receiver modules
- Test range and reliability
- Check interference issues

### 4. Production Code Development
- Prototype relay control
- Develop state machines
- Test before final implementation

## Limitations

- **Not production code**: Missing error handling, state management
- **No EEPROM**: Settings not saved
- **Basic functionality**: Testing only
- **No safety features**: Implement in production code
- **Limited documentation**: Experimental code

## Upgrading to Production

To move from testing to production:

1. **Add State Management**
   - EEPROM for persistence
   - State machine for control

2. **Add Error Handling**
   - Timeout protection
   - Invalid code handling

3. **Improve Relay Control**
   - Proper toggling logic
   - State indicators (LEDs)

4. **Add Safety Features**
   - Debouncing
   - Command validation

5. **Use Production Code**
   - See CoolerRemoteControl v1.0

## Contributing

This is a reference/testing repository. For production improvements:
- Modify CoolerRemoteControl repository
- These sketches are for learning/testing only

## License

- **RM4 Library**: BSD License (see libraries/RM4/)
- **RadioHead Library**: GPL (see libraries/RadioHead/)
- **Test Sketches**: Educational use, modify freely

## References

### RM4 Library
- GitHub: https://github.com/quadule/arduino-rm4

### RCSwitch Library
- GitHub: https://github.com/sui77/rc-switch

### RadioHead Library
- Website: http://www.airspayce.com/mikem/arduino/RadioHead/

### RF Modules
- RM4SG-M: http://www.e-madeinchn.com/ReceiverModules.html

## Repository Structure

```
RFReceiverTestingTools/
├── README.md (this file)
├── .gitignore
│
├── test-sketches/
│   ├── RFTest_RCSwitch.ino
│   └── RFTest_RM4.ino
│
├── libraries/
│   ├── RM4/
│   │   ├── rm4.h
│   │   ├── rm4.cpp
│   │   ├── README.md
│   │   └── examples/
│   └── RadioHead/
│       ├── *.h (multiple files)
│       ├── *.cpp (multiple files)
│       ├── README
│       └── examples/
│
├── docs/
│   ├── LIBRARY_GUIDE.md
│   ├── HARDWARE_SETUP.md
│   └── RF_THEORY.md
│
└── examples/
    └── (Future example sketches)
```

## Quick Start

1. Clone/download repository
2. Install RM4 and RadioHead libraries
3. Open test sketch in Arduino IDE
4. Wire hardware per diagrams
5. Upload and test
6. Record RF codes from Serial Monitor
7. Use codes in production project

## Summary

This repository contains **development tools** for RF receiver testing. Use these to learn RF communication and develop protocols. For production RF receiver code, see **CoolerRemoteControl v1.0**.

**Testing → Learning → Development → Production**
