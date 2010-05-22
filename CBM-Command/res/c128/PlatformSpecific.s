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

.export	_writeVdcRegister
.export	_readVdcRegister
.export _clearVdcScreen
.export _copyVdcScreen	; void  copyScreen(
						;		unsigned char srcHi,
						;		unsigned char trgHi)

READ:	STA $D600		; Put the value into the register 
RVR1:	BIT $D600		; Compare the top bit of the register
		BPL RVR1		; Branch if the top bit is low (0)		
		LDA $D601		; Get the result into the accumulator
		RTS

WRITE:	STX $D600		; Put the value into the register 
WVR1:	BIT $D600		; Compare the top bit of the register
		BPL WVR1		; Branch if the top bit is low (0)	
		STA $D601		; Store the accumulator in the register's value
		RTS

.proc _copyVdcScreen
		JSR pusha		; Store the accumulator

		; Write target address
		LDY #$00		; Offset for second of two parameters
		LDA (sp),y		; Load accumulator with parameter value
		LDX #18
		JSR WRITE		; Writes accumulator to register 18
		LDA #00			; Low bytes are at location 00
		INX				; Next register
		JSR WRITE		; Writes accumulator to register 19

		; Issue block copy command
		LDX #24			; Get value of register 24
		LDA #128		; Set bit 7 hi
		JSR WRITE		; Write register 24

		; Write source address
		LDY #$01		; Offset for first of two parameters
		LDA (sp),y		; Load accumulator with parameter value
		LDX #32
		JSR WRITE		; Writes accumulator to register 18
		LDA #00			; Low bytes are at location 00
		INX				; Next register
		JSR WRITE		; Writes accumulator to register 19
		
		; Set block size
		LDX #30			; block size register
		LDA #$00		; Full block size of 256 bytes
		JSR WRITE

		; Loop until executed 16 times
		LDY #$10		; Copy 16 blocks
CLRPAG:	JSR WRITE
		DEY
		BNE CLRPAG

		; We're done, clean up
		JSR incsp2
		RTS
.endproc


.proc _clearVdcScreen
		JSR pusha		; Store the accumulator

		; Set the start location
		LDY #$01		; Offset for first of two parameters
		LDA (sp),y		; Load accumulator with parameter value
		LDX #18
		JSR WRITE		; Writes accumulator to register 18

		LDY #$00		; Offset for the second of two parameters
		LDA (sp),y		; Store the parameter in the accumulator 
		INX				; Now we are on register 19
		JSR WRITE		; Write the accumulator to register 19

		; Set address to clear
		LDX #18			
		LDA #00
		JSR WRITE
		INX
		JSR WRITE

		; Clear the copy bit && Reverse Bit
		LDX #24			; Located in register 24
		;JSR READ		; Read it to accumulator
		;AND #$7F		; OR the accumulator
		LDA #$00
		JSR WRITE		; Write it back

		; Set data byte
		LDX #31			; Located in register 31
		JSR WRITE		; Set the register

		LDX #30			; Word count register?
		LDA #$00
		JSR WRITE

		LDY #$10
		LDA #00
CLRPAG:	JSR WRITE
		DEY
		BNE CLRPAG

		JSR incsp2
		RTS
.endproc

;------------------------
; Write A to VDC Register
; stored in X
.proc _writeVdcRegister
		JSR pusha		; Store the accumulator

		LDY #$01		; Offset for first of two parameters
		LDA (sp),y		; Load accumulator with parameter value
		TAX				; Copy accumulator to x

		LDY #$00		; Offset for the second of two parameters
		LDA (sp),y		; Store the parameter in the accumulator 

		JSR WRITE

		JSR	incsp2		; Finish our function
		RTS
.endproc

;-------------------------
; Read A from VDC Register
; stored in X
.proc _readVdcRegister
		JSR pusha		; Store the accumulator

		LDY #$00		; Offset for the parameter
		LDA (sp),y		; Store the parameter in the accumulator 

		JSR READ

		JSR incsp1		; Increment the stack pointer by 1
		RTS				; as the return value of the function?
.endproc
