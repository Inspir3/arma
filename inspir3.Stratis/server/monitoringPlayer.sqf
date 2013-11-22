_players = _this select 0;

{
    scopeName "loop";
    
    diag_log format["[monitoringPlayer] Process player %1", _x];
                                                                
	_UID 	= getPlayerUID _x;
    _name 	= name _x;
        
    if !(alive _x) then {
        diag_log "Player is dead";
    	breakOut "loop";
	};    
                            
    _id = format["player_exists('%1')", _UID] call JS_fnc_exec;
    
    if ( _id > 0 ) then {										//Is gamer is registered ?
		
        diag_log format["Process player '%1'", _name];															//Yes

        _pos = _x getVariable 'HOME_BASE';
            
		if isnil ("_pos") then {
			diag_log "No base to save";                
        }else{
            [_id, _pos] call db_setGamerBase;            
		};             
        
        /*
        _var = _x getVariable ['TERRITORY_OCCUPATION', ''];

        if (_var != "") then {
			diag_log "[monitoring] Un territoire occupé !"; 
		}else{
			diag_log "[monitoring] Aucun territoire occupé";
        };
		*/                                                                                           
                                                                                                                                                           	                                                    	               
    }else{																										//No
    
		_id = [_UID] call db_getGamerId;																		//Is gamer in database ?
    
        if ( _id > 0 ) then {
			[format["Welcome back %1 ! We are loading your profile...", _name]] call console_both;				//Yes
            
        	_pos = [_id] call db_getGamerBase;   
            
            if ( (count _pos) > 0 ) then {
                [format["Your base has been loaded (%1)", _pos]] call console_both;
			}else{
				["No base found !"] call console_both;
			};   
        }else{
            [format["Welcome %1, we are creating your profile...", _name]] call console_both;					//No, add gamer to database
             
			_id = [_UID, _name] call db_addGamer;                                        	  
        };
        
        format["player_add(%1, '%2', '%3')", _id, _UID, _name] call JS_fnc_exec;							//... register gamer
    };
        	            
} forEach _players;
    