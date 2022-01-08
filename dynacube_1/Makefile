CC	=	gcc
CXX	=	g++
CFLAGS	=	-g -O2 -nostdinc -fno-builtin -ffreestanding #-D__DEBUG__
CXXFLAGS=	-g -O2 -nostdinc -fno-builtin -ffreestanding -fno-rtti -fno-exceptions #-D__DEBUG__

OPTIONS= -save-temps -w 
INCLUDE=.

ASM= nasm -f elf
LD= ld
LDSCRIPT= krnl.ld

OBJS	=dstart.o main.o kstdio.o kasm.o kint.o kdesc.o kinit.o kio.o string.o stdlib.o keyboard.o mm.o proc.o kpit.o kpic.o ktime.o ktask.o queue.o message.o zorder.o gui.o container.o window.o frame.o floppy.o fat12.o mouse.o svga.o vm86.o stack.o graphics.o component.o font.o hashmap.o list.o button.o text.o textarea.o label.o paintcomp.o startmenu.o cursor.o utility.o folderview.o icon.o client_fs.o menubar.o menu.o clipboard.o cmos.o

#Rules
%.o:%.c
	$(CC) $(CFLAGS) $(OPTIONS) -I $(INCLUDE) -c -o $@ $<

%.o:%.cpp
	$(CXX) $(CXXFLAGS) $(OPTIONS) -I $(INCLUDE) -c -o $@ $<

all: kernel apps sync_all

kernel: D0.x

apps: run timeset explorer null_proc calc editor

D0.x: $(OBJS)
	${LD} -T ${LDSCRIPT} $(OBJS) -o $@
	#Symbol Dumping
	nm -s D0.x | sort > D0Sym.txt
	#Stripping
	strip -s -R .comment D0.x
	#Listing
	objdump -s D0.x > D0dump.txt
	#Gzip Compression
	gzip D0.x
	mv D0.x.gz D0.x
	cp D0.x ./mnt
	rm D0.x
	@echo Dynacube Kernel Compilation Complete

dstart.o:
	$(ASM) dstart.asm

explorer: explorer.c
	$(CC) $(CFLAGS) $(OPTIONS) -I $(INCLUDE) -c $@.c -o $@.o
	${LD} -T binary.ld $@.o string.o stdlib.o -o $@
	cp $@ ./mnt
	rm $@

null_proc: null_proc.c
	$(CC) $(CFLAGS) $(OPTIONS) -I $(INCLUDE) -c $@.c -o $@.o
	${LD} -T binary.ld $@.o string.o stdlib.o -o $@
	cp $@ ./mnt
	rm $@

calc: calc.c
	$(CC) $(CFLAGS) $(OPTIONS) -I $(INCLUDE) -c $@.c -o $@.o
	${LD} -T binary.ld $@.o string.o stdlib.o -o $@
	cp $@ ./mnt
	rm $@

timeset: timeset.c
	$(CC) $(CFLAGS) $(OPTIONS) -I $(INCLUDE) -c $@.c -o $@.o
	${LD} -T binary.ld $@.o string.o stdlib.o -o $@
	cp $@ ./mnt
	rm $@

run: run.c
	$(CC) $(CFLAGS) $(OPTIONS) -I $(INCLUDE) -c $@.c -o $@.o
	${LD} -T binary.ld $@.o string.o stdlib.o -o $@
	cp $@ ./mnt
	rm $@

editor: editor.c
	$(CC) $(CFLAGS) $(OPTIONS) -I $(INCLUDE) -c $@.c -o $@.o
	${LD} -T binary.ld $@.o string.o stdlib.o client_fs.o -o $@
	cp $@ ./mnt
	rm $@

install: all

sync_all:
	sync

clean:
	-rm -fr *.o *.i *.ii *.s
	-rm -f explorer null_proc run timeset calc
