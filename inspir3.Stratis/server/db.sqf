#define DB "inspir3.sqlite"

/*
 * Create tables into database if needed 
 */
db_create = {
	diag_log "[db_create] Begin";
    
    private ["_db"];
	
	_db = [DB] call jayarma2lib_fnc_openSql;															//Open SQLite database
	
	diag_log format["[db_create] %1 has been successfully opened", _db];
	
	_ret = [_db, "CREATE TABLE IF NOT EXISTS Player (id INTEGER PRIMARY KEY AUTOINCREMENT,
    												UID VARCHAR(255),
											        pseudo VARCHAR(255),
											        idBase INTEGER)"] call jayarma2lib_fnc_execSql;		//Table Player
	
	diag_log format["[db_create] Table Player: %1", _ret];        
	
	_ret = [_db, "CREATE TABLE IF NOT EXISTS Base (id INTEGER PRIMARY KEY AUTOINCREMENT,
										        x FLOAT,
										        y FLOAT,
										        z FLOAT)"] call jayarma2lib_fnc_execSql;				//Table Base
										        
	diag_log format["[db_create] Table Base: %1", _ret];        
	          
	[_db] call jayarma2lib_fnc_closeSql;																//Close SQLite database
	  
	diag_log "[db_create] End";
};

/*
 * Select one value from database 
 */
db_selectOne = {	    
    private ["_query", "_db", "_ret"];
	
    _query = _this select 0;
    
    diag_log format["[db_selectOne] Begin (%1)", _query];
    
	_db = [DB] call jayarma2lib_fnc_openSql;															//Open SQLite database
		
	_ret = [_db, _query] call jayarma2lib_fnc_execSelectSql;											//Execute query
	                        	
	[_db] call jayarma2lib_fnc_closeSql;																//Close SQLite database
	  
    _ret = _ret select 0;																				//Keep first record
    
    if ((typeName _ret) == "ARRAY") then {
    	_ret = _ret select 0;																			//Keep first value
    };

    diag_log format["[db_selectOne] End (%1)", _ret];
        
    _ret;
};

/*
 * If gamer exists ? 
 */
db_getGamerId = {	    
    private ["_uid", "_ret", "_id"];

	_uid = _this select 0;
    
    diag_log format["[db_getGamerId] Begin (uid: '%1')", _uid];
            	
	_ret = [format["SELECT id FROM Player WHERE UID = '%1'", _uid]] call db_selectOne;
        
    _id = parseNumber _ret;
            
	diag_log format["[db_getGamerId] End (%1)", _id];
        
	_id;      
};

/*
 * Register the gamer 
 */
db_addGamer = {	    
    private ["_uid", "_gamerName", "_query", "_db", "_id"];

	_uid 		= _this select 0;
    _gamerName 	= _this select 1;
    
    diag_log format["[db_addGamer] Begin (uid: '%1', gamerName: '%2')", _uid, _gamerName];
            	
	_db = [DB] call jayarma2lib_fnc_openSql;															//Open SQLite database
			
    _query = format["INSERT INTO Player (UID, Pseudo) VALUES ('%1', '%2')", _uid, _gamerName];
    
    diag_log _query;
    
    [_db, _query] call jayarma2lib_fnc_execSql;															//Execute query

	[_db] call jayarma2lib_fnc_closeSql;																//Close SQLite database
                                                            
    _id = [_uid] call db_getGamerId;	                        	
                
	diag_log format["[db_addGamer] End (%1)", _id];  
    
	_id;  
};

/*
 * Register the gamer's base 
 */
db_setGamerBase = {	    
    private ["_id", "_pos", "_query", "_db"];

	_id 	= _this select 0;
    _pos 	= _this select 1;
    
    diag_log format["[db_setGamerBase] Begin (id: %1, pos: %2)", _id, _pos];
            	
	_db = [DB] call jayarma2lib_fnc_openSql;															//Open SQLite database
			
    _query = format["INSERT INTO Base (id, x, y ,z) VALUES (%1, %2, %3, %4)", _id, _pos select 0, _pos select 1, _pos select 2];
    
    diag_log _query;
    
    [_db, _query] call jayarma2lib_fnc_execSql;															//Execute query

	[_db] call jayarma2lib_fnc_closeSql;																//Close SQLite database

	diag_log format["[db_setGamerBase] End"];  
};

/*
 * If gamer exists ? 
 */
db_getGamerBase = {	    
    private ["_id", "_query", "_ret", "_db", "_pos"];

	_id = _this select 0;
    
    diag_log format["[db_getGamerBase] Begin (id: %1)", _id];
            	
	_query = format["SELECT x,y,z FROM Base WHERE id = %1", _id];
    
    _db = [DB] call jayarma2lib_fnc_openSql;															//Open SQLite database
		
	_ret = [_db, _query] call jayarma2lib_fnc_execSelectSql;											//Execute query
	                        	
	[_db] call jayarma2lib_fnc_closeSql;																//Close SQLite database
	  
    _ret = _ret select 0;																				//Keep first record
    
    _pos = [];
    
    if ((typeName _ret) == "ARRAY") then {
        _pos set [0, _ret select 0];
        _pos set [1, _ret select 1];
        _pos set [2, _ret select 2];
    };
                    
	diag_log format["[db_getGamerBase] End (%1)", _pos];
        
	_pos;      
};
