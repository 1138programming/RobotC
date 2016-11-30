const short leftButton = 1;
const short centerButton = 2;
const short rightButton = 4;
int autonNumber = 0;

//Wait for Press--------------------------------------------------
void waitForPress()
{
	while(nLCDButtons == 0){}
	wait1Msec(5);
}
//----------------------------------------------------------------

//Wait for Release------------------------------------------------
void waitForRelease()
{
	while(nLCDButtons != 0){}
	wait1Msec(5);
}
void pre_auton()
{
	bLCDBacklight = true;                                    // Turn on LCD Backlight
	string mainBattery, backupBattery;
	clearLCDLine(0);                                            // Clear line 1 (0) of the LCD
	clearLCDLine(1);                                            // Clear line 2 (1) of the LCD

	//Display the Primary Robot battery voltage
	displayLCDString(0, 0, "Primary: ");
	sprintf(mainBattery, "%1.2f%c", nImmediateBatteryLevel/1000.0,'V'); //Build the value to be displayed
	displayNextLCDString(mainBattery);

	//Display the Backup battery voltage
	displayLCDString(1, 0, "Backup: ");
	sprintf(backupBattery, "%1.2f%c", BackupBatteryLevel/1000.0, 'V');    //Build the value to be displayed
	displayNextLCDString(backupBattery);

	//Short delay for the LCD refresh rate
	wait1Msec(2000);

	//Declare count variable to keep track of our choice
	int count = 0;

	//------------- Beginning of User Interface Code ---------------
	//Clear LCD
	clearLCDLine(0);
	clearLCDLine(1);
	//Loop while center button is not pressed
	while(nLCDButtons != centerButton)
	{
		//Switch case that allows the user to choose from 4 different options
		switch(count)
		{
		case 0:
			//Display first choice
			displayLCDCenteredString(0, "3 stars");
			displayLCDCenteredString(1, "<    Enter   >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count = 3;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			else if(nLCDButtons == centerButton)
			{
				autonNumber = 0;
				startTask(autonomous);
			}
			break;
		case 1:
			//Display second choice
			displayLCDCenteredString(0, "Right Cube");
			displayLCDCenteredString(1, "<    Enter   >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			else if(nLCDButtons == centerButton)
			{
				autonNumber = 1;
				startTask(autonomous);
			}
			break;
		case 2:
			//Display third choice
			displayLCDCenteredString(0, "Left Cube");
			displayLCDCenteredString(1, "<    Enter   >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count++;
			}
			else if(nLCDButtons == centerButton)
			{
				autonNumber = 2;
				startTask(autonomous);
			}
			break;
		case 3:
			//Display fourth choice
			displayLCDCenteredString(0, "Encoder1");
			displayLCDCenteredString(1, "<    Enter   >");
			waitForPress();
			//Increment or decrement "count" based on button press
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count = 0;
			}
			else if(nLCDButtons == centerButton)
			{
				autonNumber = 3;
				startTask(autonomous);
			}
			break;
		case 4:
			displayLCDCenteredString(0, "Encoder2");
			displayLCDCenteredString(1, "<    Enter   >");
			waitForPress();
			if(nLCDButtons == leftButton)
			{
				waitForRelease();
				count--;
			}
			else if(nLCDButtons == rightButton)
			{
				waitForRelease();
				count =0;
			}
			else if(nLCDButtons == centerButton)
			{
				autonNumber = 4;
				startTask(autonomous);
			}
		default:
			count = 0;
			break;
		}
	}
}
