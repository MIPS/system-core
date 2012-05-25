/*
 * Copyright (C) 2010 The android Open Source Project
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

	.text
	.align

        /*
         * void android_memset16(uint16_t* dst, uint16_t value, size_t size);
         */

	.extern _memset16
	.global	android_memset16
	.type   android_memset16, @function
android_memset16:
        .ent	android_memset16
	.set	noreorder
	.cpload $t9
	.set	reorder
	la	$t9,_memset16
	j	$t9
        .end	android_memset16
	.size	android_memset16,.-android_memset16

        /*
         * void android_memset32(uint32_t* dst, uint32_t value, size_t size);
         */
	.extern _memset32
	.global android_memset32
	.type	android_memset32, @function
android_memset32:
        .ent	android_memset32
	.set	noreorder
	.cpload $t9
	.set	reorder
	la	$t9,_memset32
	j	$t9
        .end	android_memset32
	.size	android_memset32,.-android_memset32

