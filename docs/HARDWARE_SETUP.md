# Hardware Setup Guide

Complete wiring and setup instructions for RF receiver testing.

## Hardware Requirements

### Essential Components
- Arduino Uno or Nano
- 4-channel RF receiver module (RM4SG-M or similar)
- 4-button RF remote (433MHz)
- Jumper wires
- USB cable (for Arduino)
- Breadboard (optional)

### Optional Components
- LEDs (for status indication)
- 330Ω resistors (for LEDs)
- Relay module (for testing control)
- Multimeter (for troubleshooting)

## RF Receiver Modules

### 4-Channel Receiver (RM4SG-M Type)

**Pin Configuration:**
```
┌─────────────────┐
│  RF Receiver    │
│                 │
│  VCC  GND       │
│  D0   D1        │
│  D2   D3        │
│  Vt   Ant       │
└─────────────────┘
```

**Pin Descriptions:**
- **VCC**: Power (5V)
- **GND**: Ground
- **D0-D3**: Data outputs (one goes HIGH per button)
- **Vt**: Valid transmission indicator
- **Ant**: Antenna connection

## Wiring Diagrams

### Setup 1: RFTest_RCSwitch Configuration

This setup uses both RCSwitch and 4-channel receiver:

```
Arduino Uno          RF Receiver (Generic)
-----------          --------------------
5V               →   VCC
GND              →   GND
Pin 2            →   DATA (for RCSwitch)


Arduino Uno          4-Channel Receiver
-----------          ------------------
5V               →   VCC
GND              →   GND
Pin 8            →   D0
Pin 9            →   D1
Pin 10           →   D2
Pin 11           →   D3
Pin 12           →   Vt


Arduino Uno          LED (Optional)
-----------          ---------------
Pin 13           →   Anode (+) via 330Ω
GND              →   Cathode (-)
```

### Setup 2: RFTest_RM4 Configuration

This setup uses RM4 library with 4-channel receiver:

```
Arduino Uno          4-Channel Receiver
-----------          ------------------
Pin 13           →   VCC (enable control)
GND              →   GND
Pin 2            →   D0
Pin 10           →   D1
Pin 11           →   D2
Pin 12           →   D3
```

**Note**: Pin 13 is used to enable/disable the receiver

### Setup 3: With Relay Module (Optional)

Add relay control for testing actual loads:

```
Arduino Uno          Relay Module
-----------          ------------
5V               →   VCC
GND              →   GND
Pin 14           →   IN1 (Relay 1)
Pin 15           →   IN2 (Relay 2)
Pin 16           →   IN3 (Relay 3)
Pin 17           →   IN4 (Relay 4)


Relay Module         Load
------------         ----
COM              →   AC/DC Hot
NO               →   Load (Motor, Lamp, etc.)
```

## Step-by-Step Wiring

### For Beginners

**Step 1: Power Connections**
1. Connect RF receiver VCC to Arduino 5V
2. Connect RF receiver GND to Arduino GND
3. **Verify**: Receiver should get warm (normal)

**Step 2: Data Connections**
1. D0 → Arduino Pin 2 (or 8 for RCSwitch setup)
2. D1 → Arduino Pin 10 (or 9 for RCSwitch setup)
3. D2 → Arduino Pin 11 (or 10 for RCSwitch setup)
4. D3 → Arduino Pin 12 (or 11 for RCSwitch setup)

**Step 3: Optional Connections**
1. Vt → Arduino Pin 12 (if using RCSwitch setup)
2. Enable → Arduino Pin 13 (if using RM4 setup)

**Step 4: LED (Optional)**
1. LED anode (+, long leg) → Pin 13 via 330Ω resistor
2. LED cathode (-, short leg) → GND

## RF Remote Pairing

### Initial Pairing (If Required)

Some RF receivers require pairing with the remote:

1. **Power on receiver** (may need specific button sequence)
2. **Press pairing button** on receiver (if present)
3. **Press button on remote** within 5 seconds
4. **LED indicator** should flash to confirm pairing

**Note**: Most simple 4-channel receivers are pre-paired with their remotes

### Testing Pairing

1. Upload test sketch to Arduino
2. Open Serial Monitor (9600 baud)
3. Press button on remote
4. Should see button code in Serial Monitor
5. If no response, check wiring and power

## Antenna Setup

### RF Receiver Antenna

**Options:**
1. **Wire Antenna**: 17.3cm wire for 433MHz
2. **Coil Antenna**: Pre-made spiral antenna
3. **PCB Antenna**: Built into some receivers

**Installation:**
1. Solder wire to antenna pad
2. Keep wire straight and vertical
3. Avoid near metal objects
4. Length = 69mm for quarter-wave, 173mm for half-wave

**Range Improvement:**
- Use proper length antenna
- Orient vertically
- Keep away from metal
- Use shielded cable if needed

