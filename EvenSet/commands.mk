# Standard compile commands.

C.o:
		$(CC) $< $(CFLAGS) -c -o $@

.cxx.o:
		$(CC) $< $(CFLAGS) -c -o $@      

.cpp.o:
		$(CC) $< $(CFLAGS) -c -o $@

.C :
		$(CC) $< $(LDFLAGS) $(CLIBS) $(FLIBS) -o $@

.cxx :
		$(CC) $< $(LDFLAGS) $(CLIBS) $(FLIBS) -o $@		

.cpp :
		$(CC) $< $(LDFLAGS) $(CLIBS) $(FLIBS) -o $@

.f.o :
		$(F77) $< -c -o $@
