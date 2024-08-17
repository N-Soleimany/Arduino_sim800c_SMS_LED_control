
# SMS-Controlled Device using SIM800C

This project allows you to control an LED (or any other device) remotely using SMS commands via the SIM800C GSM module. The code is designed to turn an LED on or off based on the content of received SMS messages, but it can be easily adapted to control other devices or sensors such as temperature, humidity, etc.

## Features

- **SMS-based control:** The system receives SMS commands to control the LED or any other connected device.
- **Status Feedback:** After executing a command, the system sends a confirmation SMS to the sender.
- **Customizable Commands:** The keywords for controlling the LED (e.g., "LED ON", "LED OFF") can be customized to suit your needs.

## Requirements

- **Arduino Board**
- **SIM800C GSM Module**
- **LED or any other output device**
- **Jumper Wires**
- **SIM Card**

## Circuit Diagram

| Arduino Pin | SIM800C Pin |
|-------------|-------------|
| GND         | GND         |
| RX (Pin 8)  | TX          |
| TX (Pin 9)  | RX          |

Connect the LED to digital pin 13 on the Arduino.

## Installation

1. Clone the repository or download the ZIP file.
2. Open the project in the Arduino IDE.
3. Make sure you have the `BareBoneSim800` library installed. You can install it via the Arduino Library Manager.
4. Replace the placeholder phone number (`-------PhoneNumber------`) in the code with your own phone number.
5. Upload the code to your Arduino board.

## Usage

Once the setup is complete and the code is uploaded:

1. **Power up the system:** After the Arduino and SIM800C module are powered on, the system will send an SMS to the configured phone number indicating that the device is ready.
2. **Send Commands via SMS:**
   - Send `LED ON` to turn the LED on.
   - Send `LED OFF` to turn the LED off.
   - Send `EMPTY` to delete all received SMS messages from the SIM800C module.
3. The system will execute the command and send a confirmation SMS back to the sender.

## Customization

### Controlling Other Devices

You can modify the code to control other devices besides an LED. For example:
- **Temperature Control:** Replace the LED control code with commands to read or adjust a thermostat.
- **Relay Control:** Replace the digital pin output with a relay module to control higher power devices.

### Changing Commands

You can customize the SMS commands to anything you prefer. Simply change the strings `"LED ON"`, `"LED OFF"`, and `"EMPTY"` in the code to your desired commands.

## Troubleshooting

- **SIM800C Not Responding:** Ensure the SIM800C module is properly powered and connected. Double-check the RX and TX connections.
- **No SMS Received:** Verify that the SIM card is active, has SMS capabilities, and sufficient balance.
- **Device Not Controlling:** Check the connections to the LED or the controlled device.

