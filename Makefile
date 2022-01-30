gnu-efi:
	@git clone https://github.com/VanGutan/gnu-efi
	@mv ringOS-Beta17-bootloader gnu-efi/bootloader
	
kernel:
	@mv ringOS-Beta17 kernel
	
OVMFbin:
	@git clone https://github.com/VanGutan/ringOS-Beta14-OVMFTemplate
	@mv ringOS-Beta14-OVMFTemplate OVMFbin
