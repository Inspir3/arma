/*
 * Listen to keyboard 
 */
keyboardHandler = {
	private ["_key"];
	
	_key = _this select 1;
	
	switch _key do {           
		
		case 41: {
			
			if !(dialog) then {							//Dialog not already displayed ?
				createDialog "DialogMain";
				
				waitUntil { !dialog }; 					//Wait ESC key or close button
			};
	    };
	    
	    default {
	    		//[format["Touche %1 appuyée", _key]] call console_tchat;
			}
	};
};                         
