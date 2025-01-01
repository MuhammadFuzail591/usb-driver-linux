#include <linux/usb.h>
#include <linux/module.h>





static int __init usb_driv_init(void){

    int result;
    printk(KERN_INFO "Module is initialised\n");

}

module_init(usb_driv_init);

static void __exit usb_driv_exit(void){
     printk(KERN_INFO "Module is exited\n");
}

module_exit(usb_driv_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("muhammad_fuzail");
MODULE_DESCRIPTION("USB Detection Driver");