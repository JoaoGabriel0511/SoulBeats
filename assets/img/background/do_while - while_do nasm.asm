;----------------------------------------------------------------------
; Do/While - While/do
; Usage:
;
;   DO 													WHILE CC
;     statements 									statements
;		WHILE CC 										DO
;
;----------------------------------------------------------------------

%macro DO 0
    %ifctx WHILE
        jmp %$cont
	    %$ifend:
	        %pop
	%else
	    %push DO
	    %$ifnend:
	%endif
%endmacro

%macro WHILE 1
	%ifctx DO
		j%-1 %$ifnend
		%pop
	%else
		%push WHILE
		%$cont:
		    j%-1 %$ifend
	%endif
%endmacro

;----------------------------------------------------------------------
; Switch - Case - Default - EndSwitch
; Usage:
;
;   SWITCH expression
;     CASE argument1
;       statements 
;     CASE argumentN
;       statements 
;     DEFAULT 
;       statements
;   ENDSWITCH
;
;----------------------------------------------------------------------

%macro SWITCH 1
	%push SWITCH                    ; Push context
	%assign %$case 1                ; Assign 1 to the nextcase index
	mov eax, dword %1               ; Store argument
%endmacro

%macro CASE 1
	%ifctx SWITCH
	    %$next%$case:
            %assign %$case %$case+1     ; Increment nextcase index value
    		cmp eax, %1
            jne %$next%$case            ; Jump to next case if not equal
    %else
        %error "CASE is not allowed outside a SWITCH block."
	%endif
	
%endmacro

%macro DEFAULT 0
  %ifctx SWITCH                 ; Verify context
    %$next%$case:
  %else 
    %error "DEFAULT is not allowed outside a SWITCH block."
  %endif 
%endmacro

%macro endswitch 0
	%ifctx SWITCH
	    %pop SWITCH             ; Remove context from context stack
    %else
        %error "ENDSWITCH is not allowed outside a SWITCH block."
	%endif
	
%endmacro