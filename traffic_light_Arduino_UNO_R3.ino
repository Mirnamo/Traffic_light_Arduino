long stateStartTime = 0;
int RED_LED = 11;
int GREEN_LED = 13;
int YELLOW_LED = 12;

enum State { RED_STATE, GREEN_STATE, YELLOW_STATE };
State current_state = RED_STATE;

// pedestrian states
enum Pedestrian_state { STOP, PASS };
Pedestrian_state human = STOP;

// to see if button is pressed or no
bool request_pass = false;
int button_pressed = 10;

// pedestrian LEDs
int pass_light = 8;
int stop_light = 9;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(button_pressed, INPUT_PULLUP);
  pinMode(stop_light, OUTPUT);
  pinMode(pass_light, OUTPUT);
  current_state = RED_STATE;
  stateStartTime = millis();
}

void loop() {
  // check button
  if (digitalRead(button_pressed) == LOW) {
    request_pass = true;
  }

  if(request_pass){
    trafficWithPedestrian();
  }
  else{
    traffic();
  }
}

void traffic(){
  switch(current_state){
    case RED_STATE:
      digitalWrite(RED_LED, HIGH);
      digitalWrite(stop_light, HIGH);
      if (millis() - stateStartTime > 5000){
        digitalWrite(RED_LED, LOW);
        current_state = GREEN_STATE;
        stateStartTime = millis();
      }
      break;

    case GREEN_STATE:
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(stop_light, HIGH);
      if (millis() - stateStartTime > 5000){
        digitalWrite(GREEN_LED, LOW);
        current_state = YELLOW_STATE;
        stateStartTime = millis();
      }
      break;

    case YELLOW_STATE:
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(stop_light, HIGH);
      if(millis() - stateStartTime > 2000){
        digitalWrite(YELLOW_LED, LOW);
        current_state = RED_STATE;
        stateStartTime = millis();
      }
      break;
  }
}

void trafficWithPedestrian() {
  switch(human) {

    case PASS: 
      // pass for 10 s
      digitalWrite(RED_LED, HIGH);
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(pass_light, HIGH);
      digitalWrite(stop_light, LOW);

      if (millis() - stateStartTime > 10000) {
        digitalWrite(pass_light, LOW);
        human = STOP;
        stateStartTime = millis();
      }
      break;

    case STOP:
      // stop for 5s
      if ((millis() / 500) % 2 == 0) {
        digitalWrite(stop_light, HIGH);
      } else {
        digitalWrite(stop_light, LOW);
      }

      if (millis() - stateStartTime > 5000) {
        digitalWrite(stop_light, HIGH);   
        request_pass = false;             
        human = PASS;                     
        current_state = RED_STATE;        
        stateStartTime = millis();
      }
      break;
  }
}