## Power Considerations

### Current Requirements

**4-Channel Receiver:**
- Active: 10-20mA
- Standby: 5-10mA

**Arduino:**
- Uno: 50mA typical
- With LED: +20mA

**Relay Module (if used):**
- Per relay: 70-100mA

**Total**: 100-300mA depending on configuration

### Power Supply

**USB Power**: Adequate for receiver + Arduino  
**External Power**: Required if using multiple relays  
**Battery Power**: 9V battery works, but short life under load

## Testing Hardware

### Visual Checks

- [ ] All wires firmly connected
- [ ] No shorts between adjacent pins
- [ ] Receiver getting warm (normal)
- [ ] LED on Arduino board lit
- [ ] No smoke or burning smell

### Electrical Checks (Multimeter)

**Voltage Checks:**
- VCC pin: 4.8-5.2V
- GND pin: 0V
- Data pins (idle): 0V or floating
- Data pins (active): 3-5V

**Continuity Checks:**
- Arduino 5V to receiver VCC: Continuous
- Arduino GND to receiver GND: Continuous
- Data pins: Verify correct pin mapping

### Functional Checks

**Test 1: Receiver Power**
1. Connect power only
2. Receiver should get slightly warm
3. Current draw: 10-20mA

**Test 2: Data Pins**
1. Upload test sketch
2. Open Serial Monitor
3. Press remote button
4. Verify data pin goes HIGH
5. Check correct pin number

**Test 3: Code Reception**
1. Press each button on remote
2. Verify unique code for each
3. Record codes for reference

## Common Wiring Mistakes

### Mistake 1: Wrong Pin Numbers
**Problem**: Code uses Pin 2, but wired to Pin 3  
**Solution**: Match pin numbers in code to physical wiring

### Mistake 2: Swapped VCC and GND
**Problem**: Receiver gets very hot immediately  
**Solution**: Disconnect power immediately, check polarity

### Mistake 3: Missing Ground
**Problem**: Erratic operation, random codes  
**Solution**: Ensure common ground between Arduino and receiver

### Mistake 4: Floating Inputs
**Problem**: Random noise on data pins  
**Solution**: Enable INPUT_PULLUP or use external pull-down resistors

### Mistake 5: Antenna Issues
**Problem**: Very short range (< 1 meter)  
**Solution**: Add proper antenna, check connections

## Range Testing

### Test Procedure

1. **Baseline Test**: Press button 1 meter away
2. **Distance Test**: Gradually move away
3. **Note Maximum Range**: Where response becomes unreliable
4. **Obstacle Test**: Test through walls/doors
5. **Interference Test**: Test near WiFi, microwave, etc.

### Typical Ranges

| Condition | Range |
|-----------|-------|
| Clear line of sight | 20-50m |
| Through one wall | 10-20m |
| Through multiple walls | 5-10m |
| High interference | 1-5m |

### Improving Range

- Add better antenna
- Raise receiver higher
- Reduce obstacles
- Move away from interference sources
- Use higher transmit power (remote)

## Troubleshooting

### No Response from Remote

**Check:**
- [ ] Receiver powered (5V)
- [ ] Remote has battery
- [ ] Correct pin wiring
- [ ] Remote paired (if needed)
- [ ] Antenna connected

**Test:**
- Press button near receiver (< 1m)
- Check LED on remote (if present)
- Try different remote

### Erratic Behavior

**Possible Causes:**
- Loose connections
- Power supply issues
- Interference from other devices
- Multiple remotes on same frequency
- Weak remote battery

**Solutions:**
- Check all connections
- Use fresh remote battery
- Move away from interference
- Try different frequency (if adjustable)

### Wrong Button Codes

**Issue**: Button A shows code for Button B

**Check:**
- Pin mapping in code vs. physical wiring
- Data pin order (D0-D3)
- Cross-wiring during assembly

**Solution**: Match code pins to actual wiring

## Safety Notes

- Never work on powered circuits
- Disconnect power before wiring changes
- Verify polarity before power-on
- Use current-limited power supply for first test
- Watch for overheating components

## Additional Hardware Options

### RF Signal Analyzer
- RTL-SDR dongle
- View RF spectrum
- Identify interference
- Measure signal strength

### Logic Analyzer
- Capture data pin transitions
- Analyze timing
- Debug protocol issues
- Verify button codes

## Next Steps

After successful hardware setup:
1. Upload test sketch
2. Record button codes
3. Test range
4. Develop control logic
5. Integrate with production code

## Hardware Checklist

Before testing:
- [ ] All power connections verified
- [ ] All data pins wired correctly
- [ ] Pin numbers match code
- [ ] Antenna connected
- [ ] Remote has battery
- [ ] No shorts or loose wires
- [ ] Test code uploaded
- [ ] Serial Monitor open (9600 baud)

Ready to test!
