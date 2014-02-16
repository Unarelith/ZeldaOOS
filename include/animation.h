/*
 * =====================================================================================
 *
 *       Filename:  animation.h
 *
 *    Description:  Animation system for sprites
 *
 *        Version:  1.0
 *        Created:  16/01/2014 20:06:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef ANIMATION_H_
#define ANIMATION_H_

struct s_animation
 {
  uint16_t size;
  uint16_t delay;
  
  bool     playing;
  
  t_timer  *timer;
  
  struct s_animation *next;
  
  uint8_t *animation_table;
 };

typedef struct s_animation t_animation;

t_animation *animation_new(uint16_t size, uint8_t *animation_table, uint16_t delay);
void animation_free(t_animation *animation);

#endif // ANIMATION_H_
