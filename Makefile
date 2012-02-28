ifeq ($(KERNEL_DEBUGGER),y)
  EXTRA_CFLAGS += -g -O2
endif	
ifeq ($(DEBUG),y)
  EXTRA_CFLAGS += -DSDIO_DEBUG -O2
else
  EXTRA_CFLAGS += -O2
endif	

obj-m := gpio_en.o

PWD := $(shell pwd)
all:
	pwd
	@echo EXTRA_CFLAGS = $(EXTRA_CFLAGS)
	$(MAKE) CROSS_COMPILE=$(CROSS_COMPILE) ARCH=$(ARCH) EXTRA_CFLAGS="$(EXTRA_CFLAGS)" -C $(KERNEL_DIR) M=$(PWD) modules
install:
	install -d ${DEST_DIR}${BASE_LIB_DIR}/modules/${KRNL_VER}/kernel/drivers/bt_enable
	install -m 0755 ./gpio_en.ko ${DEST_DIR}${BASE_LIB_DIR}/modules/${KRNL_VER}/kernel/drivers/bt_enable
clean:
	rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions *.symvers
