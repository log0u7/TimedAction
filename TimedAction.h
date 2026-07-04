/*
||
|| @file 	TimedAction.cpp
|| @version	2.1
|| @author	Alexander Brevig
|| @contact	alexanderbrevig@gmail.com
|| @updated by Glumgad, log0u7
||
|| @description
|| | Provide an easy way of triggering functions at a set interval
|| #
||
|| @license
|| | This library is free software; you can redistribute it and/or
|| | modify it under the terms of the GNU Lesser General Public
|| | License as published by the Free Software Foundation; version
|| | 2.1 of the License.
|| |
|| | This library is distributed in the hope that it will be useful,
|| | but WITHOUT ANY WARRANTY; without even the implied warranty of
|| | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
|| | Lesser General Public License for more details.
|| |
|| | You should have received a copy of the GNU Lesser General Public
|| | License along with this library; if not, write to the Free Software
|| | Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
|| #
||
*/

#ifndef TIMEDACTION_H
#define TIMEDACTION_H

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

class TimedAction {
  
  public:
    TimedAction(unsigned long interval,void (*function)());
    TimedAction(unsigned long prev,unsigned long interval,void (*function)());
	
	void reset();
	void disable();
	void enable();
	void check();
	
	void setInterval( unsigned long interval );

  private: 
    bool active;
    unsigned long previous;
    unsigned long interval;
    void (*execute)();
		
};

#endif

