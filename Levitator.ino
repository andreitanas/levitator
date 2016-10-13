/*
 Name:		Levitator.ino
 Created:	10/11/2016 8:25:24 PM
 Author:	Andrei
*/

int initialDistance;

// the setup function runs once when you press reset or power the board
void setup() {
	// this pin is used to control coil power through PWM
	pinMode(PIN3, OUTPUT);
	analogWrite(PIN3, 0);

	// these two pins are used to control current direction through the coil
	digitalWrite(PIN1, LOW);
	pinMode(PIN1, OUTPUT);
	digitalWrite(PIN2, HIGH);
	pinMode(PIN2, OUTPUT);

	pinMode(PIN_A0, INPUT);

	// wait for power to stabilize
	delay(100);

	// read initial distance from our sensor to the magnet
	initialDistance = analogRead(PIN_A0);
}

// the loop function runs over and over again until power down or reset
void loop() {
	// wait 1ms (1/1000 of a second) every iteration
	delayMicroseconds(1000);

	// read current distance from sensor to magnet
	int currentDistance = analogRead(PIN_A0);

	// calculate difference between initial and current distance
	int difference = currentDistance - initialDistance;

	if (difference > 0)
	{
		// if the difference is more than initial, set one direction
		digitalWrite(PIN1, HIGH);
		digitalWrite(PIN2, LOW);
	}
	else // (difference <= 0)
	{
		// otherwise, set another direction
		digitalWrite(PIN1, LOW);
		digitalWrite(PIN2, HIGH);

		// then make sure the "difference" value is not negative
		difference = -difference;
	}

	// multiply difference by 2 to get higher amplitude of output signal
	int pwmValue = difference * 4;

	// make sure it does not exceed maximum of 255
	if (pwmValue > 255)
		pwmValue = 255;

	analogWrite(PIN3, pwmValue);
}
