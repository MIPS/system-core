/*
 * Copyright (C) 2006 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/*
 *  memset32_mips.S
 *
 */

	.text
	.align

	.global android_memset32
	.type	android_memset32, @function
	.global	android_memset16
	.type   android_memset16, @function

        /*
         * (Un)Optimized memset32 and memset16 for MIPS
         *
         * void android_memset16(uint16_t* dst, uint16_t value, size_t size);
         * void android_memset32(uint32_t* dst, uint32_t value, size_t size);
         *
         */

android_memset16:
        .ent	android_memset16

	.set	noreorder
	beqz	$a2,9f
	 srl	$a2,1

1:	sh	$a1,($a0)
	subu	$a2,1
	bnez	$a2,1b
	 addu	$a0,2
	.set reorder

9:	j	$ra
        .end	android_memset16
	.size	android_memset16,.-android_memset16

android_memset32:
        .ent	android_memset32
	.set	noreorder
	beqz	$a2,9f
	 srl	$a2,2

1:	sw	$a1,($a0)
	subu	$a2,1
	bnez	$a2,1b
	 addu	$a0,4
	.set reorder

9:	j	$ra
        .end	android_memset32
	.size	android_memset32,.-android_memset32
