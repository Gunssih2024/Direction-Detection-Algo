const int mic1Pin = A1;
const int mic2Pin = A2;
const int mic3Pin = A3;

int amb_mic1 = 0;
int amb_mic2 = 0;
int amb_mic3 = 0;

const int threshold_mic1 = 2;
const int threshold_mic2 = 10;
const int threshold_mic3 = 5;

const float speedOfSound = 343.0;

const float micDistance = 0.1;

double timeMic1 = 0;
double timeMic2 = 0;
double timeMic3 = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("----------------------------------------------------");
  pinMode(mic1Pin, INPUT);
  pinMode(mic2Pin, INPUT);
  pinMode(mic3Pin, INPUT);

  pinMode(LED_BUILTIN, OUTPUT);

  for (int i=0; i<50; i++){
	  amb_mic1 += analogRead(mic1Pin);
	  amb_mic2 += analogRead(mic2Pin);
	  amb_mic3 += analogRead(mic3Pin);
  }
  amb_mic1 /= 50;
  amb_mic2 /= 50;
  amb_mic3 /= 50;

  Serial.print("Amb values: ");
  Serial.print(amb_mic1);
  Serial.print(", ");
  Serial.print(amb_mic2);
  Serial.print(", ");
  Serial.print(amb_mic3);
  Serial.println();
}

void loop() {
  int mic1Value = analogRead(mic1Pin);
  int mic2Value = analogRead(mic2Pin);
  int mic3Value = analogRead(mic3Pin);

  unsigned long currentTime = micros();

  if (mic1Value > threshold_mic1 + amb_mic1 && timeMic1 == 0) {
    timeMic1 = currentTime;
    // Serial.print("Mic1:");
    // Serial.println(timeMic1);
  }
  if (mic2Value > threshold_mic2 + amb_mic2 && timeMic2 == 0) {
    timeMic2 = currentTime;
    // Serial.print("Mic2:");
    // Serial.println(timeMic2);
  }
  if (mic3Value > threshold_mic3 + amb_mic3 && timeMic3 == 0) {
    timeMic3 = currentTime;
    // Serial.print("Mic3:");
    // Serial.println(timeMic3);
  }

  if (timeMic1 > 0 && timeMic2 > 0 && timeMic3 > 0) {
       
    double speedOfSound = 343.0;

    double t21 = (timeMic2 - timeMic1) / 1000000.0;
    double t31 = (timeMic3 - timeMic1) / 1000000.0;

    // Convert to distances
    double d21 = speedOfSound * t21;
    double d31 = speedOfSound * t31;

    // Positions of microphones in the equilateral triangle
    // Mic1: (0, 0)
    // Mic2: (micDistance, 0)
    // Mic3: (micDistance / 2, sqrt(3) / 2 * micDistance)
    // Serial.print("t21: "); Serial.print(t21); Serial.print(" s, ");
    // Serial.print("t31: "); Serial.print(t31); Serial.println(" s");
    
    // Serial.print("d21: "); Serial.print(d21); Serial.print(" m, ");
    // Serial.print("d31: "); Serial.print(d31); Serial.println(" m");
    float angleRadians = atan2(d31, d21);
    float angleDegrees = angleRadians * (180.0 / PI);

    Serial.print("Angle of sound source: ");
    Serial.print(angleDegrees);
    Serial.println(" degrees");

    timeMic1 = 0;
    timeMic2 = 0;
    timeMic3 = 0;
  }
}
