# Lab-2-


#Part 2
 External interrupts works by telling the CPU what to do after a physical action is done to the board (such as pushing a button). 
 For example, you press a button connected to a pin and that changes the voltage using either a pull up or pull down resistor. Which can cause a rising edge (low to high) or a falling edge (high to low) or even sometimes both. This singal then gets passed down to an EXTI and NVIC. The EXTI detects what kind of edge change happened and matches the designated pin to an interrupt line. Then, the NVIC decides if the interrupt is allowed to go through to the CPU and which priority it has. If it goes through the CPU stops whatever its doing, saves its progress thus far, and executes whatever is on the ISR function, the previous program is put on pending. After the function finishes the pending flag is cleared and the CPU runs where it left off in main.


 video 
 #Part 3
 Explain how timer interrupt works.
 A timer interrupt works as a signal that is sent to (CPU) at regular, timed intervals. Its similar to that of an  alarm clock that forces the processor to stop whatever its working on (just a pause), run an ISR function, and then return to what it was doing. A timer interrrupt differs from that of an external interrupt becuase a timer triggers internally at regulated intervals that reaches a preset value, whereas an external interrupt is triggered outside the CPU by a physical peripheral conencted to a specific pin. 

 Calculate the timer frequency. Show the process: 
 16 MHZ =  16 million cycles per second
 1KHZ = 1000 cycles per second 

 fCK_CNT = 16,000,000 / (PSC + 1)

 16,000,000/ (PSC + 1) = 1000 or 1kHz want so 1 cycle is 1ms
 PSC = 15999

time = PSC + 1/ftimer * ( ARR + 1) 
want time = 1s, and since 1 cycle is 1ms, 1000 would be 1s

(15999 + 1)(ARR + 1) / 16,000,000 = 1s
ARR = 999
 
which gives us 1000 ticks, which is 1 second
 

 #Part 4
 Video 