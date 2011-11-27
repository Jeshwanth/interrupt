/*
 * =====================================================================================
 *
 *       Filename:  gpio_interrupt.c
 *
 *    Description:  basic interrupt trial program
 *
 *        Version:  1.0
 *        Created:  11/27/11 10:04:25
 *       Revision:  none
 *       Compiler:  gcc
 *       Platform:  BB-xM-RevC, Ubuntu 3.0.4-x3
 *
 *         Author:  Tom Xue (), tom.xue@nokia.com
 *        Company:  Nokia
 *
 * =====================================================================================
 */
#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

#include <linux/interrupt.h>  
#include <linux/gpio.h>	//OMAP_GPIO_IRQ
#include <plat/mux.h>	//omap_cfg_reg
#include <linux/irq.h>	//IRQ_TYPE_LEVEL_LOW

MODULE_LICENSE("GPL");

//MMC2_DAT6, P9-pin5, system default GPIO input with pullup
#define OMAP3_GPIO138          (138)

static irqreturn_t my_interrupt(){
	printk(KERN_ALERT "my_interrupt executed!\n");
}

static int hello_init(void) {
	int ret;
	/*
	omap_cfg_reg(OMAP3_GPIO138);
	ret = gpio_request(OMAP3_GPIO138, "OMAP3_GPIO138");
	if(ret < 0)
		printk(KERN_ALERT "gpio_request failed!\n");
		
	gpio_direction_input(OMAP3_GPIO138);
	*/
	int irq = OMAP_GPIO_IRQ(OMAP3_GPIO138);	//irq33 <-> GPIO module 5: includes gpio_138
	irq_set_irq_type(irq, IRQ_TYPE_LEVEL_LOW);
	enable_irq(gpio_to_irq(OMAP3_GPIO138));
	
	ret = request_irq(irq, my_interrupt, IRQF_DISABLED, "my_interrupt", NULL);
	if (ret==0)
        printk(KERN_ALERT "request_irq success!\n");
    else
        printk(KERN_ALERT "request_irq fail!\n"); 
		
    printk(KERN_ALERT "Hello, Tom Xue! From inside kernel driver!\n");
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_INFO "Goodbye, Tom Xue! From inside kernel driver!\n");
}

module_init(hello_init);
module_exit(hello_exit);

