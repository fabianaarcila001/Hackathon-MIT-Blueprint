import pygame

pygame.init()


screen_width, screen_height = 680 ,330
screen = pygame.display.set_mode((screen_width, screen_height))

bg = pygame.image.load("Forest.png")

character_UP = pygame.image.load('characterUP_scaled_2x_pngcrushed.png')
character_DOWN = pygame.image.load('characterDOWN_scaled_2x_pngcrushed.png')

hallu_1 = pygame.image.load('Hallucination1.png')
hallu_2 = pygame.image.load('Hallucination2.png')
hallu_3 = pygame.image.load('Hallucination3.png')

character_UP = pygame.transform.scale(character_UP, (character_UP.get_width() * 2, character_UP.get_height() * 2))
character_DOWN = pygame.transform.scale(character_DOWN, (character_DOWN.get_width() * 2, character_DOWN.get_height() * 2))


animation_frames = [character_UP, character_DOWN]
current_frame = 0


clock = pygame.time.Clock()

x, y = screen_width // 2, screen_height // 2  


delta_time = 0.1


running = True
while running:
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    screen.blit(bg, (0, 0))

    
    current_frame = (current_frame + 1) % len(animation_frames)


    screen.blit(animation_frames[current_frame], (x, y))

    
    x += 50 * delta_time  
    if x > screen_width: 
        x = -animation_frames[current_frame].get_width()

    pygame.display.flip()

    delta_time = clock.tick(60) / 1000.0 

pygame.quit()





