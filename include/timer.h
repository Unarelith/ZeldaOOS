/*
 * =====================================================================================
 *
 *       Filename:  timer.h
 *
 *    Description:  Simple timer system using libnds
 *
 *        Version:  1.0
 *        Created:  06/01/2014 18:41:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#ifndef TIMER_H_
#define TIMER_H_

struct s_timer
 {
  uint16_t t;
  bool     started;
  uint16_t ticks;
 };

typedef struct s_timer t_timer;

void timer_system_init();

t_timer *timer_new();

void timer_stop(t_timer *tmr);
void timer_start(t_timer *tmr);
void timer_reset(t_timer *tmr);

uint16_t timer_get_time(t_timer *tmr);

#endif // TIMER_H_
