/*
 * =====================================================================================
 *
 *       Filename:  timer.c
 *
 *    Description:  Simple timer system using libnds
 *
 *        Version:  1.0
 *        Created:  06/01/2014 18:52:26
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Quentin BAZIN, <quent42340@gmail.com>
 *        Company:  Deloptia
 *
 * =====================================================================================
 */
#include <nds.h>
#include "timer.h"

uint32_t os_time = 0;

s_timer   *timer_new()
 {
  s_timer *tmr;
  
  tmr = (s_timer *)malloc(sizeof(s_timer));
  tmr->t = os_time;
  tmr->started = false;
  tmr->ticks = 0;
  
  return tmr;
 }

void timer_stop(s_timer *tmr)
 {
  if(tmr->started)
   {
    tmr->started = false;
    tmr->ticks = os_time - tmr->t;
   }
 }

void timer_start(s_timer *tmr)
 {
  if(!tmr->started)
   {
    tmr->started = true;
    tmr->t = os_time - tmr->ticks;
   }
 }

void timer_reset(s_timer *tmr)
 {
  tmr->t = os_time;
  tmr->started = false;
  tmr->ticks = 0;
 }

void on_timer()
 {
  os_time++;
 }
 
void init_timers()
 {
  TIMER1_CR = 0;
  TIMER1_DATA = TIMER_FREQ_1024(1000);
  TIMER1_CR = TIMER_ENABLE | TIMER_DIV_1024 | TIMER_IRQ_REQ;
  irqSet(IRQ_TIMER1, on_timer);
  irqEnable(IRQ_TIMER1);
  os_time = 0;
 }

uint16_t timer_get_time(s_timer *tmr)
 {
  return (tmr->started)?(os_time - tmr->t):(tmr->ticks);
 }

