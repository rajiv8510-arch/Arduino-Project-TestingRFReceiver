# RF Library Guide

Comprehensive guide to the RF libraries included in this repository.

## Libraries Overview

### 1. RM4 Library
**Purpose**: 4-channel RF receiver interface  
**Author**: Matt Sparks  
**License**: BSD  
**Best For**: RM4SG-M and similar 4-channel receivers

### 2. RadioHead Library  
**Purpose**: General RF communication  
**Author**: Mike McCauley  
**License**: GPL  
**Best For**: Advanced RF projects, various RF modules

## RM4 Library Details

### What It Does
The RM4 library simplifies working with 4-channel RF receivers. It translates the four data pins into easy-to-use button codes.

### Hardware Compatibility
- RM4SG-M RF receiver modules
- Similar 4-channel 433MHz receivers
- 4-button RF remote keyfobs

### Installation

**Method 1: Manual Installation**
1. Copy `libraries/RM4` folder
2. Paste into `Arduino/libraries/` folder
3. Restart Arduino IDE

**Method 2: ZIP Installation**
1. Compress `libraries/RM4` to RM4.zip
2. Arduino IDE → Sketch → Include Library → Add .ZIP Library
3. Select RM4.zip

### Basic Usage

```cpp
#include <rm4.h>

// Define data pins
const int kData0Pin = 2;
const int kData1Pin = 10;
const int kData2Pin = 11;
const int kData3Pin = 12;

// Create RM4 object
RM4 remote(kData0Pin, kData1Pin, kData2Pin, kData3Pin);

void setup() {
  Serial.begin(9600);
}

void loop() {
  // Get button code
  int button = remote.buttonCode();
  
  // Process button
  if (button == 1) {
    // Button A pressed
  }
  else if (button == 2) {
    // Button B pressed
  }
  else if (button == 4) {
    // Button C pressed
  }
  else if (button == 8) {
    // Button D pressed
  }
}
```

### Button Code Mapping

| Button | Code | Binary |
|--------|------|--------|
| A | 1 | 0001 |
| B | 2 | 0010 |
| C | 4 | 0100 |
| D | 8 | 1000 |

### Simultaneous Button Detection

The RM4 library supports multiple buttons pressed simultaneously:

| Buttons | Code | Calculation |
|---------|------|-------------|
| A + B | 3 | 1 OR 2 = 3 |
| A + C | 5 | 1 OR 4 = 5 |
| A + D | 9 | 1 OR 8 = 9 |
| B + C | 6 | 2 OR 4 = 6 |
| B + D | 10 | 2 OR 8 = 10 |
| C + D | 12 | 4 OR 8 = 12 |
| A + B + C | 7 | 1 OR 2 OR 4 = 7 |
| All | 15 | 1 OR 2 OR 4 OR 8 = 15 |

### API Reference

**Constructor:**
```cpp
RM4(uint8_t data0_pin, uint8_t data1_pin, 
    uint8_t data2_pin, uint8_t data3_pin)
```

**Methods:**
```cpp
int buttonCode()  // Returns current button code (0-15)
```

### Example: Relay Control

```cpp
#include <rm4.h>

const int kData0Pin = 2;
const int kData1Pin = 10;
const int kData2Pin = 11;
const int kData3Pin = 12;

const int relay1 = 14;
const int relay2 = 15;
const int relay3 = 16;
const int relay4 = 17;

RM4 remote(kData0Pin, kData1Pin, kData2Pin, kData3Pin);

void setup() {
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);
  
  // All relays OFF initially
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
}

void loop() {
  int button = remote.buttonCode();
  
  // Button A - Toggle Relay 1
  if (button == 1) {
    static bool relay1_state = false;
    relay1_state = !relay1_state;
    digitalWrite(relay1, relay1_state ? LOW : HIGH);
    delay(200);  // Debounce
  }
  
  // Similar for other buttons...
}
```

## RadioHead Library Details

### What It Does
RadioHead is a comprehensive RF communication library supporting many different RF modules and protocols.

### Supported Hardware
- 433MHz ASK/OOK modules
- nRF24L01+
- RFM69/RFM95/RFM96
- LoRa modules
- CC1101
- And many more

### Installation

**Method 1: Arduino Library Manager**
1. Arduino IDE → Sketch → Include Library → Manage Libraries
2. Search "RadioHead"
3. Install "RadioHead" by Mike McCauley

