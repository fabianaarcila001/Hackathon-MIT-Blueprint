import pygame
import serial
import time

# Initialize Serial Connection (Replace `/dev/tty.usbmodem101` with your port)
ser = serial.Serial('/dev/tty.usbmodem101', 9600, timeout=1)
time.sleep(2)  # Wait for Arduino to initialize

pygame.init()

# Screen Setup
screen_width, screen_height = 680, 330
screen = pygame.display.set_mode((screen_width, screen_height))

bg = pygame.image.load("Forest.png")

character_UP = pygame.image.load('characterUP_scaled_2x_pngcrushed.png')
character_DOWN = pygame.image.load('characterDOWN_scaled_2x_pngcrushed.png')

hallu_1 = pygame.image.load('Hallucination1.png')
hallu_2 = pygame.image.load('Hallucination2.png')
hallu_3 = pygame.image.load('Hallucination3.png')

animation_frames = [character_UP, character_DOWN]
current_frame = 0

clock = pygame.time.Clock()

x, y = screen_width // 2, screen_height // 2  

delta_time = 0.1

hallucination_positions = [(200, 150), (400, 150), (600, 150)]
hallucination_images = [hallu_1, hallu_2, hallu_3]

choices = [
    ["Choice 1 for Hallucination 1", "Choice 2 for Hallucination 1"],
    ["Choice 1 for Hallucination 2", "Choice 2 for Hallucination 2"],
    ["Choice 1 for Hallucination 3", "Choice 2 for Hallucination 3"]
]

questions = [
    "What do you see here?",
    "What do you think is going on?",
    "Why is this happening to you?"
]

def display_choices(choice_list):
    font = pygame.font.Font(None, 36)
    y_offset = 100
    for idx, choice in enumerate(choice_list):
        text = font.render(choice, True, (255, 255, 255))
        screen.blit(text, (50, y_offset + idx * 40))

def display_question(question):
    font = pygame.font.Font(None, 36)
    text = font.render(question, True, (255, 255, 255))
    screen.blit(text, (50, 50))

running = True
hallucination_index = 0
question_displayed = False  # Keeps track if the question has been displayed

while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_1:
                print(f"You selected: {choices[hallucination_index][0]}")
                hallucination_index += 1
                question_displayed = False  
            elif event.key == pygame.K_2:
                print(f"You selected: {choices[hallucination_index][1]}")
                hallucination_index += 1
                question_displayed = False  

    screen.blit(bg, (0, 0))

    current_frame = (current_frame + 1) % len(animation_frames)
    screen.blit(animation_frames[current_frame], (x, y))

    if hallucination_index < len(hallucination_positions):
        halluc_x, halluc_y = hallucination_positions[hallucination_index]
        screen.blit(hallucination_images[hallucination_index], (halluc_x, halluc_y))

        if not question_displayed:
            display_question(questions[hallucination_index])
            question_displayed = True
        else:
            display_choices(choices[hallucination_index])
    else:
        break

    pygame.display.flip()

    delta_time = clock.tick(60) / 1000.0

pygame.quit()

# 🚨 Send "end" to Arduino when game is over
print("Game over! Sending 'end' to Arduino...")
ser.write(b"end\n")

# ✅ Wait for Arduino confirmation
while True:
    arduino_response = ser.readline().decode('utf-8').strip()
    if "Light show completed!" in arduino_response:
        print("Light show completed!")
        break

ser.close()
