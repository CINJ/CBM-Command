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

.export _FILE_MENU_COUNT
_FILE_MENU_COUNT: .byte $09

.export _FILE_MENU_WIDTH
_FILE_MENU_WIDTH: .byte $11

.export _FILE_MENU_ABOUT
_FILE_MENU_ABOUT: .asciiz "About CBM-Command"

.export _FILE_MENU_ABOUT_KEY
_FILE_MENU_ABOUT_KEY: .byte $41

.export _FILE_MENU_HELP
_FILE_MENU_HELP: .asciiz "Help"

.export _FILE_MENU_HELP_KEY
_FILE_MENU_HELP_KEY: .byte $48

.export _FILE_MENU_COPY
_FILE_MENU_COPY: .asciiz "Copy"

.export _FILE_MENU_COPY_KEY
_FILE_MENU_COPY_KEY: .byte $43

.export _FILE_MENU_RENAME
_FILE_MENU_RENAME: .asciiz "Rename"

.export _FILE_MENU_RENAME_KEY
_FILE_MENU_RENAME_KEY: .byte $52

.export _FILE_MENU_MAKE_DIR
_FILE_MENU_MAKE_DIR: .asciiz "Make Directory"

.export _FILE_MENU_MAKE_DIR_KEY
_FILE_MENU_MAKE_DIR_KEY: .byte $4D

.export _FILE_MENU_DELETE
_FILE_MENU_DELETE: .asciiz "Delete"

.export _FILE_MENU_DELETE_KEY
_FILE_MENU_DELETE_KEY: .byte $44

.export _FILE_MENU_FILE_INFO
_FILE_MENU_FILE_INFO: .asciiz "File Information"

.export _FILE_MENU_FILE_INFO_KEY
_FILE_MENU_FILE_INFO_KEY: .byte $46

.export _FILE_MENU_QUIT
_FILE_MENU_QUIT: .asciiz "Quit"

.export _FILE_MENU_QUIT_KEY
_FILE_MENU_QUIT_KEY: .byte $51

.export _FILE_MENU_GO64
_FILE_MENU_GO64: .asciiz "GO64"

.export _FILE_MENU_GO64_KEY
_FILE_MENU_GO64_KEY: .byte $47
