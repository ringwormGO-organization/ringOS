#include <efi.h>
#include <efilib.h>
#include <elf.h>

typedef unsigned long long size_t;

typedef struct {
	unsigned int* BaseAddress;
	size_t BufferSize;
	unsigned int Width;
	unsigned int Height;
	unsigned int PixelsPerScanLine;
} Framebuffer;

#define PSF1_MAGIC0 0x36
#define PSF1_MAGIC1 0x04

#define BMP_MAGIC0 'B'
#define BMP_MAGIC1 'M'

typedef struct 
{
	unsigned char magic[2];
	unsigned char mode;
	unsigned char charsize;
} PSF1_HEADER;

typedef struct 
{
	PSF1_HEADER* psf1_Header;
	void* glyphBuffer;
} PSF1_FONT;

typedef struct __attribute__((packed))
{
    unsigned char magic[2];
    uint32_t fileSize;
    uint16_t reserved0;
    uint16_t reserved1;
    uint32_t offset;
} BMPHeader;

typedef struct __attribute__((packed))
{
    uint32_t dibSize;
    uint32_t width; // LONG
    uint32_t height; // LONG
    uint16_t planesCount;
    uint16_t bitsPerPixel;
    uint32_t compressionMethod;
    uint32_t bitmapSize;
    uint32_t printWidth; // LONG
    uint32_t printHeight; // LONG
    uint32_t colorCountInColorPalette;
    uint32_t importantColors;
    uint32_t redBitMask;
    uint32_t greenBitMask;
    uint32_t blueBitMask;
    uint32_t alphaBitMask;
    uint32_t colorSpace;
    unsigned char endpoints[36];
    uint32_t gammaRed;
    uint32_t gammaGreen;
    uint32_t gammaBlue;
//    uint32_t intent;
//    uint32_t profileData;
//    uint32_t profileSize;
//    uint32_t reserved;
} BITMAPV4HEADER;

typedef struct
{
    uint32_t width;
    uint32_t height;
    uint32_t bitmapSize;
    uint32_t* bitmapBuffer;
    uint32_t redBitMask;
    uint32_t greenBitMask;
    uint32_t blueBitMask;
    uint32_t alphaBitMask;
} BMPImage;

typedef struct 
{
	Framebuffer* framebuffer;
	PSF1_FONT* psf1_Font;
	BMPImage* bmpImage;
	EFI_MEMORY_DESCRIPTOR* mMap;
	UINTN mMapSize;
	UINTN mMapDescSize;
	void* rsdp;
	void* SMBIOS;
	void* LLFS;
} BootInfo;

Framebuffer framebuffer;
Framebuffer* InitializeGOP()
{
	EFI_GUID gopGuid = EFI_GRAPHICS_OUTPUT_PROTOCOL_GUID;
	EFI_GRAPHICS_OUTPUT_PROTOCOL* gop;
	EFI_STATUS status;

	status = uefi_call_wrapper(BS->LocateProtocol, 3, &gopGuid, NULL, (void**)&gop);
	if(EFI_ERROR(status))
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
		Print(L"Unable to locate GOP\n\r");
		return NULL;
	}
	else
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
		Print(L"GOP located\n\r");
	}

	framebuffer.BaseAddress = (void*)gop->Mode->FrameBufferBase;
	framebuffer.BufferSize = gop->Mode->FrameBufferSize;
	framebuffer.Width = gop->Mode->Info->HorizontalResolution;
	framebuffer.Height = gop->Mode->Info->VerticalResolution;
	framebuffer.PixelsPerScanLine = gop->Mode->Info->PixelsPerScanLine;

	return &framebuffer;
	
}

EFI_FILE* LoadFile(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
	EFI_FILE* LoadedFile;

	EFI_LOADED_IMAGE_PROTOCOL* LoadedImage;
	SystemTable->BootServices->HandleProtocol(ImageHandle, &gEfiLoadedImageProtocolGuid, (void**)&LoadedImage);

	EFI_SIMPLE_FILE_SYSTEM_PROTOCOL* FileSystem;
	SystemTable->BootServices->HandleProtocol(LoadedImage->DeviceHandle, &gEfiSimpleFileSystemProtocolGuid, (void**)&FileSystem);

	if (Directory == NULL)
	{
		FileSystem->OpenVolume(FileSystem, &Directory);
	}

	EFI_STATUS s = Directory->Open(Directory, &LoadedFile, Path, EFI_FILE_MODE_READ, EFI_FILE_READ_ONLY);
	if (s != EFI_SUCCESS){
		return NULL;
	}
	return LoadedFile;

}

