
_ia = _this select 0;

{
    scopeName "loop";
    
    diag_log format["[monitoringIA] Process IA %1", _x];
                                                                
	_UID 	= getPlayerUID _x;
    _name 	= name _x;
            
    if !(alive _x) then {
        diag_log "[monitoringIA] IA is dead";
    	breakOut "loop";
	};    
        	            
} forEach _ia;
    