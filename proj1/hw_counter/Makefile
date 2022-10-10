KDIR = /lib/modules/`uname -r`/build

build: build_r0 build_r3

build_r0: hack_cr4.c
	make -C $(KDIR) M=`pwd`

build_r3: mat_mul.c 
	gcc -o mat_mul mat_mul.c

clean:
	make -C $(KDIR) M=`pwd` clean
	rm -f *.o* mat_mul
