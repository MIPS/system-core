/*
 * NOTE: these atomic operations are SMP safe
 */

	.text
	.align

	.global android_atomic_write

	.global android_atomic_inc
	.global android_atomic_dec

	.global android_atomic_add
	.global android_atomic_and
	.global android_atomic_or

 	.global android_atomic_swap

	.global android_atomic_cmpxchg

/*
 * ----------------------------------------------------------------------------
 * android_atomic_write
 * input: a0=value, a1=address
 * output: void
 */

android_atomic_write:
	.ent	android_atomic_write
	sw	$a0,($a1)
	j	$ra
	.end	android_atomic_write

/*
 * ll/sc and branch prediction
 * The obvious implementation for an ll/sc sequence is:
 * 1: 	ll	rx,(ry)
 * 	...
 * 	sc	rx,(ry)
 * 	beqz	rx,1b	# ll/sc failed so retry
 *
 * sc rarely fails, but branch prediction normally assumes
 * backwards branches will be taken.
 * To avoid the penalty of a mispredicted branch it is worth making the
 * conditional branch go forwards and move the mispredict penalty to the
 * (unlikely) sc failure.
 */

/*
 * ----------------------------------------------------------------------------
 * android_atomic_inc
 * input: a0 = address
 * output: v0 = old value
 */

android_atomic_inc:
	.ent	android_atomic_inc
1:	ll	$v0,($a0)
	addu	$t0,$v0,1
	sc	$t0,($a0)
	beqz	$t0,2f
	j	$ra
2:	b	1b
	.end	android_atomic_inc

/*
 * ----------------------------------------------------------------------------
 * android_atomic_dec
 * input: a0=address
 * output: v0 = old value
 */

android_atomic_dec:
	.ent	android_atomic_dec
1:	ll	$v0,($a0)
	subu	$t0,$v0,1
	sc	$t0,($a0)
	beqz	$t0,2f
	j	$ra
2:	b	1b
	.end	android_atomic_dec

 /*
 * ----------------------------------------------------------------------------
 * android_atomic_add
 * input: a0=value, a1=address
 * output: v0 = old value
 */

android_atomic_add:
	.ent	android_atomic_add
1:	ll	$v0,($a1)
	addu	$t0,$v0,$a0
	sc	$t0,($a1)
	beqz	$t0,2f
	j	$ra
2:	b	1b
	.end	android_atomic_add

/*
 * ----------------------------------------------------------------------------
 * android_atomic_and
 * input: a0=value, a1=address
 * output: v0 = old value
 */

android_atomic_and:
	.ent	android_atomic_and
1:	ll	$v0,($a1)
	and	$t0,$v0,$a0
	sc	$t0,($a1)
	beqz	$t0,2f
	j	$ra
2:	b	1b
	.end	android_atomic_and

/*
 * ----------------------------------------------------------------------------
 * android_atomic_or
 * input: a0=value, a1=address
 * output: v0 = old value
 */

android_atomic_or:
	.ent	android_atomic_or
1:	ll	$v0,($a1)
	or	$t0,$v0,$a0
	sc	$t0,($a1)
	beqz	$t0,2f
	j	$ra
2:	b	1b
	.end	android_atomic_or

/*
 * ----------------------------------------------------------------------------
 * android_atomic_swap
 * input: a0=value, a1=address
 * output: v0 = old value
 */

android_atomic_swap:
	.ent	android_atomic_swap
1:	move	$t0,$a0
	ll	$v0,($a1)
	sc	$t0,($a1)
	beqz	$t0,2f
	j	$ra
2:	b	1b
	.end	android_atomic_swap

/*
 * ----------------------------------------------------------------------------
 * android_atomic_cmpxchg
 * input: a0=oldvalue, a1=newvalue, a2=address
 * output: v0 = 0 (xchg done) or non-zero (xchg not done)
 */

android_atomic_cmpxchg:
	.ent	android_atomic_cmpxchg
1:	ll	$t0,($a2)
	.set	noreorder
	bne	$t0,$a0,9f	/* fail: oldvalue != *address */
	 li	$v0,1
	.set	reorder
	move	$t1,$a1
	sc	$t1,($a2)
	beqz	$t1,2f
	move	$v0,$zero
9:	j	$ra
2:	b	1b
	.end	android_atomic_cmpxchg

/*
 * ----------------------------------------------------------------------------
 * android_atomic_cmpxchg_64
 * input: r0-r1=oldvalue, r2-r3=newvalue, arg4 (on stack)=address
 * output: r0 = 0 (xchg done) or non-zero (xchg not done)
 */
/* TODO: NEED IMPLEMENTATION FOR THIS ARCHITECTURE */
