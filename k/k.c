/*
 * Copyright (c) LSE
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY LSE AS IS AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL LSE BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <k/kstd.h>
#include <stdio.h>

#include "multiboot.h"
#include "idt.h"
#include "gdt.h"
#include "PIC.h"
#include "PIT.h"
#include "driver.h"

void enable_sti(void)
{
  asm volatile ("sti");
}

void enable_cli(void)
{
  asm volatile ("cli");
}

void k_main(unsigned long magic, multiboot_info_t *info)
{
	(void)magic;
	(void)info;

	init_driver();
	puts("Serial Com 1 OK");

	init_gdt();
	puts("gdt Initialized");

	init_pic();
	puts("PIC Initialized");

	init_idt();
	puts("idt Initialized");

	init_pit();
	puts("PIT Initialized");

	enable_sti();

	for (;;)
	  asm volatile ("hlt");
}
