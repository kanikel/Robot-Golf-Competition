#pragma config(Sensor, in1,    lineFollowerRIGHT,   sensorLineFollower)
#pragma config(Sensor, in2,    lineFollowerCENTER,  sensorLineFollower)
#pragma config(Sensor, in3,    lineFollowerLEFT,    sensorLineFollower)
#pragma config(Motor,  port2,           rightMotor,    tmotorNormal, openLoop, reversed)
#pragma config(Motor,  port3,           leftMotor,     tmotorNormal, openLoop)

task main()
{
	int threshold = 1500; // Threshold reading to indicate direction
	int turnThreshold = 2000; // Threshold reading to indicate direction
	int slowDownCount = 30; // Time after which to slow down
	int slowDownTime = 0; // Time after which to slow down
	int fastSpeed = 15; // Motor speed before slow down
	int slowSpeed = fastSpeed; // Motor speed after slow down
	//int turnSpeed = 15;//100; // Turn Speed
	int smallerspeed = 15;
	int largerspeed = 30;

	while(true) {
		int speed = fastSpeed; // motor speed;
		if (slowDownCount < slowDownTime){
			speed = slowSpeed;
		}
		if(SensorValue(lineFollowerCENTER) < threshold) {
			motor[leftMotor] = speed; //Full power is 127
			motor[rightMotor] = speed;
			writeDebugStreamLine("CENTER MODE");
		}
		else if(SensorValue(lineFollowerLEFT) < turnThreshold) {
			motor[leftMotor] = smallerspeed;
			motor[rightMotor] = largerspeed;
			writeDebugStreamLine("LEFT MODE");
		}
		else if(SensorValue(lineFollowerRIGHT) < turnThreshold) {
			motor[leftMotor] = largerspeed;
			motor[rightMotor] = smallerspeed;
			writeDebugStreamLine("RIGHT MODE");
		}
		writeDebugStreamLine("Right Line Follower: %i", SensorValue(lineFollowerRIGHT));
		writeDebugStreamLine("Center Line Follower: %i", SensorValue(lineFollowerCENTER));
		writeDebugStreamLine("Left Line Follower: %i", SensorValue(lineFollowerLEFT));

		wait1Msec(500);
		slowDownCount++;
		
	}
}