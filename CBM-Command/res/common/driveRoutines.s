;/***************************************************************
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

.import		popa, popax
.import		SETNAM, SETLFS, OPEN, CLOSE

.export		_checkDrive

.rodata
; The "soft-reset" DOS command returns a status message
; that indicates the drive model.
command:.byte	"ui"

.code
;
; unsigned char checkDrive(unsigned char drive);
;
.proc _checkDrive
		; Prepare for SETLFS.
		TAX					; A -> X (First address: device number)
		LDY		#15			; 15 -> Y (Second address: channel)
		TYA					; Y -> A (Logical file number)
			; At this point, X should have the drive number;
			; and, A and Y should have a secondary address of 15.
		JSR		SETLFS		; (15, drive, 15)

		; Prepare the DOS command.
		LDA		#.sizeof(command)
		LDX		#<command
		LDY		#>command
		JSR		SETNAM

		; Call open, and handle the result.
		JSR		OPEN
		BCS		error
		LDA		#<0
error:	PHA					; Push result to stack

		; Close our open channel
		LDA		#15			; Get the file number
		JSR		CLOSE

		; Get the error status back into A
		PLA					; Retrieve result from stack
;		LDX		#>0			; Promote it to int
		RTS					; We're done.
.endproc
