
_vehicles = _this select 0;

{
    scopeName "loop";
    
    diag_log format["[monitoringVehicle] Process vehicle %1", _x];
                                                                
	_UID 	= getPlayerUID _x;
    _name 	= name _x;
                
    if !(alive _x) then {
        diag_log "[monitoringVehicle] Vehicle is dead";
    	breakOut "loop";
	};    
    
	_driver = driver _x;    
	diag_log format["[monitoringVehicle] Driver: %1", _driver];    
        	            
} forEach _vehicles;
    