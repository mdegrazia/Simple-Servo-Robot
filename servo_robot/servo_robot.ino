/* Infrared_Read.ino Example sketch for IRLib2 and Circuit Playground Express
   Illustrates how to receive an IR signal, decode it and print
   information about it to the serial monitor.
*/
#include <Adafruit_CircuitPlayground.h>
#include <Servo.h>

#define ADAF_MINI_LEFT_ARROW  0xfd10ef
#define ADAF_MINI_RIGHT_ARROW  0xfd50af
#define ADAF_MINI_UP_ARROW  0xfda05f
#define ADAF_MINI_DOWN_ARROW  0xfdb04f
#define ADAF_MINI_PLAY_PAUSE  0xfd807f
#define ADAF_MINI_ENTER_SAVE  0xfd906f
#define ADAF_MINI_1  0xfd08f7
#define ADAF_MINI_3  0xfd48b7

#define SERVO_OFF 90

Servo leftWheel;
Servo rightWheel;

#if !defined(ARDUINO_SAMD_CIRCUITPLAYGROUND_EXPRESS)
  #error "Infrared support is only for the Circuit Playground Express, it doesn't work with the Classic version"
#endif

void setup() {
  CircuitPlayground.begin();
  Serial.begin(9600);
   
  CircuitPlayground.irReceiver.enableIRIn(); // Start the receiver
  Serial.println("Ready to receive IR signals");
 
  leftWheel.attach(A2); //attaches the servo on pin 9
  rightWheel.attach(A1); //attaches the servo on pin 9

  rightWheel.write(SERVO_OFF);
  leftWheel.write(SERVO_OFF);
}

void loop() {
 // Did we get any infrared signals?
  if (! CircuitPlayground.irReceiver.getResults()) {
    return;
  }

  // Did we get any decodable messages?
  if (! CircuitPlayground.irDecoder.decode()) {
    CircuitPlayground.irReceiver.enableIRIn(); // Restart receiver  
    return;
  }

  // We can print out the message if we want...
  CircuitPlayground.irDecoder.dumpResults(false);

  // Did we get any NEC remote messages?
  if (! CircuitPlayground.irDecoder.protocolNum == NEC) {
    CircuitPlayground.irReceiver.enableIRIn(); // Restart receiver  
    return;
  }

  // What message did we get?
  switch(CircuitPlayground.irDecoder.value) {
  
  //values may need to be adjusted to make tighter/looser turns
  case ADAF_MINI_LEFT_ARROW: 
   Serial.println("Left");
    rightWheel.write(0);
    leftWheel.write(110);
   delay(1000);
   break;
  
  //values may need to be adjusted to make tighter/looser turns
  case ADAF_MINI_RIGHT_ARROW: 
    Serial.println("Right");
    rightWheel.write(60);
    leftWheel.write(180);
    delay(1000);
    break;

case ADAF_MINI_1:
 Serial.println("Spin Left");
    rightWheel.write(45);
    leftWheel.write(45);
    delay(1000);
    break;
 
 case ADAF_MINI_3:
 Serial.println("Sprin Right");
    rightWheel.write(135);
    leftWheel.write(135);
    delay(1000);
    break;
  
 case ADAF_MINI_UP_ARROW: 
    Serial.println("Forward");
    leftWheel.write(180);
    rightWheel.write(0);
     
    break;
  case ADAF_MINI_DOWN_ARROW: 
    Serial.println("backward");
    leftWheel.write(0);
    rightWheel.write(180);
    break;
  case ADAF_MINI_PLAY_PAUSE:
    leftWheel.write(90);
    rightWheel.write(90);
    
  }
  //Restart receiver
  CircuitPlayground.irReceiver.enableIRIn();      


}



