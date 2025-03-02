import time
import pyfirmata

# Specify the correct serial port for your Arduino
PORT = '/dev/tty.usbmodem14101'  # Change this based on your system
board = pyfirmata.Arduino(PORT)

# Joystick Pins
x_pin = board.get_pin('a:0:i')
y_pin = board.get_pin('a:1:i')
sw_pin = board.get_pin('d:2:i')

# LED Pins
red_leds = [board.get_pin(f'd:{pin}:p') for pin in [13, 12, 11, 10, 9, 8]]
white_leds = [board.get_pin(f'd:{pin}:o') for pin in [7, 6, 5, 4]]

# Buzzer Pin
buzzer = board.get_pin('d:3:o')

# Brightness Control
brightness = 0
fade_amount = 5

# Game State
ENDGAME = False

print("Type 'end' to trigger the light show!")

def set_red_leds(brightness):
    for led in red_leds:
        led.write(brightness / 255)  # Normalize brightness (0 to 1)

def set_white_leds(state):
    for led in white_leds:
        led.write(state)

def play_tone(frequency, duration):
    buzzer.write(1)
    time.sleep(duration / 1000)
    buzzer.write(0)
    time.sleep(duration / 1500)

def horror_sting():
    for freq in range(800, 100, -50):
        play_tone(freq, 100)

def deep_pulses():
    for _ in range(3):
        play_tone(60, 500)
        time.sleep(0.2)

def trigger_light_show():
    global ENDGAME
    deep_pulses()
    horror_sting()
    play_tone(50, 1500)

    set_white_leds(1)
    for value in range(0, 256, fade_amount):
        set_red_leds(value)
        time.sleep(0.03)

    set_white_leds(0)
    for value in range(255, -1, -fade_amount):
        set_red_leds(value)
        time.sleep(0.03)

    set_red_leds(0)
    set_white_leds(0)
    time.sleep(0.5)

    for _ in range(10):
        set_red_leds(1)
        set_white_leds(0)
        time.sleep(0.5)
        set_red_leds(0)
        set_white_leds(1)
        time.sleep(0.5)

    set_red_leds(0)
    set_white_leds(0)

    # Final Phase - Fast Blinking Effect
    for _ in range(20):
        set_red_leds(1)
        set_white_leds(1)
        time.sleep(0.1)
        set_red_leds(0)
        set_white_leds(0)
        time.sleep(0.1)

    # Ending Glow Effect
    for value in range(0, 256, fade_amount):
        set_red_leds(value)
        time.sleep(0.02)
    for value in range(255, -1, -fade_amount):
        set_red_leds(value)
        time.sleep(0.02)

    ENDGAME = False
    print("Light show completed! Type 'end' to restart.")

while True:
    x_data = x_pin.read()
    y_data = y_pin.read()
    sw_data = sw_pin.read()

    if x_data is None or y_data is None:
        continue

    x_data *= 1023
    y_data *= 1023

    command = input("Enter command: ").strip().lower()

    if command == 'end':
        ENDGAME = True
        print("ENDGAME mode activated! Light show starting...")

    if not ENDGAME:
        if y_data > 600:
            print("Answer: No")
        elif y_data < 400:
            print("Answer: Yes")
        elif x_data > 600:
            print("Moving RIGHT")
        elif x_data < 400:
            print("Moving LEFT")
        else:
            print("Character is IDLE")
        time.sleep(0.2)

    if ENDGAME:
        trigger_light_show()