PSF1_FONT* LoadPSF1Font(EFI_FILE* Directory, CHAR16* Path, EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable)
{
	EFI_FILE* font = LoadFile(Directory, Path, ImageHandle, SystemTable);
	if (font == NULL) return NULL;

	PSF1_HEADER* fontHeader;
	SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(PSF1_HEADER), (void**)&fontHeader);
	UINTN size = sizeof(PSF1_HEADER);
	font->Read(font, &size, fontHeader);

	if (fontHeader->magic[0] != PSF1_MAGIC0 || fontHeader->magic[1] != PSF1_MAGIC1){
		return NULL;
	}

	UINTN glyphBufferSize = fontHeader->charsize * 256;
	if (fontHeader->mode == 2) { //512 glyph mode
		glyphBufferSize = fontHeader->charsize * 512;
	}

	void* glyphBuffer;
	{
		font->SetPosition(font, sizeof(PSF1_HEADER));
		SystemTable->BootServices->AllocatePool(EfiLoaderData, glyphBufferSize, (void**)&glyphBuffer);
		font->Read(font, &glyphBufferSize, glyphBuffer);
	}

	PSF1_FONT* finishedFont;
	SystemTable->BootServices->AllocatePool(EfiLoaderData, sizeof(PSF1_FONT), (void**)&finishedFont);
	finishedFont->psf1_Header = fontHeader;
	finishedFont->glyphBuffer = glyphBuffer;
	return finishedFont;

}

BMPImage* LoadBMPImage(EFI_FILE* directory, CHAR16* path, EFI_HANDLE image, EFI_SYSTEM_TABLE* SystemTable, BootInfo* bootInfo)
{
    /* Load BMP file */
    EFI_FILE* bmpFile = LoadFile(directory, path, image, SystemTable);
    if (bmpFile == NULL)
    {
        ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
        Print(L"An error occurred while attempting to load BMP file!\nLoading file from media!\n\r");
        return NULL;
    }

    // Store BMP header in memory
    BMPHeader* bmpHeader;
    UINTN headerSize = sizeof(BMPHeader);
    BS->AllocatePool(EfiLoaderData, headerSize, (void**)&bmpHeader);
    bmpFile->Read(bmpFile, &headerSize, bmpHeader);

    /*  Check if BMP file has valid header using magic bytes */
    if (bmpHeader->magic[0] != BMP_MAGIC0 || bmpHeader->magic[1] != BMP_MAGIC1)
    {
        ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
        Print(L"An error occurred while attempting to load BMP file!\nBMP Header invalid!\n\r");
        return NULL;
    }

    UINTN dibSize;
    bmpFile->SetPosition(bmpFile, headerSize);
    UINTN dibSizeSize = 4;
    bmpFile->Read(bmpFile, &dibSizeSize, &dibSize);
    if (dibSize != 124 && dibSize != 108) // BITMAPV4HEADER or BITMAPV5HEADER
    {
        ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
        Print(L"Invalid or unsupported BMP DIB header\n\r");
        return NULL;
    }

    /* 
	* The BITMAPV5HEADER has the same structure as the BITMAPV4HEADER except for 4 uint32_t at the end
    * that are not necessary for the rendering of the bitmap. (for now)
    * As such, we only need to read the first 108 bytes of the BITMAPV5HEADER. 
	*/
    if (dibSize == 124) dibSize = 108;
    BITMAPV4HEADER* dibHeader;
    bmpFile->SetPosition(bmpFile, headerSize);
    BS->AllocatePool(EfiLoaderData, dibSize, (void**)&dibHeader);
    bmpFile->Read(bmpFile, &dibSize, dibHeader);

    if (dibHeader->bitsPerPixel != 32)
    {
        ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
        Print(L"Unsupported BPP in BMP file\n\r");
        return NULL;
    }

    if (dibHeader->compressionMethod != 3) // BI_BITFIELDS
    {
        ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
        Print(L"Unsupported BMP file compression format\n\r");
        return NULL;
    }

    uint32_t* bitmapBuffer;
    UINTN bitmapSize = dibHeader->bitmapSize;
    bmpFile->SetPosition(bmpFile, bmpHeader->offset);
    BS->AllocatePool(EfiLoaderData, dibHeader->bitmapSize, (void**)&bitmapBuffer);

    Print(L"Reading BMP file contents...\n\r");
    bmpFile->Read(bmpFile, &bitmapSize, bitmapBuffer);
    Print(L"Successfully read BMP File contents into memory.\n\r");

    BMPImage* bmpImage;
    BS->AllocatePool(EfiLoaderData, sizeof(BMPImage), (void**)&bmpImage);

    bmpImage->width = dibHeader->width;
    bmpImage->height = dibHeader->height;
    bmpImage->bitmapSize = dibHeader->bitmapSize;
    bmpImage->bitmapBuffer = bitmapBuffer;
    bmpImage->alphaBitMask = dibHeader->alphaBitMask;
    bmpImage->redBitMask = dibHeader->redBitMask;
    bmpImage->greenBitMask = dibHeader->greenBitMask;
    bmpImage->blueBitMask = dibHeader->blueBitMask;

    bootInfo->bmpImage = bmpImage;
    return bmpImage;
}

