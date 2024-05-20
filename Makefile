PROJECT=hp41
CC=gcc
INCDIR=
INCS=
LIBDIR=
LIBS=-lm
DEFS=
OBJS= \
	add.o \
	addnumber.o \
	arcl.o \
	asto.o \
	aton.o \
	aview.o \
	cf.o \
	cle.o \
	clearflag.o \
	clrg.o \
	debug.o \
	dec.o \
	div.o \
	dse.o \
	eminus.o \
	eng.o \
	eplus.o \
	ereg.o \
	exec.o \
	fact.o \
	fcqc.o \
	fix.o \
	flagset.o \
	format.o \
	fractional.o \
	fs.o \
	fsqc.o \
	hms.o \
	hmsminus.o \
	hmsplus.o \
	hr.o \
	init.o \
	integer.o \
	isg.o \
	isize.o \
	iszero.o \
	main.o \
	mean.o \
	message.o \
	mod.o \
	mul.o \
	normalize.o \
	ntoa.o \
	oct.o \
	programbyte.o \
	rcl.o \
	recallnumber.o \
	rnd.o \
	sci.o \
	sdev.o \
	setflag.o \
	setx.o \
	sf.o \
	shownumber.o \
	showstatregs.o \
	sto.o \
	storenumber.o \
	sub.o \
	tenscompliment.o \
	tointeger.o \
	tone.o \
	view.o \

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

.c.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm *.o
	-rm $(PROJECT)

