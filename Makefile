PROJECT=hp41
CC=gcc
INCDIR=
INCS=
LIBDIR=
LIBS=-lm
DEFS=
OBJS= \
	acos.o \
	add.o \
	addnumber.o \
	arcl.o \
	asin.o \
	asto.o \
	atan.o \
	aton.o \
	aview.o \
	bst.o \
	cat.o \
	cf.o \
	cle.o \
	clearflag.o \
	clrg.o \
	cos.o \
	dadd.o \
	ddiv.o \
	debug.o \
	dec.o \
	del.o \
	display.o \
	div.o \
	dmul.o \
	dse.o \
	dsub.o \
	eminus.o \
	eng.o \
	eplus.o \
	ereg.o \
	ex.o \
	exec.o \
	fact.o \
	fcqc.o \
	findend.o \
	findglobal.o \
	findnextglobal.o \
	findstart.o \
	fix.o \
	fixlinenumber.o \
	flagset.o \
	format.o \
	fractional.o \
	fromptr.o \
	fs.o \
	fsqc.o \
	gto2.o \
	gtoalpha.o \
	gotoline.o \
	gtoxeq.o \
	hms.o \
	hmsminus.o \
	hmsplus.o \
	hr.o \
	init.o \
	integer.o \
	isg.o \
	isize.o \
	iszero.o \
	ln.o \
	ln1plusx.o \
	main.o \
	mean.o \
	message.o \
	mod.o \
	mul.o \
	normalize.o \
	ntoa.o \
	oct.o \
	pack.o \
	programbyte.o \
	programline.o \
	programstep.o \
	prp.o \
	push.o \
	rcl.o \
	recallnumber.o \
	rnd.o \
	rtn.o \
	sci.o \
	sdev.o \
	setflag.o \
	setx.o \
	sf.o \
	shownumber.o \
	showstatregs.o \
	size.o \
	sin.o \
	skip.o \
	sqrt.o \
	sst.o \
	sto.o \
	storenumber.o \
	sub.o \
	tan.o \
	tenscompliment.o \
	tointeger.o \
	tone.o \
	toptr.o \
	view.o \
	ytox.o

$(PROJECT): $(OBJS)
	$(CC) $(DEFS) $(LIBDIR) $(OBJS) $(LIBS) -o $(PROJECT)

.c.o:
	$(CC) $(DEFS) $(INCDIR) $(INCS) -c $<

clean:
	-rm *.o
	-rm $(PROJECT)

