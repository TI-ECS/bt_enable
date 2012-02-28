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
#include <linux/delay.h>
#include <linux/gpio.h>

/* Enabling GPIO for WL1271's Bluetooth, which is TWL4030's GPIO 13 */
#define OMAP3EVM_WL1271_BT_EN_GPIO ( OMAP_MAX_GPIO_LINES + 13 )

static int __init gpio_test_init(void)
{
	pr_info("WL1271: BT Power Enable\n");
	if (gpio_request(OMAP3EVM_WL1271_BT_EN_GPIO, "wl1271 BT Enable") < 0) {
		pr_err(KERN_ERR "Failed to request BT_EN GPIO\n");
		return -1;
	}

	gpio_direction_output(OMAP3EVM_WL1271_BT_EN_GPIO, 1);

	/* reset pulse to the BT controller */
	usleep_range(150, 220);
	gpio_set_value_cansleep(OMAP3EVM_WL1271_BT_EN_GPIO, 0);
	usleep_range(150, 220);
	gpio_set_value_cansleep(OMAP3EVM_WL1271_BT_EN_GPIO, 1);
	usleep_range(150, 220);
	gpio_set_value_cansleep(OMAP3EVM_WL1271_BT_EN_GPIO, 0);
	usleep_range(150, 220);
	gpio_set_value_cansleep(OMAP3EVM_WL1271_BT_EN_GPIO, 1);
	usleep_range(1, 2);

	return 0;
}

static void __exit gpio_test_exit(void)
{
	pr_info("WL1271: BT Power Disable\n");
	gpio_set_value_cansleep(OMAP3EVM_WL1271_BT_EN_GPIO, 0);
	gpio_free(OMAP3EVM_WL1271_BT_EN_GPIO);
}



module_init(gpio_test_init);
module_exit(gpio_test_exit);
MODULE_LICENSE("GPL");
