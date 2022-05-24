obj-m=char_dev.o

all:
	make -C /lib/modules/5.17.2/build/ M=$(PWD) modules

clean:
	make -C /lib/modules/5.17.2/build M=$(PWD) clean
