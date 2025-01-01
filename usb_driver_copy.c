#include <linux/usb.h>
#include <linux/module.h>


static struct usb_device *device;

static struct usb_device_id skel_table[] = {
    {USB_DEVICE(0x125f, 0xdb8a)},
    {}
};

static int skel_probe(struct usb_interface *interface, const struct usb_device_id *id){

    struct usb_host_interface *iface_desc;
    struct usb_endpoint_descriptor *endpoint;

    int i;

    iface_desc = interface->cur_altsetting;

    printk(KERN_INFO "Pen i/f %d now probed: {%04X:%04X}\n",
        iface_desc->desc.bInterfaceNumber,
        id->idVendor,
        id->idProduct
    );

    printk(KERN_INFO "ID->bNumEndpoints: %02X\n", iface_desc->desc.bNumEndpoints);
    printk(KERN_INFO "ID->bNumEndpoints: %02X\n", iface_desc->desc.bInterfaceClass);

    for(i = 0; i < iface_desc->desc.bNumEndpoints; i++){
        endpoint = &iface_desc->endpoint[i].desc;
        printk(KERN_INFO "ED[%d]->bEndpointAddress: 0x%02X\n", i, endpoint->bEndpointAddress);
        printk(KERN_INFO "ED[%d]->bmAttributes: 0x%02X\n", i, endpoint->bmAttributes);
        printk(KERN_INFO "ED[%d]->wMaxPacketSize: 0x%04X [%d]\n", i, endpoint->wMaxPacketSize,endpoint->wMaxPacketSize);
    }
    
    device = interface_to_usbdev(interface);
    return 0;
}

static void skel_disconnect(struct usb_interface *interface)
{
    usb_put_dev(device);
    printk(KERN_INFO "Pen drive removed\n");
}

static struct usb_driver skel_driver = {
    .name = "usb_driver_copy",
    .probe = skel_probe,
    .disconnect = skel_disconnect,
    .id_table = skel_table,
    .supports_autosuspend = 1,
};

static int __init usb_driv_init(void){

    int result;
    result = usb_register(&skel_driver);
    if(result < 0){
        pr_err("USB registeration failed with %s\n", skel_driver.name);
        return -1;
    }
    printk(KERN_INFO "Module is initialised\n");
    return 0;

}

module_init(usb_driv_init);

static void __exit usb_driv_exit(void){
     printk(KERN_INFO "Module is exited\n");
}

module_exit(usb_driv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("muhammad_fuzail");
MODULE_DESCRIPTION("USB Detection Driver");