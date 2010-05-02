;/**************************************************************
;Copyright (c) 2010, Payton Byrd
;All rights reserved.
;
;Redistribution and use in source and binary forms, with or 
;without modification, are permitted provided that the following 
;conditions are met:
;
;* Redistributions of source code must retain the above 
;  copyright notice, this list of conditions and the following 
;  disclaimer.
;
;* Redistributions in binary form must reproduce the above 
;  copyright notice, this list of conditions and the following 
;  disclaimer in the documentation and/or other materials 
;  provided with the distribution.
;
;* Neither the name of Payton Byrd nor the names of its 
;  contributors may be used to endorse or promote products 
;  derived from this software without specific prior written 
;  permission.
;
;THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND 
;CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, 
;INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
;MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
;DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
;CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
;SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
;NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
;LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) 
;HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
;CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
;OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
;EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;***************************************************************/

.setcpu		"6502"
.smart		on
.autoimport	on
.case		on
.importzp	sp, sreg, regsave, regbank, tmp1, ptr1, ptr2
.macpack	longbranch

.export _checkDrive

.proc _checkDrive
		JSR		pusha		; Store the accumulator

		JSR		decsp4

		; Let's get the drive number, we use it last
		LDY		#$04		; SP(4) is the third parameter
		LDA		(sp),y		; Get the value from the stack
		LDY		#$01		; SP(1) is the drive variable
		STA		(sp),y		; Store the value in the variable

		; Let's get the length, we use it first
		LDY		#$07		; SP(7) is the first parameter
		LDA		(sp),y		; Retrieve the parameter
		LDY		#$00		; SP(0) is the length variable
		STA		(sp),y		; Store A to the variable
		PHA					; Push A (length)

		; Let's get the command, we use it next to last
		LDY		#$06		; SP(6,5) is the second parameter
		JSR		ldaxysp		; Loads A and X from SP
		LDY		#$02		; SP(2,3) is the string variable
		JSR		staxysp		; Save the string pointer to SP(2)
		
		; Prepare for the SETNAM call
		PHA					; A -> Stack (high)
		TXA					; X -> A (low)
		TAY					; A -> Y (low)
		PLA					; Stack -> A (high)
		TAX					; A -> X (high)
		PLA					; Stack -> A (length)
			; At this point, A should have the length,
			; X should have the high byte of the string pointer
			; and Y should have the low byte of the string pointer
		JSR		$FFBD		; SETNAM

		; Prepare for the SETLFS
		LDY		#$01		; Variable for drive number
		LDA		(sp),y		; Load A with drive number
		TAX					; A -> X (drive number)
		LDY		#15			; 15 -> Y (secondary address)
			; At this point, A and X should both have 
			; the drive number and Y should have secondary
			; address of 15.
		JSR		$FFBA		; SETLFS (drive, drive, 15)

		; Call open and handle the results;
		JSR		$FFC0		; OPEN
		PHA					; Push result to stack

		; Close our open channel
		LDY		#$01		; Get the drive number again
		LDA		(sp),y		; from sp(1)
		JSR		$FFC3		; CLOSE

		; Get the error status back into A
error:	PLA					; Retrieve result from stack		

		; We're done, go home.
		JSR incsp8			; Increment the SP 
		RTS					; We're done.
.endproc