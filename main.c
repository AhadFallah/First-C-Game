#include "./constants.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <time.h>
int game_is_running = FALSE;
SDL_Window *window = NULL;
SDL_Renderer *render = NULL;
int last_frame_time = 0;
struct ball {
  float x;
  float y;
  float width;
  float height;
} ball;
int init_window(void) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    fprintf(stderr, "Error initializing SDL\n");
    return FALSE;
  }
  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WIDTH, HEIGHT, SDL_WINDOW_BORDERLESS);
  if (!window) {
    fprintf(stderr, "Error while creating window\n");
    return FALSE;
  }
  render = SDL_CreateRenderer(window, -1, 0);
  if (!render) {
    fprintf(stderr, "Error while rendering");
    return FALSE;
  }
  return TRUE;
}
void process_input() {
  SDL_Event event;
  SDL_PollEvent(&event);
  switch (event.type) {
  case SDL_QUIT:
    game_is_running = FALSE;
    break;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_ESCAPE) {
      game_is_running = FALSE;
    }
  }
}
void destroy_window() {
  SDL_DestroyRenderer(render);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
void setup() {
  ball.x = 20;
  ball.y = 20;
  ball.width = 15;
  ball.height = 15;
}
void update() {
  // int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
  // if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
  //   SDL_Delay(time_to_wait);
  // }
  float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

  last_frame_time = SDL_GetTicks();
  ball.x += 70 * delta_time;
  ball.y += 50 * delta_time;
}
void renderer() {
  SDL_SetRenderDrawColor(render, 0, 0, 0, 255);
  SDL_RenderClear(render);
  SDL_Rect rect_ball = {
      ball.x,
      ball.y,
      ball.width,
      ball.height,
  };
  SDL_SetRenderDrawColor(render, 255, 255, 255, 255);
  SDL_RenderFillRect(render, &rect_ball);

  SDL_RenderPresent(render);
}

int main(void) {
  game_is_running = init_window();
  setup();
  while (game_is_running) {
    process_input();
    update();
    renderer();
  }
  return 0;
}
