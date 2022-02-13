#include "pci.h"
#include "string.h"
#include <stdint.h>

void EnumareteFunc(uint64_t dev_addr, uint64_t func)
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

}

void EnumerateDevice(uint64_t bus_addr, uint64_t dev)
{
    uint64_t offset = dev << 15;
    uint64_t busadr = bus_addr + offset;
    DeviceHeader* pci_dev = (DeviceHeader*)busadr;
    if(pci_dev->DeviceID == 0) return;
    if(pci_dev->DeviceID == 0xFFFF) return;
    for(uint64_t function = 0;function < 8;function++)
    {
        EnumareteFunc(busadr,function);
    }

}

void EnumerateBus(uint64_t base_addr, uint64_t bus)
{
    uint64_t offset = bus << 20;
    uint64_t busadr = base_addr + offset;
    DeviceHeader* pci_dev = (DeviceHeader*)busadr;
    if(pci_dev->DeviceID == 0) return;
    if(pci_dev->DeviceID == 0xFFFF) return;
    for(uint64_t device = 0;device < 32;device++)
    {
        EnumerateDevice(busadr,device);
    }

}
void EnumeratePCI(MCFGHeader* mfghdr)
{
    int entries = ((mfghdr->header.len) - sizeof(ACPI_SDTHeader)) / sizeof(DevConfig);
    for(int k = 0; k < entries; k++)
    {
        DevConfig* newdev = (DevConfig*) ((uint64_t)mfghdr + sizeof(MCFGHeader) + ((sizeof(DevConfig)) * k));
        for(uint64_t bus = newdev->start_bus;bus < newdev->end_bus;bus++)
        {
            EnumerateBus((uint64_t)newdev, bus);
        }
    }
}