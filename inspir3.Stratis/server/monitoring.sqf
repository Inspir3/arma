loadFile "js\player.js" call JS_fnc_exec;

while{true} do {

	sleep 5;
	["[monitoring] In progress..."] call console_tchat;

	//--------------------------------------
    //Monitoring soldiers (human and ia)
    //--------------------------------------
	_players = [];
    _ia = [];
    
    _players_i = 0;
    _ia_i = 0;
    
	{
        _UID = getPlayerUID _x;
        _name 	= name _x;
        
		diag_log format["[monitoring] [allUnits] %1 (UID: %2, Name: %3)", _x, _UID, _name];
        
        if (_UID != "_SP_AI_") then { 
        	_players set [_players_i, _x];
            _players_i = _players_i + 1;
		}else{
        	_ia set [_ia_i, _x];
            _ia_i = _ia_i + 1;                        
		};
        
	}forEach allUnits;
    
	//--------------------------------------
    //Monitoring vehicles
    //--------------------------------------
    _vehicles = [];
    _i = 0;
    
	{        
        _UID = getPlayerUID _x;
        _name 	= name _x;
        
		diag_log format["[monitoring] [vehicles] %1 (UID: %2, Name: %3)", _x, _UID, _name];
    	        
		_vehicles set [_i, _x];
		_i = _i + 1;
                
	}forEach vehicles;

    diag_log format["[monitoring] %1 players (dead or not) found", _players_i];
    diag_log format["[monitoring] %1 ia (dead or not) found", _ia_i];
    diag_log format["[monitoring] %1 vehicles found", _i];
        
    _handle = [_players] execVM "server\monitoringPlayer.sqf";											//On lance les scripts un à la fois pour pas qu'ils accèdent en même temps à SQLite...
	waitUntil {scriptDone _handle};

    _handle = [_ia] execVM "server\monitoringIA.sqf";
    waitUntil {scriptDone _handle};
    
    _handle = [_vehicles] execVM "server\monitoringVehicle.sqf";
    waitUntil {scriptDone _handle};
    
};//while{true}