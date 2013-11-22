/*
 * Set the home base for player 
 */
setHomeBase = {
	
	private ["_pos", "_ret"];
	
	_pos = position player;
		
	//{ [format["Data: %1", _x]] call console_tchat } forEach _pos;
	
	createMarkerLocal [MARKER_homeBase, _pos];
		
	MARKER_homeBase setMarkerShapeLocal "ELLIPSE";
	MARKER_homeBase setMarkerColorLocal "ColorYellow";
	MARKER_homeBase setMarkerBrushLocal "DiagGrid";
	MARKER_homeBase setMarkerSizeLocal [150,150];
	MARKER_homeBase setMarkerTextLocal MARKER_homeBase;
		
	player setVariable ['HOME_BASE', _pos];
          
	["Your home base is now here."] call console_tchat;
    
	//ret = [db, format["INSERT INTO Base (x, y, z) VALUES (%1,%2,%3);", _pos select 0, _pos select 1, _pos select 2]] call jayarma2lib_fnc_execSql;	
	//[format["Ret: %1", ret]] call console_tchat;
	
	/*    
	if (ret) then {
		["Your home base is now here."] call console_tchat;		
	}else{
		["[Error] When saving your base in DB"] call console_tchat;	
	};
	*/

	/*
	_trg = createTrigger["EmptyDetector", _pos];
	_trg setTriggerArea[75, 75, 0, false];
	_trg setTriggerActivation["ANY", "PRESENT", true];
	_trg setTriggerStatements["this", "player setVariable ['TERRITORY_OCCUPATION', '%1', true]", "['territoire libre'] call console_tchat"];
	*/
     
};

/*
 * Home base already exists ? 
 */
homeBaseAlreadyExists = {
	
    private ["_color", "_ret"];
   
    _color = getMarkerColor MARKER_homeBase;
    
    _ret = (_color != "");
    
	_ret;	
};
