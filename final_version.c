#pragma config(Sensor, in1,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in2,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)

task main()
{
	int turnThresholdRight = 400;
	int turnThresholdLeft = 200;
	int forwardSpeed = 20;
	int reverseSpeed = -20;
	int leftMotorBoost = 5;

	int prevLeft = 0;
	int prevRight = 0;

	int prevLeftMotor;
	int prevRightMotor;

	while(true) {
		int currLeft = SensorValue(lineFollowerLEFT);
		int currRight = SensorValue(lineFollowerRIGHT);
		int currCenter = SensorValue(lineFollowerCENTER);
		if(prevLeft - currLeft > turnThresholdLeft){
			motor[leftMotor] = reverseSpeed - leftMotorBoost;
			motor[rightMotor] = forwardSpeed;
			prevLeftMotor = reverseSpeed - leftMotorBoost;
	    prevRightMotor = forwardSpeed;
			writeDebugStreamLine("Turn left");
		}
		else if(prevRight - currRight > turnThresholdRight){
			motor[leftMotor] = forwardSpeed + leftMotorBoost;
			motor[rightMotor] = reverseSpeed;
			prevLeftMotor = forwardSpeed + leftMotorBoost;
	    prevRightMotor = reverseSpeed;
			writeDebugStreamLine("Turn right");
		}
		else if(currCenter < 1900){
			motor[leftMotor] = forwardSpeed + leftMotorBoost; //Full power is 127
			motor[rightMotor] = forwardSpeed;
			prevLeftMotor = forwardSpeed + leftMotorBoost;
	    prevRightMotor = forwardSpeed;
			writeDebugStreamLine("Go straight");
			prevLeft = currLeft;
 	    prevRight = currRight;
		}
		else{
			motor[leftMotor] = prevLeftMotor;
	    motor[leftMotor] = prevRightMotor;
		}


		writeDebugStreamLine("Right Line Follower: %i", SensorValue(lineFollowerRIGHT));
		writeDebugStreamLine("Center Line Follower: %i", SensorValue(lineFollowerCENTER));
		writeDebugStreamLine("Left Line Follower: %i", SensorValue(lineFollowerLEFT));


		wait1Msec(250);

	}
}