**Method 2: Manual Installation**
1. Copy `libraries/RadioHead` folder
2. Paste into `Arduino/libraries/` folder
3. Restart Arduino IDE

### Basic Usage (ASK Module)

```cpp
#include <RH_ASK.h>
#include <SPI.h>  // Not used but required

RH_ASK driver;

void setup() {
  Serial.begin(9600);
  if (!driver.init())
    Serial.println("init failed");
}

void loop() {
  uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
  uint8_t buflen = sizeof(buf);
  
  if (driver.recv(buf, &buflen)) {
    // Message received
    Serial.print("Got: ");
    Serial.println((char*)buf);
  }
}
```

### Key Classes

**RH_ASK** - For ASK/OOK 433MHz modules  
**RH_NRF24** - For nRF24L01+  
**RH_RF69** - For RFM69  
**RH_RF95** - For LoRa  

### Features

**Reliable Datagram Delivery:**
- Automatic acknowledgments
- Retransmission on failure
- Duplicate detection

**Addressing:**
- Multi-node networks
- Routing capabilities
- Broadcast messages

**Error Detection:**
- CRC checking
- FEC (Forward Error Correction)
- Noise rejection

## Choosing the Right Library

### Use RM4 When:
- Working with 4-channel receivers
- Simple button press detection
- Minimal overhead needed
- RM4SG-M type modules
- Quick prototyping

### Use RadioHead When:
- Need reliable data transfer
- Working with various RF modules
- Require acknowledgments
- Need addressing/routing
- Advanced RF features
- Data packets (not just buttons)

### Use RCSwitch When:
- Generic 433MHz receivers
- Learning code remotes
- Wide remote compatibility
- Simple receive/transmit

## Library Comparison

| Feature | RM4 | RadioHead | RCSwitch |
|---------|-----|-----------|----------|
| **Complexity** | Low | High | Low |
| **Hardware** | 4-ch receiver | Many modules | Generic 433MHz |
| **Purpose** | Button reading | Data comm | Code learn/send |
| **Data Type** | Button codes | Packets | RF codes |
| **Reliability** | Basic | High (ACK) | Basic |
| **Learning Curve** | Easy | Moderate | Easy |

## Troubleshooting

### RM4 Issues

**Library Not Found:**
- Check installation path
- Restart Arduino IDE
- Verify library folder name

**Wrong Button Codes:**
- Check pin assignments
- Verify receiver wiring
- Test data pins with multimeter

**No Button Detection:**
- Verify receiver power
- Check data pin connections
- Test with LED on data pins

### RadioHead Issues

**Compilation Errors:**
- Update to latest version
- Check for SPI.h include
- Verify board selection

**No Messages Received:**
- Check frequency/bandwidth settings
- Verify antenna connection
- Check transmitter/receiver pairing

## Advanced Topics

### Power Management (RM4)
```cpp
// Enable receiver only when needed
pinMode(enablePin, OUTPUT);
digitalWrite(enablePin, HIGH);  // Power ON
delay(100);
int code = remote.buttonCode();
digitalWrite(enablePin, LOW);   // Power OFF
```

### Debouncing (RM4)
```cpp
int button = remote.buttonCode();
if (button != 0) {
  delay(200);  // Wait for button release
  while(remote.buttonCode() != 0) {
    delay(10);  // Wait for release
  }
  // Process button
}
```

### RadioHead Addressing
```cpp
RH_ASK driver;
RHReliableDatagram manager(driver, THIS_ADDRESS);

void setup() {
  manager.init();
}

void loop() {
  // Send to specific address
  manager.sendtoWait(data, len, TARGET_ADDRESS);
}
```

## Resources

### RM4
- GitHub: https://github.com/quadule/arduino-rm4
- Example: libraries/RM4/examples/

### RadioHead
- Website: http://www.airspayce.com/mikem/arduino/RadioHead/
- Documentation: Extensive in library folder
- Examples: libraries/RadioHead/examples/

### General RF
- Arduino RF Tutorial: arduino.cc/reference
- 433MHz Modules Guide: Various online resources

## Summary

- **RM4**: Best for simple 4-button remote control
- **RadioHead**: Best for reliable RF data communication
- **RCSwitch**: Best for learning/decoding RF codes

Choose based on your specific needs and hardware!
