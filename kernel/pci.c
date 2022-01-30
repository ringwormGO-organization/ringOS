#include <stdint.h>

#include "pci.h"
#include "basic.h"

void EnumareteFunc(uint64_t dev_addr,uint64_t func,void print(const char*,uint64_t length))
{
    uint64_t offset = func << 12;
    uint64_t busadr = dev_addr + offset;
    DeviceHeader* pci_dev = (DeviceHeader*)busadr;
    if(pci_dev->DeviceID == 0) return;
    if(pci_dev->DeviceID == 0xFFFF) return;
    char vendorid[8];
    char deviceid[8];
    itoa(pci_dev->VendorID,vendorid,16);
    itoa(pci_dev->DeviceID,deviceid,16);
    print(vendorid,8);
    print(" ",1);
    print(deviceid,8);
    print((const char*)'\n',1);

}

void EnumerateDevice(uint64_t bus_addr,uint64_t dev,void print(const char*,uint64_t length))
{
    uint64_t offset = dev << 15;
    uint64_t busadr = bus_addr + offset;
    DeviceHeader* pci_dev = (DeviceHeader*)busadr;
    if(pci_dev->DeviceID == 0) return;
    if(pci_dev->DeviceID == 0xFFFF) return;
    for(uint64_t function = 0;function < 8;function++)
    {
        EnumareteFunc(busadr,function,print);
    }

}

void EnumerateBus(uint64_t base_addr,uint64_t bus,void print(const char*,uint64_t length))
{
    uint64_t offset = bus << 20;
    uint64_t busadr = base_addr + offset;
    DeviceHeader* pci_dev = (DeviceHeader*)busadr;
    if(pci_dev->DeviceID == 0) return;
    if(pci_dev->DeviceID == 0xFFFF) return;
    for(uint64_t device = 0;device < 32;device++)
    {
        EnumerateDevice(busadr,device,print);
    }

}

void EnumeratePCI(MCFGHeader* mfghdr,void print(const char*,uint64_t length))
{
    int entries = ((mfghdr->header.len) - sizeof(ACPI_SDTHeader)) / sizeof(DevConfig);
    for(int k = 0;k < entries;k++)
    {
        DevConfig* newdev = (DevConfig*) ((uint64_t)mfghdr + sizeof(MCFGHeader) + ((sizeof(DevConfig)) * k));
        for(uint64_t bus = newdev->start_bus;bus < newdev->end_bus;bus++)
        {
            EnumerateBus((uint64_t)newdev,bus,print);
        }
    }
}