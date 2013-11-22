#include "define.sqf"

class DialogMain {
	
	idd = DIALOG_main;
	movingEnable = false;
	enableSimulation = true;      // dont freeze the game
	onLoad = "[0] execVM 'dialog\DialogMain.sqf'";

	class controlsBackground { 
		// define controls here
	};
	
	class objects { 
		// define controls here
	};
	
	class controls { 	
	
		////////////////////////////////////////////////////////
		// GUI EDITOR OUTPUT START (by Redge, v1.063, #Fabipo)
		////////////////////////////////////////////////////////

		class IGUIBack_2200: IGUIBack
		{
			idc = 2200;
			x = 1 * GUI_GRID_W + GUI_GRID_X;
			y = 1 * GUI_GRID_H + GUI_GRID_Y;
			w = 16 * GUI_GRID_W;
			h = 18.5 * GUI_GRID_H;
		};

		class RscButton_1600: RscButton
		{
			idc = BUTTON_setHomeBase;
			text = "Set your home base here"; //--- ToDo: Localize;
			x = 2.5 * GUI_GRID_W + GUI_GRID_X;
			y = 2 * GUI_GRID_H + GUI_GRID_Y;
			w = 13 * GUI_GRID_W;
			h = 2.5 * GUI_GRID_H;

			onButtonClick = "call setHomeBase";
			action = "closeDialog 0";
		};

		class RscButtonMenuOK_2600: RscButton
		{
			idc = 2600;
			text = "Close"; //--- ToDo: Localize;
			x = 13 * GUI_GRID_W + GUI_GRID_X;
			y = 18 * GUI_GRID_H + GUI_GRID_Y;
			w = 3.5 * GUI_GRID_W;
			h = 1 * GUI_GRID_H;

			action = "closeDialog 0";
		};

		////////////////////////////////////////////////////////
		// GUI EDITOR OUTPUT END
		////////////////////////////////////////////////////////


				
	};
};

/* #Fabipo
$[
	1.063,
	["DIalogMain",[[0,0,1,1],0.025,0.04,"GUI_GRID"],0,0,0],
	[1600,"",[2,"Set your home base here",["2.5 * GUI_GRID_W + GUI_GRID_X","2 * GUI_GRID_H + GUI_GRID_Y","13 * GUI_GRID_W","2.5 * GUI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],[]],
	[2200,"",[2,"",["1 * GUI_GRID_W + GUI_GRID_X","1 * GUI_GRID_H + GUI_GRID_Y","16 * GUI_GRID_W","18.5 * GUI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],[]],
	[2600,"",[2,"Close",["13 * GUI_GRID_W + GUI_GRID_X","18 * GUI_GRID_H + GUI_GRID_Y","3.5 * GUI_GRID_W","1 * GUI_GRID_H"],[-1,-1,-1,-1],[-1,-1,-1,-1],[-1,-1,-1,-1],"","-1"],[]]
]
*/