int memcmp(const void* aptr, const void* bptr, size_t n){
	const unsigned char* a = aptr, *b = bptr;
	for (size_t i = 0; i < n; i++){
		if (a[i] < b[i]) return -1;
		else if (a[i] > b[i]) return 1;
	}
	return 0;
}


UINTN strcmp(CHAR8* a, CHAR8* b, UINTN length){
	for (UINTN i = 0; i < length; i++){
		if (*a != *b) return 0;
	}
	return 1;
}

EFI_STATUS efi_main (EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
	InitializeLib(ImageHandle, SystemTable);
	Print(L"ringOS (C)2021-2022\nCredits: Poncho\n\r");
	Print(L"FirmwareVendor: ");
	Print(SystemTable->FirmwareVendor);
	Print(L" \n\r");
	Print(L" \n\r");

	EFI_FILE* Kernel = LoadFile(NULL, L"kernel.elf", ImageHandle, SystemTable);
	if (Kernel == NULL)
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
		Print(L"Could not load kernel \n\r");
	}
	else
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
		Print(L"Kernel Loaded Successfully \n\r");
	}

	EFI_FILE* llfs = LoadFile(NULL, L"ram.llfs", ImageHandle, SystemTable);
	if (llfs == NULL)
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
		Print(L"Could not load llfs file \n\r");
	}
	else
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
		Print(L"llfs file loaded successfully \n\r");
	}



	Elf64_Ehdr header;
	{
		UINTN FileInfoSize;
		EFI_FILE_INFO* FileInfo;
		Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, NULL);
		SystemTable->BootServices->AllocatePool(EfiLoaderData, FileInfoSize, (void**)&FileInfo);
		Kernel->GetInfo(Kernel, &gEfiFileInfoGuid, &FileInfoSize, (void**)&FileInfo);

		UINTN size = sizeof(header);
		Kernel->Read(Kernel, &size, &header);
	}

	if (memcmp(&header.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0)
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
		Print(L"Kernel ELF Magic is invalid.\r\n");
	}
	else
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
		Print(L"Kernel ELF Magic is valid.\n\r");
	}

	if (header.e_ident[EI_CLASS] != ELFCLASS64)
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
		Print(L"Kernel is not a 64 bit ELF binary.\r\n");
	}
	else
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
		Print(L"Kernel is ELF 64bit binary.\n\r");
	}

	if (header.e_ident[EI_DATA] != ELFDATA2LSB)
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
		Print(L"Kernel data segment endianess is incorrect.\r\n");
	}
	else
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
		Print(L"Kernel data segment is correct.\n\r");
	}

	if (header.e_type != ET_EXEC)
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
		Print(L"Kernel ELF Binary type is not an executable.\r\n");
	}
	else
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
		Print(L"Kernel ELF Binray type is executable.\n\r");
	}

	if (header.e_machine != EM_X86_64)
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
		Print(L"Kernel machine type is not valid for this system\r\n");
	}
	else
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
		Print(L"Kernel machine type is valid for this system.\n\r");
	}

	if (header.e_version != EV_CURRENT)
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
		Print(L"Kernel ELF version mismatch\r\n");
	}
	else
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
		Print(L"Kernel ELF version is valid.\n\r");
	}
	
	Elf64_Phdr* phdrs;
	{
		Kernel->SetPosition(Kernel, header.e_phoff);
		UINTN size = header.e_phnum * header.e_phentsize;
		SystemTable->BootServices->AllocatePool(EfiLoaderData, size, (void**)&phdrs);
		Kernel->Read(Kernel, &size, phdrs);
	}

	for (
		Elf64_Phdr* phdr = phdrs;
		(char*)phdr < (char*)phdrs + header.e_phnum * header.e_phentsize;
		phdr = (Elf64_Phdr*)((char*)phdr + header.e_phentsize)
	)
	{
		switch (phdr->p_type){
			case PT_LOAD:
			{
				int pages = (phdr->p_memsz + 0x1000 - 1) / 0x1000;
				Elf64_Addr segment = phdr->p_paddr;
				SystemTable->BootServices->AllocatePages(AllocateAddress, EfiLoaderData, pages, &segment);

				Kernel->SetPosition(Kernel, phdr->p_offset);
				UINTN size = phdr->p_filesz;
				Kernel->Read(Kernel, &size, (void*)segment);
				break;
			}
		}
	}

	ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
	Print(L"Kernel Loaded\n\r");
	

	PSF1_FONT* newFont = LoadPSF1Font(NULL, L"zap-light16.psf", ImageHandle, SystemTable);
	if (newFont == NULL)
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
		Print(L"Font is not valid or is not found\n\r");
	}
	else
	{
		ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
		Print(L"Font found. Char size = %d\n\r", newFont->psf1_Header->charsize);
	}


	Framebuffer* newBuffer = InitializeGOP();


	EFI_MEMORY_DESCRIPTOR* Map = NULL;
	UINTN MapSize, MapKey;
	UINTN DescriptorSize;
	UINT32 DescriptorVersion;
	{
		
		SystemTable->BootServices->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion);
		SystemTable->BootServices->AllocatePool(EfiLoaderData, MapSize, (void**)&Map);
		SystemTable->BootServices->GetMemoryMap(&MapSize, Map, &MapKey, &DescriptorSize, &DescriptorVersion);

	}

	//Get RSDP
	EFI_CONFIGURATION_TABLE* configTable = SystemTable->ConfigurationTable;
	void* rsdp = NULL; 
	EFI_GUID Acpi2TableGuid = ACPI_20_TABLE_GUID;

	for (UINTN index = 0; index < SystemTable->NumberOfTableEntries; index++){
		if (CompareGuid(&configTable[index].VendorGuid, &Acpi2TableGuid)){
			if (strcmp((CHAR8*)"RSD PTR ", (CHAR8*)configTable->VendorTable, 8)){
				rsdp = (void*)configTable->VendorTable;
				//break;
			}
		}
		configTable++;
	}

	//Get SMBIOS
	configTable = SystemTable->ConfigurationTable;
	void* SMBIOS = NULL;
	EFI_GUID SMBIOSGUID = SMBIOS_TABLE_GUID;
	for(UINTN i = 0;i < SystemTable->NumberOfTableEntries;i++) {
		if(CompareGuid(&configTable[i].VendorGuid, &SMBIOSGUID)){
			if(strcmp((CHAR8*)"_SM_", (CHAR8*)configTable->VendorTable,4)) {
				SMBIOS = (void*)configTable->VendorTable;
				break;
			}
		}
			
		configTable++;
	}

	//Load LLFS
	UINTN llfsSize = 0xFFFFFF;
	void* llfsBuffer;
	SystemTable->BootServices->AllocatePool(EfiLoaderData, llfsSize, (void **)&llfsBuffer);
	llfs->Read(llfs, &llfsSize, llfsBuffer);

	BootInfo bootInfo;
	bootInfo.framebuffer = newBuffer;
	bootInfo.psf1_Font = newFont;
	bootInfo.mMap = Map;
	bootInfo.mMapSize = MapSize;
	bootInfo.mMapDescSize = DescriptorSize;
	bootInfo.rsdp = rsdp;
	bootInfo.SMBIOS = SMBIOS;
	bootInfo.LLFS = llfs;


	// Load BMP desktop background image
    BMPImage* bmpImage = LoadBMPImage(NULL, L"Picture.bmp", ImageHandle, SystemTable, &bootInfo);
    if (bmpImage == NULL)
    {
        ST->ConOut->SetAttribute(ST->ConOut, EFI_RED);
        Print(L"Could not load BMP image\n\r");
    }
    else
    {
        ST->ConOut->SetAttribute(ST->ConOut, EFI_GREEN);
        Print(L"BMP image loaded %dx%d\n\r", bmpImage->width, bmpImage->height);
    }

	void (*KernelStart)(BootInfo*) = ((__attribute__((sysv_abi)) void (*)(BootInfo*) ) header.e_entry);

	bootInfo.bmpImage = bmpImage;

	SystemTable->BootServices->ExitBootServices(ImageHandle, MapKey);

	KernelStart(&bootInfo);

	return EFI_SUCCESS; // Exit the UEFI application
}