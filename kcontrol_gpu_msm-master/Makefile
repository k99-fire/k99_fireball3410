KERNEL_BUILD := /work1/a5it_backup/HTC/build-andro/kernel_compare/infernal-k99_3410_remake-base/

obj-m += kcontrol_gpu_msm.o

all:
ifneq ($(wildcard mach-msm),) 
	rm mach-msm
endif
ifneq ($(wildcard gpu_msm),) 
	rm gpu_msm
endif
	ln -s $(KERNEL_BUILD)arch/arm/mach-msm/ mach-msm
	ln -s $(KERNEL_BUILD)drivers/gpu/msm/ gpu_msm
	make -C $(KERNEL_BUILD) M=$(PWD) modules
	$(CROSS_COMPILE)strip --strip-debug kcontrol_gpu_msm.ko

clean:
ifneq ($(wildcard mach-msm),) 
	rm mach-msm
endif
ifneq ($(wildcard gpu_msm),) 
	rm gpu_msm
endif
	make -C $(KERNEL_BUILD) M=$(PWD) clean 2> /dev/null
	rm -f modules.order *~ *.o
