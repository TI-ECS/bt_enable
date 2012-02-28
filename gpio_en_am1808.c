/*
 * gpio_en.c
 *
 * Kernel module to enable Bluetooth core on WL1271
 *
 * Copyright(c) 2010 Texas Instruments. All rights reserved.      
 * All rights reserved.                                                  
 *                                                                       
 * Redistribution and use in source and binary forms, with or without    
 * modification, are permitted provided that the following conditions    
 * are met:                                                              
 *                                                                       
 *  * Redistributions of source code must retain the above copyright     
 *    notice, this list of conditions and the following disclaimer.      
 *  * Redistributions in binary form must reproduce the above copyright  
 *    notice, this list of conditions and the following disclaimer in    
 *    the documentation and/or other materials provided with the         
 *    distribution.                                                      
 *  * Neither the name Texas Instruments nor the names of its            
 *    contributors may be used to endorse or promote products derived    
 *    from this software without specific prior written permission.      
 *                                                                       
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR 
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT      
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY 
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT   
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/interrupt.h>
#include <linux/ioport.h>
#include <mach/da8xx.h>
#include <mach/gpio.h>
#include <linux/delay.h>
#include <linux/gpio.h>

#define GPIO_BT_EN                        GPIO_TO_PIN(0, 15)


static int __init gpio_test_init(void)
{
	printk("Gpio value is :%d\n", GPIO_BT_EN);
	gpio_direction_output(GPIO_BT_EN, 0);
	msleep(100);
	gpio_direction_output(GPIO_BT_EN, 1);
	printk("WL1271: BT Enable\n");
	gpio_set_value(GPIO_BT_EN, 1);
	msleep(500);
	return 0;
}

static void __exit gpio_test_exit(void)
{
	printk("WL1271: BT Disable\n");
        gpio_set_value(GPIO_BT_EN, 0);
}



module_init(gpio_test_init);
module_exit(gpio_test_exit);
MODULE_LICENSE("GPL");
