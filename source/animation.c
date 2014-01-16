/*
 * =====================================================================================
 *
 *       Filename:  animation.c
 *
 *    Description:  Animaition system for sprites
 *
 *        Version:  1.0
 *        Created:  16/01/2014 20:08:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <nds.h>
#include "timer.h"
#include "animation.h"

t_animation   *animation_new(uint16_t size,
                             uint8_t  *animation_table,
                             uint16_t delay)
 {
  t_animation *animation;
  
  animation = (t_animation *)malloc(sizeof(t_animation));
  animation->timer = timer_new();
  animation->size = size;
  animation->delay = delay;
  animation->animation_table = animation_table;
  animation->next = NULL;
  
  return animation;
 }

void animation_free(t_animation *animation)
 {
  if(animation->next)
   {
    animation_free(animation->next);
   }
  if(animation)
   {
    if(animation->animation_table)
     {
      free(animation->animation_table);
     }
    free(animation);
   }
 }

