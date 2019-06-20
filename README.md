# Rasterizer
Rasterizer example.

This is my implementation of the Rasterization using SFML 2.5.1, glm 0.9.9.5 and assimp 4.0.1.

The exercise I engaged myself in is to reproduce the GPU rasterization process in the CPU.

Goals :
  - Load any 3D models to rasterize into the scene. (Done)
  - Move in 3D the camera using both keyboard and mouse to navigate. (Done)
  - Rasterize all the 3D models. (In progress)
  - Use Blinn-Phong lighting on all 3D models in the scenes.

I am using an sf::Uint8 array furnished by SFML.
Since my goal is to reproduce as close as possible all the process of the rasterization I managed all the pixels myself which includes the 4 bytes composing a pixel.

After processing the entire screen, I send the pixel array into an sf::Image, transform it into an sf::Texture to finally being sent into my very and only sf::Sprite which will be rendered by the SFML.
This last part is handled by SFML itself, all the work is done with the pixel array who represents the very final image to render, all the rest with the sf::Image and all that stuff are to render the pixel array accordingly.

That actually represents a sort of bottleneck (out of the rasterization process on the CPU) because I recreate an sf::Image every frame, which internally create his own pixel array based on mine.
