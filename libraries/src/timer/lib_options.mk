# This library will be made by linking timer1.rel, timer3.rel and timer4.rel.
LIB_RELS := libraries/src/timer/timer1.rel libraries/src/timer/timer3.rel # libraries/src/timer/timer4.rel

# When those rel (object) files are compiled, there will be a
# special preprocessor flag to specify which UART to use.
libraries/src/timer/timer1.rel : C_FLAGS += -DTIMER1
libraries/src/timer/timer3.rel : C_FLAGS += -DTIMER3
#libraries/src/timer/timer4.rel : C_FLAGS += -DTIMER4

# The rel files will be compiled from timer1.c, timer3.c and timer4.c,
# which will both be copies of core/timer.c.
libraries/src/timer/timer1.c : libraries/src/timer/core/timer.c
	$(CP) $< $@
	
libraries/src/timer/timer3.c : libraries/src/timer/core/timer.c
	$(CP) $< $@

#libraries/src/timer/timer4.c : libraries/src/timer/core/timer.c
#	$(CP) $< $@

TARGETS += libraries/src/timer/timer1.c libraries/src/timer/timer3.c # libraries/src/timer/timer4.c
